/*
 * LCD_program.c
 *
 *  Created on: Aug 24, 2019
 *      Author: abdel_000
 */

#include "../../MCAL/DIO/DIO_interface.h"
#include "LCD_interface.h"
#include "../../MCAL/TMR1/TMR1_interface.h"

STD_ERROR LCD_SendCommand (u8 LCD_COM_){
	STD_ERROR LOC_ERROR = OK;

	u8 tmp_DataPortDirectionHolder;
	DIO_GetPortDir(LCD_DATA_CONNECTED_PORT, &tmp_DataPortDirectionHolder);

	DIO_SetPinValue(LCD_CONTROL_CONNECTED_PORT, RS, DIO_PIN_VALUE_LOW);
	DIO_SetPinValue(LCD_CONTROL_CONNECTED_PORT, R_W, DIO_PIN_VALUE_LOW);
	DIO_SetPinValue(LCD_CONTROL_CONNECTED_PORT, E, DIO_PIN_VALUE_HIGH);
	DIO_SetPortValue(LCD_DATA_CONNECTED_PORT, LCD_COM_, FLAG_DefaultOrSetFromUser_HIGH);
	DIO_SetPinValue(LCD_CONTROL_CONNECTED_PORT, E, DIO_PIN_VALUE_LOW);
	TMR1_Delay_ms(2);
	DIO_SetPinValue(LCD_CONTROL_CONNECTED_PORT, E, DIO_PIN_VALUE_HIGH);
	TMR1_Delay_us(500);
	DIO_SetPortDir(LCD_DATA_CONNECTED_PORT, tmp_DataPortDirectionHolder);
	return (LOC_ERROR);
}

