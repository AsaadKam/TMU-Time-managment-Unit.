/**********************************************
 * This driver implements timer managment unit 
 * that supplys delay from 1m to above 
 *
 **********************************************/
/*- INCLUDES ----------------------------------------------*/
#include"Timer.h"
#include"DIO.h"
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
	 uint8_t      Periodic_or_not;
	 uint64_t     Periodicity_MS;
	 uint64_t     TMU_Node_Period_Count;
	 PntrToFunc_t PntrToFunc;
	 
}TMU_Node_t;

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/

static void TMU_Function_ISR(void);

/*- GLOBAL STATIC VARIABLES -------------------------------*/

static  TMU_Node_t sga_TMU_Events[TMU_Events]={0};
static  uint64_t sgu16_index=0;
static  volatile uint64_t sgu64_TMU_Timer_ISR_Count=0;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
void  TMU_Function_ISR(void)
{
	/*DIO_toggle_Pin(3);*/
	/*Count */	
    sgu64_TMU_Timer_ISR_Count++;
}

/*- APIs IMPLEMENTATION -----------------------------------*/

TMU_Error_t TMU_Init()
{
	StrTMU_Configuration_t strTMU_configuration;
	
	strTMU_configuration.TMU_TIMER_IDS=TMU_TIMER_ID0;
	/*******************************************
	 *  Clock prescaler is adjusted internally *
	 *           no need to enter it           *  
	 *******************************************/
	strTMU_configuration.TMU_TIMER_PSC=TMU_NO_NEED_PSC;
	strTMU_configuration.TMU_TIMER_MODE=TMU_TIMER_MODE_MILIE;
	strTMU_configuration.TMU_TIMER_INT_Mode=TMU_TIMER_INT;
	
	Timer_Init(&strTMU_configuration);
	
	return TMU_Error_OK;
}


TMU_Error_t TMU_Start(PntrToFunc_t PntrToFunc_Copy_TMU_Start,uint16_t u16_Copy_Periodicity_MS_TMU_Start,uint16_t u16_Copy_Periodic_or_not_TMU_Start)
{
    TMU_Error_t TMU_Start_Error= TMU_Error_OK;
	
	if(sgu16_index>TMU_Events) TMU_Start_Error= TMU_Error_EXTRA_EVENTS;
	else
	{  

		if(NullPointer!=PntrToFunc_Copy_TMU_Start)
		{	
			if(u16_Copy_Periodicity_MS_TMU_Start==TMU_Function_PERIODIC)
			{
                
				sga_TMU_Events[sgu16_index].Periodic_or_not=u16_Copy_Periodic_or_not_TMU_Start;	

			}
			else if(u16_Copy_Periodicity_MS_TMU_Start==TMU_Function_ONESHOT)
			{
				sga_TMU_Events[sgu16_index].Periodic_or_not=u16_Copy_Periodic_or_not_TMU_Start;	   
			}  
			else 
			{
				TMU_Start_Error=TMU_Error_Function_type_undefined;
			}
			sga_TMU_Events[sgu16_index].PntrToFunc=PntrToFunc_Copy_TMU_Start;	
			sga_TMU_Events[sgu16_index].Periodicity_MS=u16_Copy_Periodicity_MS_TMU_Start;
			sgu16_index++;			
		}
		else
		{
			TMU_Start_Error=TMU_Error_Start_Null_func;
		}
	}
	return TMU_Start_Error;
}


TMU_Error_t TMU_Dispatch(void)
{
	
    TMU_Error_t TMU_Dispatch_Error= TMU_Error_OK;
    uint8_t static su8_1st_start_Dispatch_Flag=1;
	uint64_t u8_Dispatch_Func_Count=0;
	/*
	 *  Check if the disptach is the the first time to 
	 *  it to start if so start the timer
	 */
	if(su8_1st_start_Dispatch_Flag==1)   
	{
		/*Timer start working in milies*/
		TMU_Dispatch_Error=Timer_Start(TIMER0,0,TMU_Function_ISR);
		su8_1st_start_Dispatch_Flag=0;
    }
	else
	{
		/*Looping to execute the function which it's time comes(Brain of TMU)*/	
        for(uint64_t i=0;i<sgu16_index;i++)
		{ 
	        u8_Dispatch_Func_Count=((sga_TMU_Events[i].TMU_Node_Period_Count)+1)*sga_TMU_Events[i].Periodicity_MS;
			/*I will increment each function count until i reach to it's periodicity, then i will execute it's routine*/ 
			if((u8_Dispatch_Func_Count==sgu64_TMU_Timer_ISR_Count)&&(sgu64_TMU_Timer_ISR_Count!=0))
			{   
				/*DIO_toggle_Pin(3);*/
				sga_TMU_Events[i].PntrToFunc();
				sga_TMU_Events[i].TMU_Node_Period_Count=sga_TMU_Events[i].TMU_Node_Period_Count+1;

				if(sga_TMU_Events[i].Periodic_or_not==TMU_Function_ONESHOT)
				{
					
					TMU_Dispatch_Error=TMU_Stop(sga_TMU_Events[i].PntrToFunc);
				
				}
				else
				{
					
				}
			}
        }

	}

	return TMU_Dispatch_Error;
}

/*need edit*/
TMU_Error_t TMU_Stop(PntrToFunc_t PntrToFunc_Copy_TMU_Start)
{
    TMU_Error_t TMU_Dispatch_Error= TMU_Error_OK;
	if(sgu16_index==0) TMU_Dispatch_Error=TMU_Error_Nothing_To_Stop;
	else
	{
		for(uint8_t i=0;i<sgu16_index-1;i++)
		{
			if(sga_TMU_Events[i].PntrToFunc==PntrToFunc_Copy_TMU_Start) 
			{
				 if(sgu16_index-1 !=i)
				 {
					 sga_TMU_Events[i]=sga_TMU_Events[sgu16_index-1];
				 }
				 {
				 }
				
			}
			else
			{
			}
		}
	    /*Decrement the sgu16_index*/
	    sgu16_index--;
	}

	return TMU_Dispatch_Error;
}

