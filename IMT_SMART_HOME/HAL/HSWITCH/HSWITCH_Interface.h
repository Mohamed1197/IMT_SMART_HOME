/*
 * HSWITCH_Interface.h
 *
 *  Created on: Jan 20, 2022
 *      Author: Ahmed Khaled Hammad
 */

#ifndef HAL_HSWITCH_HSWITCH_INTERFACE_H_
#define HAL_HSWITCH_HSWITCH_INTERFACE_H_

typedef struct {

	u8 Copy_u8PortNumber;
	u8 Copy_u8PinNumber;

}SWITCH_t;

#define HSWITCH_PORTA   0
#define HSWITCH_PORTB   1
#define HSWITCH_PORTC   2
#define HSWITCH_PORTD   3



#define PRESSED         0

#define NOT_PRESSED     1

/*Switch initialization*/
void HSWITCH_VidInit_PullUP(SWITCH_t *Copy_SWITCH_tSwitch);

/*get Switch Value*/
u8 HSWITCH_u8SwitchState(SWITCH_t *Copy_SWITCH_tSwitch);
#endif /* HAL_HSWITCH_HSWITCH_INTERFACE_H_ */
