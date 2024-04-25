/******************************************************************************
 *                                                                            *
 *************************  SWC     : BIT MATH        *************************
 *************************  Date    : 27/01/2024      *************************
 *************************  Author  : Saed Abozied  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/





#ifndef BIT_MATH_H
#define BIT_MATH_H


#define SET_BIT(REG,BIT_NUM)   		REG|=(1<<BIT_NUM)
#define CLR_BIT(REG,BIT_NUM) 		REG&=~(1<<BIT_NUM)
#define TOG_BIT(REG,BIT_NUM) 		REG^=(1<<BIT_NUM)
#define GET_BIT(REG,BIT_NUM) 		((REG>>BIT_NUM)&0X01)













#endif