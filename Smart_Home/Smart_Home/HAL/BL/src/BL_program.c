/*
 * BL_program.c
 *
 * Created: 4/3/2024 7:38:06 PM
 *  Author: Saed Abozied
 */ 
 
 /*UTILES_LIB*/
#include"BIT_MATH.h"
#include"STD_TYPES.h"

 /*MCAL*/
#include"UART_interface.h"

 /*HAL*/
#include"BL_interface.h"



void BL_voidInit(void)
{
	UART_voidInit();
	
}


void BL_voidTxChar(u8 copy_u8BlTxData)
{
	UART_voidTxChar(copy_u8BlTxData);
}



void BL_voidRxChar(u8* copy_pu8BlRxData)
{
	UART_voidRxChar(copy_pu8BlRxData);
	
}

BL_voidRxCharWithTimeout(u8* copy_pu8BlRxData)
{
	 UART_voidRxCharWithTimeout(copy_pu8BlRxData);
}


void BL_voidTxString(u8* copy_pu8BlTxString)
{
	UART_voidTxString(copy_pu8BlTxString);
}


void BL_voidRxString(u8* copy_pu8BlRxString)
{
	UART_voidRxString(copy_pu8BlRxString);
	
}