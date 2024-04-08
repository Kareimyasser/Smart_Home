/*
 * library.c
 *
 * Created: 3/20/2024 7:57:10 PM
 *  Author: Karim
 */ 

//UTILIS	
#include "STD_TYPES.h"
#include "BIT_MATH.h"

//MCAL
#include "DIO_INTERFACE.h"

//HAL
#include "KeyPad_config.h"
#include "KeyPad_interface.h"



void	KPD_voidInit(void)
{
	//Setting Columns to output
	DIO_voidSetPinDirection(KPD_C0_Port,KPD_C0_Pin,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(KPD_C1_Port,KPD_C1_Pin,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(KPD_C2_Port,KPD_C2_Pin,DIO_PIN_OUTPUT);
	
	
	//Setting Rows To Input
	DIO_voidSetPinDirection(KPD_R0_Port,KPD_R0_Pin,DIO_PIN_INPUT);
	DIO_voidSetPinDirection(KPD_R1_Port,KPD_R1_Pin,DIO_PIN_INPUT);
	DIO_voidSetPinDirection(KPD_R2_Port,KPD_R2_Pin,DIO_PIN_INPUT);
	DIO_voidSetPinDirection(KPD_R3_Port,KPD_R3_Pin,DIO_PIN_INPUT);
	
	//Setting Rows For Pull UP
	DIO_voidActivePinInPullUpResistance(KPD_R0_Port,KPD_R0_Pin);
	DIO_voidActivePinInPullUpResistance(KPD_R1_Port,KPD_R1_Pin);
	DIO_voidActivePinInPullUpResistance(KPD_R2_Port,KPD_R2_Pin);
	DIO_voidActivePinInPullUpResistance(KPD_R3_Port,KPD_R3_Pin);
}


void	KPD_voidGetValue(u8* copy_pu8value)
{
	if (copy_pu8value != NULL)
	{
		u8	Local_u8ColsPort[4]={KPD_C0_Port,KPD_C1_Port,KPD_C2_Port};
		u8	Local_u8ColsPins[4]={KPD_C0_Pin,KPD_C1_Pin,KPD_C2_Pin};
									 
		u8	Local_u8RowsPort[4]={KPD_R0_Port,KPD_R1_Port,KPD_R2_Port,KPD_R3_Port};
		u8	Local_u8RowsPins[4]={KPD_R0_Pin,KPD_R1_Pin,KPD_R2_Pin,KPD_R3_Pin};
		u8	Local_Keys[4][4]   =KPD_Keys;
		
		u8	Local_u8ColsCounter,Local_u8RowsCounter;
		u8	Local_u8RowValue;
		
		*copy_pu8value = KPD_Not_Pressed;
		//LOOP Columns
		for (Local_u8ColsCounter=0 ; Local_u8ColsCounter<4 ; Local_u8ColsCounter++)
		{
			//Activate Each Column
			DIO_voidSetPinValue(Local_u8ColsPort[Local_u8ColsCounter] , Local_u8ColsPins[Local_u8ColsCounter],DIO_PIN_LOW);
			
			//LOOP Rows
			for(Local_u8RowsCounter=0 ; Local_u8RowsCounter<4 ; Local_u8RowsCounter++)
			{
				//Get Row Pin Value
				DIO_voidGetPinValue(Local_u8RowsPort[Local_u8RowsCounter] ,Local_u8RowsPins[Local_u8RowsCounter], &Local_u8RowValue );
				
				// Is Pressed ?
				if (0==Local_u8RowValue)
				{
					//Busy wait for button release
					while(0==Local_u8RowValue)
					{
						DIO_voidGetPinValue(Local_u8RowsPort[Local_u8RowsCounter] ,Local_u8RowsPins[Local_u8RowsCounter], &Local_u8RowValue );
					}
					//return value
					*copy_pu8value = Local_Keys[Local_u8RowsCounter][Local_u8ColsCounter];
					return;
				}
			}
			DIO_voidSetPinValue(Local_u8ColsPort[Local_u8ColsCounter],Local_u8ColsPins[Local_u8ColsCounter],DIO_PIN_HIGH);
		}
	}
	else
	{
		
	}
}