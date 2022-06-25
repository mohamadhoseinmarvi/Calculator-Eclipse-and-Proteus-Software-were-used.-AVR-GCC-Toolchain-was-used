/*
 * TMR1_config.h
 *
 *  Created on: Feb 9, 2020
 *      Author: abdel_000
 */

#ifndef TMR1_CONFIG_H_
#define TMR1_CONFIG_H_

#include "TMR1_interface.h"

/****************************Timer1 CTC mode configurations***********************************/
#define TMR1_COM_CTC								TMR1_COM_NORMAL
#define TMR1_CLOCK_SELECT_CTC						TMR1_CLOCK_SELECT_CLK_1024
#define TMR1_PRESCALER_CTC							(u16)1024
#define TMR1_INTERRUPT_CTC		 					TMR1_OCA_MATCH_INTERRUPT_ENABLE
/*********************************************************************************/

/****************************Timer1 Phase Correct PWM mode configurations***********************************/
#define TMR1_COM_PWM								TMR1_COM_CLEAR_OC1A
#define TMR1_CLOCK_SELECT_PWM						TMR1_CLOCK_SELECT_CLK_NOPRESCALING
#define TMR1_PRESCALER_PWM							(u16)1
#define TMR1_TOP_VALUE_PWM							(u16)65535
#define TMR1_INTERRUPT_CONFIG_PWM		 			TMR1_OCA_MATCH_INTERRUPT_ENABLE
/*********************************************************************************/

/****************************Timer1 ICU mode configurations***********************************/
#define TMR1_COM_ICU								TMR1_COM_NORMAL
#define TMR1_CLOCK_SELECT_ICU						TMR1_CLOCK_SELECT_CLK_1024
#define TMR1_PRESCALER_ICU							(u16)1024
#define TMR1_INTERRUPT_ICU		 					TMR1_ICR_INTERRUPT_ENABLE
/*********************************************************************************/

#endif /* TMR1_CONFIG_H_ */
