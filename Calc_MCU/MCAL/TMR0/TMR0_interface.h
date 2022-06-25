/*
 * TIMER0_interface.h
 *
 *  Created on: Nov 21, 2019
 *      Author: abdel_000
 */

#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_

#include "../../STD_TYPES_H.h"

//*******************************************TCCR0 Bits.****************************************************//
#define CS00			(u8)0
#define CS01			(u8)1
#define CS02			(u8)2
#define WGM01			(u8)3
#define COM00			(u8)4
#define COM01			(u8)5
#define WGM00			(u8)6
#define FOC0			(u8)7
//*******************************************TCCR0 Options.****************************************************//
#define TMR0_WGM_NORMAL 								(u8)0x00				//Normal timer mode.
#define TMR0_WGM_PHASECORRECT_PWM 						(u8)0x08				//Phase correct PWM timer mode.
#define TMR0_WGM_CTC									(u8)0x40				//CTC timer mode.
#define TMR0_WGM_FAST_PWM 								(u8)0x48				//Fast PWM timer mode.

#define TMR0_COM_NORMAL									(u8)0x00				//For all modes .. Normal port operation, OC0 disconnected.

#define TMR0_COM_TOGGLE 								(u8)0x10				//Toggle OC0 on compare match.
#define TMR0_COM_CLEAR									(u8)0x20				//Clear OC0 on compare match.
																				//For fast: Clear OC0 on compare match, set OC0 at BOTTOM,(non-inverting mode).
																				//For Phase correct: Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting.

#define TMR0_COM_SET	 								(u8)0x30				//Set OC0 on compare match.
																				//For fast: Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting.
																				//For Phase correct: Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting.

#define TMR0_CLOCK_SELECT_NOCLK							(u8)0x00				//Timer is off.
#define TMR0_CLOCK_SELECT_CLK_NOPRESCALING				(u8)0x01				//Clock of the mcu with no prescaling.
#define TMR0_CLOCK_SELECT_CLK_8							(u8)0x02				//Clock/8.
#define TMR0_CLOCK_SELECT_CLK_64						(u8)0x03				//Clock/64.
#define TMR0_CLOCK_SELECT_CLK_256						(u8)0x04				//Clock/256.
#define TMR0_CLOCK_SELECT_CLK_1024						(u8)0x05				//Clock/1024.
#define TMR0_CLOCK_SELECT_EXTERNAL_CLK_FALLING			(u8)0x06				//External clock on T0 pin clock on falling edge (counter mode).
#define TMR0_CLOCK_SELECT_EXTERNAL_CLK_RISING			(u8)0x07				//External clock on T0 pin clock on rising edge (counter mode).
/*************************************************************************************************************/
//*******************************************TIMSK Bits.****************************************************//
#define TOIE0											(u8)0
#define OCIE0											(u8)1
//*******************************************TIMSK Options.****************************************************//
#define TMR0_OCR_MATCH_INTERRUPT						(1<<OCIE0)
#define TMR0_OVERFLOW_INTERRUPT							(1<<TOIE0)
/*************************************************************************************************************/
//*******************************************TIFR Bits.****************************************************//
#define TOV0									(u8)0
#define OCF0									(u8)1
/*************************************************************************************************************/
#define GLOBAL_INTERRUPT_ENABLE 	(u8)7						// SREG I-bit

void TMR0_Init_Normal(void);
void TMR0_Start_NormalMode(u16 Time_ms);

void TMR0_Stop(void);

void TMR0_Init_Fast_PWM(void);
void TMR0_Start_Fast_PWM(u8 dutyCyclePercentage);

void TMR0_CallBack(ptr_2func ISR_Func);

void __vector_11 (void) __attribute__((signal,used));

#endif /* TMR0_INTERFACE_H_ */
