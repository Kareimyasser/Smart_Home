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
#include "../../../HAL/LCD/inc/LCD_interface.h"

void TEMP_SENSOR_voidReadTemp(u16* copy_u16Temp)
{
    u16 local_u16AdcValue;
    //read the raw digital value from ADC register
    ADC_voidGetDigitalValue(0, &local_u16AdcValue);
	//4 is the step size of adc compared to step size of sensor
    *copy_u16Temp = local_u16AdcValue/4;
}