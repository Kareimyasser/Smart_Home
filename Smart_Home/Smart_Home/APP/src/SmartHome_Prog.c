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
#include "TMR2_interface.h"
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


//global variable for the application accessed by SmartHome.c and main.c
// only for testing purposes
u8 global_accessType =accessPermited;
u8 usertype=HOME_NO_LOGIN;



//global variables for the application accessed only by SmartHome.c
//local KPD variables for the application
u8 Local_copyKPDValue = KPD_Not_Pressed;
u8 local_lightNum = KPD_Not_Pressed;
u8 local_lightStatus = KPD_Not_Pressed;
u8 local_KPDIdleValue = KPD_Not_Pressed;
u8 local_KPDSelectValue = KPD_Not_Pressed;
u8 door_angle = 0;
u8 local_ac_status = 0;


//local bluetooth variable for checking bluetooth status
u8 bluetooh_value=0;


//local BL variables for the displaying on terminal 
char DimmerString[20];
char tempString[20];


//local LED variable for checking led status
u8 led_status = 0;
u8 dimmer_brightness = 0;

//local temp 
u8 local_temp = 0;


void APP_init()
{
		//Local users
		u8 Local_u8IntialUserName1[8]="1112223";
		u8 Local_u8IntialUserPass1[8]="1112223";
		u8 Local_u8IntialUserName2[8]="2223334";
		u8 Local_u8IntialUserPass2[8]="2223334";
		u8 Local_u8IntialUserName3[8]="3334445";
		u8 Local_u8IntialUserPass3[8]="3334445";
		u8 Local_u8IntialUserName4[8]="4445556";
		u8 Local_u8IntialUserPass4[8]="4445556";
		u8 Local_u8IntialUserName5[8]="5556667";
		u8 Local_u8IntialUserPass5[8]="5556667";
		
		//admin user
		u8 Local_u8IntialUserName6[8]="4433221";
		u8 Local_u8IntialUserPass6[8]="4433221";
		
		//remote user
		u8 Local_u8IntialUserName7[8]="1001011";
		u8 Local_u8IntialUserPass7[8]="1001011";
		u8 Local_u8IntialUserName8[8]="2002012";
		u8 Local_u8IntialUserPass8[8]="2002012";
		u8 Local_u8IntialUserName9[8]="3003013";
		u8 Local_u8IntialUserPass9[8]="3003013";
		u8 Local_u8IntialUserName10[8]="4004014";
		u8 Local_u8IntialUserPass10[8]="4004014";
		u8 Local_u8IntialUserName11[8]="5005015";
		u8 Local_u8IntialUserPass11[8]="5005015";
		
		
		//write local users
		EEPROM_voidWritePage(0,&Local_u8IntialUserName1[0]);
		EEPROM_voidWritePage(8,&Local_u8IntialUserPass1[0]);
		EEPROM_voidWritePage(16,&Local_u8IntialUserName2[0]);
		EEPROM_voidWritePage(24,&Local_u8IntialUserPass2[0]);
		EEPROM_voidWritePage(32,&Local_u8IntialUserName3[0]);
		EEPROM_voidWritePage(40,&Local_u8IntialUserPass3[0]);
		EEPROM_voidWritePage(48,&Local_u8IntialUserName4[0]);
		EEPROM_voidWritePage(56,&Local_u8IntialUserPass4[0]);
		EEPROM_voidWritePage(64,&Local_u8IntialUserName5[0]);
		EEPROM_voidWritePage(72,&Local_u8IntialUserPass5[0]);
		
		//write adminuser
		EEPROM_voidWritePage(80,&Local_u8IntialUserName6[0]);
		EEPROM_voidWritePage(88,&Local_u8IntialUserPass6[0]);
		
		//write remoteusers
		EEPROM_voidWritePage(96,&Local_u8IntialUserName7[0]);
		EEPROM_voidWritePage(104,&Local_u8IntialUserPass7[0]);
		EEPROM_voidWritePage(112,&Local_u8IntialUserName8[0]);
		EEPROM_voidWritePage(120,&Local_u8IntialUserPass8[0]);
		EEPROM_voidWritePage(128,&Local_u8IntialUserName9[0]);
		EEPROM_voidWritePage(136,&Local_u8IntialUserPass9[0]);
		EEPROM_voidWritePage(144,&Local_u8IntialUserName10[0]);
		EEPROM_voidWritePage(152,&Local_u8IntialUserPass10[0]);
		EEPROM_voidWritePage(160,&Local_u8IntialUserName11[0]);
		EEPROM_voidWritePage(168,&Local_u8IntialUserPass11[0]);


	
}








void HOME_voidInit(void)
{
	//Home initialization function is for the hardware initialization of the smart home system
	    // initialize the LCD
    LCD_voidInit();
	// initialize the PWM
	PWM_voidInitChannel_1A();
	PWM_voidInitChannel_1B();

	// initialize the EEPROM
	EEPROM_voidInit();
	
	// initialize the Door_Servo
	SERVO_voidInit(DIO_PORTD,DIO_PIN4);
	// reset door angle to 0
	SERVO_voidStartByAngle(0);

	// initialize the KPD
    KPD_voidInit();

	// initialize the ADC
	ADC_voidInit(ADC_REFERENCE_INTRNAL);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN0,DIO_PIN_INPUT);

	// AC PIN
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN2,DIO_PIN_OUTPUT);

	// initialize the Buzzer
	BUZZER_voidInit(DIO_PORTD,DIO_PIN6);
	
    // initialize the Bluetooth
	BL_voidInit();
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN1,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN0,DIO_PIN_INPUT);
    //enable global interrupt
    GI_voidEnable();
    //intializing timer by selecting mode and enable timer interrupt overflow and saving perload values
    TMR0_voidInit();
    // initialize the LEDs(1-5)
	//LED 1
    LED_voidInit(DIO_PORTD, DIO_PIN3);
	//LED 2
    LED_voidInit(DIO_PORTB, DIO_PIN0);
	//LED 3
    LED_voidInit(DIO_PORTA, DIO_PIN2);
	//LED 4
    LED_voidInit(DIO_PORTA, DIO_PIN3);
	//LED 5
    LED_voidInit(DIO_PORTD, DIO_PIN2);
	// Dimmer LED 6
	LED_voidInit(DIO_PORTD, DIO_PIN5);

	// initialize tmr2
	TMR2_voidInit();
	TMR2_SetCallBackCTC(CheckTempForAc);
	TMR2_voidStart();

}

