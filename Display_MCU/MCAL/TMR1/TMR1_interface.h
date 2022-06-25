
#ifndef TMR1_INTERFACE_H_
#define TMR1_INTERFACE_H_

#include "../../STD_TYPES_H.h"

#ifndef PROCESSOR_FREQ
# define PROCESSOR_FREQ 1000000UL
#endif

#define WGM10											(u8)0
#define WGM11											(u8)1
#define FOC1B											(u8)2
#define FOC1A											(u8)3
#define COM1B0											(u8)4
#define COM1B1											(u8)5
#define COM1A0											(u8)6
#define COM1A1											(u8)7

#define TMR1_WGM_NORMAL_TCCR1A							(u8)0x00
#define TMR1_WGM_CTC_TCCR1A								(u8)0x00
#define TMR1_WGM_CTC_ICR1_TCCR1A						(u8)0x00

#define TMR1_WGM_FAST_PWM_ICR1_TCCR1A					(u8)0x02
#define TMR1_WGM_FAST_PWM_OCR1A_TCCR1A					(u8)0x03
#define TMR1_WGM_PHASECORRECT_PWM_ICR1_TCCR1A			(u8)0x02
#define TMR1_WGM_PHASECORRECT_PWM_OCR1A_TCCR1A			(u8)0x03


#define TMR1_COM_NORMAL 	 							(u8)0x00

#define TMR1_COM_TOGGLE_OC1A							(u8)0x40
#define TMR1_COM_TOGGLE_OC1B							(u8)0x10

#define TMR1_COM_CLEAR_OC1A								(u8)0x80
#define TMR1_COM_CLEAR_OC1B								(u8)0x20

#define TMR1_COM_SET_OC1A								(u8)0xC0

#define TMR1_COM_SET_OC1B								(u8)0x30

#define CS10											(u8)0
#define CS11											(u8)1
#define CS12											(u8)2
#define WGM12											(u8)3
#define WGM13											(u8)4
#define ICES1											(u8)6
#define ICNC1											(u8)7

#define TMR1_ICES1										(u8)0x40

#define TMR1_WGM_NORMAL_TCCR1B							(u8)0x00

#define TMR1_WGM_CTC_TCCR1B								(u8)0x08
#define TMR1_WGM_CTC_ICR1_TCCR1B						(u8)0x18

#define TMR1_WGM_FAST_PWM_ICR1_TCCR1B					(u8)0x18
#define TMR1_WGM_FAST_PWM_OCR1A_TCCR1B					(u8)0x18
#define TMR1_WGM_PHASECORRECT_PWM_ICR1_TCCR1B			(u8)0x10
#define TMR1_WGM_PHASECORRECT_PWM_OCR1A_TCCR1B			(u8)0x10


#define TMR1_CLOCK_SELECT_NOCLK							(u8)0x00
#define TMR1_CLOCK_SELECT_CLK_NOPRESCALING				(u8)0x01
#define TMR1_CLOCK_SELECT_CLK_8							(u8)0x02
#define TMR1_CLOCK_SELECT_CLK_64						(u8)0x03
#define TMR1_CLOCK_SELECT_CLK_256						(u8)0x04
#define TMR1_CLOCK_SELECT_CLK_1024						(u8)0x05
#define TMR1_CLOCK_SELECT_EXTERNAL_CLK_FALLING			(u8)0x06
#define TMR1_CLOCK_SELECT_EXTERNAL_CLK_RISING			(u8)0x07
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
void TMR1_Delay_ms(u16 time_ms);
u16 TMR1_Read_Current_Count_Value_CTC(void);
u16 TMR1_Read_Current_Time_MS_CTC(void);							

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
