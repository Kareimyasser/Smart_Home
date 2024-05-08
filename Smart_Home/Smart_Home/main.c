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

extern u8 global_accessType;
global_accessType = accessPermited;

u8 user_type =HOME_REMOTE_USER;

int main()
{
	u8 suc;
	APP_init();


	// HOME_voidFireAnALarm(HOME_LOGIN_FAILED);
	// BL_voidTxString	("ok");
	// BL_voidTxChar('\n');
	while(1)
	{
		
		//HOME_voidCheckUserAndPass(HOME_REMOTE_ACCESS,&suc);
		//
		//switch(suc)
		//{
		//	case 4:
		//	BL_voidTxChar('u');
		//	break;
		//	case 3:
		//	BL_voidTxChar('D');
		//	break;
		//	case 5:
		//	BL_voidTxChar('F');
		//	break;
		//}
		
		
		
		// HOME_voidChangeUserNameAndPass();
		if (global_accessType ==accessPermited)
		{
			if (user_type == HOME_REMOTE_ADMIN)
			{
				KPD_Interface_RemoteAdmin();
			}
			else if (user_type == HOME_REMOTE_USER)
			{
				KPD_Interface_RemoteUser();
			}

			else if (user_type == HOME_LOCAL_USER)
			{
				KPD_Interface_Localuser();
			}

			
		}
		else if (global_accessType ==accessDenied)
		{
			LCD_voidDisplayString((u8*)"Access Denied");
			break;
		}
		
		
		
	}
}


