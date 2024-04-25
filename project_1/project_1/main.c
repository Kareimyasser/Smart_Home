/*
 * project_1.c
 *
 * Created: 4/20/2024 8:31:18 PM
 * Author : Saed Abozied
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

/*UTILIES_LIB*/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/*MCAL*/
#include "DIO_interface.h"
#include "GI_interface.h"
#include "PWM_interface.h"
#include "UART_interface.h"


/*HAL*/
#include "LED_interface.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "BUZZER_interface.h"
#include "EEPROM_interface.h"
#include "SERVO_interface.h"
#include "BL_interface.h"

#define HOME_MAX_NUMBER_OF_TRIALS		3
#define HOME_USER_NAME_AND_PASS_MAX_LENGTh		8
#define HOME_ADMIN		1
#define HOME_USER		2
#define HOME_LOCAL_ACCESS		1
#define HOME_REMOTE_ACCESS		2

/*APIs prototypes*/
void HOME_voidInit(void);

//user and password
void HOME_voidLocalGetUserAndPass(u8* copy_pu8LocalUserName,u8* copy_pu8LocalUserPass);
void HOME_voidCheckUserAndPass(u8 copy_u8AccessType,u8* copy_pu8UserType );


int main(void)
{

	
	
    HOME_voidInit();
	
	
	
	LCD_voidDisplayString((u8*)"Welcome Home");
	_delay_ms(500);
	LCD_voidClear();
	
	u8 testusername[8]={"11111111"};
	u8 testuserpass[8]={"22222222"};
	u8 pCounter;	
	
	EEPROM_voidWritePage(16,&testusername[0]);
	EEPROM_voidWritePage(24,&testuserpass[0]);
	
	HOME_voidCheckUserAndPass(HOME_LOCAL_ACCESS,&pCounter);
	
    while (1) 
    {
		

    }
	
}





void HOME_voidInit(void)
{
	EEPROM_voidInit();
	
	LCD_voidInit();
	
	KEYPAD_voidInit();
	
	BL_voidInit();
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN1,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN0,DIO_PIN_INPUT);
}

void HOME_voidLocalGetUserAndPass(u8* copy_pu8LocalUserName,u8* copy_pu8LocalUserPass)
{
	if((copy_pu8LocalUserName!=NULL)&&(copy_pu8LocalUserPass!=NULL))
	{
			
		u8 Local_u8UserNameLengthCounter,Local_u8UserPassCounter;
	
		//dis request for use name and pass
		LCD_voidClear();
		LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,0);
		LCD_voidDisplayString("Please Enter User");
		LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,0);
		LCD_voidDisplayString("Name&Password");
		_delay_ms(1000);
	
		//dis request for user name
		LCD_voidClear();
		LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,0);
		LCD_voidDisplayString("User Name:");
	
		//loop for 8 digits user name
		for(Local_u8UserNameLengthCounter=0;Local_u8UserNameLengthCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8UserNameLengthCounter++)
		{
		
		
			do
			{
				KEYPAD_voidGetValue(&copy_pu8LocalUserName[Local_u8UserNameLengthCounter]);
			
			}while(copy_pu8LocalUserName[Local_u8UserNameLengthCounter]== KEYPAD_NOT_PRESSED);
		
			LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,Local_u8UserNameLengthCounter);
			LCD_voidDisplayChar(copy_pu8LocalUserName[Local_u8UserNameLengthCounter]);
		}
	
		//display request for pass
		LCD_voidClear();
		LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,0);
		LCD_voidDisplayString("PASSWORD:");
	
		//loop for 8 digits user pass
			for(Local_u8UserPassCounter=0;Local_u8UserPassCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8UserPassCounter++)
			{
				do
				{
					KEYPAD_voidGetValue(&copy_pu8LocalUserPass[Local_u8UserPassCounter]);
				
				}while(copy_pu8LocalUserPass[Local_u8UserPassCounter]==KEYPAD_NOT_PRESSED);
			
				LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,Local_u8UserPassCounter);
				LCD_voidDisplayChar(copy_pu8LocalUserPass[Local_u8UserPassCounter]);
			}
	}
	else
	{
		//error massage
	}
			
	
		
}

