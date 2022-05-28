/*
 * MTIMER_Private.h
 *
 *  Created on: Jan 17, 2022
 *      Author: Ahmed Khaled Hammad
 */

#ifndef MCAL_MTIMER_MTIMER_PRIVATE_H_
#define MCAL_MTIMER_MTIMER_PRIVATE_H_

/*************TIMER0*********************/
#define TCCR0     *((volatile u8*)0x53)
#define TIMSK     *((volatile u8*)0x59)
#define TCNT0     *((volatile u8*)0x52)
#define OCR0      *((volatile u8*)0x5C)

/****************TIMER1****************/
/*TIMER 1*/


#define ICR1         (*(volatile unsigned short*)0x46)
#define ICR1L        (*(volatile unsigned char*)0x46 )
#define ICR1H        (*(volatile unsigned char*)0x47 )
#define OCR1B        (*(volatile unsigned short*)0x48)
#define OCR1BL       (*(volatile unsigned char*)0x48 )
#define OCR1BH       (*(volatile unsigned char*)0x49 )
#define OCR1A        (*(volatile unsigned short*)0x4A)
#define OCR1AL       (*(volatile unsigned char*)0x4A )
#define OCR1AH       (*(volatile unsigned char*)0x4B )
#define TCNT1        (*(volatile unsigned short*)0x4C)
#define TCNT1L       (*(volatile unsigned char*)0x4C )
#define TCNT1H       (*(volatile unsigned char*)0x4D )
#define TCCR1B       (*(volatile unsigned char*)0x4E )
#define TCCR1A       (*(volatile unsigned char*)0x4F )

#define SFIOR        (*(volatile unsigned char*)0x50)

#define OSCCAL       (*(volatile unsigned char*)0x51)

//A#define TCNT1      *((volatile u16*)0x4C)
//#define TIMSK      *((volatile u16*)0x59)


/* TCCR1A */
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

/* TCCR1B */
#define ICNC1   7
#define ICES1   6
/* bit 5 reserved */
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0
/*Timer0 Prescaler Options */

#define TIMER_STOPPED                                    0
#define TIMER_NO_PRESCALER                               1
#define TIMER_8_PRESCALER                                2
#define TIMER_64_PRESCALER                               3
#define TIMER_256_PRESCALER                              4
#define TIMER_1024_PRESCALER                             5
#define TIMER_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE         6
#define TIMER_EXTERNAL_CLOCK_SOURCE_RISING_EDGE          7


/*Timer0 Mode options*/

#define TIMER0_NORMAL_MODE                                1
#define TIMER0_CTC_MODE                                   2
#define TIMER0_PHASECORRECT_PWM_MODE                      3
#define TIMER0_FAST_PWM_MODE                              4


/*Timer0 CTC Interrupt Options*/

#define TIMER0_CTC_INTERRUPT_ENABLED                      0
#define TIMER0_CTC_INTERRUPT_DISABLED                     1

/*Timer0 CTC OC0 PIN Options*/

#define TIMER0_OC0_PIN_DISCONNECTED                       0
#define TIMER0_OC0_PIN_TOGGLE							  1
#define TIMER0_OC0_PIN_SET								  2
#define TIMER0_OC0_PIN_CLR							      3

#define TIMER0_NON_INVERTING_PWM						  1
#define TIMER0_INVERTING_PWM                              0


/********************************************************************TIMER1*********************************************************************************/
/*Timer0 Prescaler Options */

#define TIMER1_STOPPED                                    0
#define TIMER1_NO_PRESCALER                               1
#define TIMER1_8_PRESCALER                                2
#define TIMER1_64_PRESCALER                               3
#define TIMER1_256_PRESCALER                              4
#define TIMER1_1024_PRESCALER                             5
#define TIMER1_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE         6
#define TIMER1_EXTERNAL_CLOCK_SOURCE_RISING_EDGE          7


/*Timer1 Mode options*/
//#define TIMER1_NORMAL_MODE                                1
//#define TIMER1_ICU_MODE                                   2

/*ICU Edge Selection Options:
 * 1- TIMER1_ICU_RISING_EDGE
 * 2- TIMER1_ICU_FALING_EDGE
 *  */

#define TIMER1_ICU_RISING_EDGE                            1
#define TIMER1_ICU_FALING_EDGE                            2

#endif /* MCAL_MTIMER_MTIMER_PRIVATE_H_ */
