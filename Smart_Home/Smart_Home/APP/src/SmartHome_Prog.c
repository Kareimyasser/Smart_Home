/*
 * Choose_test.c
 *
 * Created: 3/24/2024 6:24:36 AM
 * Author : Karim yasser,Saed Abozied
 */
#define F_CPU 16000000UL
#include <util/delay.h>

// include untiles
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// MCAL
#include "DIO_INTERFACE.h"
#include "TMR0_interface.h"
#include "tmr0_register.h"
#include "GI_interface.h"
#include "PWM_interface.h"
#include "UART_interface.h"
#include "ADC_interface.h"

// HAL
#include "KeyPad_config.h"
#include "KeyPad_interface.h"
#include "LCD_INTERFACE.h"
#include "LCD_CONFIG.h"
#include "LED_interface.h"
#include "BUZZER_interface.h"
#include "EEPROM_interface.h"
#include "SERVO_interface.h"
#include "BL_interface.h"
#include "SmartHome.h"




#define HOME_MAX_NUMBER_OF_TRIALS	  			3
#define HOME_USER_NAME_AND_PASS_MAX_LENGTh		8
#define HOME_MAX_NUM_OF_LOCAL_USER				15

#define HOME_LOCAL_ADMIN						1
#define HOME_LOCAL_USER							2
#define HOME_REMOTE_ADMIN						3
#define HOME_REMOTE_USER						4
#define HOME_LOGIN_FAILED						5

#define HOME_LOCAL_ACCESS						1
#define HOME_REMOTE_ACCESS						2


u8 Local_copyKPDValue = KPD_Not_Pressed;
u8 local_lightNum = KPD_Not_Pressed;
u8 local_lightStatus = KPD_Not_Pressed;
u8 led_status = 0;
u8 local_KPDIdleValue = KPD_Not_Pressed;


u8 global_accessType = accessPermited;




void APP_init(void)
{
    HOME_voidInit();
	
    ADC_voidInit(ADC_REFERENCE_AVCC);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN0,DIO_PIN_INPUT);
	
    // display the welcome screen
    WelcomeScreen();
	LCD_voidClear();
	
	u8 testusername[8]={"11111111"};
	u8 testuserpass[8]={"22222222"};
	u8 testadminname[8]={"12345678"};
	u8 testadminpass[8]={"12345678"};
	u8 usertype;	
	
	EEPROM_voidWritePage(304,&testusername[0]);
	EEPROM_voidWritePage(312,&testuserpass[0]);
	EEPROM_voidWritePage(240,&testadminname[0]);
	EEPROM_voidWritePage(248,&testadminpass[0]);
	
	HOME_voidCheckUserAndPass(HOME_REMOTE_ACCESS,&usertype);
	






}



void HOME_voidInit(void)
{
	EEPROM_voidInit();
	
    // initialize the LCD
    LCD_voidInit();
	
	// initialize the KPD
    KPD_voidInit();
	
    // initialize the Bluetooth
	BL_voidInit();
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN1,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN0,DIO_PIN_INPUT);
    //enable global interrupt
    GI_voidEnable();
    //intializing timer by selecting mode and enable timer interrupt overflow and saving perload values
    TMR0_voidInit();
    // initialize the LEDs(1-5)
    LED_voidInit(DIO_PORTD, DIO_PIN3);
    LED_voidInit(DIO_PORTA, DIO_PIN1);
    LED_voidInit(DIO_PORTA, DIO_PIN2);
    LED_voidInit(DIO_PORTA, DIO_PIN3);
    LED_voidInit(DIO_PORTD, DIO_PIN2);



	
	//check alarm 
}


