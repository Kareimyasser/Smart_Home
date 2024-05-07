/*
 * PWM_register.h
 *
 * Created: 4/9/2024 9:23:44 AM
 *  Author: Saed Abozied
 */ 




 /*UTILES_LIB*/
#include"STD_TYPES.h"


#ifndef PWM_REGISTER_H_
#define PWM_REGISTER_H_


/**************************************************TMR0***************************************************/

// /*Timer/Counter Control Register*/
// #define TCCR0_REG	(*(volatile u8*)0x53)
// #define  WGM00		6
// #define  COM01		5
// #define  COM00		4
// #define  WGM01		3
// #define  CS02		2
// #define  CS01		1
// #define  CS00		0

// /*Timer/Counter Register*/
// #define TCNT0_REG	(*(volatile u8*)0x52)

// /*Output Compare Register*/
// #define OCR0_REG	(*(volatile u8*)0x5C)

// /*Timer/Counter Interrupt Mask Register*/
// #define TIMSK_REG	(*(volatile u8*)0x59)
// #define  TOIE0		0
// #define  OCIE0		1


// /*Timer/Counter Interrupt Flag Register*/
// #define TIFR_REG	(*(volatile u8*)0x58)
// #define  TOV0		0
// #define  OCF0		1


/**************************************************TMR1***************************************************/


/*Timer/Counter1 Control Register A*/
#define TCCR1A_REG	(*(volatile u8*)0x4F)
#define  COM1A1		7
#define  COM1A0		6
#define  COM1B1		5
#define  COM1B0		4
#define  WGM11		1
#define  WGM10		0


/*Timer/Counter1 Control Register B*/
#define TCCR1B_REG	(*(volatile u8*)0x4E)
#define  WGM13		4
#define  WGM12		3
#define  CS12		2
#define  CS11		1
#define  CS10		0

/*Timer/Counter1*/
#define TCNT1_REG	(*(volatile u16*)0x4C)


/*Output Compare Register 1 A*/
#define OCR1A_REG	(*(volatile u16*)0x4A)
 
/*Output Compare Register 1 B*/
#define OCR1B_REG	(*(volatile u16*)0x48) 


/*Input Capture Register 1*/
#define ICR1_REG	(*(volatile u16*)0x46)


#endif /* PWM_REGISTER_H_ */