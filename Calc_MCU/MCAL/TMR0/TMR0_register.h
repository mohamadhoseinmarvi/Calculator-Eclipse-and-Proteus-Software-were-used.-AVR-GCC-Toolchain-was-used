/*
 * TIMER0_register.h
 *
 *  Created on: Nov 21, 2019
 *      Author: abdel_000
 */

#ifndef TMR0_REGISTER_H_
#define TMR0_REGISTER_H_

#include "../../STD_TYPES_H.h"

#define TCCR0 				*((u8 volatile*)0x53)
#define TCNT0	 			*((u8 volatile*)0x52)
#define OCR0			    *((u8 volatile*)0x5C)
#define TIMSK 				*((u8 volatile*)0x59)
#define TIFR				*((u8 volatile*)0x58)
#define DDRB				*((u8 volatile*)0x37)
#define SREG  			    *((u8 volatile*)0x5F)



#endif /* TMR0_REGISTER_H_ */
