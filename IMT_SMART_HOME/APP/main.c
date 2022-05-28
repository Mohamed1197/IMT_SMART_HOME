/*******************************************************************************************************/
/* Author            : Ahmed khaled Hammad && Mohamed Ahmed                                            */
/* Version           : V0.0.0                                                                          */
/* Data              : 24 May 2022                                                                     */
/* Description       : main.c --> IMT_SMART_HOME                                                       */
/* Project Features  :                                                                                 */
/*      1- Read Room Temperature                                                                       */
/*		2- Read Light Intensity for this room                                                          */
/*      3- Display Temperature , light Intensity on LCD                                                */
/*      4- Control Motor Speed Depends On Temperature reading                                          */
/*      5- Control LEDs Depends on Light Intensity                                                     */
/*      6- Login System Password maximum trials 3 times                                                */
/*      7- Control Servo Motor if password correct --> open door                                       */
/*      8- Buzzer ON with Red-LED ON   if  Password Wrong --> Servo motor OFF                          */
/* Future Updates:                                                                                     */
/*      1- Control IMT_HOME by using IoT --> through MQTT Protocol  by using GSM                       */
/*******************************************************************************************************/

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
/*******************************************************************************************************/

#include "../LIB/LSTD_TYPES.h"
#include "../LIB/LBIT_MATH.h"


/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      MCAL Components                                                */
/*******************************************************************************************************/

#include"../MCAL/MDIO/MDIO_Interface.h"                      //For DIO
#include"../MCAL/MTIMER/MTIMER_Interface.h"                  //For timer
#include"../MCAL/MADC/MADC_Interface.h"                      //For ADC

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      HAL Components                                                 */
/*******************************************************************************************************/

#include"../HAL/HCLCD/HCLCD_Interface.h"                    //For LCD
#include"../HAL/HLED/HLED_Interface.h"                      //For LED
#include"../HAL/HBUZZER/HBUZZER_Interface.h"                //For Buzzer
#include"../HAL/HDC_MOTOR/HDC_MOTOR_Interface.h"            //For DC Motor
#include"../HAL/HSERVO_MOTOR/HSERVO_Interface.h"            //For Servo Motor
#include"../HAL/HKPD/HKPD_Interface.h"                      //For KPD

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                   Service Layer  Components                                         */
/*******************************************************************************************************/

#define F_CPU  8000000UL
#include<util\delay.h>


/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                          Object Like MACROS                                         */
/*******************************************************************************************************/

#define ACTIVE                   1

#define DEACTIVE                 0

#define NO_SPEED                 0

#define ONE_LED                  1
#define TWO_LED                  2
#define THREE_LED                3
#define FOUR_LED                 4
#define FIVE_LED                 5


#define MAX_COUNT                20

#define ZERO                     0

#define DOOR_OPEN                180

#define DOOR_CLOSED              0

#define PASSWORD_CORRECT         8520

#define COUNTER2_MAX             1000


/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      Global Variables(Flag)                                         */
/*******************************************************************************************************/

/*#####################################################################################################*/
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                                         1- LEDs Hardware Connections                                */
/*******************************************************************************************************/


LED_t           LOC_SturctLED_1     ={HLED_PORTA,PIN0}                     ;
LED_t           LOC_SturctLED_2     ={HLED_PORTA,PIN2}                     ;
LED_t           LOC_SturctLED_3     ={HLED_PORTA,PIN3}                     ;
LED_t           LOC_SturctLED_4     ={HLED_PORTA,PIN5}                     ;
LED_t           LOC_SturctLED_5     ={HLED_PORTA,PIN6}                     ;

/*******************************************************************************************************/

static u8 Global_u8MotorSpeed = NO_SPEED    ;

/*******************************************************************************************************/

static u8 Global_u8LedsNumber = ONE_LED     ;

/*******************************************************************************************************/

static u8 Global_u8BuzzerFlag = DEACTIVE    ;

/*******************************************************************************************************/

static u8 Global_u8ServoFlag  = DEACTIVE    ;

/*******************************************************************************************************/

static u8 Global_u8Temerature      = ZERO    ;

/*******************************************************************************************************/

static u8 Global_u8Temerature_dec  = ZERO     ;

/*******************************************************************************************************/

static u8 Global_u8LightPercent    = ZERO     ;

/*#####################################################################################################*/
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                                     Application Function Prototype                                  */
/*******************************************************************************************************/

