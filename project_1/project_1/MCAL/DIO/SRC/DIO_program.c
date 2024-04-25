/*
 * DIO_program.c
 *
 * Created: 2/2/2024 6:53:51 PM
 *  Author: Saed Abozied
 */ 

/*UTILES_LIB*/
#include"BIT_MATH.h"
#include"STD_TYPES.h"

/*MCAL*/
#include"DIO_interface.h"

#include"DIO_register.h"




void DIO_voidSetPinDirection(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection)
{
	switch(copy_u8PortId)
	{
		case DIO_PORTA:
		switch(copy_u8PinDirection)
		{
			case(DIO_PIN_OUTPUT):
			SET_BIT(DDRA_REG,copy_u8PinId);
			break;
			
			case(DIO_PIN_INPUT):
			CLR_BIT(DDRA_REG,copy_u8PinId);			
			break;
			
		}
		break;
		case DIO_PORTB:
		switch(copy_u8PinDirection)
		{
			case(DIO_PIN_OUTPUT):
			SET_BIT(DDRB_REG,copy_u8PinId);
			break;
			
			case(DIO_PIN_INPUT):
			CLR_BIT(DDRB_REG,copy_u8PinId);			
			break;
			
		}
		
		break;
		case DIO_PORTC:
		switch(copy_u8PinDirection)
		{
			case(DIO_PIN_OUTPUT):
			SET_BIT(DDRC_REG,copy_u8PinId);
			break;
			
			case(DIO_PIN_INPUT):
			CLR_BIT(DDRC_REG,copy_u8PinId);			
			break;
			
		}
		break;
		case DIO_PORTD:
		switch(copy_u8PinDirection)
		{
			case(DIO_PIN_OUTPUT):
			SET_BIT(DDRD_REG,copy_u8PinId);
			break;
			
			case(DIO_PIN_INPUT):
			CLR_BIT(DDRD_REG,copy_u8PinId);			
			break;
			
		}
		break;
	}
	
	
	
	
	
}

void DIO_voidSetPinValue    (u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue)
{
	if((copy_u8PortId<4)&&(copy_u8PinId<8)&&(copy_u8PinValue<3))
	{
		switch(copy_u8PortId)
	{
		case DIO_PORTA:
		switch(copy_u8PinValue)
		{
			case(DIO_PIN_High):
			SET_BIT(PORTA_REG,copy_u8PinId);
			break;
			
			case(DIO_PIN_LOW):
			CLR_BIT(PORTA_REG,copy_u8PinId);			
			break;
			
		}
		break;
		case DIO_PORTB:
		switch(copy_u8PinValue)
		{
			case(DIO_PIN_High):
			SET_BIT(PORTB_REG,copy_u8PinId);
			break;
			
			case(DIO_PIN_LOW):
			CLR_BIT(PORTB_REG,copy_u8PinId);			
			break;
			
		}
		break;
		case DIO_PORTC:
		switch(copy_u8PinValue)
		{
			case(DIO_PIN_High):
			SET_BIT(PORTC_REG,copy_u8PinId);
			break;
			
			case(DIO_PIN_LOW):
			CLR_BIT(PORTC_REG,copy_u8PinId);			
			break;
			
		}
		break;
		case DIO_PORTD:
		switch(copy_u8PinValue)
		{
			case(DIO_PIN_High):
			SET_BIT(PORTD_REG,copy_u8PinId);
			break;
			
			case(DIO_PIN_LOW):
			CLR_BIT(PORTD_REG,copy_u8PinId);			
			break;
			
		}
		break;
		
	}
		
	}
	else
	{
		//do nothing
	}

	
	
	
	
	
}
void DIO_voidGetPinValue    (u8 copy_u8PortId, u8 copy_u8PinId, u8* copy_pu8PinValue)
{
	if((copy_u8PortId<4)&&(copy_u8PinId<8)&&(copy_pu8PinValue!=NULL))
	{
		switch(copy_u8PortId)
	{
		case DIO_PORTA:
		*copy_pu8PinValue=GET_BIT(PINA_REG,copy_u8PinId);
		break;
		case DIO_PORTB:
		*copy_pu8PinValue=GET_BIT(PINB_REG,copy_u8PinId);
		break;
		case DIO_PORTC:
		*copy_pu8PinValue=GET_BIT(PINC_REG,copy_u8PinId);
		break;
		case DIO_PORTD:
		*copy_pu8PinValue=GET_BIT(PIND_REG,copy_u8PinId);
		break;
		

		
	}
	}
	else
	{
		//do nothing
	}
}

void DIO_voidTogglePinValue  (u8 copy_u8PortId, u8 copy_u8PinId)
{
	if((copy_u8PortId<4)&&(copy_u8PinId<8))
	{
		switch(copy_u8PortId)
	{
		case DIO_PORTA:
		TOG_BIT(PORTA_REG,copy_u8PinId);
		break;
		case DIO_PORTB:
		TOG_BIT(PORTB_REG,copy_u8PinId);
		break;
		case DIO_PORTC:
		TOG_BIT(PORTC_REG,copy_u8PinId);
		break;
		case DIO_PORTD:
		TOG_BIT(PORTD_REG,copy_u8PinId);
		break;
		

		
	}
	}
	else
	{
		//do nothing
	}
}
void DIO_voidActivePinPullUpResistance (u8 copy_u8PortId, u8 copy_u8PinId)
{
	if((copy_u8PortId<4)&&(copy_u8PinId<8))
	{
		switch(copy_u8PortId)
	{
		case DIO_PORTA:
		SET_BIT(PORTA_REG,copy_u8PinId);
		break;
		case DIO_PORTB:
		SET_BIT(PORTB_REG,copy_u8PinId);
		break;
		case DIO_PORTC:
		SET_BIT(PORTC_REG,copy_u8PinId);
		break;
		case DIO_PORTD:
		SET_BIT(PORTD_REG,copy_u8PinId);
		break;
		

		
	}
	}
	else
	{
		//do nothing
	}
	
}