/*
 * TMR1_program.c
 *
 *  Created on: Feb 9, 2020
 *      Author: abdel_000
 */

#include "TMR1_register.h"
#include "TMR1_config.h"

void TMR1_Init_CTC(void){

	TCCR1A = ZERO;
	TCCR1B = ZERO;
	TCNT1 = ZERO;
	OCR1A = ZERO;
	OCR1B = ZERO;
	ICR1 = ZERO;
	TIMSK &= ~((1<<TICIE1)|(1<<OCIE1A)|(1<<OCIE1B)|(1<<TOIE1));
	TIFR &= ~((1<<ICF1)|(1<<OCF1A)|(1<<OCF1B)|(1<<TOV1));

	//DDRD |= (1<<5);
	TCCR1B |= TMR1_WGM_CTC_TCCR1B;												//Setting the timer to CTC mode.
																				//The options are set in TMR1_config.h file.
	TIMSK |= TMR1_INTERRUPT_CTC;												//Interrupt on compare A match to operate on CTC mode.
	SREG |= (1<<GLOBAL_INTERRUPT_ENABLE);										//Global interrupt flag enabled.
}

void TMR1_Start_CTC(u16 Time_ms){
	TCNT1 = ZERO;
	OCR1A |= (((u32)(Time_ms*(PROCESSOR_FREQ/1000)))/(TMR1_PRESCALER_CTC));		//This equation change the required time in ms to the required OCR register counts.
																				//Prescaler is set to X .. So Tick Time is: X/8MHz (uc frequency).
																				//Tick time is now 1024/8M = 128us.
																				//So number of counts needed is: Required Time(in seconds)/Tick time.
																				//Maximum number of OCR counts is 65535 which corresponds to maximum of 8.38 sec.
	TCCR1B |= TMR1_CLOCK_SELECT_CTC;
}

void TMR1_Delay_ms(u16 time_ms){
	TMR1_Start_CTC(time_ms+5);
	while(time_ms>(((u32)TCNT1*TMR1_PRESCALER_CTC)/(PROCESSOR_FREQ/1000)));		//The condition checks if the required time is equal the current time, the equation gives the current time from the TCNT1.
	TMR1_Stop();
}

void TMR1_Delay_us(u16 time_us){
	TMR1_Start_CTC(8200);
	while(time_us>(((u32)TCNT1*TMR1_PRESCALER_CTC)/(PROCESSOR_FREQ/1000000)));	//The condition checks if the required time is equal the current time. This equation gives the current time from the TCNT1.
	TMR1_Stop();
}

u16 TMR1_Read_Current_Count_Value_CTC(void){
	return TCNT1;
}

u16 TMR1_Read_Current_Time_MS_CTC(void){
	u16 timeMs = ((u32)TCNT1*TMR1_PRESCALER_CTC)/(PROCESSOR_FREQ/1000);
	return timeMs;
}

void TMR1_Stop(void){															//Works for all timer modes.
	TCCR1B &= ~(0x07);															//Set the clock select bits of the timer to no clock source (timer/counter stopped).
}

void TMR1_Init_PhaseCorrect_PWM(void){

	TCCR1A = ZERO;
	TCCR1B = ZERO;
	TCNT1 = ZERO;
	OCR1A = ZERO;
	OCR1B = ZERO;
	ICR1 = ZERO;
	TIMSK &= ~((1<<5)|(1<<4)|(1<<3)|(1<<2));
	TIFR &= ~((1<<5)|(1<<4)|(1<<3)|(1<<2));

	DDRD |= (1<<5);
	TCCR1A |= (TMR1_WGM_PHASECORRECT_PWM_ICR1_TCCR1A | TMR1_COM_CLEAR_OC1A); 	//Setting the WGM to Phase Correct mode, and the COM to non-inverting mode.
	TCCR1B |= TMR1_WGM_PHASECORRECT_PWM_ICR1_TCCR1B;							//The options are set in TMR1_config.h file.
	ICR1 |= 0xFFFF;
	//TIMSK |= TMR1_INTERRUPT_CONFIG_PWM;										//Interrupt on compare A match.
	//SREG |= (1<<GLOBAL_INTERRUPT_ENABLE);										//Global interrupt flag enabled.
}

void TMR1_Start_PhaseCorrect_PWM(u16 Period_ms, u16 dutyCyclePercentage){
	ICR1 = (((u32)((Period_ms/2)*(PROCESSOR_FREQ/1000)))/(TMR1_PRESCALER_PWM)); 	//Set the TOP value (period) of the timer.
	OCR1A = (dutyCyclePercentage*ICR1)/100; 										//Set the OCR1A register value to be compared with TCNT.

	TCCR1B |= TMR1_CLOCK_SELECT_PWM;
}

void TMR1_Change_PhaseCorrect_PWM_DutyCycle_Period(u16 Period_ms, u16 dutyCyclePercentage){
	ICR1 = (((u32)((Period_ms/2)*(PROCESSOR_FREQ/1000)))/(TMR1_PRESCALER_PWM)); 	//Set the TOP value (period) of the timer.
	OCR1A = (dutyCyclePercentage*ICR1)/100; 										//Set the OCR1A register value to be compared with TCNT.
	TCNT1 = 0;
}

void TMR1_Change_PhaseCorrect_PWM_DutyCycle(u16 dutyCyclePercentage){
	OCR1A = (dutyCyclePercentage*ICR1)/100;
}

void TMR1_Change_PhaseCorrect_PWM_Period(u16 Period_ms){
	ICR1 = (((u32)((Period_ms/2)*(PROCESSOR_FREQ/1000)))/(TMR1_PRESCALER_PWM)); 	//Set the new TOP value (period) of the timer.
	TCNT1 = ZERO;
}

