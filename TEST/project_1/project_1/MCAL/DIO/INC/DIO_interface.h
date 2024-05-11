/*
 * DIO_interface.h
 *
 * Created: 2/2/2024 6:54:33 PM
 *  Author: Saed Abozied
 */ 


#include"STD_TYPES.h"

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/*macros id*/
#define DIO_PORTA	0
#define DIO_PORTB	1
#define DIO_PORTC	2
#define DIO_PORTD	3

/*macros for pin direction*/
#define DIO_PIN_INPUT	0
#define DIO_PIN_OUTPUT	1

/*macros for pin id*/
#define DIO_PIN0	0
#define DIO_PIN1	1
#define DIO_PIN2	2
#define DIO_PIN3	3
#define DIO_PIN4	4
#define DIO_PIN5	5
#define DIO_PIN6	6
#define DIO_PIN7	7

/*macros for pin values*/
#define DIO_PIN_LOW		0
#define DIO_PIN_High	1	


				/************************API PIN PROTOTYPES************************/
void DIO_voidSetPinDirection(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection);
void DIO_voidSetPinValue    (u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue);
void DIO_voidGetPinValue    (u8 copy_u8PortId, u8 copy_u8PinId, u8* copy_pu8PinValue);
void DIO_voidTogglePinValue (u8 copy_u8PortId, u8 copy_u8PinId);
void DIO_voidActivePinPullUpResistance (u8 copy_u8PortId, u8 copy_u8PinId);



				/************************API PORT PROTOTYPES************************/
void DIO_voidSetPortDirection(u8 copy_u8PortId, u8 copy_u8PinDirection);
void DIO_voidSetPortValue    (u8 copy_u8PortId, u8 copy_u8PinValue);
void DIO_voidGetPortValue    (u8 copy_u8PortId, u8* copy_pu8PinValue);
void DIO_voidTogglePortValue (u8 copy_u8PortId);
void DIO_voidActivePortPullUpResistance (u8 copy_u8PortId);




#endif /* DIO_INTERFACE_H_ */