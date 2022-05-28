/*
 * HSEVEN_SEGMENT.h
 *
 *  Created on: Jan 20, 2022
 *      Author: Ahmed Khaled Hammad
 */

#ifndef HAL_HSEVEN_SEGMENT_HSEVEN_SEGMENT_INTERFACE_H_
#define HAL_HSEVEN_SEGMENT_HSEVEN_SEGMENT_INTERFACE_H_


/*7 Segment Truth Table common cathode
 * 0-->0b00111111
 * 1-->0b00000110
 * 2-->0b01011011
 * 3-->0b01001111
 * 4-->0b01100110
 * 5-->0b01101101
 * 6-->0b01111101
 * 7-->0b00000111
 * 8-->0b01111111
 * 9-->0b01101111
 * E-->0b01111001*/

#define ZERO   0b00111111
#define ONE    0b00000110
#define TWO    0b01011011
#define THREE  0b01001111
#define FOUR   0b01100110
#define FIVE   0b01101101
#define SIX    0b01111101
#define SEVEN  0b00000111
#define EIGHT  0b01111111
#define NINE   0b01101111
#define ERROR  0b01111001
#define OFF    0b00000000

/*Configuration Options:
 * 1- COMMON_CATHODE
 * 2- COMMON_ANODE */

#define COMMON_ANODE      0
#define COMMON_CATHODE    1

/*Seven Segment Port Options:
 * 1- HSEVEN_SEGMENT_PORTA
 * 2- HSEVEN_SEGMENT_PORTB
 * 3- HSEVEN_SEGMENT_PORTC
 * 4- HSEVEN_SEGMENT_PORTD*/

#define HSEVEN_SEGMENT_PORTA    0
#define HSEVEN_SEGMENT_PORTB    1
#define HSEVEN_SEGMENT_PORTC    2
#define HSEVEN_SEGMENT_PORTD    3

typedef struct{

	u8 Copy_u8SevenSegmentPort;
	u8 Copy_u87SegConfiguration;

}SEVEN_SEGMENT_t;

/*Seven Segment initialization*/
void HSEVEN_SEGMENT_VidInit(SEVEN_SEGMENT_t *Copy_SEVEN_SEGMENT_t7SEG);

/*Display a Number */
void HSEVEN_SEGMENT_VidDisplayNumber(SEVEN_SEGMENT_t *Copy_SEVEN_SEGMENT_t7SEG,u8 Copy_u8Number);

/*Seven Segment OFF*/
void HSEVEN_SEGMENT_VidOff(SEVEN_SEGMENT_t *Copy_SEVEN_SEGMENT_t7SEG,u8 Copy_u8Off);

#endif /* HAL_HSEVEN_SEGMENT_HSEVEN_SEGMENT_INTERFACE_H_ */
