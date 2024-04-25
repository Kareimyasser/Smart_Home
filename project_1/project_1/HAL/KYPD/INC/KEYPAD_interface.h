/*
 * KEYPAD_interface.h
 *
 * Created: 2/10/2024 7:53:22 PM
 *  Author: Saed Abozied
 */ 

#include"STD_TYPES.h"

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#define KEYPAD_NOT_PRESSED	0Xff


/****************************KEYPAD APIs**************************/
void KEYPAD_voidInit(void);
void KEYPAD_voidGetValue(u8* copy_pu8ReturnedValue);



#endif /* KEYPAD_INTERFACE_H_ */