//#if Mode_Of_Oper == Eight_Bit_Mode
STD_ERROR LCD_INIT (void) {
	STD_ERROR LOC_ERROR = OK;

	TMR1_Init_CTC();

	DIO_SetPortDir(LCD_DATA_CONNECTED_PORT, DIO_PORT_DIR_FULL_OUTPUT);
	DIO_SetPinDir(LCD_CONTROL_CONNECTED_PORT, RS, DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDir(LCD_CONTROL_CONNECTED_PORT, E, DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDir(LCD_CONTROL_CONNECTED_PORT, R_W, DIO_PIN_DIR_OUTPUT);

	LCD_SendCommand(LCD_COM_HOME);
	LCD_SendCommand(LCD_COM_FUNCTION_SET_8BIT);
	LCD_SendCommand(LCD_COM_DISPLAY_ON_CURSOR_BLINK);
	LCD_SendCommand(LCD_COM_CLEAR);
	LCD_SendCommand(LCD_COM_ENTRYMODE);

	return LOC_ERROR;
}
//#elif Mode_Of_Oper =  Four_Bit_Mode

/********4 bit mode initialization function*********/

//#else #error "No Mode of Operation is entered."

//#endif

void LCD_GetAddress(u8* address){
	u8 busyFlagValue;
	u8 tmp_DataPortDirectionHolder;

	DIO_GetPortDir(LCD_DATA_CONNECTED_PORT, &tmp_DataPortDirectionHolder);

	DIO_SetPortDir(LCD_DATA_CONNECTED_PORT, DIO_PORT_DIR_FULL_INPUT);
	DIO_SetPinValue(LCD_CONTROL_CONNECTED_PORT, RS, DIO_PIN_VALUE_LOW);
	DIO_SetPinValue(LCD_CONTROL_CONNECTED_PORT, R_W, DIO_PIN_VALUE_HIGH);
	DIO_SetPinValue(LCD_CONTROL_CONNECTED_PORT, E, DIO_PIN_VALUE_HIGH);
	do{
		DIO_GetPinValue(LCD_DATA_CONNECTED_PORT, LCD_BUSY_FLAG_BIT, &busyFlagValue);
	}
	while(busyFlagValue);
	DIO_GetPortValue(LCD_DATA_CONNECTED_PORT, address);

	DIO_SetPortDir(LCD_DATA_CONNECTED_PORT, tmp_DataPortDirectionHolder);
}

STD_ERROR LCD_WriteChar (u8 const Copy_LCD_WR_CHAR) {

	STD_ERROR LOC_ERROR = OK;

	if(Copy_LCD_WR_CHAR <= LCD_MAX_ASCII_CODE){

		DIO_SetPinValue(LCD_CONTROL_CONNECTED_PORT, RS, DIO_PIN_VALUE_HIGH);
		DIO_SetPinValue(LCD_CONTROL_CONNECTED_PORT, R_W, DIO_PIN_VALUE_LOW);
		DIO_SetPinValue(LCD_CONTROL_CONNECTED_PORT, E, DIO_PIN_VALUE_HIGH);
		DIO_SetPortValue(LCD_DATA_CONNECTED_PORT, Copy_LCD_WR_CHAR, FLAG_DefaultOrSetFromUser_HIGH);
		DIO_SetPinValue(LCD_CONTROL_CONNECTED_PORT, E, DIO_PIN_VALUE_LOW);
		DIO_SetPinValue(LCD_CONTROL_CONNECTED_PORT, E, DIO_PIN_VALUE_HIGH);
	}
	else {
		LOC_ERROR = NOT_OK;
	}
	return LOC_ERROR;
}

void LCD_DeleteChar (void){

	LCD_SendCommand(LCD_COM_CURSOR_SHIFT_LEFT);
	LCD_WriteChar(' ');
	TMR1_Delay_us(10);
	LCD_SendCommand(LCD_COM_CURSOR_SHIFT_LEFT);
}

STD_ERROR LCD_WriteString (u8 const * Copy_String) {
	STD_ERROR LOC_ERROR = OK;

	while(*Copy_String != '\0') {
		LCD_WriteChar(*Copy_String);
		Copy_String++;
		TMR1_Delay_us(100);
	}
	return (LOC_ERROR);
}

STD_ERROR LCD_GoTo_X_Y (u8 const x, u8 const y) {

	STD_ERROR LOC_ERROR = OK;
	switch(y) {
	case 0:
		if((x >= ZERO) && (x < LCD_MAX_CHAR_PER_LINE)) {
			LCD_SendCommand(LCD_COM_SET_CURSOR_FIRST_LINE + x);
		}
		else {
			LOC_ERROR = NOT_OK;
		}
		break;
	case 1:
		if((x >= ZERO) && (x < LCD_MAX_CHAR_PER_LINE)) {
			LCD_SendCommand(LCD_COM_SET_CURSOR_SECOND_LINE + x);
		}
		else {
			LOC_ERROR = NOT_OK;
		}
		break;
	default:
		LOC_ERROR = NOT_OK;
		break;
	}
	return LOC_ERROR;
}

/*STD_ERROR LCD_WriteNumber(s32 LCD_NUMBER){
	STD_ERROR LOC_ERROR = OK;
	u64 numberHolder=0;
	u32 LCD_NUMBER_tmp=(u32)LCD_NUMBER;
	u8 digitsCounter=0;
	if(LCD_NUMBER==0){
		LCD_WriteChar('0');
	}
	else {
		if(LCD_NUMBER<0){
			LCD_NUMBER_tmp=(u32)0-LCD_NUMBER;
			LCD_WriteChar('-');
		}
		while(LCD_NUMBER_tmp){
			numberHolder=numberHolder*10 + LCD_NUMBER_tmp%10;
			LCD_NUMBER_tmp/=10;
			digitsCounter++;
		}
		while(digitsCounter){
			LCD_WriteChar((numberHolder%10)+48);
			numberHolder/=10;
			digitsCounter--;
		}
	}
	return (LOC_ERROR);
}*/

STD_ERROR LCD_WriteNumber(s32 LCD_NUMBER){
	STD_ERROR LOC_ERROR = OK;
	if(LCD_NUMBER<2147483648 && LCD_NUMBER>-2147483649){
		u32 numberHolder=(u32)LCD_NUMBER;
		u32 digitsCounter=0;
		if(LCD_NUMBER==0){
			LCD_WriteChar('0');
		}
		else {
			if(LCD_NUMBER<0){
				LCD_NUMBER=0-LCD_NUMBER;
				numberHolder=LCD_NUMBER;
				LCD_WriteChar('-');
			}
			while(LCD_NUMBER){
				LCD_NUMBER/=10;
				if(digitsCounter==0){
					digitsCounter=1;
				}
				else {
					digitsCounter*=10;
				}
			}
			while(digitsCounter!=0){
				LCD_WriteChar(((numberHolder/digitsCounter)%10)+48);
				digitsCounter/=10;
			}
		}
	}
	else {
		LOC_ERROR = NOT_OK;
		LCD_WriteString("ERROR/RESTART");
	}
	return (LOC_ERROR);
}

STD_ERROR LCD_WriteNumber_unsigned(u32 LCD_NUMBER){
	STD_ERROR LOC_ERROR = OK;
	u32 numberHolder=0;
	u8 digitsCounter=0;
	if(LCD_NUMBER==0){
		LCD_WriteChar('0');
	}
	else {
		while(LCD_NUMBER){
			numberHolder*=10;
			numberHolder+=LCD_NUMBER%10;
			LCD_NUMBER/=10;
			digitsCounter++;
		}
		while(digitsCounter){
			LCD_WriteChar((numberHolder%10)+48);
			numberHolder/=10;
			digitsCounter--;
		}
	}
	return (LOC_ERROR);
}

STD_ERROR LCD_WriteNumber_floatingPoint(f32 LCD_NUMBER){
	STD_ERROR LOC_ERROR = OK;
	s32 LCD_NUMBER_INTEGRAL=(s32)LCD_NUMBER;
	u32 fractionalCounter=1;
	u8 zeroFirstFlag=1;

	LCD_NUMBER=(f32)(LCD_NUMBER-LCD_NUMBER_INTEGRAL);					//This makes LCD_NUMBER its fractional part only without the whole number (e.g. 0.23 the integral part has to be 0).

	if(LCD_NUMBER<0){
		if(!LCD_NUMBER_INTEGRAL){
			LCD_WriteChar('-');											//Only print the negative sign if the integral part of the number is zero, because the negative sign will not be printed later if the integral part is zero and the fractional part is negative (e.g. -0.23).
		}
		LCD_NUMBER=0-LCD_NUMBER;
	}

	LCD_WriteNumber(LCD_NUMBER_INTEGRAL);								//Print the integral part of the number, and if its a negative then it prints the sign.

	LCD_WriteChar('.');													//Print the decimal point.

	f32 LCD_NUMBER_tmp=LCD_NUMBER;										//This iteration counts the number of digits in the fractional part to print all of it, but as AVR does not support f64, there are some problems in representing the fractional numbers.

	while(LCD_NUMBER_tmp!=(s32)LCD_NUMBER_tmp){							//As long as the integral part of the number is not equal the number (for example 0.23 is not equal 0).
		LCD_NUMBER_tmp*=10;												//Then next iteration will be 2.3 not equal 2, and the one after it will be 23 equal 23, which satisfy the condition.

		if(zeroFirstFlag){												//This condition checks if the leading digit/digits in the fractional part are zeros, if so print zero (because it will not print it later as zero on the left is not significant).
			if((s32)LCD_NUMBER_tmp%10==0){
				LCD_WriteChar('0');
			}
			else {
				zeroFirstFlag=0;
			}
		}
		fractionalCounter*=10;
	}
	if(fractionalCounter<1000000000){
		LCD_WriteNumber(LCD_NUMBER*fractionalCounter);
	}
	else {
		LCD_WriteNumber(LCD_NUMBER*100000000);
	}

	return (LOC_ERROR);
}
