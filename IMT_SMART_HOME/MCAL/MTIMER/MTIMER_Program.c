/*
 * MTIMER_Program.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Ahmed Khaled Hammad
 */

#include"../../LIB/LSTD_TYPES.h"
#include"../../LIB/LBIT_MATH.h"
#include"MTIMER_Private.h"
#include"MTIMER_Config.h"
#include"MTIMER_Interface.h"


/*Pointer to Function*/
void (*TIMER0_CallBack)(void);

void (*TIMER1_CallBack)(void);

void (*TIMER1_ICF_CallBack)(void);
/*Timer0 Initialization*/
void MTIMER0_VidInit(void)
{
	/*Select the suitable Prescaler*/
	TCCR0&=0xF8;  //Bit masking
	TCCR0|=TIMER_SET_PRESCALER;
	/*Mode Select*/
#if TIMER0_SET_MODE == TIMER0_NORMAL_MODE
	CLR_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
	/*Timer Overflow Interrupt Enable*/
	SET_BIT(TIMSK,0);
#elif TIMER0_SET_MODE == TIMER0_CTC_MODE
	CLR_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
#if TIMER0_SET_CTC_INTERRUPT == TIMER0_CTC_INTERRUPT_ENABLED
	SET_BIT(TIMSK,1);
#elif TIMER0_SET_CTC_INTERRUPT == TIMER0_CTC_INTERRUPT_DISABLED
	CLR_BIT(TIMSK,1);
#else
#error      "TIMER0 CTC Mode INTERRUPT is not valid ..."
#endif
#if TIMER0_SET_OC0_PIN_MODE  == TIMER0_OC0_PIN_DISCONNECTED
	CLR_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);
#elif TIMER0_SET_OC0_PIN_MODE  == TIMER0_OC0_PIN_TOGGLE
	CLR_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
#elif TIMER0_SET_OC0_PIN_MODE  == TIMER0_OC0_PIN_SET
	SET_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
#elif TIMER0_SET_OC0_PIN_MODE  == TIMER0_OC0_PIN_CLR
	SET_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);

#else
#error      "TIMER0 CTC Mode OC0 PIN is not valid ..."
#endif
#elif TIMER0_SET_MODE == TIMER0_PHASECORRECT_PWM_MODE
	SET_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
#if   TIMER0_SET_PWM_MODE == TIMER0_NON_INVERTING_PWM
	SET_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);

#elif   TIMER0_SET_PWM_MODE == TIMER0_INVERTING_PWM
	SET_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
#else
#error      "PWM Mode is not valid ..."
#endif
#elif TIMER0_SET_MODE == TIMER0_FAST_PWM_MODE
	SET_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
#if   TIMER0_SET_PWM_MODE == TIMER0_NON_INVERTING_PWM
	SET_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);

#elif   TIMER0_SET_PWM_MODE == TIMER0_INVERTING_PWM
	SET_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
#else
#error      "PWM Mode is not valid ..."
#endif
#else
#error      "TIMER0 Mode is not valid ..."
#endif

}

/*Set Preload Function*/
void MTIMER0_VidSetPreload(u8 Copy_u8Preload)
{
	TCNT0 = Copy_u8Preload;
}
/*Set CTC Value Function*/
void MTIMER0_VidSetCTCValue(u8 Copy_u8CTCValue)
{
	OCR0= Copy_u8CTCValue ;
}

void MTIMER0_VidOVF_SetCallBack(void(*Copy_VidCallBack)(void))
{
	TIMER0_CallBack =Copy_VidCallBack;
}
void MTIMER0_VidCTC_SetCallBack(void(*Copy_VidCallBack)(void))
{
	TIMER0_CallBack =Copy_VidCallBack;
}
void __vector_11(void)     __attribute__((signal));
void __vector_11(void)
{
	TIMER0_CallBack();
}

void __vector_10(void)     __attribute__((signal));
void __vector_10(void)
{
	TIMER0_CallBack();
}

