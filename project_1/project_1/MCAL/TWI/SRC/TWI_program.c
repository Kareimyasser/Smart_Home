/*
 * TWC_program.c
 *
 * Created: 3/16/2024 5:32:42 PM
 *  Author: Saed Abozied
 */ 
 
 
/*UTILES_LIB*/
#include"BIT_MATH.h"
#include"STD_TYPES.h"
/*TWC*/
#include"TWI_interface.h"
#include"TWI_register.h"
#include"TWI_private.h"



void TWI_voidInitMaster(void)
{
	TWBR_REG=12;
	CLR_BIT(TWSR_REG,TWPS1);
	CLR_BIT(TWSR_REG,TWPS0);
	
	SET_BIT(TWCR_REG,TWEN);
}




void TWI_voidSendStartCondition(void)
{
	SET_BIT(TWCR_REG,TWSTA);
	
	SET_BIT(TWCR_REG,TWINT);
	
	while(0==GET_BIT(TWCR_REG,TWINT));
	
	while(TWI_STATUS_VALUE != TWI_START_CONDITION_ACK);
}






void TWI_voidSendRepeatedStartCondition(void)
{
	SET_BIT(TWCR_REG,TWSTA);
	
	SET_BIT(TWCR_REG,TWINT);
	
	while(0==GET_BIT(TWCR_REG,TWINT));
	
	while(TWI_STATUS_VALUE != TWI_REP_START_CONDITION_ACK);
}



void TWI_voidSendStopCondition(void)
{
	SET_BIT(TWCR_REG, TWSTO);
	
	SET_BIT(TWCR_REG,TWINT);
}




void TWI_voidSendSlaveAddWithWrite(u8 copy_u8SlaveAdd)
{
	if(copy_u8SlaveAdd<128)
	{
		TWDR_REG=(copy_u8SlaveAdd<<1);
		CLR_BIT(TWDR_REG,TWD0);
		
		CLR_BIT(TWCR_REG,TWSTA);
		
		/*clr flag*/
		SET_BIT(TWCR_REG,TWINT);
		
		while(0==GET_BIT(TWCR_REG,TWINT));
		
		while(TWI_STATUS_VALUE != TWI_SLAVE_ADDRESS_WRITE_ACK);
		
	}
	else
	{
		//error
	}
}

void TWI_voidSendSlaveAddWithRead(u8 copy_u8SlaveAdd)
{
	if(copy_u8SlaveAdd<128)
	{
		TWDR_REG=(copy_u8SlaveAdd<<1);
		SET_BIT(TWDR_REG,TWD0);
		
		CLR_BIT(TWCR_REG,TWSTA);
		
		/*clr flag*/
		SET_BIT(TWCR_REG,TWINT);
		
		while(0==GET_BIT(TWCR_REG,TWINT));
		
		while(TWI_STATUS_VALUE != TWI_SLAVE_ADDRESS_READ_ACK);
		
	}
	else
	{
		//error
	}
}



void TWI_voidTransmitMasterDataByte(u8 copy_u8TxData)
{
	TWDR_REG=copy_u8TxData;
	
	/*clr flag*/
	SET_BIT(TWCR_REG,TWINT);
	
	while(0==GET_BIT(TWCR_REG,TWINT));
		
	while(TWI_STATUS_VALUE != TWI_MATER_DATA_TRANSMIT_ACK);
}




void TWI_voidRecieveMasterDataByteWithAch(u8* copy_pu8RxData)
{
	if(copy_pu8RxData!=NULL)
	{
		SET_BIT(TWCR_REG,TWEA);
		
		/*clr flag*/
		SET_BIT(TWCR_REG,TWINT);
		
		while(0==GET_BIT(TWCR_REG,TWINT));
		
		while(TWI_STATUS_VALUE != TWI_MATER_DATA_RECIEVE_ACK);
		
		*copy_pu8RxData=TWDR_REG;
		
		CLR_BIT(TWCR_REG,TWEA);
		
	}
	else
	{
		//error
	}
	
	
}






void TWI_voidRecieveMasterDataByteWithNAch(u8* copy_pu8RxData)
{
	if(copy_pu8RxData!=NULL)
	{
		
		
		
		/*clr flag*/
		SET_BIT(TWCR_REG,TWINT);
		
		while(0==GET_BIT(TWCR_REG,TWINT));
		
		while(TWI_STATUS_VALUE != TWI_MATER_DATA_RECIEVE_NACK);
		
		*copy_pu8RxData=TWDR_REG;
		

		
	}
	else
	{
		//error
	}
	
	
}