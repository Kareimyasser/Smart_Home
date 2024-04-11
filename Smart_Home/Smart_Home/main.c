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
#include "TMR0_interface.h"

//HAL
#include "KeyPad_config.h"
#include "KeyPad_interface.h"
#include "LCD_INTERFACE.h"
#include "LCD_CONFIG.h"
#include "LED_interface.h"
#include "GI_interface.h"

void LCD_DisplayTemp();
void WelcomeScreen();
void HomeScreen();
void action(void);
void getKPD(void);
void KPD_Interface(void);
void Reset_AllKPDValues();

	u8	Local_copyKPDValue=KPD_Not_Pressed;
	u8	local_lightNum=KPD_Not_Pressed;
	u8 local_lightStatus=KPD_Not_Pressed;
	u8 led_status =0;

int main(void)
{
	/*enable global interrupt*/
	GI_voidEnable();
	/*intializing timer by selecting mode and enable timer interrupt overflow and saving perload values*/
	TMR0_voidInit();
	//initialize the LEDs(1-5)
	LED_voidInit(DIO_PORTA,DIO_PIN0);
	LED_voidInit(DIO_PORTA,DIO_PIN1);
	LED_voidInit(DIO_PORTA,DIO_PIN2);
	LED_voidInit(DIO_PORTA,DIO_PIN3);
	LED_voidInit(DIO_PORTD,DIO_PIN2);
	//initialize the LCD
    LCD_voidInit();
	//initialize the KPD
	KPD_voidInit();
	//display the welcome screen
	WelcomeScreen();
	//display the home screen
	HomeScreen();

	//local variables

	
	
}
KPD_Interface()
	{
    while (1) 
		{
			TMR0_SetCallBackCTC(&LCD_DisplayTemp);
			TMR0_voidStart();
			//busy wait for KPD
			while (Local_copyKPDValue== KPD_Not_Pressed)
			{
			KPD_voidGetValue(&Local_copyKPDValue);
			}
			TMR0_voidStop();
				
				switch (Local_copyKPDValue)
				{
					case ('1'):

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
					
						TMR0_SetCallBackCTC(&LCD_DisplayTemp);
						TMR0_voidStart();
						//busy wait for KPD
						while(local_lightNum== KPD_Not_Pressed)
						{
						//get KPD Light Number
						KPD_voidGetValue(&local_lightNum);
						}
						TMR0_voidStop();
												if (local_lightNum=='1')
						
						{
							DIO_voidGetPinValue(DIO_PORTA,DIO_PIN0,&led_status);
							LCD_voidClear();
							if (led_status ==1)
							{
								LCD_voidDisplayStringDelay((u8*)"Light 1 is On");
								LCD_voidSendCommand(Write_SecondLine);
								LCD_voidDisplayStringDelay((u8*)"1-To Turn It Off");
								while(local_lightStatus== KPD_Not_Pressed)
								{
									KPD_voidGetValue(&local_lightStatus);
								}
									if (local_lightStatus=='1')
									{
									LED_voidOff(DIO_PORTA,DIO_PIN0,LED_FORWARD_CONNECTION);
									}
								Reset_AllKPDValues();
								HomeScreen();
								
								
							}
							else if (led_status ==0)
							{
								LCD_voidDisplayStringDelay((u8*)"Light 1 is OFF");
								LCD_voidSendCommand(Write_SecondLine);
								LCD_voidDisplayStringDelay((u8*)"1-To Turn It On");
								while(local_lightStatus== KPD_Not_Pressed)
								{
								KPD_voidGetValue(&local_lightStatus);
								}
								if (local_lightStatus=='1')
									{
										LED_voidOn(DIO_PORTA,DIO_PIN0,LED_FORWARD_CONNECTION);
									}
								Reset_AllKPDValues();
								HomeScreen();

								
							}
							
						}
						
											else if (local_lightNum=='2')
						{
							DIO_voidGetPinValue(DIO_PORTA,DIO_PIN1,&led_status);
							LCD_voidClear();
							if (led_status ==1)
							{
								LCD_voidDisplayStringDelay((u8*)"Light 2 is On");
								LCD_voidSendCommand(Write_SecondLine);
								LCD_voidDisplayStringDelay((u8*)"1-To Turn It Off");
								while(local_lightStatus== KPD_Not_Pressed)
								{
									KPD_voidGetValue(&local_lightStatus);
								}
									if (local_lightStatus=='1')
									{
									LED_voidOff(DIO_PORTA,DIO_PIN1,LED_FORWARD_CONNECTION);
									}
								local_lightStatus=KPD_Not_Pressed;
								HomeScreen();

							}
							else if (led_status ==0)
							{
								LCD_voidDisplayStringDelay((u8*)"Light 2 is OFF");
								LCD_voidSendCommand(Write_SecondLine);
								LCD_voidDisplayStringDelay((u8*)"1-To Turn It On");
								while(local_lightStatus== KPD_Not_Pressed)
								{
								KPD_voidGetValue(&local_lightStatus);
								}
								if (local_lightStatus=='1')
									{
										LED_voidOn(DIO_PORTA,DIO_PIN1,LED_FORWARD_CONNECTION);
									}
								local_lightStatus=KPD_Not_Pressed;
								HomeScreen();
							}
							
						}
											else if (local_lightNum=='3')
						{
							DIO_voidGetPinValue(DIO_PORTA,DIO_PIN2,&led_status);
							LCD_voidClear();
							if (led_status ==1)
							{
								LCD_voidDisplayStringDelay((u8*)"Light 3 is On");
								LCD_voidSendCommand(Write_SecondLine);
								LCD_voidDisplayStringDelay((u8*)"1-To Turn It Off");
								while(local_lightStatus== KPD_Not_Pressed)
								{
									KPD_voidGetValue(&local_lightStatus);
								}
								
									if (local_lightStatus=='1')
									{
									LED_voidOff(DIO_PORTA,DIO_PIN2,LED_FORWARD_CONNECTION);
									}
								local_lightStatus=KPD_Not_Pressed;
								HomeScreen();
							}
							else if (led_status ==0)
							{
								LCD_voidDisplayStringDelay((u8*)"Light 3 is OFF");
								LCD_voidSendCommand(Write_SecondLine);
								LCD_voidDisplayStringDelay((u8*)"1-To Turn It On");
								while(local_lightStatus== KPD_Not_Pressed)
								{
								KPD_voidGetValue(&local_lightStatus);
								}
								
								if (local_lightStatus=='1')
									{
										LED_voidOn(DIO_PORTA,DIO_PIN2,LED_FORWARD_CONNECTION);
									}
								local_lightStatus=KPD_Not_Pressed;
								HomeScreen();
							}

						}
											else if (local_lightNum=='4')
						{
							DIO_voidGetPinValue(DIO_PORTA,DIO_PIN3,&led_status);
							LCD_voidClear();
							if (led_status ==1)
							{
								LCD_voidDisplayStringDelay((u8*)"Light 4 is On");
								LCD_voidSendCommand(Write_SecondLine);
								LCD_voidDisplayStringDelay((u8*)"1-To Turn It Off");
								while(local_lightStatus== KPD_Not_Pressed)
								{
									KPD_voidGetValue(&local_lightStatus);
								}
								
									if (local_lightStatus=='1')
									{
									LED_voidOff(DIO_PORTA,DIO_PIN3,LED_FORWARD_CONNECTION);
									}
								local_lightStatus=KPD_Not_Pressed;
								HomeScreen();
							}
							else if (led_status ==0)
							{
								LCD_voidDisplayStringDelay((u8*)"Light 4 is OFF");
								LCD_voidSendCommand(Write_SecondLine);
								LCD_voidDisplayStringDelay((u8*)"1-To Turn It On");
								while(local_lightStatus== KPD_Not_Pressed)
								{
								KPD_voidGetValue(&local_lightStatus);
								}
								
								if (local_lightStatus=='1')
									{
										LED_voidOn(DIO_PORTA,DIO_PIN3,LED_FORWARD_CONNECTION);
									}
								local_lightStatus=KPD_Not_Pressed;
								HomeScreen();
							}
							
						}
											else if (local_lightNum=='5')
						{
							DIO_voidGetPinValue(DIO_PORTD,DIO_PIN2,&led_status);
							LCD_voidClear();
							if (led_status ==1)
							{
								LCD_voidDisplayStringDelay((u8*)"Light 5 is On");
								LCD_voidSendCommand(Write_SecondLine);
								LCD_voidDisplayStringDelay((u8*)"1-To Turn It Off");
								while(local_lightStatus== KPD_Not_Pressed)
								{
									KPD_voidGetValue(&local_lightStatus);
								}
								
									if (local_lightStatus=='1')
									{
									LED_voidOff(DIO_PORTD,DIO_PIN2,LED_FORWARD_CONNECTION);
									}
								local_lightStatus=KPD_Not_Pressed;
								HomeScreen();
							}
							else if (led_status ==0)
							{
								LCD_voidDisplayStringDelay((u8*)"Light 5 is OFF");
								LCD_voidSendCommand(Write_SecondLine);
								LCD_voidDisplayStringDelay((u8*)"1-To Turn It On");
								while(local_lightStatus== KPD_Not_Pressed)
								{
								KPD_voidGetValue(&local_lightStatus);
								}
								
								if (local_lightStatus=='1')
									{
										LED_voidOn(DIO_PORTD,DIO_PIN2,LED_FORWARD_CONNECTION);
									}
								local_lightStatus=KPD_Not_Pressed;
								HomeScreen();
							}
							
							
						}
						//if the user choose light 6 (DIMMER LED)
											else if (local_lightNum=='6')
						{
							LCD_voidClear();
							if (led_status ==1)
							{
								LCD_voidDisplayStringDelay((u8*)"Light 6 is On");
								LCD_voidSendCommand(Write_SecondLine);
								LCD_voidDisplayStringDelay((u8*)"1-To Turn It Off");
							}
							else if (led_status ==0)
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
							
							}
							local_lightNum =KPD_Not_Pressed;
							Local_copyKPDValue=KPD_Not_Pressed;
							break;						
				}

			
		}
	}

