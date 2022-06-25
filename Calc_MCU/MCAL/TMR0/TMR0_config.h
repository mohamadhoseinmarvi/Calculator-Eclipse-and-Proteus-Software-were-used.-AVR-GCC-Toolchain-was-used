/*
 * TIMER0_config.h
 *
 *  Created on: Nov 21, 2019
 *      Author: abdel_000
 */

#ifndef TMR0_CONFIG_H_
#define TMR0_CONFIG_H_

#include "TMR0_interface.h"

/****************************Timer0 NORMAL mode configurations***********************************/
#define TMR0_COM_NORMALMODE							TMR0_COM_TOGGLE
#define TMR0_CLOCK_SELECT_NORMALMODE				TMR0_CLOCK_SELECT_CLK_1024
#define TMR0_INTERRUPT_NORMALMODE					TMR0_OVERFLOW_INTERRUPT
/*********************************************************************************/

/****************************Timer0 FAST PWM mode configurations***********************************/
#define TMR0_COM_PWM								TMR0_COM_CLEAR
#define TMR0_CLOCK_SELECT_PWM						TMR0_CLOCK_SELECT_CLK_64
#define TMR0_INTERRUPT_PWM							TMR0_OCR_MATCH_INTERRUPT
/*********************************************************************************/

#endif /* TMR0_CONFIG_H_ */