void App_voidCheckTempretuare(s8 Copy_s8Temperature)                     ;
void App_voidCheckLightIntensity(u8 Copy_u8LightIntenisity)              ;
void App_voidSystemLogin(void)                                           ;
void App_voidReadTemp(void)                                              ;
void App_voidReadLight(void)                                             ;
void APP_voidLightControl(void)                                          ;
void APP_voidFanControl(void)                                            ;
void APP_voidDisplayTemperature(void)                                    ;
void APP_voidDisplayLightIntensity(void)                                 ;

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                    Beginning of the System                                          */
/*******************************************************************************************************/

int main(void)
{
	/*#####################################################################################################*/
	/*#####################################################################################################*/

	/*******************************************************************************************************/
	/*                                       01 -System variables(LOCAL)                                   */
	/*******************************************************************************************************/

	/*#####################################################################################################*/
	/*#####################################################################################################*/


	/*******************************************************************************************************/
	/*                                         1- Buzzer Hardware Connections                              */
	/*******************************************************************************************************/


	Buzzer_t        LOC_SturctBuzzer_1  ={HBUZZER_PORTA,PIN7}                  ;

	/*******************************************************************************************************/
	/*                                         2- DC Motor Hardware Connections                            */
	/*-----------------------------------------------------------------------------------------------------*/
	/* DC Motor is connected with special HW pin OC0 to control its speed by PWM generated on this pin     */
	/*******************************************************************************************************/

	DCMotor_t       LOC_StructMotor_1   ={HLED_PORTB,PIN3}                     ;     //Hardware Interface--> OC0

	/*******************************************************************************************************/
	/*                                         3- Counter Delay For Buzzer                                 */
	/*******************************************************************************************************/

	u16 LOC_u16Counter   = ZERO                                                ;

	/*******************************************************************************************************/
	/*                                         4- Time out for Door open                                   */
	/*******************************************************************************************************/

	u16 LOC_u16DoorTimeOut = ZERO                                              ;

	/*******************************************************************************************************/
	/*                                         5-  Local_u8Key                                             */
	/*******************************************************************************************************/

	u8 Local_u8Key   =  NOT_PRESSED                                            ;

	/*******************************************************************************************************/
	/*                                         6-  LOC_u16Counter2                                             */
	/*******************************************************************************************************/


	u16 LOC_u16Counter2  = ZERO ;

	/*#####################################################################################################*/
	/*#####################################################################################################*/


	/*******************************************************************************************************/
	/*                                       02- System Initialization                                     */
	/*******************************************************************************************************/

	/*#####################################################################################################*/
	/*#####################################################################################################*/

	/*******************************************************************************************************/
	/*                                         1- Initialize LEDs Direction                                */
	/*******************************************************************************************************/

	HLED_VidInit(&LOC_SturctLED_1)                                     ;
	HLED_VidInit(&LOC_SturctLED_2)                                     ;
	HLED_VidInit(&LOC_SturctLED_3)                                     ;
	HLED_VidInit(&LOC_SturctLED_4)                                     ;
	HLED_VidInit(&LOC_SturctLED_5)                                     ;

	/*******************************************************************************************************/
	/*                                   2- Initialize Buzzer Direction,initial value                      */
	/*******************************************************************************************************/

	HBUZZER_voidInit(&LOC_SturctBuzzer_1)                              ;

	/*******************************************************************************************************/
	/*                                       3- Initialize Motor                                           */
	/*******************************************************************************************************/

	HDCMOTOR_voidInit(&LOC_StructMotor_1)                              ;

	/*******************************************************************************************************/
	/*                                       4-  Timer0  Initialization                                    */
	/*-----------------------------------------------------------------------------------------------------*/
	/*Notes:                                                                                               */
	/*Timer0 Initialization in Phase Correct PWM  -->OC0                                                   */
	/*                              Set CTC Value 255 -->DutyCycle=100%                                    */
	/*                              Set CTC Value 191 -->DutyCycle=75%                                     */
	/*	                            Set CTC Value 127 -->DutyCycle=50%                                     */
	/*                              Set CTC Value 63-->DutyCycle  =25%                                     */
	/*                              Set CTC Value 0 -->DutyCycle  =0%                                      */
	/*******************************************************************************************************/

	MTIMER0_VidInit()                                                  ;

	/*                             Set CTC Value 0 -->DutyCycle= 0%                                       */
	APP_voidFanControl()                                               ;



	/*******************************************************************************************************/
	/*                                       6- Initialize Servo Motor                                     */
	/*-----------------------------------------------------------------------------------------------------*/
	/*Note:                                                                                                */
	/* Servo Pin interfaced with OC1A                                                                      */
	/*******************************************************************************************************/

	HSERVO_voidInit() ;


	/*******************************************************************************************************/
	/*                                       7-  ADC Initialization                                        */
	/*******************************************************************************************************/

	MADC_VidInit()                                                     ;

	/*******************************************************************************************************/
	/*                                       8-  LCD Initialization                                        */
	/*******************************************************************************************************/

	HCLCD_Vid4Bits_Init()                                              ;


	/*******************************************************************************************************/
	/*                                       9-  KeyPad Initialization                                     */
	/*******************************************************************************************************/

	HKPD_VidInit()                                                   ;



	/*#####################################################################################################*/
	/*#####################################################################################################*/

	/*******************************************************************************************************/
	/*                                          Debugging Section                                          */
	/*******************************************************************************************************/

	/*#####################################################################################################*/
	/*#####################################################################################################*/


	while(1)
	{
		/*#####################################################################################################*/
		/*#####################################################################################################*/

		/*******************************************************************************************************/
		/*                                          System Algorithm                                           */
		/*******************************************************************************************************/

		/*#####################################################################################################*/
		/*#####################################################################################################*/

		APP_voidDisplayTemperature   ();

		APP_voidDisplayLightIntensity();



		for(LOC_u16Counter2= ZERO ; LOC_u16Counter2<COUNTER2_MAX ;LOC_u16Counter2++)
		{
			Local_u8Key = HKPD_U8GetKeyPressed();
			if(Local_u8Key != NOT_PRESSED)
			{
				/* Key is Pressed */
				/* Calls a Functions that Enters a Login System */
				App_voidSystemLogin() ;
			}
			else
			{
				/*Do Nothing*/
			}
		}

		if(Global_u8ServoFlag == ACTIVE)
		{
			//Servo_ON()
			HSERVO_voidSetAngle(DOOR_OPEN);
			Global_u8ServoFlag = DEACTIVE ;
		}
		else
		{
			LOC_u16DoorTimeOut++ ;
			if(LOC_u16DoorTimeOut==MAX_COUNT)
			{
				HSERVO_voidSetAngle(DOOR_CLOSED);
				LOC_u16DoorTimeOut = ZERO ;
			}
			/*Do Nothing*/
		}
		if(Global_u8BuzzerFlag == ACTIVE)
		{
			LOC_u16Counter++ ;
			HBUZZER_voidBuzzerOn(&LOC_SturctBuzzer_1);
			if(LOC_u16Counter == MAX_COUNT)
			{
				Global_u8BuzzerFlag = DEACTIVE ;
				HBUZZER_voidBuzzerOff(&LOC_SturctBuzzer_1);
				LOC_u16Counter = ZERO ;
			}
			else{/*Do Nothing*/}
		}
		else
		{
			/*Do Nothing*/
		}
		/*MOTOR Control*/
		APP_voidFanControl();
		/*Light Control */
    	APP_voidLightControl();


	}
	return 0 ;

}

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                     Application Function Implementation                             */
/*******************************************************************************************************/