void HOME_voidCheckUserAndPass(u8 copy_u8AccessType,u8* copy_pu8UserType )
{
	//we have 512 byte in EEPROM consists of 64 page first 0 to 29 page for local user and password the first page for user name the followed by password
	//page 30 &31 for admin user name and password the first page for user name the followed by password
	//page 32 to 62 for remote user name and password the first page for user name the followed by password
	
	
	if(copy_pu8UserType!=NULL)
	{
		if(copy_u8AccessType==HOME_LOCAL_ACCESS)
		{
			u8 local_u8EnteredLocalUserName[HOME_USER_NAME_AND_PASS_MAX_LENGTh],local_u8EnteredLocalUserPass[HOME_USER_NAME_AND_PASS_MAX_LENGTh];
			u8 local_u8StoredLocalUserName[HOME_USER_NAME_AND_PASS_MAX_LENGTh],local_u8StoredLocalUserPass[HOME_USER_NAME_AND_PASS_MAX_LENGTh];
			u8 Local_u8TrailsCounter,Local_u8NameByteCheckCounter,Local_u8NameByteCheck=0,Local_u8PassByteCheckCounter,Local_u8PassByteCheck=0,
			Local_u8FireAnAlarm,Local_u8PagesCounter,Local_u8WrongUserNameCounter=0,Local_u8WrongUserPassCounter=0,Local_u8LocalUserNameLocation,LocaL_u8RightEntery=0;
			
			for(Local_u8TrailsCounter=0;Local_u8TrailsCounter<HOME_MAX_NUMBER_OF_TRIALS;Local_u8TrailsCounter++)
			{
				Local_u8FireAnAlarm=Local_u8TrailsCounter;
				Local_u8WrongUserNameCounter=0;
				Local_u8WrongUserPassCounter=0;
				HOME_voidLocalGetUserAndPass(&local_u8EnteredLocalUserName,&local_u8EnteredLocalUserPass);
				
				//loop on all local eeprom locations
				for(Local_u8PagesCounter=0;Local_u8PagesCounter<16;Local_u8PagesCounter++)
				
				{
					Local_u8NameByteCheck=0;
					Local_u8PassByteCheck=0;
					
					Local_u8LocalUserNameLocation=(2*Local_u8PagesCounter)*HOME_USER_NAME_AND_PASS_MAX_LENGTh;
					EEPROM_voidSequentialRead(Local_u8LocalUserNameLocation,HOME_USER_NAME_AND_PASS_MAX_LENGTh,&local_u8StoredLocalUserName);
					EEPROM_voidSequentialRead(Local_u8LocalUserNameLocation+HOME_USER_NAME_AND_PASS_MAX_LENGTh,HOME_USER_NAME_AND_PASS_MAX_LENGTh,&local_u8StoredLocalUserPass);
					
					for(Local_u8NameByteCheckCounter=0;Local_u8NameByteCheckCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8NameByteCheckCounter++)
					{
						
						
						if(local_u8EnteredLocalUserName[Local_u8NameByteCheckCounter]==local_u8StoredLocalUserName[Local_u8NameByteCheckCounter])
						{
							Local_u8NameByteCheck++;
							
							
						}
					}
					
				
					
					if(Local_u8NameByteCheck==HOME_USER_NAME_AND_PASS_MAX_LENGTh)
					{
						
						for(Local_u8PassByteCheckCounter=0;Local_u8PassByteCheckCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8PassByteCheckCounter++)
						{
							
							
							
							if(local_u8EnteredLocalUserPass[Local_u8PassByteCheckCounter]==local_u8StoredLocalUserPass[Local_u8PassByteCheckCounter])
							{
								Local_u8PassByteCheck++;
								
								
							}
									
						}
						
						
						if(Local_u8PassByteCheck==HOME_USER_NAME_AND_PASS_MAX_LENGTh)
						{
							
							
							LocaL_u8RightEntery=1;
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
			
				
				if(LocaL_u8RightEntery==1)
				{
					LCD_voidClear();
					LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,0);
					LCD_voidDisplayString("ACCESS PERMITED");
					_delay_ms(500);
					break;
				}
				else if(Local_u8WrongUserNameCounter==16)
				{
					LCD_voidClear();
					LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,0);
					LCD_voidDisplayString("ACCESS DENIED");
					LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,0);
					LCD_voidDisplayString("Wrong User Name");
					_delay_ms(1000);
					LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,0);
					LCD_voidDisplayString("Please Try Again");	
				}
				else if(Local_u8WrongUserPassCounter!=0)
				{
					LCD_voidClear();
					LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,0);
					LCD_voidDisplayString("ACCESS DENIED");
					LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,0);
					LCD_voidDisplayString("Wrong Password");
					_delay_ms(1000);
					LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,0);
					LCD_voidDisplayString("Please Try Again");
				}
				
			
			}
		}
		
		else if(copy_u8AccessType==HOME_REMOTE_ACCESS)
		{
			//implenet check in case of bl access
		}
	
	}
	else
	{
		//error massage
	}
}