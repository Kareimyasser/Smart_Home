/*
 * KEYPAD_program.c
 *
 * Created: 2/10/2024 7:52:41 PM
 *  Author: Saed Abozied
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

/*include HAL*/
#include"KEYPAD_interface.h"
#include"KEYPAD_config.h"


/*include MCAL*/
#include"DIO_interface.h"


void KEYPAD_voidInit(void)
{
	//inti keypad rowa as inpts pins
	DIO_voidSetPinDirection(KEYPAD_ROW0_PORT,KEYPAD_ROW0_PIN,DIO_PIN_INPUT);
	DIO_voidSetPinDirection(KEYPAD_ROW1_PORT,KEYPAD_ROW1_PIN,DIO_PIN_INPUT);
	DIO_voidSetPinDirection(KEYPAD_ROW2_PORT,KEYPAD_ROW2_PIN,DIO_PIN_INPUT);
	DIO_voidSetPinDirection(KEYPAD_ROW3_PORT,KEYPAD_ROW3_PIN,DIO_PIN_INPUT);
	
	//inti keypad cols as outputs pins
	DIO_voidSetPinDirection(KEYPAD_COL0_PORT,KEYPAD_COL0_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(KEYPAD_COL1_PORT,KEYPAD_COL1_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(KEYPAD_COL2_PORT,KEYPAD_COL2_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(KEYPAD_COL3_PORT,KEYPAD_COL3_PIN,DIO_PIN_OUTPUT);
	
	//active pull up res for inpts pins
	DIO_voidActivePinPullUpResistance (KEYPAD_ROW0_PORT,KEYPAD_ROW0_PIN);
	DIO_voidActivePinPullUpResistance (KEYPAD_ROW1_PORT,KEYPAD_ROW1_PIN);
	DIO_voidActivePinPullUpResistance (KEYPAD_ROW2_PORT,KEYPAD_ROW2_PIN);
	DIO_voidActivePinPullUpResistance (KEYPAD_ROW3_PORT,KEYPAD_ROW3_PIN);
	
}

void KEYPAD_voidGetValue(u8* copy_pu8ReturnedValue)
{
	if(copy_pu8ReturnedValue!=NULL)
	{
		//case i didnt press anything on keypad
		*copy_pu8ReturnedValue=KEYPAD_NOT_PRESSED;
		
		u8 Local_u8ColsCounter;
		//matrics for cols port and pins
		u8 Local_u8ColsPorts[4]={KEYPAD_COL0_PORT,KEYPAD_COL1_PORT,KEYPAD_COL2_PORT,KEYPAD_COL3_PORT};
		u8 Local_u8ColsPins[4]={KEYPAD_COL0_PIN,KEYPAD_COL1_PIN,KEYPAD_COL2_PIN,KEYPAD_COL3_PIN};
		
		u8 Local_u8RowsCounter;
		//matrics for rows port and pins
		u8 Local_u8RowsPorts[4]={KEYPAD_ROW0_PORT,KEYPAD_ROW1_PORT,KEYPAD_ROW2_PORT,KEYPAD_ROW3_PORT};
		u8 Local_u8RowsPins[4]={KEYPAD_ROW0_PIN,KEYPAD_ROW1_PIN,KEYPAD_ROW2_PIN,KEYPAD_ROW3_PIN};
		
		u8 Local_u8RowValue;
		
		//keypad chars
		u8 Local_u8Keys[4][4]=KeyPAD_KEYS;
		
		for(Local_u8ColsCounter=0;Local_u8ColsCounter<4;Local_u8ColsCounter++)
		{
			//activate each colomns
			DIO_voidSetPinValue(Local_u8ColsPorts[Local_u8ColsCounter],Local_u8ColsPins[Local_u8ColsCounter],DIO_PIN_LOW );
			
			//read each row
			for(Local_u8RowsCounter=0;Local_u8RowsCounter<4;Local_u8RowsCounter++)
			{
				//read each row
				DIO_voidGetPinValue(Local_u8RowsPorts[Local_u8RowsCounter],Local_u8RowsPins[Local_u8RowsCounter],&Local_u8RowValue);
				//is pressed
				if(0==Local_u8RowValue)
				{
					//to make loop until i move my finger
					while(0==Local_u8RowValue)
					{
						DIO_voidGetPinValue(Local_u8RowsPorts[Local_u8RowsCounter],Local_u8RowsPins[Local_u8RowsCounter],&Local_u8RowValue);
						
					}
					
					*copy_pu8ReturnedValue=Local_u8Keys[Local_u8RowsCounter][Local_u8ColsCounter];
					return;
				}
				
				
				
			}
			
			//decativate current colomns
			DIO_voidSetPinValue(Local_u8ColsPorts[Local_u8ColsCounter],Local_u8ColsPins[Local_u8ColsCounter],DIO_PIN_High);
		}
		
	}
	else
	{
		//error
	}
	
	
}
	
	