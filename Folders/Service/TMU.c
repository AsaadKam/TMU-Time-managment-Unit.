/**********************************************
 * This driver implements timer managment unit 
 * that supplys delay from 1m to above 
 *
 **********************************************/
/*- INCLUDES ----------------------------------------------*/
#include"Timer.h"
#include"TMU.h"
#include"TMU_Config.h"
#include"Atmega32Registers.h"


/*- LOCAL MACROS ------------------------------------------*/
/*- LOCAL Dataypes ----------------------------------------*/

/********************************************
 * This stucture contain the three variables 
 * pointer to function and the peridicity in
 * milisecond
 ********************************************/
 
typedef struct 
{
	 uint16_t  Periodic_or_not;
	 uint16_t  Periodicity_MS;
	 PntrToFunc_t PntrToFunc;
	
}TMU_Node;

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/

static void TMU_Function_ISR(void);

/*- GLOBAL STATIC VARIABLES -------------------------------*/

static TMU_Node TMU_Events_Array[TMU_Events]={0};
static uint16_t index=0, sgu16_OverFlow_Counts_TMU=0;
	
/*- GLOBAL EXTERN VARIABLES -------------------------------*/
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/


/*- APIs IMPLEMENTATION -----------------------------------*/

uint8_t TMU_Init()
{
	StrTMU_Configuration_t* psTMU_configuration=NullPointer;
	
	psTMU_configuration->TMU_TIMER_IDS=TMU_TIMER_ID0;
	/*****************************************
	 *  We will adjust clock sgau8_Prescaler *
	 *  divded by 8need count 125 to get 1m  *  
	 *			second tick                  *
	 *****************************************/
	psTMU_configuration->TMU_TIMER_PSC=F_CPU_CLOCK_64_TMU_TIMER_0;
	psTMU_configuration->TMU_TIMER_MODE=TMU_TIMER_COUNTER_MODE;
	psTMU_configuration->TMU_TIMER_INT_Mode=TMU_TIMER_INT;
	
	Timer_Init(psTMU_configuration);
	
	return Error_OK;
}


uint8_t TMU_Start(PntrToFunc_t PntrToFunc,uint16_t Periodicity_MS,uint16_t Periodic_or_not)
{
	/*static uint8_t First_Start_flag=1;*/

	Timer_Start(TIMER0,TMU_Counts_One_mili_TIMER_ID_ZERO,TMU_Function_ISR);

	if(index>TMU_Events-1) return Error_NOK;
	else
	{		
	
		TMU_Events_Array[index].PntrToFunc=PntrToFunc;	
		TMU_Events_Array[index].Periodicity_MS=Periodicity_MS;

		index++;
	
	}
	return Error_OK;
}


uint8_t TMU_Dispatch(void)
{

	for(uint8_t i=0;i<index-1;i++)
	{ 
		/*We need to put counter increment in ISR and also add the idea of call back function to timers*/ 
		if(sgu16_OverFlow_Counts_TMU!=0)
		{ 
		  if(!(TMU_Events_Array[i].Periodicity_MS%sgu16_OverFlow_Counts_TMU)) TMU_Events_Array[i].PntrToFunc(); 			  
		}
	}
	
	return Error_OK;
}

/*need edit*/
uint8_t TMU_Stop(PntrToFunc_t PntrToFunc)
{

	if(index==0) return Error_NOK;
	for(uint8_t i=0;i<index-1;i++)
	{
		if(TMU_Events_Array[i].PntrToFunc==PntrToFunc) 
		{
			 if(index-1 !=i)
			 {
				 TMU_Events_Array[i]=TMU_Events_Array[index-1];
			 }
			
		}
	}
	/*Decrement the index*/
	index--;
	
	return Error_OK;
	
}

