/*
 * TMR0_program.c
 *
 * Created: 4/4/2024 12:03:40 PM
 *  Author: Saed Abozied
 */ 

/*UTILES_LIB*/
#include"BIT_MATH.h"
#include"STD_TYPES.h"

/*TM0*/
#include"TMR0_register.h"
#include"TMR0_interface.h"
#include"TMR0_private.h"
#include"TMR0_config.h"


static void(*PRV_pFunCallBackOVF)(void) = NULL;
static void(*PRV_pFunCallBackCTC)(void) = NULL;

void TMR0_voidInit(void)
{

#if TMR0_MODE == TMR0_NORMAL_MODE
	
	/*Waveform Generation Mode>>Normal_mode*/
	CLR_BIT(TCCR0_REG,WGM00);
	CLR_BIT(TCCR0_REG,WGM01);
	
	/*Timer/Counter0 Overflow Interrupt Enable>>Enable*/
	SET_BIT(TIMSK_REG,TOIE0);
	
	/*put preload value in timer register*/
	TCNT0_REG=TMR0_PRELOAD_VALUE;
	
#elif TMR0_MODE == TMR0_CTC_MODE
	
	/*Waveform Generation Mode>>CTC*/
	CLR_BIT(TCCR0_REG,WGM00);
	SET_BIT(TCCR0_REG,WGM01);
	
	/*Compare Match Output Mode>>Normal port operation, OC0 disconnected*/
	CLR_BIT(TCCR0_REG,COM00);
	CLR_BIT(TCCR0_REG,COM01);
	
	/*Timer/Counter0 Output Compare Match Interrupt Enable>>Enable*/
	SET_BIT(TIMSK_REG,OCIE0);
	
	/*put preload value in timer register*/
	OCR0_REG=TMR0_COMPARE_VALUE;
	
#endif
}

	
	

void TMR0_voidStart(void)
{
	/*Clock Select>>clk/64(From prescaler)*/
	SET_BIT(TCCR0_REG,CS00);
	SET_BIT(TCCR0_REG,CS01);
	CLR_BIT(TCCR0_REG,CS02);
}
void TMR0_voidStop(void)
{
	/*Clock Select>>clk/No clock source (Timer/Counter stopped).*/
	CLR_BIT(TCCR0_REG,CS00);
	CLR_BIT(TCCR0_REG,CS01);
	CLR_BIT(TCCR0_REG,CS02);
}

void TMR0_SetCallBackOVF(void (*copy_pFunAction)(void))
{
	if(copy_pFunAction != NULL)
	{
		
		PRV_pFunCallBackOVF=copy_pFunAction;
	}
	else
	{
		//error state
	}
}

void TMR0_SetCallBackCTC(void (*copy_pFunAction)(void))
{
	if(copy_pFunAction != NULL)
	{
		
		PRV_pFunCallBackCTC=copy_pFunAction;
	}
	else
	{
		//error state
	}
}


void __vector_11(void)__attribute__((signal));
void __vector_11(void)
{
	static u16 local_u16Counter=0;
	
	local_u16Counter++;
	
	if(local_u16Counter==TMR0_OVERFLOW_COUNTER)
	{
		/*put preload value in timer register*/
		TCNT0_REG=TMR0_PRELOAD_VALUE;
		
		/*CLR counter*/
		local_u16Counter=0;
		
		if(PRV_pFunCallBackOVF != NULL)
		{
			/*execute action*/
			PRV_pFunCallBackOVF();
		}
		else
		{
				//error state
		}
	}
}

void __vector_10(void)__attribute__((signal));
void __vector_10(void)
{
	
	static u16 local_u16Counter=0;
	
	local_u16Counter++;
	
	if(local_u16Counter==TMR0_CTC_COUNTER)
	{
		
		/*CLR counter*/
		local_u16Counter=0;
		
		if(PRV_pFunCallBackCTC != NULL)
		{
			/*execute action*/
			PRV_pFunCallBackCTC();
		}
		else
		{
				//error state
		}
	}
	
}