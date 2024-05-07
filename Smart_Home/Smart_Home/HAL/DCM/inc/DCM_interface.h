/*
 * DCM_interface.h
 *
 * Created: 15-Mar-2014 10:58:45 PM
 *  Author: Athar
 */ 


#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_


#define DCM_MOTOR_A                      1
#define DCM_MOTOR_B                      2

#define DCM_CLOCK_WISE                   1
#define DCM_COUNTER_CLOCK_WISE           2


void DCM_init(u8 motorId);
void DCM_on(u8 motorId, u8 motorDirection);
void DCM_onControlSpeed(u8 motorId, u8 motorDirection, u8 motorSpeed);
void DCM_off(u8 motorId);


#endif /* DCM_INTERFACE_H_ */