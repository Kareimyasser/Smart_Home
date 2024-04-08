/*
 * Choose_test.c
 *
 * Created: 3/24/2024 6:24:36 AM
 * Author : Karim
 */ 
#define F_CPU	16000000UL
#include <util/delay.h>

//include untiles
#include "STD_TYPES.h"
#include "BIT_MATH.h"

//MCAL
#include "DIO_INTERFACE.h"

//HAL
#include "KeyPad_config.h"
#include "KeyPad_interface.h"
#include "LCD_INTERFACE.h"
#include "LCD_CONFIG.h"


int main(void)
{
    LCD_voidInit();
	KPD_voidInit();
	LCD_voidDisplayStringDelay((u8*)" Welcome to your");
	LCD_voidSendCommand(Write_SecondLine);
	LCD_voidDisplayStringDelay((u8*)"   Smart Home");
	_delay_ms(1000);
	LCD_voidClear();
	LCD_voidDisplayString((u8*)"1-AC 2-light");
	LCD_voidSendCommand(Write_SecondLine);
	LCD_voidDisplayString((u8*)"3-temperature");
	u8	Local_copyKPDValue;
	u8	local_lightNum=KPD_Not_Pressed;
	u8 i=0;
	
    while (1) 
    {
		KPD_voidGetValue(&Local_copyKPDValue);
		if (Local_copyKPDValue != KPD_Not_Pressed)
		{	
			switch (Local_copyKPDValue)
			{
				case '1':
					LCD_voidClear();
					LCD_voidDisplayStringDelay((u8*)"AC Is On/off");
					LCD_voidSendCommand(Write_SecondLine);
					LCD_voidDisplayStringDelay((u8*)"Room Temp: 30c");
				break;
				
				case ('2'):
					
					LCD_voidClear();
					LCD_voidDisplayStringDelay((u8*)"Choose light to");
					LCD_voidSendCommand(Write_SecondLine);
					LCD_voidDisplayStringDelay((u8*)"control(1-6)");
					_delay_ms(30);
					light_choosing_KPD_WAIT:
					//busy wait for KPD
					while(local_lightNum== KPD_Not_Pressed)
					{
					//get KPD Light Number
					KPD_voidGetValue(&local_lightNum);
					}
											if (local_lightNum=='1')
					{
						LCD_voidClear();
						if (i==1)
						{
							LCD_voidDisplayStringDelay((u8*)"Light 1 is On");
							LCD_voidSendCommand(Write_SecondLine);
							LCD_voidDisplayStringDelay((u8*)"1-To Turn It Off");
						}
						else if (i==0)
						{
							LCD_voidDisplayStringDelay((u8*)"Light 1 is OFF");
							LCD_voidSendCommand(Write_SecondLine);
							LCD_voidDisplayStringDelay((u8*)"1-To Turn It On");
						}
						
					}
					
										else if (local_lightNum=='2')
					{
						LCD_voidClear();
						if (i==1)
						{
							LCD_voidDisplayStringDelay((u8*)"Light 2 is On");
							LCD_voidSendCommand(Write_SecondLine);
							LCD_voidDisplayStringDelay((u8*)"1-To Turn It Off");
						}
						else if (i==0)
						{
							LCD_voidDisplayStringDelay((u8*)"Light 2 is OFF");
							LCD_voidSendCommand(Write_SecondLine);
							LCD_voidDisplayStringDelay((u8*)"1-To Turn It On");
						}
						
					}
										else if (local_lightNum=='3')
					{
						LCD_voidClear();
						if (i==1)
						{
							LCD_voidDisplayStringDelay((u8*)"Light 3 is On");
							LCD_voidSendCommand(Write_SecondLine);
							LCD_voidDisplayStringDelay((u8*)"1-To Turn It Off");
						}
						else if (i==0)
						{
							LCD_voidDisplayStringDelay((u8*)"Light 3 is OFF");
							LCD_voidSendCommand(Write_SecondLine);
							LCD_voidDisplayStringDelay((u8*)"1-To Turn It On");
						}

					}
										else if (local_lightNum=='4')
					{
						LCD_voidClear();
						if (i==1)
						{
							LCD_voidDisplayStringDelay((u8*)"Light 4 is On");
							LCD_voidSendCommand(Write_SecondLine);
							LCD_voidDisplayStringDelay((u8*)"1-To Turn It Off");
						}
						else if (i==0)
						{
							LCD_voidDisplayStringDelay((u8*)"Light 4 is OFF");
							LCD_voidSendCommand(Write_SecondLine);
							LCD_voidDisplayStringDelay((u8*)"1-To Turn It On");
						}
						
					}
										else if (local_lightNum=='5')
					{
						LCD_voidClear();
						if (i==1)
						{
							LCD_voidDisplayStringDelay((u8*)"Light 5 is On");
							LCD_voidSendCommand(Write_SecondLine);
							LCD_voidDisplayStringDelay((u8*)"1-To Turn It Off");
						}
						else if (i==0)
						{
							LCD_voidDisplayStringDelay((u8*)"Light 5 is OFF");
							LCD_voidSendCommand(Write_SecondLine);
							LCD_voidDisplayStringDelay((u8*)"1-To Turn It On");
						}
						
					}
										else if (local_lightNum=='6')
					{
						LCD_voidClear();
						if (i==1)
						{
							LCD_voidDisplayStringDelay((u8*)"Light 6 is On");
							LCD_voidSendCommand(Write_SecondLine);
							LCD_voidDisplayStringDelay((u8*)"1-To Turn It Off");
						}
						else if (i==0)
						{
							LCD_voidDisplayStringDelay((u8*)"Light 6 is OFF");
							LCD_voidSendCommand(Write_SecondLine);
							LCD_voidDisplayStringDelay((u8*)"1-To Turn It On");
						}
						
					}
										else 
						{
							LCD_voidClear();
							LCD_voidDisplayStringDelay((u8*)"  Invalid Input");
							_delay_ms(1000);
							LCD_voidClear();
							LCD_voidDisplayStringDelay((u8*)"  please choose ");
							LCD_voidSendCommand(Write_SecondLine);
							LCD_voidDisplayStringDelay((u8*)"  from 1 to 6");
							_delay_ms(1000);
							
							//clear the local_lightNum to get the light number again
							local_lightNum = KPD_Not_Pressed;
							// go to the beginning of the loop to get the light number again
							goto light_choosing_KPD_WAIT;
						}
						local_lightNum =KPD_Not_Pressed;
				break;						
			}

		}
    }
}