/*
 * ADC_interface.h
 *
 *  Created on: Oct 4, 2019
 *      Author: abdel_000
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "../../STD_TYPES_H.h"

//*******************************************ADMUX Bits.****************************************************//
#define ADLAR 									(u8)5
#define REFS0 									(u8)6
#define REFS1 									(u8)7
//*******************************************ADMUX Options.****************************************************//
#define ADC_Voltage_Reference_AREF 				(u8)0x00
#define ADC_Voltage_Reference_AVCC 				(u8)0x40
#define ADC_Voltage_Reference_Internal			(u8)0xA0

#define ADC_ADLAR_LOW							(0<<ADLAR)
#define ADC_ADLAR_HIGH							(1<<ADLAR)
/*************************************************************************************************************/
//*******************************************ADCSRA Bits.****************************************************//
#define ADPS0									(u8)0
#define ADPS1									(u8)1
#define ADPS2									(u8)2
#define ADIE									(u8)3
#define ADIF									(u8)4
#define ADATE									(u8)5
#define ADSC									(u8)6
#define ADEN									(u8)7
//*******************************************ADCSRA Options.****************************************************//
#define ADC_Prescaler_2							(1<<ADPS0)
#define ADC_Prescaler_4							(1<<ADPS1)
#define ADC_Prescaler_8							(1<<ADPS1)|(1<<ADPS0)
#define ADC_Prescaler_16						(1<<ADPS2)
#define ADC_Prescaler_32						(1<<ADPS2)|(1<<ADPS0)
#define ADC_Prescaler_64						(1<<ADPS2)|(1<<ADPS1)
#define ADC_Prescaler_128						(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)
/*************************************************************************************************************/
//*******************************************SFIOR Bits.****************************************************//
#define ADTS2									(u8)5
#define ADTS1									(u8)6
#define ADTS0									(u8)7
//*******************************************SFIOR Options.****************************************************//
#define AUTO_TRIGGER_MODE_FREE_RUNNING									(u8)0
#define AUTO_TRIGGER_MODE_ANALOG_COMP									(u8)1
#define AUTO_TRIGGER_MODE_EXTI0											(u8)2
#define AUTO_TRIGGER_MODE_TIMER0_COMPARE_MATCH							(u8)3
#define AUTO_TRIGGER_MODE_TIMER0_OVERFLOW								(u8)4
#define AUTO_TRIGGER_MODE_TIMER1_COMPARE_MATCHB							(u8)5
#define AUTO_TRIGGER_MODE_TIMER1_OVERFLOW								(u8)6
#define AUTO_TRIGGER_MODE_CAPTURE_EVENT									(u8)7
/*************************************************************************************************************/
#define GLOBAL_INTERRUPT_ENABLE 	(u8)7						// SREG I-bit

void ADC_INIT(void);

u16 ADC_Read_Polling_SingleConversion(u8 channel);
void ADC_SC_Polling_AutoTrigger(u8 channel);
u16 ADC_Read_Polling_AutoTrigger(void);

void ADC_SC_Interrupt_SingleConversion(u8 channel);				//Channel choice is by the 3 first LSBs only (there are only 8 channels), differential mode is not supported in this driver.
u16 ADC_Read_Interrupt(void);									//Do not call this function except in the attribute ptr2func of the callback function.
void ADC_SC_Interrupt_AutoTrigger(u8 channel);

void ADC_CallBack(ptr_2func ISR_Func);

void __vector_16 (void) __attribute__((signal,used));

#endif /* ADC_INTERFACE_H_ */