/*#####################################################################################################*/
/*#####################################################################################################*/



/*******************************************************************************************************/
/*                                        1- App_voidReadTemp                                          */
/*-----------------------------------------------------------------------------------------------------*/
/*Notes:                                                                                               */
/*******************************************************************************************************/

void App_voidReadTemp(void)
{

	/*Set Algorithm*/
	/*******************************************************************************************************/
	/*                                     Local Variables Initialization                                  */
	/*******************************************************************************************************/

	u16 Local_u16Digital_Value = ZERO  ;
	u16 Local_u16Analog_value  = ZERO  ;

	/*******************************************************************************************************/
	/*                                         Calculate Temperature                                       */
	/*******************************************************************************************************/

	Local_u16Digital_Value = MADC_u16ADC_StartConversion(CHANNEL_4);         /*     Get ADC Reading          */
	Local_u16Analog_value = (u16)((Local_u16Digital_Value*5000UL)/1024);     /*     Read Analog Voltage      */
	Global_u8Temerature_dec = (Local_u16Analog_value % 10);
	Global_u8Temerature = (Local_u16Analog_value/10);                        /*     Calculate Temperature    */
}


/*******************************************************************************************************/
/*                                        2- App_voidReadLight                                         */
/*-----------------------------------------------------------------------------------------------------*/
/*Notes:                                                                                               */
/*******************************************************************************************************/

