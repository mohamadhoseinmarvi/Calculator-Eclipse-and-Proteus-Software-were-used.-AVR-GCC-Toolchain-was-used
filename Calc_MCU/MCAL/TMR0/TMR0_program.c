/*
 * TIMER0_program.c
 *
 *  Created on: Nov 21, 2019
 *      Author: abdel_000
 */

#include "TMR0_register.h"
#include "TMR0_config.h"

void TMR0_Init_Normal(void){

	TCCR0=ZERO;
	TCNT0=ZERO;
	OCR0=ZERO;
	TIMSK&=~((1<<0)|(1<<1));
	TIFR&=~((1<<0)|(1<<1));

	DDRB |= (1<<3);
	TCCR0 |= TMR0_WGM_NORMAL | TMR0_COM_NORMALMODE;									//The options are set in TMR0_config.h file.
	TIMSK |= TMR0_INTERRUPT_NORMALMODE;												//Interrupt on overflow to operate on normal mode.
	OCR0 |= 0xFF;																	//Setting the OCR to 255 to have a compare match at overflow.
	SREG |= (1<<GLOBAL_INTERRUPT_ENABLE);								  			//Global interrupt flag enabled.
}

u8 Timer_Flag = ZERO;
u16 Time_ms_Clone;
u8 Overflow_Counts_Required = ZERO;
u8 Overflow_Counts = ZERO;

void TMR0_Start_NormalMode(u16 Time_ms){

	Time_ms_Clone = Time_ms;														//The required user-defined time (Time_ms) is cloned using Time_ms_Clone to access it outside the function.

	TCNT0=(u8)((u16)256-(((u32)(Time_ms-((u32)(32768*((u32)Time_ms*1000/32768)))/1000)*256*1000)/32768));			//This equation gives the appropriate starting number for the TCNT0 register for all cases (time is less or more to the overflow time (or zero if the required time is equal to the overflow time or one of its multiples).
	Overflow_Counts_Required = (u8)(((u32)Time_ms*1000)/32768);						//33 is the overflow time, calculated in the comments below.

	TCCR0 |= TMR0_CLOCK_SELECT_NORMALMODE;												//Prescaler is set to X .. So Tick Time is: X/8MHz (uc frequency).
																					//Tick time is now 1024/8M = 128us.
																					//Overflow time is now 128u x 256 (resolution of timer) = 32.76840ms.
}

void TMR0_Stop(void){
	TCCR0 &= ~ TMR0_CLOCK_SELECT_NORMALMODE;											//Set the clock select bits of the timer to no clock source (timer/counter stopped).
}

void TMR0_Init_Fast_PWM(void){
	TCCR0=ZERO;
	TCNT0=ZERO;
	OCR0=ZERO;
	TIMSK&=~((1<<0)|(1<<1));
	TIFR&=~((1<<0)|(1<<1));

	DDRB |= (1<<3);
	TCCR0 |= TMR0_WGM_FAST_PWM | TMR0_COM_PWM;										//The options are set in TMR0_config.h file.
}

void TMR0_Start_Fast_PWM(u8 dutyCyclePercentage){
	OCR0 = (dutyCyclePercentage*256)/100; 											//Set the OCR0 register value to be compared with TCNT.

	TCCR0 |= TMR0_CLOCK_SELECT_PWM;
}

ptr_2func TMR0_CallBacked = NULL;

void TMR0_CallBack(ptr_2func ISR_Func){												//Callback function to be done when the counter reaches the required time (Time_ms).
	TMR0_CallBacked = ISR_Func;
}

void __vector_11(void){

	Overflow_Counts++;																//This counter counts each overflow.
	if (Overflow_Counts == (Overflow_Counts_Required+1)){								//This condition is checking if the overflow counts reached the overflow counts required for the desired time (Time_ms) to be achieved.
		TCNT0=(u8)((u16)256-(((u32)(Time_ms_Clone-((u32)(32768*((u32)Time_ms_Clone*1000/32768)))/1000)*256*1000)/32768));			//The equation is called again so that if the required time is reached the timer resets and starts counting the same ammount of time again.
		Overflow_Counts = 0;														//The target time is reached, so the timer has to restart.
		if(TMR0_CallBacked != NULL){
			TMR0_CallBacked();														//Do the callback function when the required time is reached.
		}
	}
}
