/*
 * UART_register.h
 *
 * Created: 4/3/2024 7:36:38 PM
 *  Author: Saed Abozied
 */ 



 /*UTILES_LIB*/
#include"STD_TYPES.h"



#ifndef UART_REGISTER_H_
#define UART_REGISTER_H_


/*USART I/O Data Register*/
#define UDR_REG	(*(volatile u8*)0x2C)


/*USART Control and Status Register A*/
#define UCSRA_REG	(*(volatile u8*)0x2B)
#define RXC			7
#define UDRE		5
#define U2X			1


/*USART Control and Status Register B*/
#define UCSRB_REG	(*(volatile u8*)0x2A)
#define RXEN		4
#define TXEN		3
#define UCSZ2		2


/*USART Control and Status Register C*/
#define UCSRC_REG	(*(volatile u8*)0x40)
#define URSEL		7
#define UMSEL		6
#define UPM1		5
#define UPM0		4
#define USBS		3
#define UCSZ1		2
#define UCSZ0		1
#define UCPOL		0



/*USART Baud Rate Registers*/
#define UBRRL_REG	(*(volatile u8*)0x29)
#define UBRRH_REG	(*(volatile u8*)0x40)


#endif /* UART_REGISTER_H_ */