/*
 * TMR0_config.h
 *
 * Created: 4/4/2024 12:03:15 PM
 *  Author: Saed Abozied
 */ 


#ifndef TMR0_CONFIG_H_
#define TMR0_CONFIG_H_

/*TMR0 modes options*/
//1_TMR0_NORMAL_MODE
//2_TMR0_CTC_MODE
#define TMR0_MODE				TMR0_CTC_MODE

#define TMR0_PRELOAD_VALUE		113
#define TMR0_OVERFLOW_COUNTER	1000

#define TMR0_COMPARE_VALUE		249
#define TMR0_CTC_COUNTER		5000


#endif /* TMR0_CONFIG_H_ */