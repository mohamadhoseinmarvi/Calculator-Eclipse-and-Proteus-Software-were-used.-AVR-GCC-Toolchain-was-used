/*
 * TMR1_register.h
 *
 *  Created on: Feb 9, 2020
 *      Author: abdel_000
 */

#ifndef TMR1_REGISTER_H_
#define TMR1_REGISTER_H_

#include "../../STD_TYPES_H.h"

#define TCCR1A 				*((u8 volatile*)0x4F)
#define TCCR1B 				*((u8 volatile*)0x4E)
#define TCNT1	 			*((u16 volatile*)0x4C)
#define OCR1A			    *((u16 volatile*)0x4A)
#define OCR1B			    *((u16 volatile*)0x48)
#define ICR1			    *((u16 volatile*)0x46)
#define TIMSK 				*((u8 volatile*)0x59)
#define TIFR				*((u8 volatile*)0x58)
#define DDRD				*((u8 volatile*)0x31)
#define SREG  			    *((u8 volatile*)0x5F)

#endif /* TMR1_REGISTER_H_ */
