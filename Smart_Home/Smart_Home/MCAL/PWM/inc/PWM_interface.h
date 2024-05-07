/*
 * PWM_interface.h
 *
 * Created: 4/9/2024 9:28:05 AM
 *  Author: Saed Abozied
 */ 


 /*UTILES_LIB*/
#include"STD_TYPES.h"

#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_


/*************************************************PWM_APIs*************************************************/

void PWM_voidInitChannel_0		(void);
void PWM_voidGenerateChannel_0	(u8 copy_u8DutyCycle);

void PWM_voidInitChannel_1A		(void);
void PWM_voidInitChannel_1B     (void);
void PWM_voidGenerateChannel_1A	(u16 copy_u16Frequency_hz,f32 copy_f32DutyCycle);
void PWM_voidGenerateChannel_1B (u16 copy_u16Frequency_hz,f32 copy_f32DutyCycle);

#endif /* PWM_INTERFACE_H_ */