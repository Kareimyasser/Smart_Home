/*
 * TMR2_interface.h
 *
 * Created: 5/10/2024 2:51:21 AM
 *  Author: Karim
 */ 


#ifndef TMR2_INTERFACE_H_
#define TMR2_INTERFACE_H_

 /*UTILES_LIB*/
#include"STD_TYPES.h"

void TMR2_voidStart					(void);
void TMR2_voidStop					(void);
void TMR2_voidInit					(void);
void TMR2_SetCallBackOVF			(void (*copy_pFunAction)(void));
void TMR2_SetCallBackCTC			(void (*copy_pFunAction)(void));
void TMR2_clear_flag                 (void);
void TMR2_Reset_timer_value         (void);


#endif /* TMR2_INTERFACE_H_ */