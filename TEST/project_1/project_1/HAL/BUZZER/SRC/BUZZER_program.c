/*
 * BUZZER_program.c
 *
 * Created: 2/3/2024 10:23:58 PM
 *  Author: pc
 */ 
/*HAL*/
#include"BUZZER_interface.h"

/*MCAL*/
#include"DIO_interface.h"

/*UTILES_LIB*/
#include"BIT_MATH.h"
#include"STD_TYPES.h"

void BUZZER_voidInit	(u8 copy_u8BuzzerPortId,u8 copy_u8BuzzerPinId)
{
	DIO_voidSetPinDirection(copy_u8BuzzerPortId,copy_u8BuzzerPinId,DIO_PIN_High);
}
void BUZZER_voidOn		(u8 copy_u8LBuzzerPortId,u8 copy_u8BuzzerPinId)
{

		DIO_voidSetPinValue    (copy_u8LBuzzerPortId,copy_u8BuzzerPinId, DIO_PIN_High);
}
void BUZZER_voidOff		(u8 copy_u8BuzzerPortId,u8 copy_u8BuzzerPinId)
{
		DIO_voidSetPinValue    (copy_u8BuzzerPortId,copy_u8BuzzerPinId, DIO_PIN_LOW);
}
void BUZZER_voidToggle	(u8 copy_u8BuzzerPortId,u8 copy_u8BuzzerPinId)
{
	 DIO_voidTogglePinValue (copy_u8BuzzerPortId,copy_u8BuzzerPinId);
}