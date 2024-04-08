/*
 * config.h
 *
 * Created: 3/20/2024 7:58:51 PM
 *  Author: Karim
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_


//					MACROS FOR COLUMNS					//
#define KPD_C0_Port		DIO_PORTB
#define KPD_C0_Pin		DIO_PIN4

#define KPD_C1_Port		DIO_PORTB
#define KPD_C1_Pin		DIO_PIN5

#define KPD_C2_Port		DIO_PORTB
#define KPD_C2_Pin		DIO_PIN6

// #define KPD_C3_Port		DIO_PORTC
// #define KPD_C3_Pin		DIO_PIN3


//					MACROS FOR ROWS					//

#define KPD_R0_Port		DIO_PORTC
#define KPD_R0_Pin		DIO_PIN3

#define KPD_R1_Port		DIO_PORTC
#define KPD_R1_Pin		DIO_PIN4

#define KPD_R2_Port		DIO_PORTC
#define KPD_R2_Pin		DIO_PIN5

#define KPD_R3_Port		DIO_PORTC
#define KPD_R3_Pin		DIO_PIN6

//					Arranging Keys For The KeyPad					//

#define KPD_Keys		{{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}}


#endif /* CONFIG_H_ */