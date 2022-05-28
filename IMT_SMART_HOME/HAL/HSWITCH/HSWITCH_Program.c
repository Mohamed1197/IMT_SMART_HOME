/*
 * HSWITCH_Program.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Ahmed Khaled Hammad
 */

#include"../../MCAL/MDIO/MDIO_Interface.h"
#include"HSWITCH_Interface.h"
void HSWITCH_VidInit_PullUP(SWITCH_t *Copy_SWITCH_tSwitch)
{
 /*Set pin direction*/
  /*Active Pull up resistor*/
  MDIO_VidActivePullUP(Copy_SWITCH_tSwitch->Copy_u8PinNumber, Copy_SWITCH_tSwitch->Copy_u8PortNumber);
}

/*get Switch Value*/
u8 HSWITCH_u8SwitchState(SWITCH_t *Copy_SWITCH_tSwitch)
{
       /*Default state for Switch NOT_PRESSED = 1 IN PULL UP RESISTANCE*/
     u8 Copy_u8Pinvalue = 1 ;

	MDIO_Error_State_GetPinValue(Copy_SWITCH_tSwitch->Copy_u8PinNumber, Copy_SWITCH_tSwitch->Copy_u8PortNumber,&Copy_u8Pinvalue);


return Copy_u8Pinvalue ;
}
