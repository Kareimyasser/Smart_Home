#ifndef SmartHome
#define SmartHome





#define accessPermited 1
#define accessDenied 0

#define HOME_MAX_NUMBER_OF_TRIALS	  			3
#define HOME_USER_NAME_AND_PASS_MAX_LENGTh		8
#define HOME_MAX_NUM_OF_LOCAL_USER				5


#define HOME_LOCAL_ADMIN						1
#define HOME_LOCAL_USER							2
#define HOME_REMOTE_ADMIN						3
#define HOME_REMOTE_USER						4
#define HOME_LOGIN_FAILED						5
#define HOME_NO_LOGIN							6

#define HOME_LOCAL_ACCESS						1
#define HOME_REMOTE_ACCESS						2

#define HOME_ALARM_LOCATION						180
#define HOME_ALARM_VALUE						0xff
#define HOME_ALARM_CLEAR_VALUE					0x00

#define Led_freq                                10000


void APP_init(void);
void Idle_Action();
void WelcomeScreen();
void action(void);
void KPD_Interface_user(void);
void KPD_Interface_RemoteAdmin(void);
void Reset_AllKPDValues();
void Display_temp(void);



void HOME_voidInit(void);
void HOME_voidLocalGetUserAndPass(u8* copy_pu8LocalUserName,u8* copy_pu8LocalUserPass);
void HOME_voidRemoteGetUserAndPass(u8* copy_pu8RemoteUserName,u8* copy_pu8RemoteUserPass);
void HOME_voidCheckUserAndPass(u8 copy_u8AccessType,u8* copy_pu8UserStatus );
void HOME_voidChangeUserNameAndPass(void);
void HOME_voidFireAnALarm(u8 copy_pu8UserStatus);


#endif