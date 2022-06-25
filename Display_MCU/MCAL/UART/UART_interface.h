
#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "../../STD_TYPES_H.h"

#define U2X 			(u8)1
#define UDRE			(u8)5
#define TXC				(u8)6
#define RXC				(u8)7

#define TXEN			(u8)3
#define RXEN			(u8)4
#define TXCIE			(u8)6
#define RXCIE			(u8)7

#define UCSZ0			(u8)1
#define UCSZ1			(u8)2
#define URSEl			(u8)7

#define GLOBAL_INTERRUPT_ENABLE 	(u8)7

extern u8 RX_Char;

void UART_Init(void);
void UART_SendChar_Polling(u8 UART_Send_Char);
u8 UART_RecieveChar_Polling(void);
void UART_SendNumber_Polling(s32 UART_Send_Number);
void UART_SendChar_Interrupt(u8 UART_Send_Char);
void UART_RecieveChar_Interrupt(void);
void UART_CallBackTx(ptr_2func ISR_Func);
void UART_CallBackRx(ptr_2func ISR_Func);

void __vector_13 (void) __attribute__((signal,used));
void __vector_14 (void) __attribute__((signal,used));

#endif 
