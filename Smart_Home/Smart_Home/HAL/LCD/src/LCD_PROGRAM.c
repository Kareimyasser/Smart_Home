/*
 * LCD_PROGRAM.c
 *
 * Created: 3/12/2024 5:46:45 AM
 *  Author: Karim
 */ 

#define F_CPU	16000000UL
#include <util/delay.h>

//include utiles
#include "STD_TYPES.h"
#include "BIT_MATH.h"
//include MCAL
#include "DIO_interface.h"
//include HAL
#include "LCD_INTERFACE.h"
#include "LCD_PRIVATE.h"
#include "LCD_CONFIG.h"

void	LCD_voidInit(void)
{
	//Intialize LCD pins as output pins
	DIO_voidSetPinDirection(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_OUTPUT);
	
	_delay_ms(35);
	//set RS pin = 0	(command)
	DIO_voidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	
	//set RW pin = 0	(write)
	DIO_voidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	
	PRV_voidWriteHalfPort(0b0010);
	
	
	/* Enable Pulse *//* H => L */
	DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	
	DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	LCD_voidSendCommand(0b00101000);
	_delay_us(45);
	
	// Display on off Control (DisplayOn, Cursor on, Blink on)
	LCD_voidSendCommand(0b00001111);
	_delay_us(45);
	
	//Clear Display
	LCD_voidSendCommand(0b00000001);
	_delay_ms(2);
	
	// Set Entry Mode (Increment on, Shift off)
	LCD_voidSendCommand(0b00000110);
	
	
	
}

void	LCD_voidSendCommand(u8 copy_u8cmd)
{
	//set RS pin = 0	(command)
	DIO_voidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	
	//set RW pin = 0	(write)
	DIO_voidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	//Write The Most 4 Bits Of command On Data Pins
	PRV_voidWriteHalfPort(copy_u8cmd>>4);
	
	/* Enable Pulse *//* H => L */
	DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	
	//Write The Least 4 Bits Of Command On Data Pins
	PRV_voidWriteHalfPort(copy_u8cmd);
	
	/* Enable Pulse *//* H => L */
	DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	
}

void	LCD_voidDisplayChar(u8 copy_u8Data)
{
		//set RS pin = 1	(Data)
		DIO_voidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_HIGH);
		
		//set RW pin = 0	(write)
		DIO_voidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
		
		//Write The Most 4 Bits Of Data On Data Pins
		PRV_voidWriteHalfPort(copy_u8Data>>4);
		
		/* Enable Pulse *//* H => L */
		DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
		_delay_ms(1);
		DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
		
		//Write The Least 4 Bits Of Data On Data Pins
		PRV_voidWriteHalfPort(copy_u8Data);
		
		/* Enable Pulse *//* H => L */
		DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
		_delay_ms(1);
		DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
}

void LCD_voidDisplayString(u8* copy_pu8String)
{
	if(copy_pu8String!=NULL)
	{
		u8 local_u8Counter=0;
		while(copy_pu8String[local_u8Counter]!='\0')
		{
			LCD_voidDisplayChar(copy_pu8String[local_u8Counter]);
			local_u8Counter++;
		}
	}
	else
	{
		// return Error state
	}
}

void	LCD_voidDisplayStringDelay  (u8* copy_pu8StringDelay)
{
	{
		if(copy_pu8StringDelay!=NULL)
		{
			u8 local_u8Counter=0;
			
			while(copy_pu8StringDelay[local_u8Counter]!='\0')
			{
				
				LCD_voidDisplayChar(copy_pu8StringDelay[local_u8Counter]);
				local_u8Counter++;
				_delay_ms(50);
			}
			
		}
		else
		{
			
			// return Error state
		}
	}
}


