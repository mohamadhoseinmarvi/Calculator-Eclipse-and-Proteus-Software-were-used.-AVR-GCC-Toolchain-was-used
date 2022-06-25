/*
 * TMR1_interface.h
 *
 *  Created on: Feb 9, 2020
 *      Author: abdel_000
 */

#ifndef TMR1_INTERFACE_H_
#define TMR1_INTERFACE_H_

#include "../../STD_TYPES_H.h"

#ifndef PROCESSOR_FREQ
# define PROCESSOR_FREQ 1000000UL
#endif

//*******************************************TCCR1A Bits.****************************************************//
#define WGM10											(u8)0
#define WGM11											(u8)1
#define FOC1B											(u8)2
#define FOC1A											(u8)3
#define COM1B0											(u8)4
#define COM1B1											(u8)5
#define COM1A0											(u8)6
#define COM1A1											(u8)7
//*******************************************TCCR1A Options.****************************************************//
#define TMR1_WGM_NORMAL_TCCR1A							(u8)0x00				//Normal timer mode.
							//TCCR1A in the end of the WGM names refers to the bits of WGM in the TCCR1A register, as there are WGM bit in the TCCR1B register as well.
#define TMR1_WGM_CTC_TCCR1A								(u8)0x00				//CTC timer mode.
#define TMR1_WGM_CTC_ICR1_TCCR1A						(u8)0x00				//CTC timer mode with the top represented by ICR1.

#define TMR1_WGM_FAST_PWM_ICR1_TCCR1A					(u8)0x02				//Fast (single slope) PWM mode with the top value set by the ICR1 register (works better if our TOP fixed not changing).
#define TMR1_WGM_FAST_PWM_OCR1A_TCCR1A					(u8)0x03				//Fast (single slope) PWM mode with the top value set by the OCR1A register (works better if we want to vary TOP values because its double buffered).

#define TMR1_WGM_PHASECORRECT_PWM_ICR1_TCCR1A			(u8)0x02				//Phase Correct (dual slope) PWM mode with the top value set by the ICR1 register (works better if our TOP fixed not changing).
#define TMR1_WGM_PHASECORRECT_PWM_OCR1A_TCCR1A			(u8)0x03				//Phase Correct (dual slope) PWM mode with the top value set by the OCR1A register (works better if we want to vary TOP values because its double buffered).


#define TMR1_COM_NORMAL 	 							(u8)0x00				//For all modes .. Normal port operation, OC1A/B disconnected.

#define TMR1_COM_TOGGLE_OC1A							(u8)0x40				//For Normal and CTC mode: Toggle OC1A on compare match.
																				//For Fast PWM when WGM is WGM_FAST_PWM_OCR1A: Toggle OC1A on compare match (for 50% duty cycle pwm), OC1B is disconnected (act as normal mode).
																				//For Phase Correct PWM when WGM is WGM_PHASECORRECT_PWM_OCR1A: Toggle OC1A/OC1B on compare match.
#define TMR1_COM_TOGGLE_OC1B							(u8)0x10

#define TMR1_COM_CLEAR_OC1A								(u8)0x80				//For Normal and CTC mode: Clear OC1A/OC1B on compare match.
																				//For Fast PWM: Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM (non-inverting mode).
																				//For Phase Correct PWM: Clear OC1A/OC1B on compare match when up-counting. Set OC1A/OC1B on compare match when down-counting (non-inverting mode).
#define TMR1_COM_CLEAR_OC1B								(u8)0x20

#define TMR1_COM_SET_OC1A								(u8)0xC0				//For Normal and CTC mode: Set OC1A/OC1B on compare match.
																				//For Fast PWM: Set OC1A/OC1B on compare match, clear OC1A/OC1B at BOTTOM (inverting mode).
																				//For Phase Correct PWM: Set OC1A/OC1B on compare match when up-counting. Clear OC1A/OC1B on compare match when down-counting (inverting mode).
#define TMR1_COM_SET_OC1B								(u8)0x30
/*************************************************************************************************************/
//*******************************************TCCR1B Bits.****************************************************//
#define CS10											(u8)0
#define CS11											(u8)1
#define CS12											(u8)2
#define WGM12											(u8)3
#define WGM13											(u8)4
#define ICES1											(u8)6
#define ICNC1											(u8)7
//*******************************************TCCR1B Options.****************************************************//
#define TMR1_ICES1										(u8)0x40

#define TMR1_WGM_NORMAL_TCCR1B							(u8)0x00				//Normal timer mode.

#define TMR1_WGM_CTC_TCCR1B								(u8)0x08				//CTC timer mode.
#define TMR1_WGM_CTC_ICR1_TCCR1B						(u8)0x18				//CTC timer mode with the top represented by ICR1.

