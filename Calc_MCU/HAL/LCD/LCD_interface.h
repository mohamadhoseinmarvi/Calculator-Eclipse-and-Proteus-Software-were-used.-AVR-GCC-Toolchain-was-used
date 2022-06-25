/*
 * LCD_interface.h
 *
 *  Created on: Aug 24, 2019
 *      Author: abdel_000
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "../../STD_TYPES_H.h"

u16 h1,h2,h3, h22;
u8 cursorAddress;

#define LCD_COM_CLEAR					(u8)(0x01)
#define LCD_COM_HOME					(u8)(0x02)
#define LCD_COM_ENTRYMODE				(u8)(0x06)
#define LCD_COM_DISPLAY_OFF				(u8)(0x08)
#define LCD_COM_DISPLAY_ON				(u8)(0x0C)
#define LCD_COM_DISPLAY_ON_CURSOR_BLINK	(u8)(0x0D)
#define LCD_COM_CURSOR_SHIFT_LEFT		(u8)(0x10)
#define LCD_COM_CURSOR_SHIFT_RIGHT		(u8)(0x14)
#define LCD_COM_DISPLAY_SHIFT_LEFT		(u8)(0x18)
#define LCD_COM_DISPLAY_SHIFT_RIGHT		(u8)(0x1C)
#define LCD_COM_FUNCTION_RESET			(u8)(0x30)
#define LCD_COM_FUNCTION_SET_8BIT		(u8)(0x38)
#define LCD_COM_SET_CURSOR_FIRST_LINE	(u8)(0x80)
#define LCD_COM_SET_CURSOR_SECOND_LINE	(u8)(0xc0)

#define LCD_DATA_CONNECTED_PORT			(PORT_C)       	// Change this value (PORT_D) if you connected to a different port of the AVR.
#define LCD_BUSY_FLAG_BIT				(P_7)
#define LCD_DATA_PORT_INIT 				(u8)0xFF;

#define LCD_FIRST_LINE_BASE_ADDRESS		(u8)0x00
#define LCD_SECOND_LINE_BASE_ADDRESS	(u8)0x40
#define LCD_MAX_CHAR_PER_LINE			(u8)16

#define LCD_CONTROL_CONNECTED_PORT		(PORT_D)
#define RS 								(P_4)
#define R_W								(P_3)
#define E 								(P_2)

#define Eight_Bit_Mode 					(u8)(0)
#define Four_Bit_Mode 					(u8)(1)
#define Mode_Of_Oper Eight_Bit_Mode

#define LCD_MAX_ASCII_CODE 				(u8)127

STD_ERROR LCD_SendCommand (u8 LCD_COM_);

STD_ERROR LCD_INIT (void);								//Notice that this function calls TMR1_Init_CTC();.

void LCD_GetAddress(u8* address);

STD_ERROR LCD_WriteChar (u8 const Copy_LCD_WR_CHAR);

void LCD_DeleteChar (void);

STD_ERROR LCD_GoTo_X_Y (u8 const x, u8 const y);

STD_ERROR LCD_WriteString (u8 const * Copy_String);

STD_ERROR LCD_WriteNumber(s32 LCD_NUMBER);

STD_ERROR LCD_WriteNumber_unsigned(u32 LCD_NUMBER);

STD_ERROR LCD_WriteNumber_floatingPoint(f32 LCD_NUMBER);

#endif /* LCD_INTERFACE_H_ */