void TMR1_Init_Fast_PWM(void){
	TCCR1A = ZERO;
	TCCR1B = ZERO;
	TCNT1 = ZERO;
	OCR1A = ZERO;
	OCR1B = ZERO;
	ICR1 = ZERO;
	TIMSK &= ~((1<<5)|(1<<4)|(1<<3)|(1<<2));
	TIFR &= ~((1<<5)|(1<<4)|(1<<3)|(1<<2));

	DDRD |= (1<<5);
	TCCR1A |= (TMR1_WGM_FAST_PWM_ICR1_TCCR1A | TMR1_COM_CLEAR_OC1A); 			//Setting the WGM to Phase Correct mode, and the COM to non-inverting mode.
	TCCR1B |= TMR1_WGM_FAST_PWM_ICR1_TCCR1B;									//The options are set in TMR1_config.h file.
	ICR1 |= 0xFFFF;
}

void TMR1_Start_Fast_PWM(u16 Period_ms, u16 dutyCyclePercentage){
	ICR1 = (((u32)((Period_ms)*(PROCESSOR_FREQ/1000)))/(TMR1_PRESCALER_PWM)); 	//Set the TOP value (period) of the timer.
	OCR1A = (dutyCyclePercentage*ICR1)/100; 									//Set the OCR1A register value to be compared with TCNT.

	TCCR1B |= TMR1_CLOCK_SELECT_PWM;
}

void TMR1_Change_Fast_PWM_DutyCycle_Period(u16 Period_ms, u16 dutyCyclePercentage){
	ICR1 = (((u32)((Period_ms)*(PROCESSOR_FREQ/1000)))/(TMR1_PRESCALER_PWM)); 	//Set the TOP value (period) of the timer.
	OCR1A = (dutyCyclePercentage*ICR1)/100; 									//Set the OCR1A register value to be compared with TCNT.
	TCNT1 = 0;
}

void TMR1_Change_Fast_PWM_DutyCycle(u16 dutyCyclePercentage){
	OCR1A = (dutyCyclePercentage*ICR1)/100;
}

void TMR1_Change_Fast_PWM_Period(u16 Period_ms){
	ICR1 = (((u32)((Period_ms)*(PROCESSOR_FREQ/1000)))/(TMR1_PRESCALER_PWM)); 	//Set the new TOP value (period) of the timer.
	TCNT1 = ZERO;
}

volatile u8 ICUFlag;

void TMR1_Init_ICU(void){
	TCCR1A = ZERO;
	TCCR1B = ZERO;
	TCNT1 = ZERO;
	OCR1A = ZERO;
	OCR1B = ZERO;
	ICR1 = ZERO;
	TIMSK &= ~((1<<5)|(1<<4)|(1<<3)|(1<<2));
	TIFR &= ~((1<<5)|(1<<4)|(1<<3)|(1<<2));

	DDRD &= ~(1<<6);
	TCCR1B |= TMR1_WGM_CTC_TCCR1B | (1<<ICES1);									//Setting the timer to CTC mode (any dummy mode other than WGM = 8/10/12/14).
																				//The options are set in TMR1_config.h file.
	TIMSK |= TMR1_INTERRUPT_ICU;												//Interrupt on Input capture register (ICR) when an event is captured on Input capture pin (ICP1).
	SREG |= (1<<GLOBAL_INTERRUPT_ENABLE);										//Global interrupt flag enabled.
	ICUFlag=0;
}

void TMR1_Start_ICU(void){
	OCR1A |= 0xFFFF;															//CTC mode with maximum value for OCR1A.
	TCCR1B |= TMR1_CLOCK_SELECT_ICU;											//Setting clock to start timer counting.
}

ptr_2func TMR1_CallBacked_CTC = NULL;
ptr_2func TMR1_CallBacked_ICU = NULL;

void TMR1_Callback_CTC(ptr_2func ISR_Func){										//Callback function to be done when the counter reaches the required time (Time_ms).
	TMR1_CallBacked_CTC = ISR_Func;
}

void TMR1_Callback_ICU(ptr_2func ISR_Func){										//Callback function to be done when the counter reaches the required time (Time_ms).
	TMR1_CallBacked_ICU = ISR_Func;
}

void __vector_7 (void){
	if(TMR1_CallBacked_CTC != NULL){
		TMR1_CallBacked_CTC();													//Do the callback function when the required time is reached.
	}
}

void __vector_6 (void){
	if(ICUFlag==0){
		ICUFlag=1;
		TCCR1B ^= (1<<ICES1);
		TCNT1=0;
	}
	else if(ICUFlag==1){
		tOn=ICR1;
		ICUFlag=2;
		TCCR1B ^= (1<<ICES1);
		TCNT1=0;
	}
	else if(ICUFlag==2){
		tOff=ICR1;
		TCNT1=0;
		SREG |= (1<<GLOBAL_INTERRUPT_ENABLE);									//Global interrupt flag enabled.
		ICUFlag=0;
		TCCR1B |= (1<<ICES1);
																				//tOn and tOff are the number of counts of TCNT1 register when when an event occurs on the icp1 pin.
		period = (u32)tOn+(u32)tOff;											//The period is the summation of number of counts, if we want to get the real period time, we multiply the summation of number of counts by tick time.
		freq = F_CPU/((u32)((period)*TMR1_PRESCALER_ICU));								//The most minimum prescaler this mode can have is 8.
		dutyCycle = (u32)tOn*100/period;

		if(TMR1_CallBacked_ICU != NULL){
			TMR1_CallBacked_ICU();												//Do the callback function when the tOn then the tOff are both calculated.
		}
	}
}
