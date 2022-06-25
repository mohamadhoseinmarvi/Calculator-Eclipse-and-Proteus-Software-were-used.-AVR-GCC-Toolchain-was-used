
#include "KEYPAD_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/TMR1/TMR1_interface.h"

const u8 Pressed_Key[4][4] = {
		{'7','4','1','A'},
		{'8','5','2','0'},
		{'9','6','3','='},
		{'/','x','-','+'},
};

STD_ERROR KEYPAD_INIT(void) {
	STD_ERROR LOC_ERROR = OK;

	DIO_SetPortDir(KEYPAD_CONNECTED_PORT, DIO_PORT_DIR_FIRST_HALF_OUTPUT);
	DIO_SetPortValue(KEYPAD_CONNECTED_PORT, DIO_PORT_VALUE_FULL_HIGH, FLAG_DefaultOrSetFromUser_LOW);


	return LOC_ERROR;
}

u8 KEYPAD_GetPressedKey(void) {
	u8 Pin_Value = 1;
	u8 Return_Value = 0xFF;

	u16 buttonPressTime=0;

	for(int i = COL_START; i < COL_FIN; i++){

		DIO_SetPinValue(KEYPAD_CONNECTED_PORT, i, DIO_PIN_VALUE_LOW);

		for(int j = ROW_START; j < ROW_FIN; j++){
			DIO_GetPinValue(KEYPAD_CONNECTED_PORT, j, &Pin_Value);
			if(Pin_Value == PRESSED){
				Return_Value = Pressed_Key[i-COL_START][j-ROW_START];
				while(Pin_Value == PRESSED){
					DIO_GetPinValue(KEYPAD_CONNECTED_PORT, j, &Pin_Value);
				}
				TMR1_Delay_ms(10);
			}
		}
		DIO_SetPinValue(KEYPAD_CONNECTED_PORT, i, DIO_PIN_VALUE_HIGH);
	}																			

	return Return_Value;
}
