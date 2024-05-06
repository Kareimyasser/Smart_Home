#ifndef SmartHome
#define SmartHome

#define accessPermited 1
#define accessDenied 0

void APP_init(void);
void Idle_Action();
void WelcomeScreen();
void action(void);
void KPD_Interface(void);
void Reset_AllKPDValues();
void Display_temp(void);



void HOME_voidInit(void);

void HOME_voidLocalGetUserAndPass(u8* copy_pu8LocalUserName,u8* copy_pu8LocalUserPass);
void HOME_voidCheckUserAndPass(u8 copy_u8AccessType,u8* copy_pu8UserType );
#endif