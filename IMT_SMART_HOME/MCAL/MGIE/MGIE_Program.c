/*
 * MGIE_Program.c
 *
 *  Created on: Jan 14, 2022
 *      Author: Ahmed Khaled Hammad
 */

#include"..\..\LIB\LSTD_TYPES.h"
#include"..\..\LIB\LBIT_MATH.h"

#include"MGIE_Private.h"

/*GIE Enable Function*/
void MGIE_VidEnable(void)
{
	SET_BIT(SREG,7);
}
/*GIE Disable Function*/
void MGIE_VidDisable(void)
{
	CLR_BIT(SREG,7);
}

