/*
 * ADC_interface.h
 *
 * Created: 2/17/2024 10:19:13 PM
 *  Author: Kareem Hussein
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


// Macros for Channel Number as Single Ended Input
#define ADC_CHANNEL_0                   0
#define ADC_CHANNEL_1                   1
#define ADC_CHANNEL_2                   2
#define ADC_CHANNEL_3                   3
#define ADC_CHANNEL_4                   4
#define ADC_CHANNEL_5                   5
#define ADC_CHANNEL_6                   6
#define ADC_CHANNEL_7                   7

// Macros for Reference Voltage 
#define ADC_REFERENCE_AVCC              1
#define ADC_REFERENCE_AREF              2
#define ADC_REFERENCE_INTRNAL			3


              /*************** APIS PROTOTYPES ***************/

void ADC_voidInit           (u8 copy_u8ReferenceVoltage);
void ADC_voidGetDigitalValue(u8 copy_u8ChannelNumber, u16* copy_pu16DigitalValue);


#endif /* ADC_INTERFACE_H_ */