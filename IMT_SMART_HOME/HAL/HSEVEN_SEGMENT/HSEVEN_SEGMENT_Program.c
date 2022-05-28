/*
 * HSEVEN_SEGMENT_Program.c
 *
 *  Created on: Jan 19, 2022
 *      Author: Ahmed Khaled Hammad
 */


#include"..\..\LIB\LSTD_TYPES.h"
#include"..\..\MCAL\MDIO\MDIO_Interface.h"
#include"HSEVEN_SEGMENT_Interface.h"




/*Seven Segment initialization*/
void HSEVEN_SEGMENT_VidInit(SEVEN_SEGMENT_t *Copy_SEVEN_SEGMENT_t7SEG)
{
	MDIO_Error_State_SetPortDirection(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,PORT_OUTPUT);
}

/*Seven Segment OFF*/
void HSEVEN_SEGMENT_VidOff(SEVEN_SEGMENT_t *Copy_SEVEN_SEGMENT_t7SEG,u8 Copy_u8Off)
{
	if (Copy_SEVEN_SEGMENT_t7SEG->Copy_u87SegConfiguration == COMMON_CATHODE)
	{
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,Copy_u8Off);
	}
	if (Copy_SEVEN_SEGMENT_t7SEG->Copy_u87SegConfiguration == COMMON_ANODE)
	{
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,~Copy_u8Off);
	}
}




/*Display a Number */
void HSEVEN_SEGMENT_VidDisplayNumber(SEVEN_SEGMENT_t *Copy_SEVEN_SEGMENT_t7SEG,u8 Copy_u8Number)
{
if (Copy_SEVEN_SEGMENT_t7SEG->Copy_u87SegConfiguration == COMMON_CATHODE)
{
	switch(Copy_u8Number)
	{
	case 0:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,ZERO);
		break ;
	case 1:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,ONE);
		break ;
	case 2:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,TWO);
		break ;
	case 3:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,THREE);
		break ;
	case 4:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,FOUR);
		break ;
	case 5:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,FIVE);
		break ;
	case 6:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,SIX);
		break ;
	case 7:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,SEVEN);
		break ;
	case 8:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,EIGHT);
		break ;
	case 9:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,NINE);
		break ;
	default:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,ERROR);
	}
}
else if (Copy_SEVEN_SEGMENT_t7SEG->Copy_u87SegConfiguration==COMMON_ANODE)
{
	switch(Copy_u8Number)
	{
	case 0:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,~ZERO);
		break ;
	case 1:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,~ONE);
		break ;
	case 2:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,~TWO);
		break ;
	case 3:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,~THREE);
		break ;
	case 4:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,~FOUR);
		break ;
	case 5:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,~FIVE);
		break ;
	case 6:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,~SIX);
		break ;
	case 7:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,~SEVEN);
		break ;
	case 8:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,~EIGHT);
		break ;
	case 9:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,~NINE);
		break ;
	default:
		MDIO_Error_State_SetPortValue(Copy_SEVEN_SEGMENT_t7SEG->Copy_u8SevenSegmentPort,~ERROR);
	}
}
}
