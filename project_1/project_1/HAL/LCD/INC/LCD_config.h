/*
 * LCD_config.h
 *
 * Created: 2/9/2024 10:51:17 PM
 *  Author: Saed Abozied
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

//control pins
#define LCD_RS_PORT 		DIO_PORTB
#define LCD_RS_PIN			DIO_PIN1

#define LCD_RW_PORT 		DIO_PORTB
#define LCD_RW_PIN			DIO_PIN2

#define LCD_E_PORT 			DIO_PORTB
#define LCD_E_PIN			DIO_PIN3

//data pins configure
#define LCD_D4_PORT 		DIO_PORTA
#define LCD_D4_PIN			DIO_PIN4

#define LCD_D5_PORT 		DIO_PORTA
#define LCD_D5_PIN			DIO_PIN5

#define LCD_D6_PORT 		DIO_PORTA
#define LCD_D6_PIN			DIO_PIN6

#define LCD_D7_PORT 		DIO_PORTA
#define LCD_D7_PIN			DIO_PIN7

#define LCD_MAX_DISPLAY_CHAR	40


#endif /* LCD_CONFIG_H_ */