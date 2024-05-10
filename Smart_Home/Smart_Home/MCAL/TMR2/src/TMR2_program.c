/*
 * TMR2_program.c
 *
 * Created: 5/10/2024 2:51:43 AM
 *  Author: Karim
 */ 
/*UTILES_LIB*/
#include"BIT_MATH.h"
#include"STD_TYPES.h"


#include"TMR2_register.h"
#include"TMR2_interface.h"
#include"TMR2_private.h"
#include"TMR2_config.h"

static void(*PRV_pFunCallBackOVF)(void) = NULL;
static void(*PRV_pFunCallBackCTC)(void) = NULL;

static u16 local_u16Counter=0;

void TMR2_voidInit(void)
{

#if TMR2_MODE == TMR2_NORMAL_MODE
    
    /*Waveform Generation Mode>>Normal_mode*/
    CLR_BIT(TCCR2_REG,WGM20);
    CLR_BIT(TCCR2_REG,WGM21);
    
    /*Timer/Counter2 Overflow Interrupt Enable>>Enable*/
    SET_BIT(TIMSK2_REG,TOIE2);
    
    /*put preload value in timer register*/
    TCNT2_REG=TMR2_PRELOAD_VALUE;
    
#elif TMR2_MODE == TMR2_CTC_MODE
    
    /*Waveform Generation Mode>>CTC*/
    CLR_BIT(TCCR2_REG,WGM20);
    SET_BIT(TCCR2_REG,WGM21);
    
    /*Compare Match Output Mode>>Normal port operation, OC2 disconnected*/
    CLR_BIT(TCCR2_REG,COM20);
    CLR_BIT(TCCR2_REG,COM21);
    
    /*Timer/Counter2 Output Compare Match Interrupt Enable>>Enable*/
    SET_BIT(TIMSK2_REG,OCIE2);
    
    /*put preload value in timer register*/
    OCR2_REG=TMR2_COMPARE_VALUE;
    
#endif
}

void TMR2_voidStart(void)
{
    /*Clock Select>>clk/64(From prescaler)*/
    SET_BIT(TCCR2_REG,CS20);
    SET_BIT(TCCR2_REG,CS21);
    CLR_BIT(TCCR2_REG,CS22);
    local_u16Counter=0;
}

void TMR2_voidStop(void)
{
    /*Clock Select>>clk/No clock source (Timer/Counter stopped).*/
    CLR_BIT(TCCR2_REG,CS20);
    CLR_BIT(TCCR2_REG,CS21);
    CLR_BIT(TCCR2_REG,CS22);
}

void TMR2_SetCallBackOVF(void (*copy_pFunAction)(void))
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

void TMR2_SetCallBackCTC(void (*copy_pFunAction)(void))
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

void TMR2_clear_flag(void)
{
    TIFR2_REG |= (1 << OCF2); 
    SET_BIT(TIFR2_REG,TOV2);
}

void __vector_5(void)__attribute__((signal));
void __vector_5(void)
{
    local_u16Counter++;
    
    if(local_u16Counter==TMR2_OVERFLOW_COUNTER)
    {
        /*put preload value in timer register*/
        TCNT2_REG=TMR2_PRELOAD_VALUE;
        
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

void __vector_4(void)__attribute__((signal));
void __vector_4(void)
{
    local_u16Counter++;
    
    if(local_u16Counter==TMR2_CTC_COUNTER)
    {
        /*CLR counter*/
        local_u16Counter=0;
        
        if(PRV_pFunCallBackCTC != NULL)
        {
            /*execute action*/
            PRV_pFunCallBackCTC();
            TMR2_clear_flag();
        }
        else
        {
            //error state
        }
    }
}
