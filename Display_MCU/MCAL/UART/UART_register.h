
#ifndef UART_REGISTER_H_
#define UART_REGISTER_H_

#define UDR 				*((u8 volatile*)0x2C)
#define UCSRA	 			*((u8 volatile*)0x2B)
#define UCSRB			    *((u8 volatile*)0x2A)
#define UBRRL 				*((u8 volatile*)0x29)
#define UCSRC				*((u8 volatile*)0x40)
#define UBRRH				*((u8 volatile*)0x40)
#define SREG  			    *((u8 volatile*)0x5F)

#endif 
