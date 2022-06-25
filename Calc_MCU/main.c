/*
 * main.c
 *
 *  Created on: Mar 25, 2020
 *      Author: abdel_000
 */

#include "STD_TYPES_H.h"
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/UART/UART_interface.h"
#include "HAL/KEYPAD/KEYPAD_interface.h"
#include "HAL/LCD/LCD_interface.h"
#include "calc.h"


int main(void){

	DIO_INIT();
	UART_Init();
	KEYPAD_INIT();
	LCD_INIT();

	while(1){
		calculator();
	}
	return 0;
}
