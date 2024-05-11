/*
 * Choose_test.c
 *
 * Created: 3/24/2024 6:24:36 AM
 * Author : Karim
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



extern u8 usertype;

int main()
{
	//use for first time to init users and pass  then comment this line and download again
	void APP_init();
	
	//check alarm
	// HOME_voidFireAnALarm(usertype);
	
	//init home  
	HOME_voidInit();
	

	while(1)
	{
		

		// display the welcome screen
		WelcomeScreenLocal();
		WelcomeScreenRemote();
		HOME_voidRemoteGetUserAndPass(HOME_REMOTE_ACCESS,&usertype);

		// GetUserType();
		
			if (usertype == HOME_REMOTE_ADMIN)
			{
				KPD_Interface_RemoteAdmin();
			}
			else if (usertype == HOME_REMOTE_USER)
			{
				KPD_Interface_RemoteUser();
			}

			else if (usertype == HOME_LOCAL_USER)
			{
				KPD_Interface_Localuser();
			}

	
		
			else if (usertype ==HOME_LOGIN_FAILED)
			{
			LCD_voidDisplayString((u8*)"Access Denied");
			break;
			}
		
		
		
	}
}