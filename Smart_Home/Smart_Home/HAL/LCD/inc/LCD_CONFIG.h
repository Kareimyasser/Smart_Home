/*
 * LCD_CONFIG.h
 *
 * Created: 3/12/2024 5:46:15 AM
 *  Author: Karim
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_
//RS PIN
#define LCD_RS_PORT		DIO_PORTB
#define LCD_RS_PIN		DIO_PIN1
//RW PIN
#define LCD_RW_PORT		DIO_PORTB
#define LCD_RW_PIN		DIO_PIN2
//E PIN
#define LCD_EN_PORT		DIO_PORTB
#define LCD_EN_PIN		DIO_PIN3

//4 BIT MODE PIN CONFIG
#define	LCD_D4_PORT		DIO_PORTA
#define	LCD_D4_PIN		DIO_PIN4

#define	LCD_D5_PORT		DIO_PORTA
#define	LCD_D5_PIN		DIO_PIN5

#define	LCD_D6_PORT		DIO_PORTA
#define	LCD_D6_PIN		DIO_PIN6

#define	LCD_D7_PORT		DIO_PORTA
#define	LCD_D7_PIN		DIO_PIN7


// MACROS
#define Cursor_ShiftLeft		/*0x10*/0b00010000
#define Cursor_ShiftRight		/*0x24*/0b00010100
#define	Display_ShiftLeft				0b00011000
#define	Display_ShiftRight				0b00011100

#define Write_FirstLine					0x80
#define Write_SecondLine				0XC0

#endif /* LCD_CONFIG_H_ */