void App_voidReadLight(void)
{

	/*Set Algorithm*/
	/*******************************************************************************************************/
	/*                                     Local Variables Initialization                                  */
	/*******************************************************************************************************/

	u16 Local_u16Digital_Value1;

	/*******************************************************************************************************/
	/*                                         Calculate Light Intensity                                   */
	/*******************************************************************************************************/

	Local_u16Digital_Value1 = MADC_u16ADC_StartConversion(CHANNEL_1);           /* Getting ADC Reading from the LDR       */
	/* Calculating the Light Intensity Percent  */
	Global_u8LightPercent = (u16)((Local_u16Digital_Value1*100UL)/1024);        /* Converting The Reading into Percentage */

}

/*******************************************************************************************************/
/*                                        3- App_voidSystemLogin                                       */
/*-----------------------------------------------------------------------------------------------------*/
/*Notes:                                                                                               */
/*******************************************************************************************************/

void App_voidSystemLogin(void)
{
	/*******************************************************************************************************/
	/*                                         Login System Function                                       */
	/*******************************************************************************************************/

	/*******************************************************************************************************/
	/*                                     Local Variables Initialization                                  */
	/*******************************************************************************************************/
	u8  Local_u8Key        = NOT_PRESSED      ;
	u8  Local_u8Counter    = ZERO             ;
	u8  Local_u8Counter2   = ZERO             ;
	u16 Local_u16value     = ZERO             ;
	u16 Local_Num1         = ZERO             ;
	u16 Local_u16Password  = PASSWORD_CORRECT ;


	HCLCD_Vid4Bits_ClearScreen();
	HCLCD_Vid4Bits_DisplayString("Enter Passcode :");       /* Asking User to Enter Password */
	HCLCD_Vid4Bits_SetPosition(HCLCD_LINE2,4);
	while(1)
	{
		Local_u8Key = HKPD_U8GetKeyPressed();             /* Checks if The Key is Pressed  */

		if(Local_u8Key != NOT_PRESSED)                 /* if Key is Pressed */
		{
			if(Local_u8Counter<4)                      /* wait 4 digit  display on LCD */
			{
				Local_u8Counter++;

				switch(Local_u8Key)
				{
				case '0':
					Local_u16value =0;
					Local_Num1 = (Local_Num1*10) + Local_u16value ;
					HCLCD_Vid4Bits_DisplayCharacter('0');
					break;
				case '1':
					Local_u16value =1;
					Local_Num1 = (Local_Num1*10) + Local_u16value ;
					HCLCD_Vid4Bits_DisplayCharacter('1');
					break;
				case '2':
					Local_u16value =2;
					Local_Num1 = (Local_Num1*10) + Local_u16value ;
					HCLCD_Vid4Bits_DisplayCharacter('2');
					break;
				case '3':
					Local_u16value =3;
					Local_Num1 = (Local_Num1*10) + Local_u16value ;
					HCLCD_Vid4Bits_DisplayCharacter('3');
					break;
				case '4':
					Local_u16value =4;
					Local_Num1 = (Local_Num1*10) + Local_u16value ;
					HCLCD_Vid4Bits_DisplayCharacter('4');
					break;
				case '5':
					Local_u16value =5;
					Local_Num1 = (Local_Num1*10) + Local_u16value ;
					HCLCD_Vid4Bits_DisplayCharacter('5');
					break;
				case '6':
					Local_u16value =6;
					Local_Num1 = (Local_Num1*10) + Local_u16value ;
					HCLCD_Vid4Bits_DisplayCharacter('6');
					break;
				case '7':
					Local_u16value =7;
					Local_Num1 = (Local_Num1*10) + Local_u16value ;
					HCLCD_Vid4Bits_DisplayCharacter('7');
					break;
				case '8':
					Local_u16value =8;
					Local_Num1 = (Local_Num1*10) + Local_u16value ;
					HCLCD_Vid4Bits_DisplayCharacter('8');
					break;
				case '9':
					Local_u16value =9;
					Local_Num1 = (Local_Num1*10) + Local_u16value ;
					HCLCD_Vid4Bits_DisplayCharacter('9');
					break;
				default:                                             /* if any Button is pressed other than Numbers */
					HCLCD_Vid4Bits_ClearScreen();

					HCLCD_Vid4Bits_SetPosition(HCLCD_LINE1,1);
					HCLCD_Vid4Bits_DisplayString("Please Enter");

					HCLCD_Vid4Bits_SetPosition(HCLCD_LINE2,1);
					HCLCD_Vid4Bits_DisplayString("Numbers Only");
					_delay_ms(1500);

					HCLCD_Vid4Bits_ClearScreen();
					HCLCD_Vid4Bits_DisplayString("   Try Again ");     /* Asks The User to Enter Password Again */
					HCLCD_Vid4Bits_SetPosition(HCLCD_LINE2,4);
					_delay_ms(500);
					Local_u8Counter =0 ;

				}

			}
			if(Local_u8Counter>3)                         /* if 4 Numbers Are Entered */
			{
				if(Local_Num1 == Local_u16Password)        /* Checks if Password Match */
				{
					_delay_ms(1000);

					HCLCD_Vid4Bits_ClearScreen();

					HCLCD_Vid4Bits_DisplayString("    Welcome ");       /* Welcome Message is Displayed */
					HCLCD_Vid4Bits_SetPosition(HCLCD_LINE2,1);
					HCLCD_Vid4Bits_DisplayString("Opening  Door");
					Global_u8ServoFlag  = ACTIVE;                       /*  Set Global_u8ServoFlag  = 1  */
					_delay_ms(1000);
					break;
				}
				else
				{

					if(Local_u8Counter2 < 2)           /* if a wrong password is entered less than three times */
					{
						_delay_ms(1000);
						HCLCD_Vid4Bits_ClearScreen();
						HCLCD_Vid4Bits_DisplayString("  Try Again ");
						Local_u8Counter = 0 ;
						Local_Num1=0;
						Local_u8Counter2++;
						HCLCD_Vid4Bits_SetPosition(HCLCD_LINE2,4);


					}
					else                                   /* if Password is entered 3 times Wrong */
					{
						_delay_ms(1000);
						HCLCD_Vid4Bits_ClearScreen();
						HCLCD_Vid4Bits_DisplayString(" Out of tries !");
						Global_u8BuzzerFlag  = ACTIVE;     /* Set Global_u8BuzzerFlag  = 1 */
						_delay_ms(3000);

						break;


					}

				}

			}

		}
	}
}




