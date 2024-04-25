/*
 * EEPROM_program.c
 *
 * Created: 3/22/2024 5:13:19 PM
 *  Author: Saed Abozied
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

/*UTILES_LIB*/
#include"BIT_MATH.h"
#include"STD_TYPES.h"

//MCAL
/*TWC*/
#include"TWI_interface.h"

//HAL
/*EEPROM*/
#include"EEPROM_interface.h"
#include"EEPROM_private.h"

void EEPROM_voidInit(void)
{
	TWI_voidInitMaster();
}
void EEPROM_voidWriteByte(u16 copy_u16WordAdress,u8 copy_u8Data)
{
	u8 Local_u8DeviceAddress = ( copy_u16WordAdress>>8)|EEPROM_FIXED_ADDRESS;
	TWI_voidSendStartCondition();
	TWI_voidSendSlaveAddWithWrite(Local_u8DeviceAddress);
	TWI_voidTransmitMasterDataByte((u8)copy_u16WordAdress);
	TWI_voidTransmitMasterDataByte(copy_u8Data);
	TWI_voidSendStopCondition();
	_delay_ms(5);
	
	
	
}

	void EEPROM_voidWritePage(u16 copy_u16WordAdress,u8* copy_pu8TxData)
	{
		if(copy_pu8TxData!=NULL)
		{
			u8 Local_u8WordCounter,Local_u8DeviceAddress = ( copy_u16WordAdress>>8)|EEPROM_FIXED_ADDRESS;
			TWI_voidSendStartCondition();
			TWI_voidSendSlaveAddWithWrite(Local_u8DeviceAddress);
			TWI_voidTransmitMasterDataByte((u8)copy_u16WordAdress);
			
			for(Local_u8WordCounter=0;Local_u8WordCounter<EEPROM_MAX_PAGE_SIZE;Local_u8WordCounter++)
			{
				TWI_voidTransmitMasterDataByte(copy_pu8TxData[Local_u8WordCounter]);
					
			}
			TWI_voidSendStopCondition();
			_delay_ms(5);
		}
		else
		{
			//error state
		}
		
		
	}

void EEPROM_voidReadByte(u16 copy_u16WordAdress,u8* copy_pu8Data)
{
	if(copy_pu8Data!=NULL)
	{
		u8 Local_u8DeviceAddress = ( copy_u16WordAdress>>8)|EEPROM_FIXED_ADDRESS;
		TWI_voidSendStartCondition();
		TWI_voidSendSlaveAddWithWrite(Local_u8DeviceAddress);
		TWI_voidTransmitMasterDataByte((u8)copy_u16WordAdress);
		TWI_voidSendRepeatedStartCondition();
		TWI_voidSendSlaveAddWithRead(Local_u8DeviceAddress);
		TWI_voidRecieveMasterDataByteWithNAch(copy_pu8Data);
		TWI_voidSendStopCondition();
		_delay_ms(5);
		
	}
	else
	{
		//error
	}
	
	
}

void EEPROM_voidSequentialRead(u16 copy_u16WordAdress,u16 copy_u18NumOfDataBytes,u8* copy_pu8RxData)
{
	if((copy_pu8RxData !=NULL)&&copy_u18NumOfDataBytes<512)
	{
		u8 Local_u8DeviceAddress = ( copy_u16WordAdress>>8)|EEPROM_FIXED_ADDRESS;
		u16 Local_u16BytesCounter;
		TWI_voidSendStartCondition();
		TWI_voidSendSlaveAddWithWrite(Local_u8DeviceAddress);
		TWI_voidTransmitMasterDataByte((u8)copy_u16WordAdress);
		TWI_voidSendRepeatedStartCondition();
		TWI_voidSendSlaveAddWithRead(Local_u8DeviceAddress);
		
		for(Local_u16BytesCounter=0;Local_u16BytesCounter<copy_u18NumOfDataBytes-1;Local_u16BytesCounter++)
		{
			TWI_voidRecieveMasterDataByteWithAch(&copy_pu8RxData[Local_u16BytesCounter]);
			
		}
		
		TWI_voidRecieveMasterDataByteWithNAch(&copy_pu8RxData[copy_u18NumOfDataBytes-1]);
		TWI_voidSendStopCondition();
		_delay_ms(5);
	}
	else
	{
		//error state
	}


}