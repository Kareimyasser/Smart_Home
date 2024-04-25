/*
 * KEYPAD_config.h
 *
 * Created: 2/10/2024 8:17:28 PM
 *  Author: Saed Abozied
 */ 


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

//macros for keypad rows ports&pins config
//inputs
#define KEYPAD_ROW0_PORT	DIO_PORTC
#define KEYPAD_ROW0_PIN		DIO_PIN3

#define KEYPAD_ROW1_PORT	DIO_PORTC
#define KEYPAD_ROW1_PIN		DIO_PIN4

#define KEYPAD_ROW2_PORT	DIO_PORTC
#define KEYPAD_ROW2_PIN		DIO_PIN5

#define KEYPAD_ROW3_PORT	DIO_PORTC
#define KEYPAD_ROW3_PIN		DIO_PIN6


//macros for keypad columns ports&pins config
//outs
#define KEYPAD_COL0_PORT	DIO_PORTB
#define KEYPAD_COL0_PIN		DIO_PIN4
			   
#define KEYPAD_COL1_PORT	DIO_PORTB
#define KEYPAD_COL1_PIN		DIO_PIN5
			   
#define KEYPAD_COL2_PORT	DIO_PORTB
#define KEYPAD_COL2_PIN		DIO_PIN6
			  
#define KEYPAD_COL3_PORT	DIO_PORTB
#define KEYPAD_COL3_PIN		DIO_PIN7


#define KeyPAD_KEYS		{{'1','2','3','A'},\
						{'4','5','6','B'},\
						{'7','8','9','C'},\
						{'*','0','#','D'}}	


#endif /* KEYPAD_CONFIG_H_ */