/*******************************************************************************************************/
/*                                        4- APP_voidFanControl                                        */
/*-----------------------------------------------------------------------------------------------------*/
/*Notes:                                                                                               */
/*******************************************************************************************************/

void APP_voidFanControl(void)
{
	MTIMER0_VidSetCTCValue(Global_u8MotorSpeed) ;
}

/*******************************************************************************************************/
/*                                        5- APP_voidLightControl                                      */
/*-----------------------------------------------------------------------------------------------------*/
/*Notes:                                                                                               */
/*******************************************************************************************************/

void APP_voidLightControl(void)
{
	/*Set Algorithm*/
	switch(Global_u8LedsNumber)
	{
	case ONE_LED:
		HLED_VidLed_On(&LOC_SturctLED_1);
		HLED_VidLed_Off(&LOC_SturctLED_2);
		HLED_VidLed_Off(&LOC_SturctLED_3);
		HLED_VidLed_Off(&LOC_SturctLED_4);
		HLED_VidLed_Off(&LOC_SturctLED_5);
		break ;
	case TWO_LED:
		HLED_VidLed_On(&LOC_SturctLED_1);
		HLED_VidLed_On(&LOC_SturctLED_2);
		HLED_VidLed_Off(&LOC_SturctLED_3);
		HLED_VidLed_Off(&LOC_SturctLED_4);
		HLED_VidLed_Off(&LOC_SturctLED_5);
		break ;
	case THREE_LED:
		HLED_VidLed_On(&LOC_SturctLED_1);
		HLED_VidLed_On(&LOC_SturctLED_2);
		HLED_VidLed_On(&LOC_SturctLED_3);
		HLED_VidLed_Off(&LOC_SturctLED_4);
		HLED_VidLed_Off(&LOC_SturctLED_5);
		break ;
	case FOUR_LED:
		HLED_VidLed_On(&LOC_SturctLED_1);
		HLED_VidLed_On(&LOC_SturctLED_2);
		HLED_VidLed_On(&LOC_SturctLED_3);
		HLED_VidLed_On(&LOC_SturctLED_4);
		HLED_VidLed_Off(&LOC_SturctLED_5);
		break ;
	case FIVE_LED:
		HLED_VidLed_On(&LOC_SturctLED_1);
		HLED_VidLed_On(&LOC_SturctLED_2);
		HLED_VidLed_On(&LOC_SturctLED_3);
		HLED_VidLed_On(&LOC_SturctLED_4);
		HLED_VidLed_On(&LOC_SturctLED_5);
		break ;
	default:
		/* Do Nothing */
		break;
	}
}
/*******************************************************************************************************/
/*                                        6- App_voidCheckTempretuare                                  */
/*-----------------------------------------------------------------------------------------------------*/
/*Notes:                                                                                               */
/*******************************************************************************************************/

