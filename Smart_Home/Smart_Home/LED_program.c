/*
 * LEB_program.c
 *
 * Created: 2/3/2024 8:05:56 PM
 *  Author: Saed Abozied
 */ 
 
/*HAL*/
#include"LED_interface.h"

/*MCAL*/
#include "DIO_interface.h"

/*UTILES_LIB*/
#include"BIT_MATH.h"
#include"STD_TYPES.h"

void LED_voidInit	(u8 copy_u8LedPortId,u8 copy_u8LedPinId)
{
	DIO_voidSetPinDirection( copy_u8LedPortId,  copy_u8LedPinId, DIO_PIN_OUTPUT);
}


void LED_voidOn		(u8 copy_u8LedPortId,u8 copy_u8LedPinId,u8 copy_u8LedConnectionType)
{
	switch(copy_u8LedConnectionType)
	{
	case LED_FORWARD_CONNECTION:
		DIO_voidSetPinValue    ( copy_u8LedPortId,  copy_u8LedPinId, DIO_PIN_HIGH);
		break;
	
	case LED_REVERSE_CONNECTION:
		DIO_voidSetPinValue    ( copy_u8LedPortId,  copy_u8LedPinId, DIO_PIN_LOW);
		break;
	}
}
void LED_voidOff	(u8 copy_u8LedPortId,u8 copy_u8LedPinId,u8 copy_u8LedConnectionType)
{
	switch(copy_u8LedConnectionType)
	{
	case LED_FORWARD_CONNECTION	:
		DIO_voidSetPinValue    ( copy_u8LedPortId,  copy_u8LedPinId, DIO_PIN_LOW);
		break;
	
	case LED_REVERSE_CONNECTION	:
		DIO_voidSetPinValue    ( copy_u8LedPortId,  copy_u8LedPinId, DIO_PIN_HIGH);
		break;
	}
}
void LED_voidToggle	(u8 copy_u8LedPortId,u8 copy_u8LedPinId)
{
	 DIO_voidTogglePinValue ( copy_u8LedPortId,  copy_u8LedPinId);
}