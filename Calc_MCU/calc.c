/*
 * calc.c
 *
 *  Created on: Apr 19, 2020
 *      Author: abdel_000
 */

#include "calc.h"
#include "MCAL/UART/UART_interface.h"
#include "HAL/KEYPAD/KEYPAD_interface.h"
#include "MCAL/TMR1/TMR1_interface.h"
#include "HAL/LCD/LCD_interface.h"


u8 input=0;														//This is the user input on the keypad (digit or operation).
u8 inputsCounter=0;												//This variable counts the number of inputs entered by the user to shift the LCD if the number is more than 16 (maximum number of characters that can be displayed on the LCD at a time).
u32 operandHolder=0;											//Variable that holds the number entered from the user.
u32 decimalHolder=0;											//Variable the holds the decimal part of the number entered from the user if any.
u32 fractionalCounter=1;										//Variable the counts the numbers entered after the decimal point (fractional numbers).
u8 operandsCounter=0;											//Counter that counts the number of operands (full operands not only one digit, i.e. input until an operation is entered) entered in the array.
f32 operandsHolder[MAX_OPERANDS]={0.0};							//Array that holds the operands entered from the user.
u8 operationsCounter=0;											//Counter that counts the number of operations entered in the array.
u8 operationsHolder[MAX_OPERATIONS]={0}; 						//Array that holds the operations entered from the user (+,-,*,/), The extra 1 is for the '=' operation.
f32 result=0;													//Holds the result of the operation.
u8 endIndicatorFlag=0;											//States if the user finished entering the whole operation.
u8 clearLCDFlag=0;												//Allows the screen to be cleared after entering a new number after an operation is finished.
u8 sequenceCorrectFlag=0;										//If the input sequence is right this flag is set; for example a correct sequence is 1+2=, a wrong sequence is 1+x2= or +2=.
u8 wrongInputCounter=0;											//If the user entered a wrong input this flag is set; for example: two operations (except minus sign because it can act as a negative sign) after each other.
u8 negativeNumberFlag=0;										//If the input number is negative this flag is set.
u8 negativeSignPosition[MAX_OPERATIONS]={0};					//Array that its elements is set if there is a negative sign in the corresponding position (if there is a negative sign on the 23rd input then negativeSignPosition[23]=1).
u8 decimalNumberFlag=0;											//If the input number is decimal this flag is set.
u8 decimalPointPosition[MAX_OPERATIONS]={0};					//Array that its elements is set if there is a decimal point in the corresponding position (if there is a decimal point on the 23rd input then decimalPointPosition[23]=1).
u8 wrongInputPosition[MAX_OPERATIONS]={0};						//Array that its elements is set if there is a wrong input (for example two operations after each other: ++) in the corresponding position.

void reset_calculator(void){									//This function resets the calculator (all its variables, without clearing the LCD).
	for(u8 i=0;i<=operationsCounter;i++){						//Reset the arrays.
		operandsHolder[i]=0;
		operationsHolder[i]=0;
	}
	for(u8 i=0;i<=inputsCounter;i++){
		negativeSignPosition[i]=0;
		wrongInputPosition[i]=0;
		decimalPointPosition[i]=0;
	}
	operandHolder=0;
	decimalHolder=0;
	fractionalCounter=1;
	operandsCounter=0;
	operationsCounter=0;
	inputsCounter=0;
	input=0;
	result=0;
	endIndicatorFlag=0;
	sequenceCorrectFlag=0;
	wrongInputCounter=0;
	negativeNumberFlag=0;
	decimalNumberFlag=0;
}

void clear_LCD(void){
	LCD_SendCommand(LCD_COM_CLEAR);								//clear the LCD.
	LCD_SendCommand(LCD_COM_DISPLAY_ON_CURSOR_BLINK);
	UART_SendChar_Polling('C');
	UART_SendChar_Polling('B');
}

void error_report(u8 limit_exceed_string[]){					//When the input exceeds either the limit of the LCD or the limit of the holding variable, this error print a "limit exceed" message on the LCD.
	LCD_SendCommand(LCD_COM_HOME);
	LCD_SendCommand(LCD_COM_SET_CURSOR_SECOND_LINE);
	LCD_WriteString(limit_exceed_string);
	UART_SendChar_Polling('H');
	UART_SendChar_Polling('S');
	if(limit_exceed_string=="LCD Limit Exceed"){
		UART_SendChar_Polling('Q');
	}
	else if(limit_exceed_string=="VariableOverflow"){
		UART_SendChar_Polling('W');
	}
	else {
		UART_SendChar_Polling('E');
	}
}