/***************************************************************TIMER1*******************************************************************************/
/*Timer1 Initialization*/
void MTIMER1_VidInit(void)
{
	/*Select the suitable Prescaler*/
	TCCR1B&=0xF8;  //Bit masking
	TCCR1B|=TIMER1_SET_PRESCALER;
	/*Mode Select*/
#if TIMER1_SET_MODE == TIMER1_NORMAL_MODE
	/*Set Normal mode */
	CLR_BIT(TCCR1B,4);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1A,0);
	/*TIMER OVERFLOW INTERRUPT ENABLLED*/
	SET_BIT(TIMSK,2);

#elif TIMER1_SET_MODE == TIMER1_ICU_MODE
	/*Set Normal mode */
	CLR_BIT(TCCR1B,4);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1A,0);
	/*TIMER OVERFLOW INTERRUPT ENABLLED*/
	SET_BIT(TIMSK,2);
	/*ICU INTERRUPT ENABLLED*/
	SET_BIT(TIMSK,5);
	/*ICU Edge Select-->Rising edge*/
#if TIMER1_ICU_EDGE_SELECT == TIMER1_ICU_RISING_EDGE
	SET_BIT(TCCR1B,6);
#elif TIMER1_ICU_EDGE_SELECT == TIMER1_ICU_FULING_EDGE
	CLC_BIT(TCCR1B,6);
#else
#error      "TIMER1 ICU Edge Select is not valid ..."
#endif

#else
#error      "TIMER1 Mode is not valid ..."
#endif
}

/***********************************************************************************************/
/*                          Anther way to initialize Timer 1                                   */
/***********************************************************************************************/
void MTIMER1_voidInit( Timer1Mode_type mode,Timer1Scaler_type scaler,OC1A_Mode_type oc1a_mode,OC1B_Mode_type oc1b_mode)
{
	switch (mode)
	{
	case TIMER1_NORMAL_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_CTC_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_CTC_OCRA_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_FASTPWM_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_FASTPWM_OCRA_TOP_MODE:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	}
	switch (oc1a_mode)
	{
	case OCRA_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
	case OCRA_TOGGLE:
		SET_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
	case OCRA_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	case OCRA_INVERTING:
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	}
	switch (oc1b_mode)
	{
	case OCRB_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
	case OCRB_TOGGLE:
		SET_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
	case OCRB_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	case OCRB_INVERTING:
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	}


	TCCR1B&=0XF8;
	TCCR1B|=scaler;
	ICR1 = 19999;     /* top ICR for frequency 50 Hz for Servo */

}
/**************************************************************************************************/
/*                                      For Servo Motor                                           */
/**************************************************************************************************/

void MTIMER1_voidSetOcr1b(u16 Copy_u16OCRValue)
{
	OCR1A=999+((u32)Copy_u16OCRValue*1000)/180;
}


/*Set Preload Function*/
void MTIMER1_VidSetPreload(u16 Copy_u16Preload)
{
	TCNT1 = Copy_u16Preload;
}

/*Get Counter Value In Timer1*/
u16 MTIMER1_u16GetTCNT1Value(void)
{
	return TCNT1 ;
}

/*Get Counter Value In ICR1  */
u16 MTIMER1_u16GetICR1Value(void)
{
	return 	ICR1 ;
}


/*select sense control Function*/
void MTIMER1_VidSenseControl(u8 Copy_u8SenseControl)
{
	if(Copy_u8SenseControl==MTIMER1_ICU_FALLING_EDGE)
	{
		/*ICU Sense with Falling*/

		CLR_BIT(TCCR1B,6);
	}
	else if(Copy_u8SenseControl==MTIMER1_ICU_RISING_EDGE)
	{
		/*ICU Sense with Rising*/
		SET_BIT(TCCR1B,6);
	}
	else
	{
		/*Do Nothing*/
	}
}
void MTIMER1_VidOVF_SetCallBack(void(*Copy_VidCallBack)(void))
{
	TIMER1_CallBack =Copy_VidCallBack;
}

void MTIMER1_VidICF_SetCallBack(void(*Copy_VidCallBack)(void))
{
	TIMER1_ICF_CallBack =Copy_VidCallBack;
}
/*TIMER1 OFV  ISR*/
void __vector_9(void)      __attribute__((signal));
void __vector_9(void)
{
	TIMER1_CallBack();
}

/*TIMER1 Capture Event ISR*/
void __vector_6(void)      __attribute__((signal));
void __vector_6(void)
{
	TIMER1_ICF_CallBack();
}
