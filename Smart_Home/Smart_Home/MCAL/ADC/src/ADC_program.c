/*
 * ADC_program.c
 *
 * Created: 17-Feb-2024 10:19:38 PM
 *  Author: Kareem Hussein
 */ 


/* UTILES_LIB */
#include "../../../UTILS_LIB/STD_TYPES.h"
#include "../../../UTILS_LIB/BIT_MATH.h"

/* MCAL */
#include "../../../MCAL/ADC/inc/ADC_interface.h"
#include "../../../MCAL/ADC/inc/ADC_register.h"


void ADC_voidInit(u8 copy_u8ReferenceVoltage)
{
	//Select the voltage source
	switch(copy_u8ReferenceVoltage)
	{
		case ADC_REFERENCE_AVCC:
		SET_BIT(ADMUX_REG,REFS0);
		CLR_BIT(ADMUX_REG,REFS1);
		break;
		
		case ADC_REFERENCE_AREF:
		CLR_BIT(ADMUX_REG,REFS0);
		CLR_BIT(ADMUX_REG,REFS1);
		break;
		
		// Vref = 2.56V internal
		case ADC_REFERENCE_INTRNAL:
		SET_BIT(ADMUX_REG,REFS0);
		SET_BIT(ADMUX_REG,REFS1);
		break;
	}
	
	//Select Right Adjustment
	CLR_BIT(ADMUX_REG,ADLAR);
	
	//Clear the auto trigger bit - Single Conversation Mode
	CLR_BIT(ADCSRA_REG,ADATE);
	
	//Disable ADC Interrupt
	CLR_BIT(ADCSRA_REG,ADIE);
	
	//Prescaler 128 For 16MHZ (125 KHZ)
	SET_BIT(ADCSRA_REG,ADPS2);
	SET_BIT(ADCSRA_REG,ADPS1);
	SET_BIT(ADCSRA_REG,ADPS0);
	
	//ADC Enable (make the enable the last step)
	SET_BIT(ADCSRA_REG,ADEN);
}


void ADC_voidGetDigitalValue(u8 copy_u8ChannelNumber, u16* copy_pu16DigitalValue)
{
	if(copy_pu16DigitalValue!=NULL)
	{
		//1. Select channel
		ADMUX_REG &= 0xE0; //0b11100000
		// Select Channel Number 
		ADMUX_REG |= copy_u8ChannelNumber;
		
		//2. Start Conversition
	    SET_BIT(ADCSRA_REG,ADSC);
		// Busy Wait for ADC Flag 
		while(0 == GET_BIT(ADCSRA_REG,ADIF));
		//Clear Flag(write one to clear)
		SET_BIT(ADCSRA_REG,ADIF);
		
		*copy_pu16DigitalValue = ADC_u16_REG;
	}
	else
	{
		// return Error state
	}
}