

#include "UART_interface.h"
#include "UART_register.h"
#include "../TMR1/TMR1_interface.h"

void UART_Init(void){
	UDR = 0;
	UCSRA = 0;
	UCSRB = 0;
	UCSRC = 0;
	UBRRL = 0;
	UBRRH = 0;

	UCSRB |= (1<<RXEN)|(1<<TXEN);
	UBRRL = 207;
	UCSRC |= (1<<URSEl)|(1<<UCSZ1)|(1<<UCSZ0);
}

void UART_DeInit(void){
	UDR = 0;
	UCSRA = 0;
	UCSRB = 0;
	UCSRC = 0;
	UBRRL = 0;
	UBRRH = 0;
}

void UART_SendChar_Polling(u8 UART_Send_Char){
	while(!(UCSRA & (1<<UDRE)));
	UDR = UART_Send_Char;
	UCSRA |= (1<<UDRE);
}

u8 UART_RecieveChar_Polling(void){
	while(!(UCSRA & (1<<RXC)));
	UCSRA |= (1<<RXC);
	return UDR;
}

void UART_SendNumber_Polling(s32 UART_Send_Number){
	s32 numberHolder=0;
	u8 digitsCounter=0;
	if(UART_Send_Number==0){
		UART_SendChar_Polling('0');
	}
	else {
		if(UART_Send_Number<0){
			UART_Send_Number=0-UART_Send_Number;
			UART_SendChar_Polling('-');
		}
		while(UART_Send_Number){
			numberHolder*=10;
			numberHolder+=UART_Send_Number%10;
			UART_Send_Number/=10;
			digitsCounter++;
		}
		while(digitsCounter){
			UART_SendChar_Polling((numberHolder%10)+48);
			numberHolder/=10;
			digitsCounter--;
		}
	}
}

void UART_SendNumber_floatingPoint_Polling(f32 UART_Send_Number){
	s32 tmp_UART_Send_Number=(s32)UART_Send_Number;

	UART_SendNumber_Polling(tmp_UART_Send_Number);
	UART_Send_Number=(f32)(UART_Send_Number-tmp_UART_Send_Number);
	if(UART_Send_Number<0){
		UART_Send_Number=0-UART_Send_Number;
	}
	UART_SendChar_Polling('.');
	UART_SendNumber_Polling(UART_Send_Number*100);
}

u8 TX_Char;
u8 RX_Char;

void UART_SendChar_Interrupt(u8 UART_Send_Char){
	UCSRB |= (1<<TXCIE);
	SREG |= (1<<GLOBAL_INTERRUPT_ENABLE);
	TX_Char = UART_Send_Char;
}

void UART_RecieveChar_Interrupt(void){
	UCSRB |= (1<<RXCIE);
	SREG |= (1<<GLOBAL_INTERRUPT_ENABLE);
}

ptr_2func UART_CallBackedTx = NULL;
ptr_2func UART_CallBackedRx = NULL;

void UART_CallBackTx(ptr_2func ISR_Func){
	UART_CallBackedTx = ISR_Func;
}

void UART_CallBackRx(ptr_2func ISR_Func){
	UART_CallBackedRx = ISR_Func;
}

void __vector_14 (void) {
	if (UART_CallBackedTx != NULL){
		UART_CallBackedTx();
	}
	UDR = TX_Char;
}

void __vector_13 (void) {
	RX_Char = UDR;
	if (UART_CallBackedRx != NULL){
		UART_CallBackedRx();
	}
}
