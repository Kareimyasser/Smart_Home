/*
 * LCD_program.c
 *
 * Created: 2/9/2024 9:33:42 PM
 *  Author: Saed Abozied
 */ 
 
 #define F_CPU 16000000UL
 #include<util/delay.h>
 
/*UTILES_LIB*/
#include"BIT_MATH.h"
#include"STD_TYPES.h"

/*MCAL*/
//Dio
#include"DIO_interface.h"
//LCD
#include"LCD_interface.h"
#include"LCD_private.h"
#include"LCD_config.h"

void LCD_voidInit(void)
{
	//intialize pins as outputs
	DIO_voidSetPinDirection(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_E_PORT,LCD_E_PIN,DIO_PIN_OUTPUT);
	
	DIO_voidSetPinDirection(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_OUTPUT);
	
	
	
	_delay_ms(35);

	DIO_voidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	DIO_voidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	//define 4 bit mode and font size and number of lines
	PRV_voidWriteHalfPort(0b0010);
	
	//enable
	DIO_voidSetPinValue    (LCD_E_PORT,LCD_E_PIN,DIO_PIN_High);
	_delay_ms(1);
	DIO_voidSetPinValue    (LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
	
	LCD_voidSendCommand(0b00101000);
	_delay_us(45);
	
	
	
	//display on,cursor on,blink on
	LCD_voidSendCommand(0b00001111);
	_delay_us(45);
	
	//clear display
	LCD_voidSendCommand(0b00000001);
	_delay_ms(2);
	
	//increament on ,shift off
	LCD_voidSendCommand(0b00000110);

	
}

void LCD_voidSendCommand(u8 copy_u8Command)
{
	//set RS low>> 0(comand)
	DIO_voidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	
	//set RW low>> 0(write)
	DIO_voidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	//send most 4 bits on data pins
	PRV_voidWriteHalfPort(copy_u8Command>>4);
	
	//enable
	DIO_voidSetPinValue    (LCD_E_PORT,LCD_E_PIN,DIO_PIN_High);
	_delay_ms(1);
	DIO_voidSetPinValue    (LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
	
	//send least 4 bits on data pins
	PRV_voidWriteHalfPort(copy_u8Command);
	
	//enable
	DIO_voidSetPinValue    (LCD_E_PORT,LCD_E_PIN,DIO_PIN_High);
	_delay_ms(1);
	DIO_voidSetPinValue    (LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
	
}

void LCD_voidDisplayChar(u8 copy_u8Data)
{
	//set RS low>> 1(Data)
	DIO_voidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_High);
	
	//set RW low>> 0(write)
	DIO_voidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	//send most 4 bits on data pins
	PRV_voidWriteHalfPort(copy_u8Data>>4);
	
	//enable
	DIO_voidSetPinValue    (LCD_E_PORT,LCD_E_PIN,DIO_PIN_High);
	_delay_ms(1);
	DIO_voidSetPinValue    (LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
	
	//send least 4 bits on data pins
	PRV_voidWriteHalfPort(copy_u8Data);
	
	//enable
	DIO_voidSetPinValue    (LCD_E_PORT,LCD_E_PIN,DIO_PIN_High);
	_delay_ms(1);
	DIO_voidSetPinValue    (LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
}


void LCD_voidDisplayString(u8* copy_pu8String)
{
	if(copy_pu8String != NULL)
	{
		u8 Local_u8Counter=0;
		
		//loop until reach null char
		while(copy_pu8String[Local_u8Counter] != '\0')
		{
			LCD_voidDisplayChar(copy_pu8String[Local_u8Counter]);
			_delay_ms(50);
			Local_u8Counter++;
		}
		
	}
	
}


void LCD_voidDisplayNumber(u8 copy_u8Number)
{

	
	u8 Local_u8NumToStringArr[LCD_MAX_DISPLAY_CHAR];
	u8 Local_u8Iterator,Local_u8NumReminder,Local_u8NumLen=0,Local_u8NumTemp;
	
	//dectect number digits
	Local_u8NumTemp= copy_u8Number;
	while (Local_u8NumTemp != 0)
	{
		Local_u8NumLen++;
		Local_u8NumTemp /= 10;
	}
	
	
	//transform num to string
	for (Local_u8Iterator = 0; Local_u8Iterator < Local_u8NumLen; Local_u8Iterator++)
	{
		Local_u8NumReminder = copy_u8Number % 10;
		copy_u8Number = copy_u8Number / 10;
		
		Local_u8NumToStringArr[Local_u8NumLen - (Local_u8Iterator + 1)] = Local_u8NumReminder + '0';
	}
	
	//add null char at the end of string
	Local_u8NumToStringArr[Local_u8NumLen] = '\0';
	
	//print number after transformation to string
	LCD_voidDisplayString(Local_u8NumToStringArr);

}

void LCD_voidClear(void)
{
	//send this cmnd to clr the display
	LCD_voidSendCommand(0b00000001);
}

void LCD_voidShift(u8 copy_u8ShifttingDirection)
{
	switch(copy_u8ShifttingDirection)
	{
		//move display to right
		case LCD_SHIFT_DIS_RIGHT:
		LCD_voidSendCommand(0b00011100);
		break;
		
		//move display to left
		case LCD_SHIFT_DIS_LEFT:
		LCD_voidSendCommand(0b00011000);
		break;
		
	}
	
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



static void PRV_voidWriteHalfPort(u8 copy_u8Value)
{
	if(1 == GET_BIT(copy_u8Value,0))
	{
	DIO_voidSetPinValue    (LCD_D4_PORT, LCD_D4_PIN,DIO_PIN_High);
	}
	else
	{
	DIO_voidSetPinValue    (LCD_D4_PORT, LCD_D4_PIN,DIO_PIN_LOW);
	}
	if(1 == GET_BIT(copy_u8Value,1))
	{
	DIO_voidSetPinValue    (LCD_D5_PORT, LCD_D5_PIN,DIO_PIN_High);
	}
	else
	{
	DIO_voidSetPinValue    (LCD_D5_PORT, LCD_D5_PIN,DIO_PIN_LOW);
	}
	if(1==GET_BIT(copy_u8Value,2))
	{
	DIO_voidSetPinValue    (LCD_D6_PORT, LCD_D6_PIN,DIO_PIN_High);
	}
	else
	{
		DIO_voidSetPinValue    (LCD_D6_PORT, LCD_D6_PIN,DIO_PIN_LOW);
	}
	if(1==GET_BIT(copy_u8Value,3))
	{
	DIO_voidSetPinValue    (LCD_D7_PORT, LCD_D7_PIN,DIO_PIN_High);
	}
	else
	{
	DIO_voidSetPinValue    (LCD_D7_PORT, LCD_D7_PIN,DIO_PIN_LOW);
	}	
}