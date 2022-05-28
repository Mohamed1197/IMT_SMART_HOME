/*
 * MTIMER_Interface.h
 *
 *  Created on: Jan 17, 2022
 *      Author: Ahmed Khaled Hammad
 */

#ifndef MCAL_MTIMER_MTIMER_INTERFACE_H_
#define MCAL_MTIMER_MTIMER_INTERFACE_H_


#define  MTIMER1_ICU_FALLING_EDGE             0
#define  MTIMER1_ICU_RISING_EDGE              1


/*Timer0 Initialization*/
void MTIMER0_VidInit(void);
/*Set Preload Function*/
void MTIMER0_VidSetPreload(u8 Copy_u8Preload);
/*Set CTC Value Function*/
void MTIMER0_VidSetCTCValue(u8 Copy_u8CTCValue);
void MTIMER0_VidOVF_SetCallBack(void(*Copy_VidCallBack)(void));
void MTIMER0_VidCTC_SetCallBack(void(*Copy_VidCallBack)(void));

/***************************************************TIMER1************************************************************/
/*Timer1 Initialization*/
void MTIMER1_VidInit(void);
/*Set Preload Function*/
void MTIMER1_VidSetPreload(u16 Copy_u16Preload);
/*Get Counter Value In Timer1*/
u16 MTIMER1_u16GetTCNT1Value(void);
/*Get Counter Value In ICR1  */
u16 MTIMER1_u16GetICR1Value(void);
/*Set Sense Control*/
void MTIMER1_VidSenseControl(u8 Copy_u8SenseControl);

void MTIMER1_VidOVF_SetCallBack(void(*Copy_VidCallBack)(void));
void MTIMER1_VidICF_SetCallBack(void(*Copy_VidCallBack)(void));


typedef enum{
	TIMER1_STOP=0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
}Timer1Scaler_type;


typedef enum
{
	TIMER1_NORMAL_MODE = 0 ,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE
}Timer1Mode_type;

typedef enum
{
	OCRA_DISCONNECTED=0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING

}OC1A_Mode_type;

typedef enum
{
	OCRB_DISCONNECTED=0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING

}OC1B_Mode_type;


typedef enum{
	RISING,
	FALLING
}ICU_Edge_type;




void MTIMER1_voidInit( Timer1Mode_type mode,Timer1Scaler_type scaler,OC1A_Mode_type oc1a_mode,OC1B_Mode_type oc1b_mode);
void MTIMER1_voidSetOcr1b(u16 Copy_u16OCRValue);

#endif /* MCAL_MTIMER_MTIMER_INTERFACE_H_ */
