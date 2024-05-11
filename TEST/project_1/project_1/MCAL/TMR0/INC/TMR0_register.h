/*
 * TMR0_register.h
 *
 * Created: 4/4/2024 12:02:05 PM
 *  Author: Saed Abozied
 */ 


 /*UTILES_LIB*/
#include"STD_TYPES.h"

#ifndef TMR0_REGISTER_H_
#define TMR0_REGISTER_H_


/*Timer/Counter Control Register*/
#define TCCR0_REG	(*(volatile u8*)0x53)
#define  WGM00		6
#define  COM01		5
#define  COM00		4
#define  WGM01		3
#define  CS02		2
#define  CS01		1
#define  CS00		0

/*Timer/Counter Register*/
#define TCNT0_REG	(*(volatile u8*)0x52)

/*Output Compare Register*/
#define OCR0_REG	(*(volatile u8*)0x5C)

/*Timer/Counter Interrupt Mask Register*/
#define TIMSK_REG	(*(volatile u8*)0x59)
#define  TOIE0		0
#define  OCIE0		1


/*Timer/Counter Interrupt Flag Register*/
#define TIFR_REG	(*(volatile u8*)0x58)
#define  TOV0		0
#define  OCF0		1


#endif /* TMR0_REGISTER_H_ */