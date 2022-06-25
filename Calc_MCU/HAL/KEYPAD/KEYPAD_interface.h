/*
 * KEYPAD_interface.h
 *
 *  Created on: Aug 30, 2019
 *      Author: abdel_000
 */

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#include "../../STD_TYPES_H.h"

extern u16 buttonPressTime;

#define KEYPAD_CONNECTED_PORT		(PORT_A)

#define C1 							P_0
#define C2 							P_1
#define C3 							P_2
#define C4 							P_3
#define R1 							P_4
#define R2 							P_5
#define R3 							P_6
#define R4 							P_7

#define COL_START					0
#define COL_FIN						4
#define ROW_START					4
#define ROW_FIN						8

#define PRESSED						0

STD_ERROR KEYPAD_INIT(void);
u8 KEYPAD_GetPressedKey(void);						//This function returns a char that resembles the button pressed on the keypad.

#endif /* KEYPAD_INTERFACE_H_ */