void GetUserType(void)
//this function is to check if user is connecting remotly or local 
{
	LCD_voidClear();
	LCD_voidDisplayStringDelay((u8*)"Press # to login");
	BL_voidTxChar('\r');
	BL_voidTxString("Press # to login");
	BL_voidTxChar('\r');
	while (Local_copyKPDValue == KPD_Not_Pressed && bluetooh_value != '#')
	{
		BL_voidRxCharWithTimeout(&bluetooh_value);
		KPD_voidGetValue(&Local_copyKPDValue);
	}
	if (Local_copyKPDValue == '#')
	{
		BL_voidTxString("system is being used by local user");
		HOME_voidCheckUserAndPass(HOME_LOCAL_ACCESS,&usertype);
		
	}
	else if (bluetooh_value == '#')
	{
		LCD_voidClear();
		LCD_voidDisplayString("system is being used");
		LCD_voidSendCommand(Write_SecondLine);
		LCD_voidDisplayString("by remote user");
		HOME_voidCheckUserAndPass(HOME_REMOTE_ACCESS,&usertype);

		
	}

	

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
		for(Local_u8UserNameLengthCounter=0;Local_u8UserNameLengthCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh-1;Local_u8UserNameLengthCounter++)
		{
		
		
			do
			{
				KPD_voidGetValue(&copy_pu8LocalUserName[Local_u8UserNameLengthCounter]);
			
			}while(copy_pu8LocalUserName[Local_u8UserNameLengthCounter]== KPD_Not_Pressed);
		
			LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,Local_u8UserNameLengthCounter);
			LCD_voidDisplayChar(copy_pu8LocalUserName[Local_u8UserNameLengthCounter]);
		}
		copy_pu8LocalUserName[Local_u8UserNameLengthCounter]='\0';
		//display request for pass
		LCD_voidClear();
		LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,0);
		LCD_voidDisplayString((u8 *)"PASSWORD:");
	
		//loop for 8 digits user pass
			for(Local_u8UserPassCounter=0;Local_u8UserPassCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh-1;Local_u8UserPassCounter++)
			{
				do
				{
					KPD_voidGetValue(&copy_pu8LocalUserPass[Local_u8UserPassCounter]);
				
				}while(copy_pu8LocalUserPass[Local_u8UserPassCounter]==KPD_Not_Pressed);
			
				LCD_voidGoTOSpecificPosition(LCD_LINE_TWO,Local_u8UserPassCounter);
				LCD_voidDisplayChar(copy_pu8LocalUserPass[Local_u8UserPassCounter]);
			}
			copy_pu8LocalUserPass[Local_u8UserPassCounter]='\0';
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
	
		
	
		//dis request for user name
		BL_voidTxString	("User Name:");
		BL_voidTxChar('\n');
	
		//loop for 8 digits user name
		for(Local_u8UserNameLengthCounter=0;Local_u8UserNameLengthCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8UserNameLengthCounter++)
		{
			
			
			BL_voidRxChar(&copy_pu8RemoteUserName[Local_u8UserNameLengthCounter]);	
			if(copy_pu8RemoteUserName[Local_u8UserNameLengthCounter]=='#')
			{
				break;
			}
			
		}
		copy_pu8RemoteUserName[Local_u8UserNameLengthCounter]='\0';
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
		for(Local_u8UserPassCounter=0;Local_u8UserPassCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh+1;Local_u8UserPassCounter++)
		{
			
			BL_voidRxChar(&copy_pu8RemoteUserPass[Local_u8UserPassCounter]);
			if(copy_pu8RemoteUserPass[Local_u8UserPassCounter]=='#')
			{
				break;
			}
			
		}
		copy_pu8RemoteUserPass[Local_u8UserPassCounter]='\0';
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


void HOME_voidCheckUserAndPass(u8 copy_u8AccessType,u8* copy_pu8UserStatus)
{
														/*purpose*/
	/*the purpose of this function is to enable user to log in the system whether locally or remotely the function take one argument
	to define if the user want to access from local or remoter and return if the login successed or not and user type 
	when calling this function must be followed by an alarm check function*/
	
														/*EEPROM MAPPING*/
	//we have 512 byte in EEPROM consists of 64 page first 0 to 9 page for local user and password the first page for user name the followed by password
	//page 10 &11 for admin user name and password the first page for user name the followed by password
	//page 12 to 21 for remote user name and password the first page for user name the followed by password
	//word 180 in eeprom is saved for alarm history
	
	
	//validate pointer
	if(copy_pu8UserStatus!=NULL)
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
								*copy_pu8UserStatus=HOME_LOCAL_ADMIN;	
							}
							else
							{
								*copy_pu8UserStatus=HOME_LOCAL_USER;
							
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
				else if(Local_u8WrongUserNameCounter==(HOME_MAX_NUM_OF_LOCAL_USER+1))
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
				*copy_pu8UserStatus=HOME_LOGIN_FAILED;
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
				
				
				//dis request for use name and pass
				BL_voidTxString	("Please Enter User Name & Password ");
				BL_voidTxString("\n");
				
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
								*copy_pu8UserStatus=HOME_REMOTE_ADMIN;	
							}
							else
							{
								*copy_pu8UserStatus=HOME_REMOTE_USER;
							
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
				else if(Local_u8WrongUserNameCounter==(HOME_MAX_NUM_OF_LOCAL_USER+1))
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
			//check the alarm after the 3rd trial
			if((HOME_MAX_NUMBER_OF_TRIALS==Local_u8FireAnAlarm)&&(LocaL_u8RightEntery==0))
			{
				*copy_pu8UserStatus=HOME_LOGIN_FAILED;
			}
			
			
			
		}
		
	
	}
	else
	{
		//error massage
	}
}