void	LCD_voidDisplayNumber (u32 copy_u32Number)
{
	u8 Str[5];
	u8 length=0,rem,num;
	num	=	copy_u32Number;
	while (num!=0)
	{
		length++;
		num=num / 10;
	}
	for (u8 i=0;i<length;i++)
	{
		rem= copy_u32Number % 10;
		copy_u32Number=copy_u32Number / 10;
		Str[(length-(i+1))]=rem +'0';
	}
	Str[length]='\0';
	
	
	u8 local_u8Counter=0;
	while(Str[local_u8Counter]!='\0')
	{
		LCD_voidDisplayChar(Str[local_u8Counter]);
		local_u8Counter++;
	}
	
}


void	LCD_voidClear (void)

{
	//set RS pin = 0	(command)
	DIO_voidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	
	//set RW pin = 0	(write)
	DIO_voidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	//Write The Most 4 Bits Of command On Data Pins
	PRV_voidWriteHalfPort(0b0000>>4);
	
	/* Enable Pulse *//* H => L */
	DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	
	//Write The Least 4 Bits Of Command On Data Pins
	PRV_voidWriteHalfPort(0b0001);
	
	/* Enable Pulse *//* H => L */
	DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
}


void	LCD_voidShiftCursor (u8 copy_u8ShifttingDirection)
{
	//set RS pin = 0	(command)
	DIO_voidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	
	//set RW pin = 0	(write)
	DIO_voidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	//Write The Most 4 Bits Of command On Data Pins
	PRV_voidWriteHalfPort(copy_u8ShifttingDirection>>4);
	
	/* Enable Pulse *//* H => L */
	DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	
	//Write The Least 4 Bits Of Command On Data Pins
	PRV_voidWriteHalfPort(copy_u8ShifttingDirection);
	
	/* Enable Pulse *//* H => L */
	DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
}


void LCD_voidShiftDisplay(u8 copy_u8ShifttingDirection)
{
		DIO_voidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
		
		//set RW pin = 0	(write)
		DIO_voidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
		
		//Write The Most 4 Bits Of command On Data Pins
		PRV_voidWriteHalfPort(copy_u8ShifttingDirection>>4);
		
		/* Enable Pulse *//* H => L */
		DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
		_delay_ms(1);
		DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
		
		//Write The Least 4 Bits Of Command On Data Pins
		PRV_voidWriteHalfPort(copy_u8ShifttingDirection);
		
		/* Enable Pulse *//* H => L */
		DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
		_delay_ms(1);
		DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
}


void LCD_voidGoTOSpecificPosition(u8 copy_u8LineNumber,u8 copy_u8Position)
{
	if(copy_u8Position<40)
	{
		//cmnd to return cursor to home position
		LCD_voidSendCommand(0b00000010);
		
		switch(copy_u8LineNumber)
		{
			case LCD_LINE_ONE:
			
			LCD_voidSendCommand(0b10000000|copy_u8Position);
		
			
			break;
			
			case LCD_LINE_TWO:

			LCD_voidSendCommand(0b10000000|(copy_u8Position+0x40));

			break;
		}

		
	}
	else
	{
		//error state
	}
	
	
	
}


static	void PRV_voidWriteHalfPort(u8 copy_u8Value)
{
	if (1== GET_BIT(copy_u8Value,0))
	{
		DIO_voidSetPinValue(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_HIGH);
	}
	else
		{
			DIO_voidSetPinValue(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_LOW);
		}
	if (1== GET_BIT(copy_u8Value,1))
	{
		DIO_voidSetPinValue(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_HIGH);
	}
	else
		{
		DIO_voidSetPinValue(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_LOW);
		}
	if (1== GET_BIT(copy_u8Value,2))
	{
		DIO_voidSetPinValue(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_HIGH);
	}
	else
		{
		DIO_voidSetPinValue(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_LOW);
		}
	if (1== GET_BIT(copy_u8Value,3))
	{
		DIO_voidSetPinValue(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_HIGH);
	}
	else
		{
		DIO_voidSetPinValue(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_LOW);
		}
}

void LCD_voidPwdEffect()
{
	//this function replaces the pwd char with * to hide pwd after
	//some delay 
	_delay_ms(200);
	LCD_voidCursorShift(LEFT);
	LCD_voidDisplayChar('*');
}
