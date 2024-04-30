/*
 * TWC_interface.h
 *
 * Created: 3/16/2024 5:33:28 PM
 *  Author: Saed Abozied
 */ 
/*UTILES_LIB*/
#include"BIT_MATH.h"
#include"STD_TYPES.h"

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

void TWI_voidInitMaster			(void);
void TWI_voidSendStartCondition(void);
void TWI_voidSendRepeatedStartCondition(void);
void TWI_voidSendStopCondition(void);
void TWI_voidSendSlaveAddWithWrite(u8 copy_u8SlaveAdd);
void TWI_voidSendSlaveAddWithRead(u8 copy_u8SlaveAdd);
void TWI_voidTransmitMasterDataByte(u8 copy_u8TxData);
void TWI_voidRecieveMasterDataByteWithAch(u8* copy_pu8RxData);
void TWI_voidRecieveMasterDataByteWithNAch(u8* copy_pu8RxData);

#endif /* TWC_INTERFACE_H_ */