void HOME_voidChangeUserNameAndPass(void)
{
	u8 local_u8OldUserName[HOME_USER_NAME_AND_PASS_MAX_LENGTh],local_u8OldUserPass[HOME_USER_NAME_AND_PASS_MAX_LENGTh];
	u8 local_u8TempUserName[HOME_USER_NAME_AND_PASS_MAX_LENGTh],local_u8TempUserPass[HOME_USER_NAME_AND_PASS_MAX_LENGTh];
	u8 local_u8SavedUserName[HOME_USER_NAME_AND_PASS_MAX_LENGTh],local_u8SavedUserPass[HOME_USER_NAME_AND_PASS_MAX_LENGTh];
	u8 Local_u8NameByteCheckCounter,Local_u8PagesCounter,Local_u8NameByteCheck,Local_u8PassByteCheck,Local_u8PassByteCheckCounter,
	Local_u8UserNameLocation,LocaL_u8RightEntery=0,Local_u8WrongUserPassCounter=0,Local_u8WrongUserNameCounter=0,Local_u8ReplaceCounter;
	
	
	//dis request for use name and pass
	BL_voidTxString	("Please Enter User Name & Password u want to change");
	BL_voidTxString("\n");
	
	//get user name and pass from BL
	HOME_voidRemoteGetUserAndPass(&local_u8OldUserName,&local_u8OldUserPass);
	
	//loop on every user except admin
	for(Local_u8PagesCounter=0;Local_u8PagesCounter<((HOME_MAX_NUM_OF_LOCAL_USER*2)+1);Local_u8PagesCounter++)
	{
		Local_u8NameByteCheck=0;
		Local_u8PassByteCheck=0;
		
		//skip admin page
		if(Local_u8PagesCounter==HOME_MAX_NUM_OF_LOCAL_USER)
		{
			continue;
		}
		
		//get user name and pass from EEPROM
		Local_u8UserNameLocation=(2*Local_u8PagesCounter)*HOME_USER_NAME_AND_PASS_MAX_LENGTh;
		EEPROM_voidSequentialRead(Local_u8UserNameLocation,HOME_USER_NAME_AND_PASS_MAX_LENGTh,&local_u8SavedUserName);
		EEPROM_voidSequentialRead((Local_u8UserNameLocation+HOME_USER_NAME_AND_PASS_MAX_LENGTh),HOME_USER_NAME_AND_PASS_MAX_LENGTh,&local_u8SavedUserPass);
		
		//loop on every byte of user name
		for(Local_u8NameByteCheckCounter=0;Local_u8NameByteCheckCounter<HOME_USER_NAME_AND_PASS_MAX_LENGTh;Local_u8NameByteCheckCounter++)
		{
			
			//check the byte stored with the entered	
			if(local_u8OldUserName[Local_u8NameByteCheckCounter]==local_u8SavedUserName[Local_u8NameByteCheckCounter])
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
				if(local_u8OldUserPass[Local_u8PassByteCheckCounter]==local_u8SavedUserPass[Local_u8PassByteCheckCounter])
				{
					Local_u8PassByteCheck++;
					
					
				}
						
			}
			
			//check the entry is right or wrong
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
	
	//case of wright entry
	if(LocaL_u8RightEntery==1)
	{
		
		BL_voidTxString	("Please Enter The new User And Pass");
		BL_voidTxChar('\n');
		//get New user name and pass from BL
		HOME_voidRemoteGetUserAndPass(&local_u8TempUserName,&local_u8TempUserPass);
		//write the new user name & pass in EEPROM
		EEPROM_voidWritePage(Local_u8UserNameLocation,&local_u8TempUserName);
		EEPROM_voidWritePage((Local_u8UserNameLocation+HOME_USER_NAME_AND_PASS_MAX_LENGTh),&local_u8TempUserPass);
		BL_voidTxString	("User Data Changed Successfully");
		BL_voidTxChar('\n');
		
	}
	//is the entery was wrong 
	else 
	{

		BL_voidTxString	("Wrong User Name or password");
		BL_voidTxChar('\n');
		

	}

	
	
}


void HOME_voidFireAnALarm(u8 copy_pu8UserStatus)
{
	u8 Local_u8CheckAlarm,Local_u8ResetValue;
	
	// fire alarm if the user entry failed
	if(copy_pu8UserStatus==HOME_LOGIN_FAILED)
	{
		EEPROM_voidWriteByte(HOME_ALARM_LOCATION,HOME_ALARM_VALUE);
	}
	
	//check alarm status
	EEPROM_voidReadByte(HOME_ALARM_LOCATION,&Local_u8CheckAlarm);
	
	//block system if there is an alarm
	if(Local_u8CheckAlarm==HOME_ALARM_VALUE)
	{
		while(1)
		{
			BL_voidTxString	("ACCESS DENIED");
			BL_voidTxChar('\r');

			BUZZER_voidOn(DIO_PORTD,DIO_PIN6);
			
			LCD_voidClear();
			LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,0);
			LCD_voidDisplayString("ACCESS DENIED");
			
			//if the user enter # end alarm
			BL_voidRxChar(&Local_u8ResetValue);
			if(Local_u8ResetValue=='#')
			{
				BUZZER_voidOff(DIO_PORTD,DIO_PIN6);
				break;
			}
			
		}
		//clear alarm byte
		EEPROM_voidWriteByte(HOME_ALARM_LOCATION,HOME_ALARM_CLEAR_VALUE);
	}
}