void HOME_voidLocalGetUserAndPass(u8* copy_pu8LocalUserName,u8* copy_pu8LocalUserPass)
{
	if((copy_pu8LocalUserName!=NULL)&&(copy_pu8LocalUserPass!=NULL))
	{
			
		u8 Local_u8UserNameLengthCounter,Local_u8UserPassCounter;
	
		//dis request for use name and pass
		LCD_voidClear();
		LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,0);
		LCD_voidDisplayString((u8 *)"Please Enter User");
		LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,0);
		LCD_voidDisplayString((u8 *)"Name&Password");
		_delay_ms(1000);
	
		//dis request for user name
		LCD_voidClear();
		LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,0);
		LCD_voidDisplayString((u8 *)"User Name:");
	
		//loop for 8 digits user name
		for(Local_u8UserNameLengthCounter=0;Local_u8UserNameLengthCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8UserNameLengthCounter++)
		{
		
		
			do
			{
				KPD_voidGetValue(&copy_pu8LocalUserName[Local_u8UserNameLengthCounter]);
			
			}while(copy_pu8LocalUserName[Local_u8UserNameLengthCounter]== KPD_Not_Pressed);
		
			LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,Local_u8UserNameLengthCounter);
			LCD_voidDisplayChar(copy_pu8LocalUserName[Local_u8UserNameLengthCounter]);
		}
	
		//display request for pass
		LCD_voidClear();
		LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,0);
		LCD_voidDisplayString((u8 *)"PASSWORD:");
	
		//loop for 8 digits user pass
			for(Local_u8UserPassCounter=0;Local_u8UserPassCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8UserPassCounter++)
			{
				do
				{
					KPD_voidGetValue(&copy_pu8LocalUserPass[Local_u8UserPassCounter]);
				
				}while(copy_pu8LocalUserPass[Local_u8UserPassCounter]==KPD_Not_Pressed);
			
				LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,Local_u8UserPassCounter);
				LCD_voidDisplayChar(copy_pu8LocalUserPass[Local_u8UserPassCounter]);
			}
	}
	else
	{
		//error massage
	}
			
	
		
}



void HOME_voidRemoteGetUserAndPass(u8* copy_pu8RemoteUserName,u8* copy_pu8RemoteUserPass)
{
	if((copy_pu8RemoteUserName!=NULL)&&(copy_pu8RemoteUserPass!=NULL))
	{
	
		u8 Local_u8UserNameLengthCounter=0,Local_u8UserPassCounter=0;
	
		//dis request for use name and pass
		BL_voidTxString	("Please Enter User Name & Password ");
		BL_voidTxString("\n");
	
		//dis request for user name
		BL_voidTxString	("User Name:");
		BL_voidTxChar('\n');
	
		//loop for 8 digits user name
		for(Local_u8UserNameLengthCounter=0;Local_u8UserNameLengthCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8UserNameLengthCounter++)
		{
			
			
			BL_voidRxChar(&copy_pu8RemoteUserName[Local_u8UserNameLengthCounter]);	
		//if(Local_u8UserNameLengthCounter==(HOME_USER_NAME_AND_PASS_MAX_LENGTh-1))
		//{
		//	break;
		//}
			
		}
		BL_voidTxString("Entered User Name:");
		//loop for 8 digits user name
		
		for(Local_u8UserNameLengthCounter=0;Local_u8UserNameLengthCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8UserNameLengthCounter++)
		{
			
			
			BL_voidTxChar(copy_pu8RemoteUserName[Local_u8UserNameLengthCounter]);	
			
		}
		
		BL_voidTxChar('\n');
		
		
		//display request for pass
		BL_voidTxString	("Password:");
		BL_voidTxChar('\n');
	
		//loop for 8 digits user pass
		for(Local_u8UserPassCounter=0;Local_u8UserPassCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8UserPassCounter++)
		{
			
			BL_voidRxChar(&copy_pu8RemoteUserPass[Local_u8UserPassCounter]);
			//if(Local_u8UserPassCounter==(HOME_USER_NAME_AND_PASS_MAX_LENGTh-1))
			//{
			//	break;
			//}
			
		}
		BL_voidTxString("Entered Pass:");
		//loop for 8 digits user pass
		for(Local_u8UserPassCounter=0;Local_u8UserPassCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8UserPassCounter++)
		{
			
			BL_voidTxChar(copy_pu8RemoteUserPass[Local_u8UserPassCounter]);
		
		}

		BL_voidTxChar('\n');
	}
	else
	{
		//error massage
	}
			
	
		
}


