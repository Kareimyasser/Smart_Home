/*
 * BL_interface.h
 *
 * Created: 4/3/2024 7:37:47 PM
 *  Author: Saed Abozied
 */ 


 /*UTILES_LIB*/
#include"STD_TYPES.h"



#ifndef BL_INTERFACE_H_
#define BL_INTERFACE_H_

/********************************UART_APIs********************************/


void BL_voidInit		(void);
void BL_voidTxChar		(u8 copy_u8BlTxData);
void BL_voidRxChar		(u8* copy_pu8BlRxData);
void BL_voidTxString	(u8* copy_pu8BlTxString);
void BL_voidRxString	(u8* copy_pu8BlRxString);



#endif /* BL_INTERFACE_H_ */