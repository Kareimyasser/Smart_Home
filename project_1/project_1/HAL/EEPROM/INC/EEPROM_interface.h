/*
 * EEPROM_interface.h
 *
 * Created: 3/22/2024 5:12:35 PM
 *  Author: Saed Abozied
 */ 

/*UTILES_LIB*/
#include"BIT_MATH.h"
#include"STD_TYPES.h"


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

#define EEPROM_MAX_PAGE_SIZE	 8

void EEPROM_voidInit(void);
void EEPROM_voidWriteByte(u16 copy_u16WordAdress,u8 copy_u8Data);
void EEPROM_voidReadByte(u16 copy_u16WordAdress,u8* copy_pu8Data);

void EEPROM_voidWritePage(u16 copy_u16WordAdress,u8* copy_pu8TxData);
void EEPROM_voidSequentialRead(u16 copy_u16WordAdress,u16 copy_u18NumOfDataBytes,u8* copy_pu8RxData);

#endif /* EEPROM_INTERFACE_H_ */