void HOME_voidCheckUserAndPass(u8 copy_u8AccessType,u8* copy_pu8UserType )
{
														/*purpose*/
	/*the purpose of this function is to enable user to log in the system whether locally or remotely the function take one argument
	to define if the user want to access from local or remoter and return if the login successed or not and user type 
	when calling this function must be followed by an alarm check function*/
	
														/*EEPROM MAPPING*/
	//we have 512 byte in EEPROM consists of 64 page first 0 to 29 page for local user and password the first page for user name the followed by password
	//page 30 &31 for admin user name and password the first page for user name the followed by password
	//page 32 to 61 for remote user name and password the first page for user name the followed by password
	//word 500 in eeprom is saved for alarm history
	
	
	//validate pointer
	if(copy_pu8UserType!=NULL)
	{
		u8 Local_u8TrailsCounter,Local_u8NameByteCheckCounter,Local_u8NameByteCheck=0,
		Local_u8PassByteCheckCounter,Local_u8PassByteCheck=0,Local_u8FireAnAlarm=0,Local_u8PagesCounter,
		Local_u8WrongUserNameCounter=0,Local_u8WrongUserPassCounter=0,LocaL_u8RightEntery=0;
		
		//first case for local access
		if(copy_u8AccessType==HOME_LOCAL_ACCESS)
		{
			u8 local_u8EnteredLocalUserName[HOME_USER_NAME_AND_PASS_MAX_LENGTh],local_u8EnteredLocalUserPass[HOME_USER_NAME_AND_PASS_MAX_LENGTh];
			u8 local_u8StoredLocalUserName[HOME_USER_NAME_AND_PASS_MAX_LENGTh],local_u8StoredLocalUserPass[HOME_USER_NAME_AND_PASS_MAX_LENGTh];
			u8 Local_u8LocalUserNameLocation;
			
			//every user have max of 3 trials for user name and pass
			for(Local_u8TrailsCounter=0;Local_u8TrailsCounter<HOME_MAX_NUMBER_OF_TRIALS;Local_u8TrailsCounter++)
			{
				Local_u8FireAnAlarm++;
				Local_u8WrongUserNameCounter=0;
				Local_u8WrongUserPassCounter=0;
				
				//get user name and pass from KPD & LCD
				HOME_voidLocalGetUserAndPass(&local_u8EnteredLocalUserName,&local_u8EnteredLocalUserPass);
				
				//loop on all reserved local eeprom locations
				for(Local_u8PagesCounter=0;Local_u8PagesCounter<(HOME_MAX_NUM_OF_LOCAL_USER+1);Local_u8PagesCounter++)
				
				{
					Local_u8NameByteCheck=0;
					Local_u8PassByteCheck=0;
					
					//get user name and pass from eeprom for local sys
					Local_u8LocalUserNameLocation=(2*Local_u8PagesCounter)*HOME_USER_NAME_AND_PASS_MAX_LENGTh;
					EEPROM_voidSequentialRead(Local_u8LocalUserNameLocation,HOME_USER_NAME_AND_PASS_MAX_LENGTh,&local_u8StoredLocalUserName);
					EEPROM_voidSequentialRead(Local_u8LocalUserNameLocation+HOME_USER_NAME_AND_PASS_MAX_LENGTh,HOME_USER_NAME_AND_PASS_MAX_LENGTh,&local_u8StoredLocalUserPass);
					
					//check user name which is entered by is user is the same as the one from eeprom
					for(Local_u8NameByteCheckCounter=0;Local_u8NameByteCheckCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8NameByteCheckCounter++)
					{
							
						if(local_u8EnteredLocalUserName[Local_u8NameByteCheckCounter]==local_u8StoredLocalUserName[Local_u8NameByteCheckCounter])
						{
							Local_u8NameByteCheck++;
							
							
						}
					}
					
					
					//if the user name is right now we can check pass
					if(Local_u8NameByteCheck==HOME_USER_NAME_AND_PASS_MAX_LENGTh)
					{
						
						for(Local_u8PassByteCheckCounter=0;Local_u8PassByteCheckCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8PassByteCheckCounter++)
						{
							
							if(local_u8EnteredLocalUserPass[Local_u8PassByteCheckCounter]==local_u8StoredLocalUserPass[Local_u8PassByteCheckCounter])
							{
								Local_u8PassByteCheck++;
								
								
							}
									
						}
						
						//if the pass right now we difine the user type(admin or user)
						if(Local_u8PassByteCheck==HOME_USER_NAME_AND_PASS_MAX_LENGTh)
						{
							

							LocaL_u8RightEntery=1;
							
							//admin user name is saved at loc 240(page 30)
							if(Local_u8PagesCounter==HOME_MAX_NUM_OF_LOCAL_USER)
							{
								*copy_pu8UserType=HOME_LOCAL_ADMIN;	
							}
							else
							{
								*copy_pu8UserType=HOME_LOCAL_USER;
							
							}
							
							break;
							
						}
						else
						{
							Local_u8WrongUserPassCounter++;
							
							
						}
							
					}
					else
					{
						Local_u8WrongUserNameCounter++;
						
						
						
					}
				
				}
			
				//is the entery was right dis on LCD
				if(LocaL_u8RightEntery==1)
				{
					LCD_voidClear();
					LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,0);
					LCD_voidDisplayString("ACCESS PERMITED");
					_delay_ms(500);
					break;
				}
				//is the entery was wrong dis on LCD and hint the reason
				else if(Local_u8WrongUserNameCounter==16)
				{
					LCD_voidClear();
					LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,0);
					LCD_voidDisplayString("ACCESS DENIED");
					LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,0);
					LCD_voidDisplayString("Wrong User Name");
					//dont display this message on trial 3
					if(Local_u8TrailsCounter!=(HOME_MAX_NUMBER_OF_TRIALS-1))
					{	
						_delay_ms(1000);
						LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,0);
						LCD_voidDisplayString("Please Try Again");
					}
				}
				//is the entery was wrong dis on LCD and hint the reason
				else if(Local_u8WrongUserPassCounter!=0)
				{
					LCD_voidClear();
					LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,0);
					LCD_voidDisplayString("ACCESS DENIED");
					LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,0);
					LCD_voidDisplayString("Wrong Password");
					
					//dont display this message on trial 3
					if(Local_u8TrailsCounter!=(HOME_MAX_NUMBER_OF_TRIALS-1))
					{
						_delay_ms(1000);
						LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,0);
						LCD_voidDisplayString("Please Try Again");
					}
				}
				
			
			}
			//check the alarm after the 3rd trial
			if((HOME_MAX_NUMBER_OF_TRIALS==Local_u8FireAnAlarm)&&(LocaL_u8RightEntery==0))
			{
				*copy_pu8UserType=HOME_LOGIN_FAILED;
			}
		}
		
		else if(copy_u8AccessType==HOME_REMOTE_ACCESS)
		{
			
			u8 local_u8EnteredRemoteUserName[HOME_USER_NAME_AND_PASS_MAX_LENGTh],local_u8EnteredRemoteUserPass[HOME_USER_NAME_AND_PASS_MAX_LENGTh];
			u8 local_u8StoredRemoteUserName[HOME_USER_NAME_AND_PASS_MAX_LENGTh],local_u8StoredRemoteUserPass[HOME_USER_NAME_AND_PASS_MAX_LENGTh];
			u8 Local_u8RemoteUserNameLocation;
			
			//every user have max of 3 trials for user name and pass
			for(Local_u8TrailsCounter=0;Local_u8TrailsCounter<HOME_MAX_NUMBER_OF_TRIALS;Local_u8TrailsCounter++)
			{
				
				Local_u8FireAnAlarm++;
				Local_u8WrongUserNameCounter=0;
				Local_u8WrongUserPassCounter=0;
				
				//delete this line later
				_delay_ms(20000);
				
				//get user name and pass from BL
				HOME_voidRemoteGetUserAndPass(&local_u8EnteredRemoteUserName,&local_u8EnteredRemoteUserPass);
				
				//loop on every remote user
				for(Local_u8PagesCounter=HOME_MAX_NUM_OF_LOCAL_USER;Local_u8PagesCounter<((HOME_MAX_NUM_OF_LOCAL_USER*2)+1);Local_u8PagesCounter++)
				{
					Local_u8NameByteCheck=0;
					Local_u8PassByteCheck=0;
					
					//get user name and pass from EEPROM
					Local_u8RemoteUserNameLocation=(2*Local_u8PagesCounter)*HOME_USER_NAME_AND_PASS_MAX_LENGTh;
					EEPROM_voidSequentialRead(Local_u8RemoteUserNameLocation,HOME_USER_NAME_AND_PASS_MAX_LENGTh,&local_u8StoredRemoteUserName);
					EEPROM_voidSequentialRead((Local_u8RemoteUserNameLocation+HOME_USER_NAME_AND_PASS_MAX_LENGTh),HOME_USER_NAME_AND_PASS_MAX_LENGTh,&local_u8StoredRemoteUserPass);
					
					//loop on every byte of user name
					for(Local_u8NameByteCheckCounter=0;Local_u8NameByteCheckCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8NameByteCheckCounter++)
					{
						
						//check the byte stored with the entered	
						if(local_u8EnteredRemoteUserName[Local_u8NameByteCheckCounter]==local_u8StoredRemoteUserName[Local_u8NameByteCheckCounter])
						{
							
							Local_u8NameByteCheck++;
							
							
						}
					
					}
					if(Local_u8NameByteCheck==HOME_USER_NAME_AND_PASS_MAX_LENGTh)
					{
						//loop on every byte of password
						for(Local_u8PassByteCheckCounter=0;Local_u8PassByteCheckCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8PassByteCheckCounter++)
						{
							//check the byte stored with the entered
							if(local_u8EnteredRemoteUserPass[Local_u8PassByteCheckCounter]==local_u8StoredRemoteUserPass[Local_u8PassByteCheckCounter])
							{
								Local_u8PassByteCheck++;
								
								
							}
									
						}
						//check the entry is right or wrong
						if(Local_u8PassByteCheck==HOME_USER_NAME_AND_PASS_MAX_LENGTh)
						{
							

							LocaL_u8RightEntery=1;
							
							//admin user name is saved at loc 240(page 30)
							if(Local_u8PagesCounter==HOME_MAX_NUM_OF_LOCAL_USER)
							{
								*copy_pu8UserType=HOME_REMOTE_ADMIN;	
							}
							else
							{
								*copy_pu8UserType=HOME_REMOTE_USER;
							
							}
							
							break;
							
						}
						else
						{
							Local_u8WrongUserPassCounter++;
							
							
						}
						
						
						
						
						
					}
					else
					{
						Local_u8WrongUserNameCounter++;
						
						
						
					}
						
				}
				//case of wright entry
				if(LocaL_u8RightEntery==1)
				{
					
					BL_voidTxString	("ACCESS PERMITED");
					BL_voidTxChar('\n');
					break;
				}
				//is the entery was wrong 
				else if(Local_u8WrongUserNameCounter==16)
				{
					BL_voidTxString	("ACCESS DENIED");
					BL_voidTxChar('\n');
					BL_voidTxString	("Wrong User Name");
					BL_voidTxChar('\n');
					
					//dont display this message on trial 3
					if(Local_u8TrailsCounter!=(HOME_MAX_NUMBER_OF_TRIALS-1))
					{	
						
						BL_voidTxString	("Please Try Again");
						BL_voidTxChar('\n');
						
					}
				}
				//is the entery was wrong dis on LCD and hint the reason
				else if(Local_u8WrongUserPassCounter!=0)
				{
					BL_voidTxString	("ACCESS DENIED");
					BL_voidTxChar('\n');
					BL_voidTxString	("Wrong Password");
					BL_voidTxChar('\n');
										
					//dont display this message on trial 3
					if(Local_u8TrailsCounter!=(HOME_MAX_NUMBER_OF_TRIALS-1))
					{
						BL_voidTxString	("Please Try Again");
						BL_voidTxChar('\n');
					}
				}
				
			}
			
		}
		
	
	}
	else
	{
		//error massage
	}
}