//Name: "Inputs store and display" part. Function: It handles storing all the inputs from the user into two arrays; operansdHolder and operationsHolder.
//Also clears the LCD if AC button is pressed for a long time, and deletes the last entered character if it is pressed for a short time.
//It also handles some error that may happen by wrong sequence of inputs or out of variable and LCD limits.
void inputs_store_and_display(void){
	while(!endIndicatorFlag){												//!endIndicatorFlag states that the user did not finish entering the whole operation (didn't press =) .
		while(!input || input==255){										//This condition checks if nothing is entered yet.
			input = KEYPAD_GetPressedKey();									//If nothing is entered keep checking on the keypad.
		}
		if(clearLCDFlag){													//This condition clears the LCD if an operation is finished (the result or an error is displayed) then a new number is entered (without pressing the AC button).
																			//Note: after finishing the operation the endIndicatorFlag is reset again.
			clear_LCD();
			clearLCDFlag=0;
		}
		//Name: "Reset Calculator" part. Function: It handles the long press on the AC button, it resets the calculator and clears the LCD no matter what is going on (has the highest priority).
		if(input=='A'){
			reset_calculator();
			clear_LCD();
		}

		//Name: "Input digit or decimal point" part. Function: It handles forming the whole number from the digits entered by the user, also handles entering a decimal point and recognizing the number as a decimal number. It is divided to two partitions.
		//Name: "Input digit" partition.
		else if(input>=48 && input <=57){					//Checks if the input is a number (0 to 9).
			sequenceCorrectFlag=1;
				//If the input sequence is right this flag is set; for example a correct sequence is 1+2=, a wrong sequence is 1+x2= or +2=.
				//sequenceCorrectFlag is set when an operand is entered and is reset when an operation is entered. Its kept as it is if a decimal point or a negative sign is entered. Here is an example to clarify it.
				//initially SCF is 0, so if you press = without entering anything it gives you syntax error. Entering a digit (2 for example) then SCF is 1, now there are three cases; entering another digit: in which case SCF keeps its value and no error.
				//Second case is entering an operation (+ for example): in which case SCF changed to 0. From now there are two cases: entering a number so SCF changes to 1 and operation is correct, or entering another operation and operation gives an error because of two occurunces of SCF = 0 successively.
				//Third case is entering an equal (=): in which case SCF is checked and if equal zero an error counter incremented by 1 and an error would be displayed on the LCD (if not deleted).

			inputsCounter++;												//This counter counts all the inputs entered by the user (its also used as an index to arrays as it acts as an indicator to the position of the inputs).

			LCD_WriteChar(input);											//print and send the input digit.
			UART_SendChar_Polling(input);

			if((operandHolder>=100000000 && !decimalNumberFlag) || decimalHolder>=100000000){		//This condition checks if the user input exceeds the maximum value that u32 can hold, if so prints "Limit Reached" and then resets the calculator.
				error_report("VariableOverflow");
				clearLCDFlag=1;												//clearLCDFlag clear the LCD on a new number entrance (after the operation is finished and represented on the LCD, the calculator is reset but the LCD is not cleared, if a new number is entered the LCD is cleared).
				reset_calculator();											//This method resets input=0 (this is a null character), so doesn't matter if i print it on LCD at the end of the method.
			}
			else {
				if(inputsCounter>15){										//If the input count is more than 16 (which is the maximum that my LCD can display at a time), shift the display to the left.
					LCD_SendCommand(LCD_COM_DISPLAY_SHIFT_LEFT);
					UART_SendChar_Polling('L');
				}
				if(!decimalNumberFlag){
					operandHolder=operandHolder*10+(u32)(input-48);			//Forming the integer part of the number (the newest digit is the least significant digit).
				}
				else {														//If decimalNumberFlag=1, this means that a decimal point was entered before, so the input is a fractional number.
					decimalHolder=decimalHolder*10+(u32)(input-48);			//Forming the fractional part of the number (the newest digit is the least significant digit).
					fractionalCounter*=10;									//Counts the fractional part of the number in tens, so that when we can divide the decimalHolder by this count and add it to the operandHolder to form the number the user intended.
				}
				if(inputsCounter>=40){										//This condition is for if the user tried to enter another digit after the limit of the LCD (40), if so prints "Limit reached and then resets the calculator.
					error_report("LCD Limit Exceed");
					clearLCDFlag=1;											//clearLCDFlag clear the LCD on a new number entrance (after the operation is finished and represented on the LCD, the calculator is reset but the LCD is not cleared, if a new number is entered the LCD is cleared).
					reset_calculator();										//This method resets input=0 (this is a null character), so doesn't matter if i print it on LCD at the end of the method.
				}
			}
		}
		//Name: "Input decimal point" partition.
		else if(input=='D'){												//Checks if the input is a decimal point. 'D' in the keypad driver resembles the '.'.
			sequenceCorrectFlag=1;
			inputsCounter++;

			LCD_WriteChar('.');												//print and send the input digit.
			UART_SendChar_Polling('.');

			if(!decimalNumberFlag){											//If the decimalNumberFlag=0 then there has been no decimal point entered before in this number.
				decimalNumberFlag=1;
			}
			else {															//If decimalNumberFlag=1 already then a decimal point has been entered before, hence increase the wrong input counter and put its position (inputsCounter) in array.
				wrongInputCounter++;
				wrongInputPosition[inputsCounter]=1;
			}
			decimalPointPosition[inputsCounter]=1;							//Add this decimal's point position to the decimal point array.

			if(inputsCounter>=40){											//This condition is for if the user tried to enter another digit after the limit of the LCD (40), if so prints "Limit reached and then resets the calculator.
				error_report("LCD Limit Exceed");
				clearLCDFlag=1;												//clearLCDFlag clear the LCD on a new number entrance (after the operation is finished and represented on the LCD, the calculator is reset but the LCD is not cleared, if a new number is entered the LCD is cleared).
				reset_calculator();											//This method resets input=0 (this is a null character), so doesn't matter if i print it on LCD at the end of the method.
			}
			else if(inputsCounter>15){										//If the input count is more than 16 (which is the maximum that my LCD can display at a time), shift the display to the left.
				LCD_SendCommand(LCD_COM_DISPLAY_SHIFT_LEFT);
				UART_SendChar_Polling('L');
			}
		}
		//Name: "Input operation" part. Function: It handles entering an operation (+,x,/) excluding subtraction.
		else if((input=='+'||input=='x'||input=='/')){						//Checks if the input is an operation.
			inputsCounter++;

			operandsHolder[operandsCounter]=(f32)operandHolder;				//After entering an operation, the number held in operandHolder (which is completed by now because an operation is entered) variable should be saved in the operandsHolder array.

			if(decimalNumberFlag){											//If decimalNumberFlag=1 then the number has a fractional part, hence update the saved value in the operandsHolder array by adding the fractional part stored in decimalHolder to it.
				operandsHolder[operandsCounter]+=((f32)decimalHolder/fractionalCounter);		//The importance of fractionalCounter is shown here.
				decimalNumberFlag=0;
			}

			if(negativeNumberFlag){											//If negativeNumberFlag=1 then the number is negative, hence update the saved value in the operandsHolder array.
				operandsHolder[operandsCounter]=(f32)0-operandsHolder[operandsCounter];			//0-operandHolder to get the negative number of the operandHolder as the user entered a negative sign.
				negativeNumberFlag=0;
			}

			operandHolder=0;												//reset everything related to the "input digit or decimal point" part.
			decimalHolder=0;
			fractionalCounter=1;
			operandsCounter++;
			operationsHolder[operationsCounter]=input;						//Save the new operand in the operationsHolder array.
			operationsCounter++;

			if(!sequenceCorrectFlag){										//If the sequence is wrong (last thing entered is an operation).
				wrongInputCounter++;
				wrongInputPosition[inputsCounter]=1;
			}
			else {
				sequenceCorrectFlag=0;										//To prevent entering two operations (except for minus) after each other.
			}

			if(inputsCounter>=40){											//This condition is for if the user tried to enter another operation after the limit of the LCD (40), if so prints "Limit reached and then resets the calculator.
				error_report("LCD Limit Exceed");
				clearLCDFlag=1;												//clearLCDFlag clear the LCD on a new number entrance (after the operation is finished and represented on the LCD, the calculator is reset but the LCD is not cleared, if a new number is entered the LCD is cleared).
				reset_calculator();											//This method resets input=0 (this is a null character), so doesn't matter if i print it on LCD at the end of the method.
			}
			else if(inputsCounter>15){										//If the input count is more than 16 (which is the maximum that my LCD can display at a time), shift the display to the left.
				LCD_SendCommand(LCD_COM_DISPLAY_SHIFT_LEFT);
				UART_SendChar_Polling('L');
			}

			LCD_WriteChar(input);
			UART_SendChar_Polling(input);
		}
		//Name: "Input minus sign" part. Function: It handles entering a minus sign (-), to either consider it as a negative for the number or an operation. It is divided to two partitions.
		else if(input=='-'){												//Checks if the input is a minus sign.
			inputsCounter++;

			//Name: "Input negative sign" partition.
			if(!sequenceCorrectFlag){										//This condition checks if the minus sign is for a negative number.
				negativeNumberFlag^=1;
				negativeSignPosition[inputsCounter]=1;
			}
			//Name: "Input subtraction sign" partition.
			else {															//This condition checks if the minus sign is for subtraction operation.
				sequenceCorrectFlag=0;										//If it is a subtraction, then do the same process as in addition, mult and division.

				operandsHolder[operandsCounter]=(f32)operandHolder;

				if(decimalNumberFlag){
					operandsHolder[operandsCounter]+=((f32)decimalHolder/fractionalCounter);
					decimalNumberFlag=0;
				}

				if(negativeNumberFlag){
					operandsHolder[operandsCounter]=(f32)0-operandsHolder[operandsCounter];		//0-operandHolder to get the negative number of the operandHolder as the user entered a negative sign.
					negativeNumberFlag=0;
				}

				operandHolder=0;
				decimalHolder=0;
				fractionalCounter=1;
				operandsCounter++;
				operationsHolder[operationsCounter]=input;
				operationsCounter++;
			}

			if(inputsCounter>=40){											//This condition is for if the user tried to enter another operation after the limit of the LCD (40), if so prints "Limit reached and then resets the calculator.
				error_report("LCD Limit Exceed");
				clearLCDFlag=1;												//clearLCDFlag clear the LCD on a new number entrance (after the operation is finished and represented on the LCD, the calculator is reset but the LCD is not cleared, if a new number is entered the LCD is cleared).
				reset_calculator();											//This method resets input=0 (this is a null character), so doesn't matter if i print it on LCD at the end of the method.
			}
			else if(inputsCounter>15){										//If the input count is more than 16 (which is the maximum that my LCD can display at a time), shift the display to the left.
				LCD_SendCommand(LCD_COM_DISPLAY_SHIFT_LEFT);
				UART_SendChar_Polling('L');
			}
			LCD_WriteChar(input);
			UART_SendChar_Polling(input);
		}
		//Name: "Input equal sign" part. Function: It handles entering an equal sign '=', and proceed to the next part of the code "Calculating the result".
		else if(input=='='){
			inputsCounter++;

			operandsHolder[operandsCounter]=(f32)operandHolder;				//After entering =, the number held in operandHolder (which is completed by now because an operation is entered) variable should be saved in the operandsHolder array.

			if(decimalNumberFlag){											//If decimalNumberFlag=1 then the number has a fractional part, hence update the saved value in the operandsHolder array by adding the fractional part stored in decimalHolder to it.
				operandsHolder[operandsCounter]+=((f32)decimalHolder/fractionalCounter);
				decimalNumberFlag=0;
			}

			if(negativeNumberFlag){											//If negativeNumberFlag=1 then the number is negative, hence update the saved value in the operandsHolder array.
				operandsHolder[operandsCounter]=(f32)0-operandsHolder[operandsCounter];		//0-operandHolder to get the negative number of the operandHolder as the user entered a negative sign.
				negativeNumberFlag=0;
			}

			operandHolder=0;												//reset everything related to the "input digit or decimal point" part.
			decimalHolder=0;
			fractionalCounter=1;
			operationsHolder[operationsCounter]=input;						//Save the new operation in the operationsHolder array.
			endIndicatorFlag=1;

			if(inputsCounter>15){											//If the input count is more than 16 (which is the maximum that my LCD can display at a time), shift the display to the left.
				LCD_SendCommand(LCD_COM_DISPLAY_SHIFT_LEFT);
				UART_SendChar_Polling('L');
			}
			LCD_SendCommand(LCD_COM_DISPLAY_ON);							//Remove the blinking cursor when '=' is entered.
			LCD_WriteChar(input);
			UART_SendChar_Polling(input);
			UART_SendChar_Polling('O');

			if(!sequenceCorrectFlag){										//If the sequence is wrong (last thing entered is an operation).
				wrongInputCounter++;
			}

			if(wrongInputCounter){											//Finally, if there is more than zero errors, report syntax error.
				error_report("Syntax Error");
				clearLCDFlag=1;
				reset_calculator();
			}

			if(inputsCounter>=40){											//This condition is for if the user tried to enter another digit after the limit of the LCD (40), if so prints "Limit reached and then resets the calculator.
				error_report("LCD Limit Exceed");
				clearLCDFlag=1;												//clearLCDFlag clear the LCD on a new number entrance (after the operation is finished and represented on the LCD, the calculator is reset but the LCD is not cleared, if a new number is entered the LCD is cleared).
				reset_calculator();
			}
		}

		//Name: "Clear Input" part. Function: It handles the short press on the AC button, it counters the operations done by the last input (undo what the last operation did).
		else if(input=='C'){
			if(sequenceCorrectFlag){												//If the last input was a digit (number from 0 to 9) or a decimal point, it delete it and counters everything done in the "input digit and decimal point" part.
				LCD_DeleteChar();
				UART_SendChar_Polling('D');

				if(decimalPointPosition[inputsCounter]){							//If what i am deleting is a decimal point. Counters everything done in the "input digit" partition.
					if(wrongInputPosition[inputsCounter]){							//If what i am deleting is also a wrong input (for example two decimal point after each other or two decimal points in the same number).
						wrongInputCounter--;										//Delete that there was a wrong input at this position.
						wrongInputPosition[inputsCounter]=0;
					}
					else {
						decimalNumberFlag=0;										//State the number that is going to be entered is no longer a decimal (because the decimal point was deleted).
						if(!operandHolder){											//If the number held in operandHolder is zero, then set the sequenceCorrect
							sequenceCorrectFlag=0;
						}
					}
					decimalPointPosition[inputsCounter]=0;
				}
				else if(decimalHolder){												//If what i am deleting is a digit in the fractional part of a number (decimalNumberFlag=1).
					decimalHolder=(decimalHolder-decimalHolder%10);					//Countering everything done in the "input digit" partition if the input digit is a fractional number.
					fractionalCounter/=10;
					if(decimalHolder){
						decimalHolder/=10;
					}
				}
				else if(operandHolder){												//If what i am deleting is a digit from the integer part (decimalNumberFlag=0).
					operandHolder=(operandHolder-operandHolder%10);					//Countering everything done in the "input digit" partition if the input digit is an integer number.
					if(operandHolder){
						operandHolder/=10;
					}
					else {
						sequenceCorrectFlag=0;										//If the operandHolder reached zero then the last thing entered is an operation, so make the sequenceCorrectFlag=0 to detect errors if another operation is entered.
					}
				}
				inputsCounter--;													//Decrease the number of inputs entered as i removed a digit.

				if(inputsCounter>=15){												//Shift right what was shifted left if the inputs counter was bigger than 16 (which is the lcd limit).
					LCD_SendCommand(LCD_COM_DISPLAY_SHIFT_RIGHT);
					UART_SendChar_Polling('R');
					UART_SendChar_Polling('R');
				}
			}
			else {																	//Handles the undoing of all the operations and the negative sign (+, -, X, /).

				if(negativeSignPosition[inputsCounter]){							//Handles if the minus sign is for a negative number not a subtraction, it counter does everything done in the "input negative sign" partition.
					LCD_DeleteChar();
					UART_SendChar_Polling('D');

					negativeNumberFlag^=1;
					negativeSignPosition[inputsCounter]=0;

					inputsCounter--;
				}
				else if(operandsCounter){											//Handles the undoing of all the operations (+, -, X, /), it counter does everything done in the "input operation" part and "input subtraction sign" partition..
					LCD_DeleteChar();
					UART_SendChar_Polling('D');

					operandsCounter--;

					operandHolder=(u32)operandsHolder[operandsCounter];

					if(operandsHolder[operandsCounter]!=(s32)(operandsHolder[operandsCounter])){
						decimalHolder=(u32)operandsHolder[operandsCounter]-(s32)operandsHolder[operandsCounter];

						f32 decimalHolder_tmp=decimalHolder;										//This part is to set the fractional counter as it was before entering an operation because it is reset after entering an operation.
						while(decimalHolder_tmp!=(s32)decimalHolder_tmp){							//So this loop counts the digits in the fractional part of the number to set the fractional counter as it was before it was reset.
							decimalHolder_tmp*=10;
							fractionalCounter*=10;
						}
					}

					if(operandsHolder[operandsCounter]<0){
						operandHolder=(u32)0-operandsHolder[operandsCounter];
						negativeNumberFlag=1;
					}

					operandsHolder[operandsCounter]=0;
					operationsCounter--;
					operationsHolder[operationsCounter]=0;

					if(wrongInputPosition[inputsCounter]){
						wrongInputCounter--;
						sequenceCorrectFlag=0;
						wrongInputPosition[inputsCounter]=0;
					}
					else {
						sequenceCorrectFlag=1;
					}
					inputsCounter--;
				}
				if(inputsCounter>=15){
					LCD_SendCommand(LCD_COM_DISPLAY_SHIFT_RIGHT);									//Shift right what was shifted left if the inputs counter was bigger than 16 (which is the LCD limit).
					UART_SendChar_Polling('R');
					UART_SendChar_Polling('R');
				}
			}
		}
		input=0;																					//After finishing one cycle of checking the input variable, input is reset to wait for the user to enter another input (0 in this context is null as input variable resembles the ascii table).
	}
}
//Name: "Calculating the result" part. Function: It calculates the whole operation entered by the user.
void operation_perform(void){

	for(u8 i=0;i<=operationsCounter && endIndicatorFlag;i++){				//This for loop handles multiplication and division operations and produces a new operandsHodler array with the results of multiplying and dividing the operands, and a new operationsHolder array without any multiplication and division operations.
		//This for loop was made for multiplication and division only to handle the priorities of a mathematical operation.
		//It basically search for multiplication and division operations in the operationsHolder array. and then perform this operation between its two consecutive operands in the operandsHolder,
		//and takes the result and store it in the first operand position, then update the operandsHolder array by shifting its contents to the left (seconds operand position).
		//It also updates the operationsHolder array removing that operation from it. Then it produces two arrays that has no multiplication or division operations.
		if(operationsHolder[i]=='x'){
			operandsHolder[i]*=operandsHolder[i+1];
			u8 j;
			for(j=i+1;j<operationsCounter;j++){
				operandsHolder[j]=operandsHolder[j+1];
				operationsHolder[j-1]=operationsHolder[j];
			}
			operationsHolder[j-1]=operationsHolder[j];
			operandsCounter--;
			operationsCounter--;
			i--;
		}
		else if(operationsHolder[i]=='/'){
			operandsHolder[i]/=operandsHolder[i+1];
			u8 j;
			for(j=i+1;j<operationsCounter;j++){
				operandsHolder[j]=operandsHolder[j+1];
				operationsHolder[j-1]=operationsHolder[j];
			}
			operationsHolder[j-1]=operationsHolder[j];
			operandsCounter--;
			operationsCounter--;
			i--;
		}
	}
	result=operandsHolder[0];						//Equate the result variable to the first element in the operands array.

	for(u8 i=0;i<=operationsCounter && endIndicatorFlag;i++){				//This for loop handles the addition and subtraction and calculates and displays the result.
		if(operationsHolder[i]=='+'){
			result+=operandsHolder[i+1];
		}
		else if(operationsHolder[i]=='-'){
			result-=operandsHolder[i+1];
		}
		else if(operationsHolder[i]=='='){
			//etba3 el result.
			LCD_SendCommand(LCD_COM_HOME);
			LCD_SendCommand(LCD_COM_SET_CURSOR_SECOND_LINE);
			UART_SendChar_Polling('H');
			UART_SendChar_Polling('S');
			if(result>2147483647 || result<-2147483648){
				error_report("VariableOverflow");
			}
			else if((result-(s32)result)==0){							//This condition checks the decimal part of the result .. if it is 0 then no need to print ".0" in the result.
				LCD_WriteNumber((s32)result);
				UART_SendNumber_Polling(result);
			}
			else{
				LCD_WriteNumber_floatingPoint(result);
				UART_SendNumber_floatingPoint_Polling(result);
			}
			clearLCDFlag=1;											//clearLCDFlag clear the LCD on a new number entrance (after the operation is finished and represented on the LCD, the calculator is reset but the LCD is not cleared, if a new number is entered the LCD is cleared).
			reset_calculator();
		}
	}
}

void calculator(void){
	inputs_store_and_display();
	operation_perform();
}
