/*
 * KEYPAD_program.c
 *
 *  Created on: Aug 30, 2019
 *      Author: abdel_000
 */

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

	DIO_SetPortDir(KEYPAD_CONNECTED_PORT, DIO_PORT_DIR_FIRST_HALF_OUTPUT);											//First 4 pins are output (for the columns), and last 4 pins are input (for the rows).
	DIO_SetPortValue(KEYPAD_CONNECTED_PORT, DIO_PORT_VALUE_FULL_HIGH, FLAG_DefaultOrSetFromUser_LOW);				//Initially the output pins are high and the input pins are pulled up (also high). So now the button terminals are both connected to VCC,
																													//so if the button is pressed (the circuit is closed) nothing happens as VCC is connected to VCC.

	return LOC_ERROR;
}

u8 KEYPAD_GetPressedKey(void) {
	u8 Pin_Value = 1;
	u8 Return_Value = 0xFF;															//Return value is all ones as initially with no buttons pressed the keypad output is high (no buttons

	u16 buttonPressTime=0;

	for(int i = COL_START; i < COL_FIN; i++){										//The keypad is 4x4 buttons, the idea is that each 4 buttons forming a column are connected together to a pin (4 pins), those pins' direction are output.
																					//Also each 4 buttons forming a row are connected together to a pin (4 pins), those pins' direction are a pulled up input (connected to VCC via a resistor).
		DIO_SetPinValue(KEYPAD_CONNECTED_PORT, i, DIO_PIN_VALUE_LOW);				//Activating a certain column by setting its value to low, so that now when a button (from the 4 buttons in the column) is pressed, it will drive the input pin of its row to the ground.

		for(int j = ROW_START; j < ROW_FIN; j++){
			DIO_GetPinValue(KEYPAD_CONNECTED_PORT, j, &Pin_Value);					//Looping on the 4 buttons of the column (4 rows), to find the pressed button.
			if(Pin_Value == PRESSED){												//Checking if this pin is the pressed pin.
				Return_Value = Pressed_Key[i-COL_START][j-ROW_START];				//If i find it, i now know which button is pressed, by knowing its certain column (the activated one) and its certain row (the row that is driven to ground, i.e. reads as 0).
				TMR1_Start_CTC(8000);												//This line starts the timer in CTC mode, can be removed from the code (serves a specific purpose).
				while(Pin_Value == PRESSED){										//This loop makes sure that the function does not keep checking on a pressed button as long as the button is being pressed.
					DIO_GetPinValue(KEYPAD_CONNECTED_PORT, j, &Pin_Value);
				}
				buttonPressTime=TMR1_Read_Current_Time_MS_CTC();					//This line gets the current reading of the timer after the button is no longer pressed, can be removed from the code (serves a specific purpose).
				TMR1_Stop();														//Stops the timer, can be removed from the code (serves a specific purpose).
				if(Return_Value=='A' && buttonPressTime<300){						//This is the specific purpose, it makes sure that pressing a certain button ('A' in this case) for more than 300ms, sends a different character (acts as if i have two buttons in this button, i.e. when its long pressed and when its short pressed).
					Return_Value='C';
				}
				if(Return_Value=='0' && buttonPressTime>300){						//Same as before.
					Return_Value='D';
				}
				TMR1_Delay_ms(10);
			}
		}
		DIO_SetPinValue(KEYPAD_CONNECTED_PORT, i, DIO_PIN_VALUE_HIGH);				//Deactivating the column that i activated, to activate another in the next iteration.
	}																				//The processor clock is much faster than the human reaction time, that is why the MCU can loop on the 4 columns activating one a time, and still be able to know which button is pressed.

	return Return_Value;
}

