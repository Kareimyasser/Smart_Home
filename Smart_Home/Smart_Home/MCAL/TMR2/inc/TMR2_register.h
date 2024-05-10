/*
 * TMR2_register.h
 *
 * Created: 5/10/2024 2:50:36 AM
 *  Author: Karim
 */ 

#include"STD_TYPES.h"
#ifndef TMR2_REGISTER_H_
#define TMR2_REGISTER_H_

/*Timer/Counter Control Register*/
#define TCCR2_REG   (*(volatile u8*)0x45)
#define  WGM20      6
#define  COM21      5
#define  COM20      4
#define  WGM21      3
#define  CS22       2
#define  CS21       1
#define  CS20       0

/*Timer/Counter Register*/
#define TCNT2_REG   (*(volatile u8*)0x44)

/*Output Compare Register*/
#define OCR2_REG    (*(volatile u8*)0x43)

/*Timer/Counter Interrupt Mask Register*/
#define TIMSK2_REG   (*(volatile u8*)0x59)
#define  TOIE2      6
#define  OCIE2      7


/*Timer/Counter Interrupt Flag Register*/
#define TIFR2_REG    (*(volatile u8*)0x58)
#define  TOV2       6
#define  OCF2       7



#endif /* TMR2_REGISTER_H_ */