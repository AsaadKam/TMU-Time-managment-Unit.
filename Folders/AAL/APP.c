  
/*
 * APP.C
 *
 * Created: 17/12/2019 18:33:53
 *  Author: Asaad
 */ 

/*- INCLUDES ----------------------------------------------*/

#include"DIO.h"
#include"Timer.h"
#include"TMU.h"
/*- LOCAL MACROS ------------------------------------------*/


/*- LOCAL Dataypes ----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/

/*- GLOBAL STATIC VARIABLES -------------------------------*/

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/

void LED_0_500mili_Oneshot(void)
{
    DIO_Write_Pin(0,HIGH);
}
void LED_1_100mili_Periodic(void)
{
    DIO_toggle_Pin(1);
}
void LED_2_200mili_Periodic(void)
{
    DIO_toggle_Pin(2);
}
int main()
{
	
	DIO_INIT_Pin(0,OUTPUT);
	DIO_INIT_Pin(1,OUTPUT);
	DIO_INIT_Pin(2,OUTPUT);
	DIO_INIT_Pin(3,OUTPUT);
    TMU_Init();
	
	TMU_Start(LED_0_500mili_Oneshot,500U,TMU_Function_ONESHOT);
	TMU_Start(LED_1_100mili_Periodic,100U,TMU_Function_PERIODIC);
	TMU_Start(LED_2_200mili_Periodic,200U,TMU_Function_PERIODIC);
    
	while(1)
	{
		
      	TMU_Dispatch();

	}
}

