/*
 * ADC_program.c
 *
 *  Created on: Oct 4, 2019
 *      Author: abdel_000
 */

#include "ADC_register.h"
#include "ADC_config.h"

void ADC_INIT(void){

	ADMUX = ZERO;
	ADCSRA = ZERO;
	SFIOR = ZERO;

	ADMUX = ADC_Voltage_Reference;
	ADMUX |= ADC_ADLAR;

	ADCSRA |= (1<<ADEN);
	ADCSRA |= ADC_Prescaler;
}

u16 ADC_Read_Polling_SingleConversion(u8 channel){
	ADMUX &= (0xE0);
	ADMUX |= (0x07 & channel);									// setting channel.
	ADCSRA |= (1<<ADSC);										// start conversion.

	while((ADCSRA & (1<<ADIF)) == ZERO);
	ADCSRA |= (1<<ADIF);										// clear ADC interrupt flag by writing one to it.
	return ADC;
}

void ADC_SC_Polling_AutoTrigger(u8 channel){
	ADMUX &= (0xE0);
	ADMUX |= (0x07 & channel);									// setting channel.
	SFIOR = AUTO_TRIGGER_MODE;									// set the auto trigger mode as ADATE is set to 1.
	ADCSRA |= (1<<ADSC)|(1<<ADATE);								// start conversion and enable auto trigger.
}

u16 ADC_Read_Polling_AutoTrigger(void){

	while((ADCSRA & (1<<ADIF)) == ZERO);
	ADCSRA |= (1<<ADIF);										// clear ADC interrupt flag by writing one to it.
	return ADC;
}

void ADC_SC_Interrupt_SingleConversion(u8 channel){			    // start conversion function.
	SREG |= (1<<GLOBAL_INTERRUPT_ENABLE);			  			// Global interrupt flag enabled.
	ADMUX &= (0xE0);
	ADMUX |= (0x07 & channel);
	ADCSRA |= (1<<ADSC)|(1<<ADIE);
}

u16 ADC_Read_Interrupt(void){				 					// Do not call this function except in the attribute ptr2func of the callback function.
	return ADC;
}

void ADC_SC_Interrupt_AutoTrigger(u8 channel){					// start converion function.
	SREG |= (1<<GLOBAL_INTERRUPT_ENABLE);			   			// Global interrupt flag enabled.
	ADMUX &= (0xE0);
	ADMUX |= (0x07 & channel);
	SFIOR = AUTO_TRIGGER_MODE;									// set the auto trigger mode as ADATE is set to 1.
	ADCSRA |= (1<<ADSC)|(1<<ADIE)|(1<<ADATE);
}


ptr_2func ADC_CallBacked = NULL;

void ADC_CallBack(ptr_2func ISR_Func){
	ADC_CallBacked = ISR_Func;
}

void __vector_16 (void) {
	if (ADC_CallBacked != NULL){
		ADC_CallBacked();
	}
}
