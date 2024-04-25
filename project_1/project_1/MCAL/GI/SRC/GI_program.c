/*
 * GI_program.c
 *
 * Created: 2/23/2024 11:05:23 PM
 *  Author: Saed Abozied
 */ 
 
 
 /*MCAL(GI.h)*/
#include"GI_interface.h"
#include"GI_register.h"


void GI_voidEnable(void)
{
	SET_BIT(SREG_REG,I);
}

void GI_voidDisable(void)
{
	CLR_BIT(SREG_REG,I);
	
}