/*
 * SERVO_interface.h
 *
 * Created: 4/9/2024 1:25:44 PM
 *  Author: Saed Abozied
 */ 

/*UTILES_LIB*/
 #include"STD_TYPES.h"
 
 
#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_

#define SERVO_FREQUENCY_HZ	50

void SERVO_voidInit(u8 copy_u8PWMPortId,u8 copy_u8PWMPinId);
void SERVO_voidStartByAngle(f32 copy_f32ServoAngle);



#endif /* SERVO_INTERFACE_H_ */