/*
 * DIO_program.c
 *
 *  Created on: Aug 23, 2019
 *      Author: abdel_000
 */

#include "DIO_interface.h"
#include "DIO_register.h"

STD_ERROR DIO_INIT (void) {
	STD_ERROR LOC_ERRORSTATE = OK;

	DDRA = ZERO;
	DDRB = ZERO;
	DDRC = ZERO;
	DDRD = ZERO;
	PORTA = ZERO;
	PORTB = ZERO;
	PORTC = ZERO;
	PORTD = ZERO;
	PINA = ZERO;
	PINB = ZERO;
	PINC = ZERO;
	PIND = ZERO;

	return (LOC_ERRORSTATE);
}

STD_ERROR DIO_SetPinDir (u8 PORT_, u8 P_, u8 DIO_PIN_DIR_) {
	STD_ERROR LOC_ERRORSTATE = OK;

	switch(PORT_) {
	case PORT_A:
		if(P_ <= DIO_MAX_PIN_PER_PORT) {
			if(DIO_PIN_DIR_ == DIO_PIN_DIR_OUTPUT){
				DDRA |= (1<<P_);
			}
			else if (DIO_PIN_DIR_ == DIO_PIN_DIR_INPUT){
				DDRA &= ~(1<<P_);
			}
			else {
				LOC_ERRORSTATE = NOT_OK;
			}
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;

	case PORT_B:
		if(P_ <= DIO_MAX_PIN_PER_PORT) {
			if(DIO_PIN_DIR_ == DIO_PIN_DIR_OUTPUT){
				DDRB |= (1<<P_);
			}
			else if (DIO_PIN_DIR_ == DIO_PIN_DIR_INPUT){
				DDRB &= ~(1<<P_);
			}
			else {
				LOC_ERRORSTATE = NOT_OK;
			}
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;

	case PORT_C:
		if(P_ <= DIO_MAX_PIN_PER_PORT) {
			if(DIO_PIN_DIR_ == DIO_PIN_DIR_OUTPUT){
				DDRC |= (1<<P_);
			}
			else if (DIO_PIN_DIR_ == DIO_PIN_DIR_INPUT){
				DDRC &= ~(1<<P_);
			}
			else {
				LOC_ERRORSTATE = NOT_OK;
			}
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;

	case PORT_D:
		if(P_ <= DIO_MAX_PIN_PER_PORT) {
			if(DIO_PIN_DIR_ == DIO_PIN_DIR_OUTPUT){
				DDRD |= (1<<P_);
			}
			else if (DIO_PIN_DIR_ == DIO_PIN_DIR_INPUT){
				DDRD &= ~(1<<P_);
			}
			else {
				LOC_ERRORSTATE = NOT_OK;
			}
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;

	default:
		LOC_ERRORSTATE = NOT_OK;
		break;
	}

	return (LOC_ERRORSTATE);
}

STD_ERROR DIO_SetPortDir(u8 PORT_, u8 DIO_PORT_DIR_) {

	STD_ERROR LOC_ERROR = OK;

	switch (PORT_) {
	case PORT_A:

		switch (DIO_PORT_DIR_) {
		case DIO_PORT_DIR_FULL_INPUT:
			DDRA = DIO_PORT_DIR_FULL_INPUT;
			break;
		case DIO_PORT_DIR_FULL_OUTPUT:
			DDRA = DIO_PORT_DIR_FULL_OUTPUT;
			break;
		case DIO_PORT_DIR_FIRST_HALF_OUTPUT:
			DDRA |= DIO_PORT_DIR_FIRST_HALF_OUTPUT;
			break;
		case DIO_PORT_DIR_SECOND_HALF_OUTPUT:
			DDRA |= DIO_PORT_DIR_SECOND_HALF_OUTPUT;
			break;
		default:
			LOC_ERROR = NOT_OK;
			break;
		}
			break;

	case PORT_B:

		switch (DIO_PORT_DIR_) {
		case DIO_PORT_DIR_FULL_INPUT:
			DDRB = DIO_PORT_DIR_FULL_INPUT;
			break;
		case DIO_PORT_DIR_FULL_OUTPUT:
			DDRB = DIO_PORT_DIR_FULL_OUTPUT;
			break;
		case DIO_PORT_DIR_FIRST_HALF_OUTPUT:
			DDRB |= DIO_PORT_DIR_FIRST_HALF_OUTPUT;
			break;
		case DIO_PORT_DIR_SECOND_HALF_OUTPUT:
			DDRB |= DIO_PORT_DIR_SECOND_HALF_OUTPUT;
			break;
		default:
			LOC_ERROR = NOT_OK;
			break;
		}
			break;

	case PORT_C:

		switch (DIO_PORT_DIR_) {
		case DIO_PORT_DIR_FULL_INPUT:
			DDRC = DIO_PORT_DIR_FULL_INPUT;
			break;
		case DIO_PORT_DIR_FULL_OUTPUT:
			DDRC = DIO_PORT_DIR_FULL_OUTPUT;
			break;
		case DIO_PORT_DIR_FIRST_HALF_OUTPUT:
			DDRC |= DIO_PORT_DIR_FIRST_HALF_OUTPUT;
			break;
		case DIO_PORT_DIR_SECOND_HALF_OUTPUT:
			DDRC |= DIO_PORT_DIR_SECOND_HALF_OUTPUT;
			break;
		default:
			LOC_ERROR = NOT_OK;
			break;
		}
			break;

	case PORT_D:

		switch (DIO_PORT_DIR_) {
		case DIO_PORT_DIR_FULL_INPUT:
			DDRD = DIO_PORT_DIR_FULL_INPUT;
			break;
		case DIO_PORT_DIR_FULL_OUTPUT:
			DDRD = DIO_PORT_DIR_FULL_OUTPUT;
			break;
		case DIO_PORT_DIR_FIRST_HALF_OUTPUT:
			DDRD |= DIO_PORT_DIR_FIRST_HALF_OUTPUT;
			break;
		case DIO_PORT_DIR_SECOND_HALF_OUTPUT:
			DDRD |= DIO_PORT_DIR_SECOND_HALF_OUTPUT;
			break;
		default:
			LOC_ERROR = NOT_OK;
			break;
		}
			break;

		default:
			LOC_ERROR = NOT_OK;
			break;
	}
	return (LOC_ERROR);
}

STD_ERROR DIO_SetPinValue(u8 PORT_, u8 P_, u8 DIO_PIN_VALUE_) {
	STD_ERROR LOC_ERRORSTATE = OK;

	switch(PORT_) {
		case PORT_A:
			if(P_ <= DIO_MAX_PIN_PER_PORT) {
				if(DIO_PIN_VALUE_ == DIO_PIN_VALUE_HIGH){
					PORTA |= (1<<P_);
				}
				else if (DIO_PIN_VALUE_ == DIO_PIN_VALUE_LOW){
					PORTA &= ~(1<<P_);
				}
				else {
					LOC_ERRORSTATE = NOT_OK;
				}
			}
			else {
				LOC_ERRORSTATE = NOT_OK;
			}
			break;

		case PORT_B:
			if(P_ <= DIO_MAX_PIN_PER_PORT) {
				if(DIO_PIN_VALUE_ == DIO_PIN_VALUE_HIGH){
					PORTB |= (1<<P_);
				}
				else if (DIO_PIN_VALUE_ == DIO_PIN_VALUE_LOW){
					PORTB &= ~(1<<P_);
				}
				else {
					LOC_ERRORSTATE = NOT_OK;
				}
			}
			else {
				LOC_ERRORSTATE = NOT_OK;
			}
			break;

		case PORT_C:
			if(P_ <= DIO_MAX_PIN_PER_PORT) {
				if(DIO_PIN_VALUE_ == DIO_PIN_VALUE_HIGH){
					PORTC |= (1<<P_);
				}
				else if (DIO_PIN_VALUE_ == DIO_PIN_VALUE_LOW){
					PORTC &= ~(1<<P_);
				}
				else {
					LOC_ERRORSTATE = NOT_OK;
				}
			}
			else {
				LOC_ERRORSTATE = NOT_OK;
			}
			break;

		case PORT_D:
			if(P_ <= DIO_MAX_PIN_PER_PORT) {
				if(DIO_PIN_VALUE_ == DIO_PIN_VALUE_HIGH){
					PORTD |= (1<<P_);
				}
				else if (DIO_PIN_VALUE_ == DIO_PIN_VALUE_LOW){
					PORTD &= ~(1<<P_);
				}
				else {
					LOC_ERRORSTATE = NOT_OK;
				}
			}
			else {
				LOC_ERRORSTATE = NOT_OK;
			}
			break;

		default:
			LOC_ERRORSTATE = NOT_OK;
			break;
		}

		return (LOC_ERRORSTATE);
}

STD_ERROR DIO_SetPortValue(u8 PORT_, u8 DIO_PORT_VALUE_, u8 FLAG_DefaultOrSetFromUser) {
	STD_ERROR LOC_ERRORSTATE = OK;

	if(FLAG_DefaultOrSetFromUser == FLAG_DefaultOrSetFromUser_LOW){
		switch(PORT_) {

		case PORT_A:
			switch (DIO_PORT_VALUE_) {

			case DIO_PORT_VALUE_FULL_HIGH:
				PORTA = DIO_PORT_VALUE_FULL_HIGH;
				break;
			case DIO_PORT_VALUE_FULL_LOW:
				PORTA = DIO_PORT_VALUE_FULL_LOW;
				break;
			case DIO_PORT_VALUE_FIRST_HALF_HIGH:
				PORTA |= DIO_PORT_VALUE_FIRST_HALF_HIGH;
				break;
			case DIO_PORT_VALUE_SECOND_HALF_HIGH:
				PORTA |= DIO_PORT_VALUE_SECOND_HALF_HIGH;
				break;
			default:
				LOC_ERRORSTATE = NOT_OK;
				break;
			}
				break;

		case PORT_B:
			switch (DIO_PORT_VALUE_) {

			case DIO_PORT_VALUE_FULL_HIGH:
				PORTB = DIO_PORT_VALUE_FULL_HIGH;
				break;
			case DIO_PORT_VALUE_FULL_LOW:
				PORTB = DIO_PORT_VALUE_FULL_LOW;
				break;
			case DIO_PORT_VALUE_FIRST_HALF_HIGH:
				PORTB |= DIO_PORT_VALUE_FIRST_HALF_HIGH;
				break;
			case DIO_PORT_VALUE_SECOND_HALF_HIGH:
				PORTB |= DIO_PORT_VALUE_SECOND_HALF_HIGH;
				break;
			default:
				LOC_ERRORSTATE = NOT_OK;
				break;
			}
				break;

		case PORT_C:
			switch (DIO_PORT_VALUE_) {

			case DIO_PORT_VALUE_FULL_HIGH:
				PORTC = DIO_PORT_VALUE_FULL_HIGH;
				break;
			case DIO_PORT_VALUE_FULL_LOW:
				PORTC = DIO_PORT_VALUE_FULL_LOW;
				break;
			case DIO_PORT_VALUE_FIRST_HALF_HIGH:
				PORTC |= DIO_PORT_VALUE_FIRST_HALF_HIGH;
				break;
			case DIO_PORT_VALUE_SECOND_HALF_HIGH:
				PORTC |= DIO_PORT_VALUE_SECOND_HALF_HIGH;
				break;
			default:
				LOC_ERRORSTATE = NOT_OK;
				break;
			}
				break;

		case PORT_D:
			switch (DIO_PORT_VALUE_) {

			case DIO_PORT_VALUE_FULL_HIGH:
				PORTD = DIO_PORT_VALUE_FULL_HIGH;
				break;
			case DIO_PORT_VALUE_FULL_LOW:
				PORTD = DIO_PORT_VALUE_FULL_LOW;
				break;
			case DIO_PORT_VALUE_FIRST_HALF_HIGH:
				PORTD |= DIO_PORT_VALUE_FIRST_HALF_HIGH;
				break;
			case DIO_PORT_VALUE_SECOND_HALF_HIGH:
				PORTD |= DIO_PORT_VALUE_SECOND_HALF_HIGH;
				break;
			default:
				LOC_ERRORSTATE = NOT_OK;
				break;
			}
				break;

		default:
			LOC_ERRORSTATE = NOT_OK;
			break;
		}
	}
	else if(FLAG_DefaultOrSetFromUser == FLAG_DefaultOrSetFromUser_HIGH){
		if(DIO_PORT_VALUE_>= 0 && DIO_PORT_VALUE_ <=255) {
			switch(PORT_) {

			case PORT_A:
				PORTA = DIO_PORT_VALUE_;
					break;

			case PORT_B:
				PORTB = DIO_PORT_VALUE_;
					break;

			case PORT_C:
				PORTC = DIO_PORT_VALUE_;
					break;

			case PORT_D:
				PORTD = DIO_PORT_VALUE_;
					break;

			default:
				LOC_ERRORSTATE = NOT_OK;
				break;
			}
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
	}
	else {
		LOC_ERRORSTATE = NOT_OK;
	}

	return (LOC_ERRORSTATE);
}


STD_ERROR DIO_GetPinValue(u8 PORT_, u8 P_, u8 *Pin_Value) {

	STD_ERROR LOC_ERRORSTATE = OK;

	switch(PORT_) {
	case PORT_A:
		if(P_ <= DIO_MAX_PIN_PER_PORT) {
			*Pin_Value = (((PINA)&(1<<P_)) >> (P_));
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;
	case PORT_B:
		if(P_ <= DIO_MAX_PIN_PER_PORT) {
			*Pin_Value = (((PINB)&(1<<P_)) >> (P_));
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;
	case PORT_C:
		if(P_ <= DIO_MAX_PIN_PER_PORT) {
			*Pin_Value = (((PINC)&(1<<P_)) >> (P_));
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;
	case PORT_D:
		if(P_ <= DIO_MAX_PIN_PER_PORT) {
			*Pin_Value = (((PIND)&(1<<P_)) >> (P_));
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;
	default:
		LOC_ERRORSTATE = NOT_OK;
		break;
	}
	return (LOC_ERRORSTATE);
}

STD_ERROR DIO_GetPortValue(u8 PORT_, u8 *Pin_Value) {

	STD_ERROR LOC_ERRORSTATE = OK;

	switch(PORT_) {
	case PORT_A:
		if(PORT_ <= DIO_MAX_PORT_NO) {
			*Pin_Value = PINA;
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;
	case PORT_B:
		if(PORT_ <= DIO_MAX_PORT_NO) {
			*Pin_Value = PINB;
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;
	case PORT_C:
		if(PORT_ <= DIO_MAX_PORT_NO) {
			*Pin_Value = PINC;
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;
	case PORT_D:
		if(PORT_ <= DIO_MAX_PORT_NO) {
			*Pin_Value = PIND;
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;
	default:
		LOC_ERRORSTATE = NOT_OK;
		break;
	}
	return (LOC_ERRORSTATE);
}

STD_ERROR DIO_GetPortDir(u8 PORT_, u8 *Port_Dir){

	STD_ERROR LOC_ERRORSTATE = OK;

	switch(PORT_) {
	case PORT_A:
		if(PORT_ <= DIO_MAX_PORT_NO) {
			*Port_Dir = DDRA;
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;
	case PORT_B:
		if(PORT_ <= DIO_MAX_PORT_NO) {
			*Port_Dir = DDRB;
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;
	case PORT_C:
		if(PORT_ <= DIO_MAX_PORT_NO) {
			*Port_Dir = DDRC;
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;
	case PORT_D:
		if(PORT_ <= DIO_MAX_PORT_NO) {
			*Port_Dir = DDRD;
		}
		else {
			LOC_ERRORSTATE = NOT_OK;
		}
		break;
	default:
		LOC_ERRORSTATE = NOT_OK;
		break;
	}
	return (LOC_ERRORSTATE);
}