void App_voidCheckTempretuare(s8 Copy_s8Temperature)
{

	if(Copy_s8Temperature>40)
	{
		Global_u8MotorSpeed = 255 ;           // Full speed
	}
	else if(Copy_s8Temperature<=40 && Copy_s8Temperature>30)
	{
		Global_u8MotorSpeed = 191 ;           //  Speed is 75%
	}
	else if(Copy_s8Temperature<=30 && Copy_s8Temperature>25)
	{
		Global_u8MotorSpeed = 127 ;           //  Speed is 50%
	}
	else if(Copy_s8Temperature<=25 && Copy_s8Temperature>20)
	{
		Global_u8MotorSpeed = 64 ;            //  Speed is 25%
	}
	else
	{
		Global_u8MotorSpeed = 0 ;             //  Speed is 0 %
	}
}

/*******************************************************************************************************/
/*                                        7- App_voidCheckLightIntensity                               */
/*-----------------------------------------------------------------------------------------------------*/
/*Notes:                                                                                               */
/*******************************************************************************************************/

void App_voidCheckLightIntensity(u8 Copy_u8LightIntenisity)
{

	if(Copy_u8LightIntenisity<= 100     && Copy_u8LightIntenisity> 85)
	{
		Global_u8LedsNumber = 1 ;
	}
	else if(Copy_u8LightIntenisity<= 85 && Copy_u8LightIntenisity> 65)
	{
		Global_u8LedsNumber = 2 ;
	}
	else if(Copy_u8LightIntenisity<= 65 && Copy_u8LightIntenisity> 45)
	{
		Global_u8LedsNumber = 3 ;
	}
	else if(Copy_u8LightIntenisity<= 45 && Copy_u8LightIntenisity> 25)
	{
		Global_u8LedsNumber = 4 ;
	}
	else
	{
		Global_u8LedsNumber = 5 ;             //  Speed is 0 %
	}
}


/*******************************************************************************************************/
/*                                        8- APP_voidDisplayTemperature                                         */
/*-----------------------------------------------------------------------------------------------------*/
/*Notes:                                                                                               */
/*******************************************************************************************************/

void APP_voidDisplayTemperature(void)
{
/*******************************************************************************************************/
/*                                          Display Temperature                                            */
/*******************************************************************************************************/

	App_voidReadTemp();                                 /* Function That Calculates Temperature */
	HCLCD_Vid4Bits_ClearScreen();
	HCLCD_Vid4Bits_SetPosition(HCLCD_LINE1,1);          /*  Position of Temperature on LCD first row */
	HCLCD_Vid4Bits_DisplayString("Temp = ");
	HCLCD_Vid4Bits_DisplayNumber(Global_u8Temerature);
	HCLCD_Vid4Bits_DisplayString(".");
	HCLCD_Vid4Bits_DisplayNumber(Global_u8Temerature_dec);
	HCLCD_Vid4Bits_DisplayString(" C");

	App_voidCheckTempretuare(Global_u8Temerature);
}


/*******************************************************************************************************/
/*                                        9- APP_voidDisplayLightIntensity                                        */
/*-----------------------------------------------------------------------------------------------------*/
/*Notes:                                                                                               */
/*******************************************************************************************************/

void APP_voidDisplayLightIntensity(void)
{
/*******************************************************************************************************/
/*                                         Display Light Intensity                                     */
/*******************************************************************************************************/
	App_voidReadLight();                               /* Function That Calculates Light Intensity */
	HCLCD_Vid4Bits_SetPosition(HCLCD_LINE2,1);
	HCLCD_Vid4Bits_DisplayString("LT INT = ");         /* Displays the Light Intensity Reading of the LDR */
	HCLCD_Vid4Bits_DisplayNumber(Global_u8LightPercent);
	HCLCD_Vid4Bits_DisplayString(" %");


	App_voidCheckLightIntensity(Global_u8LightPercent);
}

/*#####################################################################################################*/
/*                                    END OF APPLICATION FUNCTIONS                                     */
/*#####################################################################################################*/