#define TMR1_WGM_FAST_PWM_ICR1_TCCR1B					(u8)0x18				//Fast (single slope) PWM mode with the top value set by the ICR1 register (works better if our TOP fixed not changing).
#define TMR1_WGM_FAST_PWM_OCR1A_TCCR1B					(u8)0x18				//Fast (single slope) PWM mode with the top value set by the OCR1A register (works better if we want to vary TOP values because its double buffered).

#define TMR1_WGM_PHASECORRECT_PWM_ICR1_TCCR1B			(u8)0x10				//Phase Correct (dual slope) PWM mode with the top value set by the ICR1 register (works better if our TOP fixed not changing).
#define TMR1_WGM_PHASECORRECT_PWM_OCR1A_TCCR1B			(u8)0x10				//Phase Correct (dual slope) PWM mode with the top value set by the OCR1A register (works better if we want to vary TOP values because its double buffered).


#define TMR1_CLOCK_SELECT_NOCLK							(u8)0x00				//Timer is off.
#define TMR1_CLOCK_SELECT_CLK_NOPRESCALING				(u8)0x01				//Clock of the mcu with no prescaling.
#define TMR1_CLOCK_SELECT_CLK_8							(u8)0x02				//Clock/8.
#define TMR1_CLOCK_SELECT_CLK_64						(u8)0x03				//Clock/64.
#define TMR1_CLOCK_SELECT_CLK_256						(u8)0x04				//Clock/256.
#define TMR1_CLOCK_SELECT_CLK_1024						(u8)0x05				//Clock/1024.
#define TMR1_CLOCK_SELECT_EXTERNAL_CLK_FALLING			(u8)0x06				//External clock on T1 pin clock on falling edge (counter mode).
#define TMR1_CLOCK_SELECT_EXTERNAL_CLK_RISING			(u8)0x07				//External clock on T1 pin clock on rising edge (counter mode).
/*************************************************************************************************************/
//*******************************************TIMSK Bits.****************************************************//
#define TOIE1											(u8)2
#define OCIE1B											(u8)3
#define OCIE1A											(u8)4
#define TICIE1											(u8)5
//*******************************************TIMSK Options.****************************************************//
#define TMR1_ICR_INTERRUPT_ENABLE						(1<<TICIE1)
#define TMR1_OCA_MATCH_INTERRUPT_ENABLE					(1<<OCIE1A)
#define TMR1_OCB_MATCH_INTERRUPT_ENABLE					(1<<OCIE1B)
#define TMR1_OVERFLOW_INTERRUPT_ENABLE					(1<<TOIE0)
/*************************************************************************************************************/
//*******************************************TIFR Bits.****************************************************//
#define TOV1											(u8)2
#define OCF1B											(u8)3
#define OCF1A											(u8)4
#define ICF1											(u8)5
/*************************************************************************************************************/
#define GLOBAL_INTERRUPT_ENABLE 						(u8)7						// SREG I-bit

volatile u16 tOn, tOff;
u32 freq, period, dutyCycle;

void TMR1_Init_CTC(void);
void TMR1_Start_CTC(u16 Time_ms);
void TMR1_Delay_ms(u16 time_ms);										//This function and the next are the same as TMR1_Start_CTC but with adding a condition that keeps looping until TCNT is equal to OCR1A hence emulating a delay, check PROCESSOR_FREQ when using.
void TMR1_Delay_us(u16 time_us);										////Maximum delay is 8 seconds.
u16 TMR1_Read_Current_Count_Value_CTC(void);							//Multiply by the tick time (Prescaler/CPU freq) to get the time in seconds.
u16 TMR1_Read_Current_Time_MS_CTC(void);								//return current counting time in ms.

void TMR1_Stop(void);

void TMR1_Init_PhaseCorrect_PWM(void);
void TMR1_Start_PhaseCorrect_PWM(u16 Period_ms, u16 dutyCyclePercentage);
void TMR1_Change_PhaseCorrect_PWM_DutyCycle_Period(u16 Period_ms, u16 dutyCyclePercentage);
void TMR1_Change_PhaseCorrect_PWM_DutyCycle(u16 dutyCyclePercentage);
void TMR1_Change_PhaseCorrect_PWM_Period(u16 Period_ms);

void TMR1_Init_Fast_PWM(void);
void TMR1_Start_Fast_PWM(u16 Period_ms, u16 dutyCyclePercentage);
void TMR1_Change_Fast_PWM_DutyCycle_Period(u16 Period_ms, u16 dutyCyclePercentage);
void TMR1_Change_Fast_PWM_DutyCycle(u16 dutyCyclePercentage);
void TMR1_Change_Fast_PWM_Period(u16 Period_ms);

void TMR1_Init_ICU(void);
void TMR1_Start_ICU(void);

void TMR1_Callback_CTC(ptr_2func ISR_Func);
void TMR1_Callback_ICU(ptr_2func ISR_Func);
void __vector_7 (void) __attribute__((signal,used));
void __vector_6 (void) __attribute__((signal,used));

#endif /* TMR1_INTERFACE_H_ */
