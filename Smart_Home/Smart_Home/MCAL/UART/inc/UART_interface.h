/*
 * UART_interface.h
 *
 * Created: 4/3/2024 7:36:56 PM
 *  Author: Saed Abozied
 */ 



 /*UTILES_LIB*/
#include"STD_TYPES.h"




#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#define UART_TIMEOUT_MS	 100

/********************************UART_APIs********************************/


void UART_voidInit		(void);
void UART_voidTxChar	(u8 copy_u8TxData);
void UART_voidRxChar	(u8* copy_pu8RxData);
void UART_voidRxCharWithTimeout(u8* copy_pu8RxData);
void UART_voidTxString	(u8* copy_pu8TxString);
void UART_voidRxString	(u8* copy_pu8RxString);

#endif /* UART_INTERFACE_H_ */