void KPD_Interface_user(void)
{

        Reset_AllKPDValues();

        TMR0_SetCallBackCTC(&LCD_DisplayTemp);

        TMR0_voidStart();
        LCD_voidClear();
        LCD_voidDisplayString((u8 *)"1-AC 2-light");
        LCD_voidSendCommand(Write_SecondLine);
        LCD_voidDisplayString((u8 *)"3-temperature");
        Reset_AllKPDValues();

        // busy wait for KPD
        while (Local_copyKPDValue == KPD_Not_Pressed)
        {
            if (local_KPDIdleValue == '0')
            {
                local_KPDIdleValue = KPD_Not_Pressed;
                break;
            }
            else
            {
                KPD_voidGetValue(&Local_copyKPDValue);
            }
        }
        TMR0_voidStop();
        switch (Local_copyKPDValue)
        {
        case ('1'):

            LCD_voidClear();
            LCD_voidDisplayStringDelay((u8 *)"AC Is On/off");
            LCD_voidSendCommand(Write_SecondLine);
            LCD_voidDisplayStringDelay((u8 *)"Room Temp: 30c");

            break;

        case ('2'):

            LCD_voidClear();
            LCD_voidDisplayStringDelay((u8 *)"Choose light to");
            LCD_voidSendCommand(Write_SecondLine);
            LCD_voidDisplayStringDelay((u8 *)"control(1-6)");

            TMR0_SetCallBackCTC(&LCD_DisplayTemp);
            TMR0_voidStart();
            // busy wait for KPD
            while (local_lightNum == KPD_Not_Pressed)
            {
                KPD_voidGetValue(&local_lightNum);
                if(local_KPDIdleValue=='0')
                {
                    local_KPDIdleValue=KPD_Not_Pressed;
                    break;
                }
            }
            TMR0_voidStop();
            switch (local_lightNum)
            {
            case ('1'):

                DIO_voidGetPinValue(DIO_PORTA, DIO_PIN0, &led_status);
                LCD_voidClear();
                if (led_status == 1)
                {
                    LCD_voidDisplayStringDelay((u8 *)"Light 1 is On");
                    LCD_voidSendCommand(Write_SecondLine);
                    LCD_voidDisplayStringDelay((u8 *)"1-To Turn It Off");
                    while (local_lightStatus == KPD_Not_Pressed)
                    {
                        KPD_voidGetValue(&local_lightStatus);
                    }
                    if (local_lightStatus == '1')
                    {
                        LED_voidOff(DIO_PORTA, DIO_PIN0, LED_FORWARD_CONNECTION);
                    }
                    Reset_AllKPDValues();
                }
                else if (led_status == 0)
                {
                    LCD_voidDisplayStringDelay((u8 *)"Light 1 is OFF");
                    LCD_voidSendCommand(Write_SecondLine);
                    LCD_voidDisplayStringDelay((u8 *)"1-To Turn It On");
                    while (local_lightStatus == KPD_Not_Pressed)
                    {
                        KPD_voidGetValue(&local_lightStatus);
                    }
                    if (local_lightStatus == '1')
                    {
                        LED_voidOn(DIO_PORTA, DIO_PIN0, LED_FORWARD_CONNECTION);
                    }
                    Reset_AllKPDValues();
                }
                break;

            case ('2'):

                DIO_voidGetPinValue(DIO_PORTA, DIO_PIN1, &led_status);
                LCD_voidClear();
                if (led_status == 1)
                {
                    LCD_voidDisplayStringDelay((u8 *)"Light 2 is On");
                    LCD_voidSendCommand(Write_SecondLine);
                    LCD_voidDisplayStringDelay((u8 *)"1-To Turn It Off");
                    while (local_lightStatus == KPD_Not_Pressed)
                    {
                        KPD_voidGetValue(&local_lightStatus);
                    }
                    if (local_lightStatus == '1')
                    {
                        LED_voidOff(DIO_PORTA, DIO_PIN1, LED_FORWARD_CONNECTION);
                    }
                    local_lightStatus = KPD_Not_Pressed;
                }
                else if (led_status == 0)
                {
                    LCD_voidDisplayStringDelay((u8 *)"Light 2 is OFF");
                    LCD_voidSendCommand(Write_SecondLine);
                    LCD_voidDisplayStringDelay((u8 *)"1-To Turn It On");
                    while (local_lightStatus == KPD_Not_Pressed)
                    {
                        KPD_voidGetValue(&local_lightStatus);
                    }
                    if (local_lightStatus == '1')
                    {
                        LED_voidOn(DIO_PORTA, DIO_PIN1, LED_FORWARD_CONNECTION);
                    }
                    local_lightStatus = KPD_Not_Pressed;
                }
                break;

            case ('3'):

                DIO_voidGetPinValue(DIO_PORTA, DIO_PIN2, &led_status);
                LCD_voidClear();
                if (led_status == 1)
                {
                    LCD_voidDisplayStringDelay((u8 *)"Light 3 is On");
                    LCD_voidSendCommand(Write_SecondLine);
                    LCD_voidDisplayStringDelay((u8 *)"1-To Turn It Off");
                    while (local_lightStatus == KPD_Not_Pressed)
                    {
                        KPD_voidGetValue(&local_lightStatus);
                    }

                    if (local_lightStatus == '1')
                    {
                        LED_voidOff(DIO_PORTA, DIO_PIN2, LED_FORWARD_CONNECTION);
                    }
                    local_lightStatus = KPD_Not_Pressed;
                }
                else if (led_status == 0)
                {
                    LCD_voidDisplayStringDelay((u8 *)"Light 3 is OFF");
                    LCD_voidSendCommand(Write_SecondLine);
                    LCD_voidDisplayStringDelay((u8 *)"1-To Turn It On");
                    while (local_lightStatus == KPD_Not_Pressed)
                    {
                        KPD_voidGetValue(&local_lightStatus);
                    }

                    if (local_lightStatus == '1')
                    {
                        LED_voidOn(DIO_PORTA, DIO_PIN2, LED_FORWARD_CONNECTION);
                    }
                    local_lightStatus = KPD_Not_Pressed;
                }
                break;

            case ('4'):

                DIO_voidGetPinValue(DIO_PORTA, DIO_PIN3, &led_status);
                LCD_voidClear();
                if (led_status == 1)
                {
                    LCD_voidDisplayStringDelay((u8 *)"Light 4 is On");
                    LCD_voidSendCommand(Write_SecondLine);
                    LCD_voidDisplayStringDelay((u8 *)"1-To Turn It Off");
                    while (local_lightStatus == KPD_Not_Pressed)
                    {
                        KPD_voidGetValue(&local_lightStatus);
                    }

                    if (local_lightStatus == '1')
                    {
                        LED_voidOff(DIO_PORTA, DIO_PIN3, LED_FORWARD_CONNECTION);
                    }
                    local_lightStatus = KPD_Not_Pressed;
                }
                else if (led_status == 0)
                {
                    LCD_voidDisplayStringDelay((u8 *)"Light 4 is OFF");
                    LCD_voidSendCommand(Write_SecondLine);
                    LCD_voidDisplayStringDelay((u8 *)"1-To Turn It On");
                    while (local_lightStatus == KPD_Not_Pressed)
                    {
                        KPD_voidGetValue(&local_lightStatus);
                    }

                    if (local_lightStatus == '1')
                    {
                        LED_voidOn(DIO_PORTA, DIO_PIN3, LED_FORWARD_CONNECTION);
                    }
                    local_lightStatus = KPD_Not_Pressed;
                }
                break;

            case ('5'):

                DIO_voidGetPinValue(DIO_PORTD, DIO_PIN2, &led_status);
                LCD_voidClear();
                if (led_status == 1)
                {
                    LCD_voidDisplayStringDelay((u8 *)"Light 5 is On");
                    LCD_voidSendCommand(Write_SecondLine);
                    LCD_voidDisplayStringDelay((u8 *)"1-To Turn It Off");
                    while (local_lightStatus == KPD_Not_Pressed)
                    {
                        KPD_voidGetValue(&local_lightStatus);
                    }

                    if (local_lightStatus == '1')
                    {
                        LED_voidOff(DIO_PORTD, DIO_PIN2, LED_FORWARD_CONNECTION);
                    }
                    local_lightStatus = KPD_Not_Pressed;
                }
                else if (led_status == 0)
                {
                    LCD_voidDisplayStringDelay((u8 *)"Light 5 is OFF");
                    LCD_voidSendCommand(Write_SecondLine);
                    LCD_voidDisplayStringDelay((u8 *)"1-To Turn It On");
                    while (local_lightStatus == KPD_Not_Pressed)
                    {
                        KPD_voidGetValue(&local_lightStatus);
                    }

                    if (local_lightStatus == '1')
                    {
                        LED_voidOn(DIO_PORTD, DIO_PIN2, LED_FORWARD_CONNECTION);
                    }
                    local_lightStatus = KPD_Not_Pressed;
                }
                break;
                // if the user choose light 6 (DIMMER LED)

            case ('6'):

                LCD_voidClear();
                if (led_status == 1)
                {
                    LCD_voidDisplayStringDelay((u8 *)"Light 6 is On");
                    LCD_voidSendCommand(Write_SecondLine);
                    LCD_voidDisplayStringDelay((u8 *)"1-To Turn It Off");
                }
                else if (led_status == 0)
                {
                    LCD_voidDisplayStringDelay((u8 *)"Light 6 is OFF");
                    LCD_voidSendCommand(Write_SecondLine);
                    LCD_voidDisplayStringDelay((u8 *)"1-To Turn It On");
                }
                break;

            }

            local_lightNum = KPD_Not_Pressed;
            Local_copyKPDValue = KPD_Not_Pressed;
            break;
        }
    
}

void WelcomeScreen()
{
    LCD_voidDisplayStringDelay((u8 *)" Welcome to your");
    LCD_voidSendCommand(Write_SecondLine);
    LCD_voidDisplayStringDelay((u8 *)"   Smart Home");
    _delay_ms(1000);
}

void LCD_DisplayTemp()
{
    u8 local_tempValue=0;

    LCD_voidClear();

    while (local_KPDIdleValue == KPD_Not_Pressed)
    {
        KPD_voidGetValue(&local_KPDIdleValue);

        ADC_voidGetDigitalValue(ADC_CHANNEL_0, &local_tempValue);
        _delay_ms(100);
        LCD_voidDisplayNumber(local_tempValue);
        _delay_ms(1000);
        LCD_voidClear();
        // LCD_voidSendCommand(Write_SecondLine);
        // LCD_voidDisplayStringDelay((u8 *)"0-go to home");
        
        
    }
    if (local_KPDIdleValue == '0')
    {
        LCD_voidClear();
    }
    TMR0clear_flag();
    LCD_voidClear();

}

void Reset_AllKPDValues()
{
    Local_copyKPDValue = KPD_Not_Pressed;
    local_lightNum = KPD_Not_Pressed;
    local_lightStatus = KPD_Not_Pressed;
}

