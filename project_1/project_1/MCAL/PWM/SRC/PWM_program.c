/*
 * PWM_program.c
 *
 * Created: 4/9/2024 9:37:17 AM
 *  Author: Saed Abozied
 */ 

/*UTILES_LIB*/
#include"BIT_MATH.h"
#include"STD_TYPES.h"

/*TM0*/
#include"PWM_register.h"
#include"PWM_interface.h"
#include"PWM_private.h"


void PWM_voidInitChannel_0(void)
{
	/*Waveform Generation Mode>>Fast PWM*/
	SET_BIT(TCCR0_REG, WGM00);
	SET_BIT(TCCR0_REG, WGM01);
	
	
	/*Compare Match Output Mode>>Clear OC0 on compare match, set OC0 at TOP*/
	SET_BIT(TCCR0_REG, COM01);
	CLR_BIT(TCCR0_REG, COM00);
	
}
void PWM_voidGenerateChannel_0(u8 copy_u8DutyCycle)
{
	if(copy_u8DutyCycle<=100)
	{
		/*Calculating Duty for non inverting*/
		OCR0_REG=((copy_u8DutyCycle*256)/100)-1;
		
		/*Clock Select>>clk/64(From prescaler)*/
		SET_BIT(TCCR0_REG,CS00);
		SET_BIT(TCCR0_REG,CS01);
		CLR_BIT(TCCR0_REG,CS02);
	}
	else
	{
		//error 
	}
	
}


void PWM_voidInitChannel_1A(void)
{
	/*Waveform Generation Mode>>Fast PWM(channel A)*/
	SET_BIT(TCCR1B_REG, WGM13);
	SET_BIT(TCCR1B_REG, WGM12);
	SET_BIT(TCCR1A_REG, WGM11);
	CLR_BIT(TCCR1A_REG, WGM10);
	
	/*Compare Match Output Mode>>Clear OC1A/OC1B on compare match*/
	SET_BIT(TCCR1A_REG,COM1A1);
	CLR_BIT(TCCR1A_REG,COM1A0);
	
	
}



void PWM_voidGenerateChannel_1A(u16 copy_u16Frequency_hz,f32 copy_f32DutyCycle)
{
	if(copy_f32DutyCycle<=100)
	{
		/*Set freq by clkI/O/64 (From prescaler)*/
		ICR1_REG=((1000000UL/copy_u16Frequency_hz)/4)-1;
		
		/*Calculating Duty for non inverting*/
		OCR1A_REG=((copy_f32DutyCycle*(ICR1_REG+1))/100)-1;
		
		/*Clock Select>>clk/64(From prescaler)*/
		SET_BIT(TCCR1B_REG,CS10);
		SET_BIT(TCCR1B_REG,CS11);
		CLR_BIT(TCCR1B_REG,CS12);
		
	}
	else
	{
		//error 
	}
	
}