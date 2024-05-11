/*
 * UART_program.c
 *
 * Created: 4/3/2024 7:37:16 PM
 *  Author: Saed Abozied
 */ 


 /*UTILES_LIB*/
#include"BIT_MATH.h"
#include"STD_TYPES.h"
#define F_CPU 16000000UL
#include <util/delay.h>

 /*MCAL*/
#include"UART_register.h"
#include"UART_interface.h"


void UART_voidInit(void)
{
	/*Double the USART Transmission Speed>>Disable*/
	CLR_BIT(UCSRA_REG,U2X);
	
	/*USART Baud Rate Register>> set buadrate to 9600 when using 16UL clock & dis double speed*/
	UBRRL_REG=103;
	
	u8 Local_u8InitVar=0x00;
	
	/*Enable accessing UCSRC_REG*/
	SET_BIT(Local_u8InitVar,URSEL);
	
	/*USART Mode Select>>Asynchronous Operation*/
	CLR_BIT(Local_u8InitVar,UMSEL);
	
	/*Parity Mode>>Disabled*/
	CLR_BIT(Local_u8InitVar,UPM1);
	CLR_BIT(Local_u8InitVar,UPM0);
	
	/*Stop Bit Select>>1-bit*/
	CLR_BIT(Local_u8InitVar,USBS);
	
	/*Character Size(Data size)>>8-bit*/
	CLR_BIT(UCSRB_REG,UCSZ2);
	SET_BIT(Local_u8InitVar,UCSZ1);
	SET_BIT(Local_u8InitVar,UCSZ0);
	
	/*Clock Polarity>>Disable*/
	CLR_BIT(Local_u8InitVar,UCPOL);
	
	UCSRC_REG=Local_u8InitVar;
	
	/*Receiver Enable>>Enable*/
	SET_BIT(UCSRB_REG,RXEN);
	
	/*Transmitter Enable>>Enable*/
	SET_BIT(UCSRB_REG,TXEN);
	
	
}






void UART_voidTxChar(u8 copy_u8TxData)
{
	/*write data to data register*/
	UDR_REG=copy_u8TxData;
	
	/*busy wait for data moved from data register to shift register*/
	while(0==GET_BIT(UCSRA_REG,UDRE));
	
}




void UART_voidRxChar(u8* copy_pu8RxData)
{
	if(copy_pu8RxData!=NULL)
	{
		/*busy wait for unread data in data register*/
		while(0==GET_BIT(UCSRA_REG,RXC));
		
		/*Read data to data register*/
		*copy_pu8RxData=UDR_REG;
		
	}
	else
	{
		//error state
	}
}

void UART_voidTxString	(u8* copy_pu8TxString)
{
	
	if(copy_pu8TxString!=NULL)
	{
		/*Init counter*/
		u8 Local_u8Counter=0;
		
		/*loop until Null char*/
		while( copy_pu8TxString[Local_u8Counter] != '\0')
		{
			/*send data[i]*/
			UART_voidTxChar(copy_pu8TxString[Local_u8Counter]);
			
			/*increase counter*/
			Local_u8Counter++;
			
		}
		
	}
	else
	{
		//error state
	}
	
	
}

void UART_voidRxString	(u8* copy_pu8RxString)
{
	if(copy_pu8RxString!=NULL)
	{
		/*Init counter*/
		u8 Local_u8Counter=0;
		
		while(1)
		{
			/*read data[i]*/
			UART_voidRxChar(&copy_pu8RxString[Local_u8Counter]);
			
			if(copy_pu8RxString[Local_u8Counter]=='#')
			{
				/*break loop if '#' recieved*/
				break;
			}
			else
			{
				/*increase counter if not*/
				Local_u8Counter++;
				
			}
		}
		
		/*replace '#' with Null char*/
		copy_pu8RxString[Local_u8Counter]='\0';
		
	}
	else
	{
		//error state
	}
	
}

void UART_voidRxCharWithTimeout(u8* copy_pu8RxData)
{
	u16 Local_u16TimeoutCounter=0;
	if(copy_pu8RxData!=NULL)
	{
		/*busy wait for unread data in data register*/
		while(0==GET_BIT(UCSRA_REG,RXC))
		{
			if(Local_u16TimeoutCounter>=UART_TIMEOUT_MS)
			{
				return 0;
			}
			_delay_ms(1);
			Local_u16TimeoutCounter++;
		}
		/*Read data to data register*/
		*copy_pu8RxData=UDR_REG;

	}
	else
	{

	}
}