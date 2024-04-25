/*
 * BUZZER_interface.h
 *
 * Created: 2/3/2024 10:24:15 PM
 *  Author: pc
 */ 
#include"STD_TYPES.h"

#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_


				/************************API PIN PROTOTYPES************************/
void BUZZER_voidInit	(u8 copy_u8BuzzerPortId,u8 copy_u8BuzzerPinId);
void BUZZER_voidOn		(u8 copy_u8LBuzzerPortId,u8 copy_u8BuzzerPinId);
void BUZZER_voidOff	(u8 copy_u8BuzzerPortId,u8 copy_u8BuzzerPinId);
void BUZZER_voidToggle	(u8 copy_u8BuzzerPortId,u8 copy_u8BuzzerPinId);




#endif /* BUZZER_INTERFACE_H_ */