void KPD_Interface_RemoteAdmin(void)
{
	// This function is for admin usertype for accessing the smart home remotely showing all options available for the admin//

	//setting the TRM0 ctc interrupt function
	TMR0_SetCallBackCTC(&Idle_RemoteAction);
	BL_voidTxChar('\r');
	BL_voidTxString("1-AC 2-light");
	BL_voidTxChar('\r');
	BL_voidTxString("3-temp 4-Door");
	BL_voidTxChar('\r');
	BL_voidTxString("5- change username and password");
	BL_voidTxChar('\r');
	TMR0_voidStart();
	//reciving user selection from BL
	BL_voidRxChar(&bluetooh_value);
	TMR0_voidStop();
	switch (bluetooh_value)
	{
	case ('1'):
		BL_voidTxString("AC Is On/off");
        BL_voidTxChar('\r');
		//getting temp from ADC
        ADC_voidGetDigitalValue(ADC_CHANNEL_0, &local_temp); 
				//sprintf is used to format and store a string in a buffer
				sprintf(tempString, "Room Temp: %d c", local_temp);
				BL_voidTxString(tempString);
				BL_voidTxChar('\r');
				BL_voidTxString("0-go to home");
				BL_voidTxChar('\r');
				TMR0_voidStart();
				BL_voidRxChar(&bluetooh_value);
				TMR0_voidStop();
				if (bluetooh_value=='0')
				{
					
				}
		break;
	
	case ('2'):

       
	   		BL_voidTxChar('\r');     
            BL_voidTxString("Choose light to");
            BL_voidTxChar('\r');
            BL_voidTxString("control(1-6)");
			BL_voidTxChar('\r');
			BL_voidTxChar('\r');
            TMR0_voidStart();
			BL_voidRxChar(&bluetooh_value);
            TMR0_voidStop();
            switch (bluetooh_value)
            {
            case ('1'):
			//DIO_voidGetPinValue is used to check if the led is on or off before changing its state

                DIO_voidGetPinValue(DIO_PORTD, DIO_PIN3, &led_status);
                
                if (led_status == 1)
                {
                    BL_voidTxString("Light 1 is On");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It Off");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);
                    if (bluetooh_value == '1')
                    {
                        LED_voidOff(DIO_PORTD, DIO_PIN3, LED_FORWARD_CONNECTION);
                    }
                    
					break;
                }
                else if (led_status == 0)
                {
                    BL_voidTxString("Light 1 is OFF");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It On");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);
                    if (bluetooh_value == '1')
                    {
                        LED_voidOn(DIO_PORTD, DIO_PIN3, LED_FORWARD_CONNECTION);
                    }
                    
                }
                break;

            case ('2'):

                DIO_voidGetPinValue(DIO_PORTB, DIO_PIN0, &led_status);
                
                if (led_status == 1)
                {
                    BL_voidTxString("Light 2 is On");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It Off");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);
                    if (bluetooh_value == '1')
                    {
                        LED_voidOff(DIO_PORTB, DIO_PIN0, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                else if (led_status == 0)
                {
                    BL_voidTxString("Light 2 is OFF");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It On");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);
                    if (bluetooh_value == '1')
                    {
                        LED_voidOn(DIO_PORTB, DIO_PIN0, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                break;

            case ('3'):

                DIO_voidGetPinValue(DIO_PORTA, DIO_PIN2, &led_status);
                
                if (led_status == 1)
                {
                    BL_voidTxString("Light 3 is On");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It Off");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);

                    if (bluetooh_value == '1')
                    {
                        LED_voidOff(DIO_PORTA, DIO_PIN2, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                else if (led_status == 0)
                {
                    BL_voidTxString("Light 3 is OFF");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It On");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);

                    if (bluetooh_value == '1')
                    {
                        LED_voidOn(DIO_PORTA, DIO_PIN2, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                break;

            case ('4'):

                DIO_voidGetPinValue(DIO_PORTA, DIO_PIN3, &led_status);
                
                if (led_status == 1)
                {
                    BL_voidTxString("Light 4 is On");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It Off");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);

                    if (bluetooh_value == '1')
                    {
                        LED_voidOff(DIO_PORTA, DIO_PIN3, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                else if (led_status == 0)
                {
                    BL_voidTxString("Light 4 is OFF");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It On");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);

                    if (bluetooh_value == '1')
                    {
                        LED_voidOn(DIO_PORTA, DIO_PIN3, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                break;

            case ('5'):

                DIO_voidGetPinValue(DIO_PORTD, DIO_PIN2, &led_status);
                
                if (led_status == 1)
                {
                    BL_voidTxString("Light 5 is On");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It Off");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);

                    if (bluetooh_value == '1')
                    {
                        LED_voidOff(DIO_PORTD, DIO_PIN2, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                else if (led_status == 0)
                {
                    BL_voidTxString("Light 5 is OFF");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It On");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);

                    if (bluetooh_value == '1')
                    {
                        LED_voidOn(DIO_PORTD, DIO_PIN2, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                break;

                
			// if the user choose light 6 (DIMMER LED)

            case ('6'):
				// Dimmer can be controlled using TMR1 PWM mode range from 0 to 100 with -+10% step
                if (dimmer_brightness > 0)
                {
					 BL_voidTxChar('\r');
                    BL_voidTxString("Light 6 is On");
					BL_voidTxChar('\r');
					sprintf(DimmerString, "Brightness: %d%", dimmer_brightness);
					BL_voidTxString(DimmerString);
                    BL_voidTxChar('\r');
                    BL_voidTxString("1)+10 2)-10 0)H");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);
					while (bluetooh_value != 0)
					{
						if (bluetooh_value == '1')
						{
							dimmer_brightness += 10;
							PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							sprintf(DimmerString, "Brightness: %d%", dimmer_brightness);
							BL_voidTxString(DimmerString);
                    		BL_voidTxChar('\r');
                    		BL_voidTxString("1)+10 2)-10 0)H");
							BL_voidTxChar('\r');
							// check if is the brightness is more than 100
							if (dimmer_brightness > 100)
							{
								//block increasing the brightness above 100
								dimmer_brightness = 100;
								PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							}
							break;													
						}
						else if (bluetooh_value == '2')
						{
							dimmer_brightness -= 10;
							PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							sprintf(DimmerString, "Brightness: %d%", dimmer_brightness);
							BL_voidTxString(DimmerString);
                    		BL_voidTxChar('\r');
                    		BL_voidTxString("1)+10 2)-10 0)H");
							BL_voidTxChar('\r');
							// check if is the brightness is less than 0
							if (dimmer_brightness < 0)
							{
								//block decreasing the brightness below 0
								dimmer_brightness = 0;
								PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							}
							break;
						}
						// if the user choose to go to home
						else if (bluetooh_value == '0')
						{
							
							break;
						}	
						break;					
	
					}
					
                }
                else if (dimmer_brightness == 0)
                {
                    BL_voidTxString("Light 6 is OFF");
					_delay_ms(1000);
					BL_voidTxChar('\r');
					sprintf(DimmerString, "Brightness: %d%", dimmer_brightness);
					BL_voidTxString(DimmerString);
                    BL_voidTxChar('\r');
                    BL_voidTxString("1)+10 2)-10 0)H");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);
					while (bluetooh_value != 0)
					{
						if (bluetooh_value == '1')
						{
							dimmer_brightness += 10;
							PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							sprintf(DimmerString, "Brightness: %d%", dimmer_brightness);
							BL_voidTxString(DimmerString);
                    		BL_voidTxChar('\r');
                    		BL_voidTxString("1)+10 2)-10 0)H");
							BL_voidTxChar('\r');
							if (dimmer_brightness > 100)
							{
								dimmer_brightness = 100;
								PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							}
							break;
						
							
						}
						else if (bluetooh_value == '2')
						{
							dimmer_brightness -= 10;
							PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							sprintf(DimmerString, "Brightness: %d%", dimmer_brightness);
							BL_voidTxString(DimmerString);
                    		BL_voidTxChar('\r');
                    		BL_voidTxString("1)+10 2)-10 0)H");
							BL_voidTxChar('\r');
							if (dimmer_brightness < 0)
							{
								dimmer_brightness = 0;
								PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							}
							break;
						}
						else if (bluetooh_value == '0')
						{
							
							break;
						}
						
					}				
                }
                break;
		
            }
			break;

			case ('3'):
			
				// checking the temperature from the ADC before displaying it
				ADC_voidGetDigitalValue(ADC_CHANNEL_0, &local_temp); 
				sprintf(tempString, "Room Temp: %d c", local_temp);
				BL_voidTxString(tempString);
				BL_voidTxChar('\r');
				BL_voidTxString("0-go to home");
				BL_voidTxChar('\r');
				BL_voidRxChar(&bluetooh_value);	
				if (bluetooh_value=='0')
				{
					
				}
				break;

			case ('4'):
				// checking the door status before displaying it
				if (door_angle==0)
				{
					BL_voidTxString("Door is closed");
					BL_voidTxChar('\r');
					BL_voidTxString("1-Open Door 0-Home");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);
					BL_voidTxChar('\r');
					if (bluetooh_value=='1')
					{
						BL_voidTxString("Door is opening");
						SERVO_voidStartByAngle(90);
						door_angle=90;
						
					}
					// if the user choose to go to home
					else if (bluetooh_value=='0')
					{
						break;
					}
					break;

				}
				else if (door_angle==90)
				{
					BL_voidTxString("Door is open");
					BL_voidTxChar('\r');
					BL_voidTxString("1-Close Door 0-Home");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);
					BL_voidTxChar('\r');
					if (bluetooh_value=='1')
					{
						BL_voidTxString("Door is closing");
						SERVO_voidStartByAngle(0);
						door_angle=0;
						
					}
					else if (bluetooh_value=='0')
					{
						break;
					}
				}			
			break;


			case ('5'):
			// this case is only for admin to change the username and password (Admin is only remote typeuser)
			HOME_voidChangeUserNameAndPass();
					
        break;
        }
    
	}


void KPD_Interface_RemoteUser(void)
{
	//this is the remote user interface to control the smart home (same as the admin but with less options without(door control,changing username and password))
	TMR0_SetCallBackCTC(&Idle_RemoteAction);
	BL_voidTxChar('\r');
	BL_voidTxString("1-AC 2-light");
	BL_voidTxChar('\r');
	BL_voidTxString("3-temp 4-Door");
	BL_voidTxChar('\r');
	TMR0_voidStart();
	BL_voidRxChar(&bluetooh_value);
	TMR0_voidStop();
	switch (bluetooh_value)
	{
	case ('1'):
		// DIO_voidGetPinValue()/////////////////////////////
		BL_voidTxString("AC Is On/off");
        BL_voidTxChar('\r');
        ADC_voidGetDigitalValue(ADC_CHANNEL_0, &local_temp); 
				sprintf(tempString, "Room Temp: %d c", local_temp);
				BL_voidTxString(tempString);
				BL_voidTxChar('\r');
				BL_voidTxString("0-go to home");
				BL_voidTxChar('\r');
				TMR0_voidStart();
				BL_voidRxChar(&bluetooh_value);
				TMR0_voidStop();
				if (bluetooh_value=='0')
				{
					
				}
		break;
	
	case ('2'):

       
	   		BL_voidTxChar('\r');     
            BL_voidTxString("Choose light to");
            BL_voidTxChar('\r');
            BL_voidTxString("control(1-6)");
			BL_voidTxChar('\r');
			BL_voidTxChar('\r');
            TMR0_voidStart();
			BL_voidRxChar(&bluetooh_value);
            TMR0_voidStop();
            switch (bluetooh_value)
            {
            case ('1'):

                DIO_voidGetPinValue(DIO_PORTD, DIO_PIN3, &led_status);
                
                if (led_status == 1)
                {
                    BL_voidTxString("Light 1 is On");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It Off");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);
                    if (bluetooh_value == '1')
                    {
                        LED_voidOff(DIO_PORTD, DIO_PIN3, LED_FORWARD_CONNECTION);
                    }
                    
					break;
                }
                else if (led_status == 0)
                {
                    BL_voidTxString("Light 1 is OFF");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It On");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);
                    if (bluetooh_value == '1')
                    {
                        LED_voidOn(DIO_PORTD, DIO_PIN3, LED_FORWARD_CONNECTION);
                    }
                    
                }
                break;

            case ('2'):

                DIO_voidGetPinValue(DIO_PORTB, DIO_PIN0, &led_status);
                
                if (led_status == 1)
                {
                    BL_voidTxString("Light 2 is On");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It Off");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);
                    if (bluetooh_value == '1')
                    {
                        LED_voidOff(DIO_PORTB, DIO_PIN0, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                else if (led_status == 0)
                {
                    BL_voidTxString("Light 2 is OFF");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It On");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);
                    if (bluetooh_value == '1')
                    {
                        LED_voidOn(DIO_PORTB, DIO_PIN0, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                break;

            case ('3'):

                DIO_voidGetPinValue(DIO_PORTA, DIO_PIN2, &led_status);
                
                if (led_status == 1)
                {
                    BL_voidTxString("Light 3 is On");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It Off");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);

                    if (bluetooh_value == '1')
                    {
                        LED_voidOff(DIO_PORTA, DIO_PIN2, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                else if (led_status == 0)
                {
                    BL_voidTxString("Light 3 is OFF");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It On");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);

                    if (bluetooh_value == '1')
                    {
                        LED_voidOn(DIO_PORTA, DIO_PIN2, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                break;

            case ('4'):

                DIO_voidGetPinValue(DIO_PORTA, DIO_PIN3, &led_status);
                
                if (led_status == 1)
                {
                    BL_voidTxString("Light 4 is On");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It Off");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);

                    if (bluetooh_value == '1')
                    {
                        LED_voidOff(DIO_PORTA, DIO_PIN3, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                else if (led_status == 0)
                {
                    BL_voidTxString("Light 4 is OFF");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It On");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);

                    if (bluetooh_value == '1')
                    {
                        LED_voidOn(DIO_PORTA, DIO_PIN3, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                break;

            case ('5'):

                DIO_voidGetPinValue(DIO_PORTD, DIO_PIN2, &led_status);
                
                if (led_status == 1)
                {
                    BL_voidTxString("Light 5 is On");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It Off");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);

                    if (bluetooh_value == '1')
                    {
                        LED_voidOff(DIO_PORTD, DIO_PIN2, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                else if (led_status == 0)
                {
                    BL_voidTxString("Light 5 is OFF");
                    BL_voidTxChar('\r');
                    BL_voidTxString("1-To Turn It On");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);

                    if (bluetooh_value == '1')
                    {
                        LED_voidOn(DIO_PORTD, DIO_PIN2, LED_FORWARD_CONNECTION);
                    }
                    bluetooh_value = KPD_Not_Pressed;
                }
                break;

                
			// if the user choose light 6 (DIMMER LED)

            case ('6'):
				
                
				
                if (dimmer_brightness > 0)
                {
					 BL_voidTxChar('\r');
                    BL_voidTxString("Light 6 is On");
					BL_voidTxChar('\r');
					sprintf(DimmerString, "Brightness: %d%", dimmer_brightness);
					BL_voidTxString(DimmerString);
                    BL_voidTxChar('\r');
                    BL_voidTxString("1)+10 2)-10 0)H");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);
					while (bluetooh_value != 0)
					{
						if (bluetooh_value == '1')
						{
							dimmer_brightness += 10;
							PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							sprintf(DimmerString, "Brightness: %d%", dimmer_brightness);
							BL_voidTxString(DimmerString);
                    		BL_voidTxChar('\r');
                    		BL_voidTxString("1)+10 2)-10 0)H");
							BL_voidTxChar('\r');
							if (dimmer_brightness > 100)
							{
								dimmer_brightness = 100;
								PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							}
							break;													
						}
						else if (bluetooh_value == '2')
						{
							dimmer_brightness -= 10;
							PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							sprintf(DimmerString, "Brightness: %d%", dimmer_brightness);
							BL_voidTxString(DimmerString);
                    		BL_voidTxChar('\r');
                    		BL_voidTxString("1)+10 2)-10 0)H");
							BL_voidTxChar('\r');
							if (dimmer_brightness < 0)
							{
								dimmer_brightness = 0;
								PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							}
							break;
						}
						else if (bluetooh_value == '0')
						{
							
							break;
						}	
						break;					
	
					}
					
                }
                else if (dimmer_brightness == 0)
                {
                    BL_voidTxString("Light 6 is OFF");
					_delay_ms(1000);
					BL_voidTxChar('\r');
					sprintf(DimmerString, "Brightness: %d%", dimmer_brightness);
					BL_voidTxString(DimmerString);
                    BL_voidTxChar('\r');
                    BL_voidTxString("1)+10 2)-10 0)H");
					BL_voidTxChar('\r');
					BL_voidRxChar(&bluetooh_value);
					while (bluetooh_value != 0)
					{
						if (bluetooh_value == '1')
						{
							dimmer_brightness += 10;
							PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							sprintf(DimmerString, "Brightness: %d%", dimmer_brightness);
							BL_voidTxString(DimmerString);
                    		BL_voidTxChar('\r');
                    		BL_voidTxString("1)+10 2)-10 0)H");
							BL_voidTxChar('\r');
							if (dimmer_brightness > 100)
							{
								dimmer_brightness = 100;
								PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							}
							break;
						
							
						}
						else if (bluetooh_value == '2')
						{
							dimmer_brightness -= 10;
							PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							sprintf(DimmerString, "Brightness: %d%", dimmer_brightness);
							BL_voidTxString(DimmerString);
                    		BL_voidTxChar('\r');
                    		BL_voidTxString("1)+10 2)-10 0)H");
							BL_voidTxChar('\r');
							if (dimmer_brightness < 0)
							{
								dimmer_brightness = 0;
								PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							}
							break;
						}
						else if (bluetooh_value == '0')
						{
							
							break;
						}
						
					}				
                }
                break;
		
            }
			break;

			case ('3'):
			
				
				ADC_voidGetDigitalValue(ADC_CHANNEL_0, &local_temp); 
				sprintf(tempString, "Room Temp: %d c", local_temp);
				BL_voidTxString(tempString);
				BL_voidTxChar('\r');
				BL_voidTxString("0-go to home");
				BL_voidTxChar('\r');
				BL_voidRxChar(&bluetooh_value);	
				if (bluetooh_value=='0')
				{
					
				}

					
        break;
        }
    
	}



void KPD_Interface_Localuser(void)
{
	//this is the local user interface to control the smart home all user allowed functions using lcd to display options and KPD for interaction
		//reseting all KPD variables for new values to be entered
        Reset_AllKPDValues();
		/*using the tmr0 for the 5 secs idle 
		1-set the ctc function to do after interrupt flag is up
		2-start tmr0 before busy wait for KPD to avoid starting the tmr0 counter when the lcd didnt finish printing the options
		3-after the wihle loop is finished make sure to stop the tmr0 to avoid going to the idle function
		*/
	
		//setting the TRM0 ctc interrupt function
        TMR0_SetCallBackCTC(&Idle_Action);
		//starting the timer0
        TMR0_voidStart();
        LCD_voidClear();
        LCD_voidDisplayString((u8 *)"1-AC 2-light");
        LCD_voidSendCommand(Write_SecondLine);
        LCD_voidDisplayString((u8 *)"3-temp 4-Door");
        Reset_AllKPDValues();

        // busy wait for KPD to get the value. timr0 is still counting for the 5 sec idle to go to interrupt function
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
		//stopping timer after reciving the value to avoid tmr0 from going to idle function
        TMR0_voidStop();
        switch (Local_copyKPDValue)
        {
        case ('1'):

            LCD_voidClear();
            LCD_voidDisplayStringDelay((u8 *)"AC Is On/off 0-H");
            LCD_voidSendCommand(Write_SecondLine);
			ADC_voidGetDigitalValue(ADC_CHANNEL_0, &local_temp);
            LCD_voidDisplayStringDelay((u8 *)"Room Temp:  c");
			LCD_voidGoTOSpecificPosition(LCD_LINE_TWO, 12);
			LCD_voidDisplayNumber(local_temp);
			while (local_KPDSelectValue == KPD_Not_Pressed)
			{
				KPD_voidGetValue(&local_KPDSelectValue);
				ADC_voidGetDigitalValue(ADC_CHANNEL_0, &local_temp);
				LCD_voidGoTOSpecificPosition(LCD_LINE_TWO, 12);
				LCD_voidDisplayNumber(local_temp);
				if (local_KPDSelectValue == '0')
				{
					local_KPDSelectValue = KPD_Not_Pressed;
					break;
				}
				
			}
			

            break;
			

        case ('2'):

            LCD_voidClear();
            LCD_voidDisplayStringDelay((u8 *)"Choose light to");
            LCD_voidSendCommand(Write_SecondLine);
            LCD_voidDisplayStringDelay((u8 *)"control(1-6)");

            TMR0_SetCallBackCTC(&Idle_Action);
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

                DIO_voidGetPinValue(DIO_PORTD, DIO_PIN3, &led_status);
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
                        LED_voidOff(DIO_PORTD, DIO_PIN3, LED_FORWARD_CONNECTION);
                    }
                    Reset_AllKPDValues();
					break;
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
                        LED_voidOn(DIO_PORTD, DIO_PIN3, LED_FORWARD_CONNECTION);
                    }
                    Reset_AllKPDValues();
                }
                break;

            case ('2'):

                DIO_voidGetPinValue(DIO_PORTD, DIO_PIN4, &led_status);
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
                        LED_voidOff(DIO_PORTD, DIO_PIN4, LED_FORWARD_CONNECTION);
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
                        LED_voidOn(DIO_PORTD, DIO_PIN4, LED_FORWARD_CONNECTION);
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
				
                if (dimmer_brightness > 0)
                {
                    LCD_voidDisplayStringDelay((u8 *)"Light 6 is On");
					_delay_ms(1000);
					LCD_voidClear();
					LCD_voidDisplayString("Brightness:  %");
					LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,13);
					LCD_voidDisplayNumber(dimmer_brightness);
                    LCD_voidSendCommand(Write_SecondLine);
                    LCD_voidDisplayStringDelay((u8 *)"1)+10 2)-10 0)H");
					while (local_lightStatus == KPD_Not_Pressed)
					{
						KPD_voidGetValue(&local_lightStatus);
						if (local_lightStatus == '1')
						{
							dimmer_brightness += 10;
							PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,13);
							LCD_voidDisplayNumber(dimmer_brightness);
							if (dimmer_brightness > 100)
							{
								dimmer_brightness = 100;
								PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							}
						
							
						}
						else if (local_lightStatus == '2')
						{
							dimmer_brightness -= 10;
							PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,13);
							LCD_voidDisplayNumber(dimmer_brightness);
							if (dimmer_brightness < 0)
							{
								dimmer_brightness = 0;
								PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							}
						}
						else if (local_lightStatus == '0')
						{
							LCD_voidClear();
							break;
						}						
						
					}
					
                }
                else if (led_status == 0)
                {
                    LCD_voidDisplayStringDelay((u8 *)"Light 6 is OFF");
					_delay_ms(1000);
                    LCD_voidClear();
					LCD_voidDisplayString("Brightness:  %");
					LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,13);
					LCD_voidDisplayNumber(dimmer_brightness);
                    LCD_voidSendCommand(Write_SecondLine);
                    LCD_voidDisplayStringDelay((u8 *)"1)+10 2)-10 0)H");
					while (local_lightStatus == KPD_Not_Pressed)
					{
						KPD_voidGetValue(&local_lightStatus);
						if (local_lightStatus == '1')
						{
							dimmer_brightness += 10;
							PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,13);
							LCD_voidDisplayNumber(dimmer_brightness);
							if (dimmer_brightness > 100)
							{
								dimmer_brightness = 100;
								PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							}
						
							
						}
						else if (local_lightStatus == '2')
						{
							dimmer_brightness -= 10;
							PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,13);
							LCD_voidDisplayNumber(dimmer_brightness);
							if (dimmer_brightness < 0)
							{
								dimmer_brightness = 0;
								PWM_voidGenerateChannel_1A(1000, dimmer_brightness);
							}
						}
						else if (local_lightStatus == '0')
						{
							LCD_voidClear();
							break;
						}
						
					}				
                }
                break;
		
            }
			break;

			case ('3'):
			
				LCD_voidClear();
				ADC_voidGetDigitalValue(ADC_CHANNEL_0, &local_temp);
				LCD_voidSendCommand(Write_FirstLine);
				LCD_voidDisplayString((u8 *)"Room Temp:  c");
				LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,11);
				LCD_voidDisplayNumber(local_temp);
				LCD_voidDisplayChar('c');
				LCD_voidSendCommand(Write_SecondLine);
				LCD_voidDisplayStringDelay((u8 *)"0-go to home");
				while(local_KPDIdleValue==KPD_Not_Pressed)
				{
					KPD_voidGetValue(&local_KPDIdleValue);
					Display_temp();
				}	
				if (local_KPDIdleValue=='0')
				{
					LCD_voidClear();
				}
			break;



			break;
			
		Reset_AllKPDValues();
        break;
        }
    
}

void WelcomeScreenRemote()
// this function is for greeting the user in remote user interface
{
    BL_voidTxString(" Welcome to your");
    BL_voidTxChar('\r');
    BL_voidTxString("Smart Home");
    BL_voidTxChar('\r');
    _delay_ms(1000);
}

void WelcomeScreenLocal()
// this function is for greeting the user in local user interface
{
    LCD_voidDisplayStringDelay((u8 *)" Welcome to your");
    LCD_voidSendCommand(Write_SecondLine);
    LCD_voidDisplayStringDelay((u8 *)"   Smart Home");
    _delay_ms(1000);
}

void CheckTempForAc()
//this function is for cheking the temperature and turn on the AC if the temperature is above 28 and turn it off if the temperature is below 21
// this is the function that get called for tmr2 interrupt
{
	ADC_voidGetDigitalValue(ADC_CHANNEL_0, &local_temp);
	if (local_temp > 28)
	{
		DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);
		
	}
	else if (local_temp <21)
	
	{
		DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH);
	}

}




void Idle_RemoteAction()
//this function is for the remote user interface to go to the idle function after 5 sec of inactivity
// tmr0 interrupt function for the remote user 
{ 
    BL_voidTxChar('\r');
	Display_Remotetemp();
	BL_voidTxString("0-Go to Home");
	BL_voidTxChar('\r');
	BL_voidRxChar(&bluetooh_value);
    if (bluetooh_value == '0')
    {
        TMR0clear_flag();
		
    }
}

void Display_Remotetemp(void)
//function for getting temp value from temp sensor and displaying it for remote user
{
	ADC_voidGetDigitalValue(ADC_CHANNEL_0, &local_temp); 
	sprintf(tempString, "Room Temp: %d c", local_temp);
	BL_voidTxString(tempString);
	BL_voidTxChar('\r');
}

void Idle_Action()
//this function is for the local user interface to go to the idle function after 5 sec of inactivity
// tmr0 interrupt function for the local user
{ 
    LCD_voidClear();
	LCD_voidSendCommand(Write_FirstLine);
	LCD_voidDisplayString((u8 *)"Room Temp:   c");
	Display_temp();
	LCD_voidSendCommand(Write_SecondLine);
	LCD_voidDisplayString("0-Go to Home");
	
    while (local_KPDIdleValue == KPD_Not_Pressed)
    {
        KPD_voidGetValue(&local_KPDIdleValue);
		Display_temp();

        
    }
    if (local_KPDIdleValue == '0')
    {
        LCD_voidClear();
    }
    TMR0clear_flag();
    LCD_voidClear();

}

void Display_temp(void)
//function for getting temp value from temp sensor and displaying it for local user
{
	ADC_voidGetDigitalValue(ADC_CHANNEL_0, &local_temp);
	LCD_voidGoTOSpecificPosition(LCD_LINE_ONE,11);
	LCD_voidDisplayNumber(local_temp);

}

void Reset_AllKPDValues()
//function for reseting all KPD values for new values to be entered
{
    Local_copyKPDValue = KPD_Not_Pressed;
    local_lightNum = KPD_Not_Pressed;
    local_lightStatus = KPD_Not_Pressed;
	local_KPDIdleValue = KPD_Not_Pressed;
}

