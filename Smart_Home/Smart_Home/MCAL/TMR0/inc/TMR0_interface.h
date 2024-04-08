/*
 * TMR0_interface.h
 *
 * Created: 4/4/2024 12:02:25 PM
 *  Author: Saed Abozied
 */ 


#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_

 /*UTILES_LIB*/
#include"STD_TYPES.h"

/*****************************************TMR0_APIs*****************************************/
void TMR0_voidInit					(void);
void TMR0_voidStart					(void);
void TMR0_voidStop					(void);
void TMR0_SetCallBackOVF			(void (*copy_pFunAction)(void));
void TMR0_SetCallBackCTC			(void (*copy_pFunAction)(void));
void TMR0_voidSetDelay_ms_UsingCTC	(u16 copy_u16Delay_ms);
#endif /* TMR0_INTERFACE_H_ */