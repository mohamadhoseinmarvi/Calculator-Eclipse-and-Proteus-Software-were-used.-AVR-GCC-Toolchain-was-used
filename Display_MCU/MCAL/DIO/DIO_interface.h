

#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#include "../../STD_TYPES_H.h"

#define PORT_A								(u8)1
#define PORT_B								(u8)2
#define PORT_C								(u8)3
#define PORT_D								(u8)4

#define P_0									(u8)0
#define P_1									(u8)1
#define P_2									(u8)2
#define P_3									(u8)3
#define P_4									(u8)4
#define P_5									(u8)5
#define P_6									(u8)6
#define P_7									(u8)7

#define DIO_MAX_PIN_PER_PORT 				(u8)7

#define DIO_MAX_PORT_NO		 				(u8)4

#define DIO_PIN_DIR_INPUT   				(u8)0
#define DIO_PIN_DIR_OUTPUT  				(u8)1

#define DIO_PORT_DIR_FULL_INPUT				(u8)(0x00)
#define DIO_PORT_DIR_FULL_OUTPUT			(u8)(0xFF)
#define DIO_PORT_DIR_FIRST_HALF_OUTPUT		(u8)(0x0F)
#define DIO_PORT_DIR_SECOND_HALF_OUTPUT		(u8)(0xF0)

#define DIO_PIN_VALUE_LOW						(u8)0
#define DIO_PIN_VALUE_HIGH						(u8)1

#define DIO_PORT_VALUE_FULL_HIGH			(u8)0xFF
#define DIO_PORT_VALUE_FULL_LOW				(u8)0x00
#define DIO_PORT_VALUE_FIRST_HALF_HIGH		(u8)0x0F
#define DIO_PORT_VALUE_SECOND_HALF_HIGH		(u8)0xF0

#define FLAG_DefaultOrSetFromUser_LOW	   	(u8)0
#define FLAG_DefaultOrSetFromUser_HIGH		(u8)1


STD_ERROR DIO_INIT (void);

STD_ERROR DIO_SetPinDir(u8 PORT_, u8 P_, u8 DIO_PIN_DIR_);

STD_ERROR DIO_SetPortDir(u8 PORT_, u8 DIO_PORT_DIR_);

STD_ERROR DIO_GetPortDir(u8 PORT_, u8 *Port_Dir);

STD_ERROR DIO_GetPinValue(u8 PORT_, u8 P_, u8 *Pin_Value);

STD_ERROR DIO_GetPortValue(u8 PORT_, u8 *Pin_Value);

STD_ERROR DIO_SetPinValue(u8 PORT_, u8 P_, u8 DIO_PIN_VALUE_);

STD_ERROR DIO_SetPortValue(u8 PORT_, u8 DIO_PORT_VALUE_, u8 FLAG_DefaultOrSetFromUser);

#endif
