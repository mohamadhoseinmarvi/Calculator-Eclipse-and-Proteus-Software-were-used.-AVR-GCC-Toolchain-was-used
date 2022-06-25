/*
 * ADC_register.h
 *
 *  Created on: Oct 4, 2019
 *      Author: abdel_000
 */

#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define ADMUX 			   *((u8 volatile*)0x27)
#define ADCSRA   		   *((u8 volatile*)0x26)
#define ADC 		       *((u16 volatile*)0x24)
#define SFIOR     		   *((u8 volatile*)0x50)
#define SREG  			   *((u8 volatile*)0x5F)

#endif /* ADC_REGISTER_H_ */
