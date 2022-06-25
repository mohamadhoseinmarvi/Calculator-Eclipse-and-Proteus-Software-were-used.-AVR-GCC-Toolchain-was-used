#include"STD_TYPES_H.h"
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/UART/UART_interface.h"
#include "HAL/LCD/LCD_interface.h"
#include "MCAL/TMR1/TMR1_interface.h"
#include "HAL/KEYPAD/KEYPAD_interface.h"


int main(void){

	DIO_INIT();
	UART_Init();
	LCD_INIT();
	KEYPAD_INIT();

	u8 input=0;
	u8 ctr_moreThan15CharsOnLCD=0;
	u8 tmp_ctr_moreThan15CharsOnLCD=0;
	u8 equal_sign_pressed_flag=0;
	u8 charHolder=0;
	UART_RecieveChar_Interrupt();

	while(1){

		input=KEYPAD_GetPressedKey();

		charHolder=RX_Char;
		if(charHolder==0){

		}
		else if(charHolder=='C'){
			LCD_SendCommand(LCD_COM_CLEAR);
			ctr_moreThan15CharsOnLCD=0;
			tmp_ctr_moreThan15CharsOnLCD=0;
			equal_sign_pressed_flag=0;
		}
		else if(charHolder=='B'){
			LCD_SendCommand(LCD_COM_DISPLAY_ON_CURSOR_BLINK);
		}
		else if(charHolder=='O'){
			LCD_SendCommand(LCD_COM_DISPLAY_ON);						
		}
		else if(charHolder=='D'){
			LCD_DeleteChar();
			ctr_moreThan15CharsOnLCD--;
			tmp_ctr_moreThan15CharsOnLCD--;
		}
		else if(charHolder=='S'){
			LCD_SendCommand(LCD_COM_SET_CURSOR_SECOND_LINE);
		}
		else if(charHolder=='Q'){
			LCD_WriteString("LCD Limit Exceed");
		}
		else if(charHolder=='W'){
			LCD_WriteString("VariableOverflow");
		}
		else if(charHolder=='E'){
			LCD_WriteString("Syntax Error");
		}
		else if(charHolder=='L'){
			LCD_SendCommand(LCD_COM_DISPLAY_SHIFT_LEFT);
		}
		else if(charHolder=='R'){
			LCD_SendCommand(LCD_COM_DISPLAY_SHIFT_RIGHT);
		}
		else if(charHolder=='H'){
			if(ctr_moreThan15CharsOnLCD){
				LCD_SendCommand(LCD_COM_HOME);
			}
		}
		else {
			LCD_WriteChar(charHolder);
			if(!equal_sign_pressed_flag){
				ctr_moreThan15CharsOnLCD++;
				tmp_ctr_moreThan15CharsOnLCD++;
			}
			if(charHolder=='='){
				tmp_ctr_moreThan15CharsOnLCD=15;
				equal_sign_pressed_flag=1;
			}
		}
		RX_Char=0;

		if(ctr_moreThan15CharsOnLCD>15){
			if(input=='A' && tmp_ctr_moreThan15CharsOnLCD>15){
				LCD_SendCommand(LCD_COM_DISPLAY_SHIFT_RIGHT);
				tmp_ctr_moreThan15CharsOnLCD--;
			}
			else if(input=='=' && tmp_ctr_moreThan15CharsOnLCD<ctr_moreThan15CharsOnLCD){
				LCD_SendCommand(LCD_COM_DISPLAY_SHIFT_LEFT);
				tmp_ctr_moreThan15CharsOnLCD++;
			}
			input=0;
		}
	}
	return 0;
}
