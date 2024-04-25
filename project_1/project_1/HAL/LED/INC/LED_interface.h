/*
 * LED_interface.h
 *
 * Created: 2/3/2024 8:08:41 PM
 *  Author: pc
 */ 

/*UTILES_LIB*/
#include"BIT_MATH.h"
#include"STD_TYPES.h"



#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#define LED_FORWARD_CONNECTION		1
#define LED_REVERSE_CONNECTION		2

				/************************API PIN PROTOTYPES************************/
void LED_voidInit	(u8 copy_u8LedPortId,u8 copy_u8LedPinId);
void LED_voidOn		(u8 copy_u8LedPortId,u8 copy_u8LedPinId,u8 copy_u8LedConnectionType);
void LED_voidOff	(u8 copy_u8LedPortId,u8 copy_u8LedPinId,u8 copy_u8LedConnectionType);
void LED_voidToggle	(u8 copy_u8LedPortId,u8 copy_u8LedPinId);



#endif /* LED_INTERFACE_H_ */