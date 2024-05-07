/*
 * SERVO_program.c
 *
 * Created: 4/9/2024 1:26:09 PM
 *  Author: Saed Abozied
 */ 

/*UTILES_LIB*/
 #include"BIT_MATH.h"
 #include"STD_TYPES.h"
 
 /*HAL*/
 #include"SERVO_interface.h"

/*MCAL*/
 #include"DIO_interface.h"
 #include"PWM_interface.h"
 
 
void SERVO_voidInit(u8 copy_u8PWMPortId,u8 copy_u8PWMPinId)
{
	//Init pin as an outputpin
	DIO_voidSetPinDirection(copy_u8PWMPortId,copy_u8PWMPinId,DIO_PIN_OUTPUT);
	
	//init PWM(channel1A)
	PWM_voidInitChannel_1A();
}


void SERVO_voidStartByAngle(f32 copy_f32ServoAngle)
{
	
	f32 Local_f32Dutycycle;
	
	//calculate servo duty
	Local_f32Dutycycle=((2.5*copy_f32ServoAngle)+675)/90;
	
	PWM_voidGenerateChannel_1B(SERVO_FREQUENCY_HZ,Local_f32Dutycycle);
}