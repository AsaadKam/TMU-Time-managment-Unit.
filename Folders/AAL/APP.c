/*
 * APP.C
 *
 * Created: 17/12/2019 18:33:53
 *  Author: Asaad
 */ 

/*- INCLUDES ----------------------------------------------*/

#include"DIO.h"
#include"Timer.h"

/*- LOCAL MACROS ------------------------------------------*/


/*- LOCAL Dataypes ----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/

/*- GLOBAL STATIC VARIABLES -------------------------------*/

volatile uint16_t sgu16_Count_main=0;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/

void function(void)
{
    sgu16_Count_main++;
}

int main()
{
	DIO_INIT_Pin(0,OUTPUT);
    DIO_Write_Pin(0,HIGH);
	
    StrTimerConfiguration_t  s_TIMER_Init_Config;
	
	s_TIMER_Init_Config.Timer_Channel=TIMER0;
	s_TIMER_Init_Config.Timer_Psc=F_CPU_CLOCK_8_TIMER_0;
	s_TIMER_Init_Config.Timer_Mode=TIMER_MODE_MILIE;
	s_TIMER_Init_Config.Interrupt_Mode=INTERRUPT;
	
    Timer_Init(&s_TIMER_Init_Config);
	
    Timer_Start(TIMER0,0,function);
	
	while(1)
	{

    	if(sgu16_Count_main>=1000U) 	 		
		{
	        DIO_toggle_Pin(0);
			sgu16_Count_main=0;
		}
		else
		{
		}

	}
}




