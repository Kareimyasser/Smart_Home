/*
 * TWC_register.h
 *
 * Created: 3/16/2024 5:33:12 PM
 *  Author: Saed Abozied
 */ 
 
/*UTILES_LIB*/
#include"BIT_MATH.h"
#include"STD_TYPES.h"

#ifndef TWC_REGISTER_H_
#define TWC_REGISTER_H_

/*TWI Bit Rate Register*/
#define TWBR_REG	(*(volatile u8*)0x20)


/*TWI Control Register*/
#define TWCR_REG	(*(volatile u8*)0x56)
#define  TWINT		7
#define  TWEA		6
#define  TWSTA		5
#define  TWSTO		4
#define  TWWC		3
#define  TWEN		2
#define  TWIE		0

/*TWI Status Register*/
#define TWSR_REG	(*(volatile u8*)0x21)
#define  TWPS1		1
#define  TWPS0		0

/*TWI Data Register*/
#define TWDR_REG	(*(volatile u8*)0x23)
#define  TWD0		0

/*TWI (Slave) Address Register*/
#define TWAR_REG	(*(volatile u8*)0x22)

#endif /* TWC_REGISTER_H_ */