void WelcomeScreen()
{
	LCD_voidDisplayStringDelay((u8*)" Welcome to your");
	LCD_voidSendCommand(Write_SecondLine);
	LCD_voidDisplayStringDelay((u8*)"   Smart Home");
	_delay_ms(1000);
}


void HomeScreen()
{
	LCD_voidClear();
	LCD_voidDisplayString((u8*)"1-AC 2-light");
	LCD_voidSendCommand(Write_SecondLine);
	LCD_voidDisplayString((u8*)"3-temperature");
	KPD_Interface();
	
}


void LCD_DisplayTemp()
{
	u8 local_KPDIdleValue = KPD_Not_Pressed;
	
	// TMR0_voidStop();
	 LCD_voidClear();
	LCD_voidDisplayStringDelay((u8*)"Temp: 30c");
	LCD_voidSendCommand(Write_SecondLine);
	LCD_voidDisplayStringDelay((u8*)"0-go to home");
		do {
		KPD_voidGetValue(&local_KPDIdleValue);
	} while (local_KPDIdleValue != '0');
	HomeScreen();

	
}

void Reset_AllKPDValues()
{
	Local_copyKPDValue=KPD_Not_Pressed;
	local_lightNum=KPD_Not_Pressed;
	local_lightStatus=KPD_Not_Pressed;
}


void action()
{
	LED_voidToggle(DIO_PORTA,DIO_PIN0);
}

