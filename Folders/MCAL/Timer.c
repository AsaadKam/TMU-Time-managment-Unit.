/*
 *  Timer.c
 *  Created: 05/11/2019 18:34:27
 *  Author: Asaad
 */ 
 
/*- INCLUDES ----------------------------------------------*/

#include "Timer.h"


/*- LOCAL MACROS ------------------------------------------*/

#define  EnableGeneralInterrupt()     SET_BIT(CPU_FLAG_Register,INT_BIT)
#define  EnableOVIntTimer1()          SET_BIT(TIMER_ENABLE_INTERRUPT_REGISTER,TIMER1_OVERFLOW_INT_EN_BIT)


/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/



/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer/Counter Initialization
 * Input     : Timer_Configuration_S* Confg_S (Struct contain : Timer Channel, Prescaler, Timer mode , Mode as described in Struct)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t  Timer_Init(StrTimerConfiguration_t* Confg_S);
/*_______________________________________________________________________________________________________________________________*/


/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer/Counter Start
 * Input     :  Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2), Tick Counting (Counts given by user)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t Timer_Start(uint8_t Copy_uint8_TimerChannel,uint32_t Copy_uint32_TickCounts);
/*_______________________________________________________________________________________________________________________________*/


/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer/Counter Stop
 * Input     :  Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t  Timer_Stop(uint8_t Copy_uint8_TimerChannel);
/*_______________________________________________________________________________________________________________________________*/

/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer Reset
 * Input     :  Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t Timer_Reset(uint8_t Copy_uint8_TimerChannel);
/*_______________________________________________________________________________________________________________________________*/

/*_______________________________________________________________________________________________________________________________*/
/*Description: Get Timer Tick Time value to use it by user
 * Input     : Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2), *Timer_Time (Pointer to return Value)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t Timer_Get_TickTime(uint8_t Copy_uint8_TimerChannel, void volatile*Copy_uint8Ptr_TimerTickTime);
/*_______________________________________________________________________________________________________________________________*/

/*_______________________________________________________________________________________________________________________________*/
/*Description: Get Timer Flag Status
 * Input     : Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2), *FlagStatus (Pointer to Flag)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t Timer_Get_FlagStatus(uint8_t Copy_uint8_TimerChannel, void volatile *Copy_uint8Ptr_FlagStatus);

/*_______________________________________________________________________________________________________________________________*/



/*- GLOBAL STATIC VARIABLES -------------------------------*/

static uint8_t Interrupt_Mode[NO_OF_CHANNELS]={0},TimerMode[NO_OF_CHANNELS]={0},Prescaler[NO_OF_CHANNELS]={0};

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/

/*- APIs IMPLEMENTATION -----------------------------------*/
	
uint8_t Timer_Init(StrTimerConfiguration_t* Confg_S)
{
	/*To Check whether the structure values that have been passed is in the scope of configuration nor not*/
    if(Confg_S->Timer_Channel >TIMER2   ) return ERROR_NOK;
	if(Confg_S->Timer_Mode>COUNTER_MODE ) return ERROR_NOK;
	if(Confg_S->Interrupt_Mode>INTERRUPT) return ERROR_NOK;
	if(Confg_S->Timer_Psc >7            ) return ERROR_NOK;	
			
	TimerMode[Confg_S->Timer_Channel]=Confg_S->Timer_Mode;
	Interrupt_Mode[Confg_S->Timer_Channel]=Confg_S->Interrupt_Mode;
	Prescaler[Confg_S->Timer_Channel]=Confg_S->Timer_Psc;
    
	/*Check IF mode of Interrupt is enabled*/
	if(Confg_S->Interrupt_Mode==INTERRUPT)
	{
              //Enable Interrupt if it is chosen in the mode
              EnableGeneralInterrupt();
              //Enable OverFlow Interrupt for Timer1
              EnableOVIntTimer1();
	}
     return ERROR_OK;
}

uint8_t Timer_Start(uint8_t Copy_uint8_TimerChannel,uint32_t Copy_uint32_TickCounts)//with prescaler
{
	    int16_t count=0;
	    
		switch(Copy_uint8_TimerChannel)
		{
			case TIMER0:
			{
					//Check whether it is poll or not
					if(Interrupt_Mode[TIMER0]==POLLING)
					{
						//check whether it is counter or timer
						if(TimerMode[TIMER0]==TIMER_MODE)
						{
							//Set the initial value of prescaler according to the delay
							SET_VAlUE_IN_POSTION_FROM_TO(0,2,TIMER0_CNTRL_Register,Prescaler[TIMER0]);
							//Initiate the timer counter to do delay in multiple of millisecond
							/*TIMER0_COUNTER_Register=(0xFFFF-1)-1000;*/
							//Stay until the time of milliseconds finished
							while(count!=Copy_uint32_TickCounts)
							{
								
								count++;
/*
								while(TIMER0_COUNTER_Register!=(0xFFFF-1));
								TIMER0_COUNTER_Register=(0xFFFF-1)-1000;*/
								
							}
							//Stop timer
							SET_VAlUE_IN_POSTION_FROM_TO(0,2,TIMER0_CNTRL_Register,NO_CLOCK_TIMER_0);
						}
						
						else if(TimerMode[TIMER0]==COUNTER_MODE)
						{
							if(Copy_uint32_TickCounts>TIMER0_OVERFLOW) return ERROR_NOK;
							//Set the initial value of prescaler external as we count events
							SET_VAlUE_IN_POSTION_FROM_TO(0,2,TIMER0_CNTRL_Register,Prescaler[TIMER0]);
							//Stay until count is finished
							while(TIMER1_COUNTER_Register!=(Copy_uint32_TickCounts) );
							SET_VAlUE_IN_POSTION_FROM_TO(0,2,TIMER0_CNTRL_Register,NO_CLOCK_TIMER_0);
							
						}
						
					}
			}
			break;
			
			case TIMER1:
			{
					//Check whether it is poll or not
					if(Interrupt_Mode[TIMER1]==POLLING) 
					{
							//check whether it is counter or timer
							if(TimerMode[TIMER1]==TIMER_MODE)
							{
          								//Set the initial value of prescaler according to the delay
          								SET_VAlUE_IN_POSTION_FROM_TO(0,2,TIMER1_CNTRL_Register_B,Prescaler[TIMER1]);	
										//Initiate the timer counter to do delay in multiple of millisecond
										TIMER1_COUNTER_Register=(0xFFFF-1)-1000; 
										//Stay until the time of milliseconds finished					
										while(count!=Copy_uint32_TickCounts)
										{
						    
												count++;
          			        					while(TIMER1_COUNTER_Register!=(0xFFFF-1));
          			        					TIMER1_COUNTER_Register=(0xFFFF-1)-1000; 
								                     
										}
										//Stop timer
										SET_VAlUE_IN_POSTION_FROM_TO(0,2,TIMER1_CNTRL_Register_B,NO_CLOCK_TIMER_1);	
							}
					
							else if(TimerMode[TIMER1]==COUNTER_MODE)
							{
								        if(Copy_uint32_TickCounts>TIMER1_OVERFLOW) return ERROR_NOK;
			        					//Set the initial value of prescaler external as we count events
			         					SET_VAlUE_IN_POSTION_FROM_TO(0,2,TIMER1_CNTRL_Register_B,Prescaler[TIMER1]);
										//Stay until count is finished	
			         					while(TIMER1_COUNTER_Register!=(Copy_uint32_TickCounts) );
			         					SET_VAlUE_IN_POSTION_FROM_TO(0,2,TIMER1_CNTRL_Register_B,NO_CLOCK_TIMER_1);					   
				   
							}
				  
					 }
	
			}
			break;
			
			case TIMER2:
			{
					//Check whether it is poll or not
					if(Interrupt_Mode[TIMER2]==POLLING)
					{
						//check whether it is counter or timer
						if(TimerMode[TIMER2]==TIMER_MODE)
						{
							//Set the initial value of prescaler according to the delay
							SET_VAlUE_IN_POSTION_FROM_TO(0,2,TIMER2_CNTRL_Register,Prescaler[TIMER2]);
							//Initiate the timer counter to do delay in multiple of millisecond
							/*TIMER1_COUNTER_Register=(0xFFFF-1)-1000;*/
							//Stay until the time of milliseconds finished
							while(count!=Copy_uint32_TickCounts)
							{
								
								count++;
/*
								while(TIMER2_COUNTER_Register!=(0xFFFF-1));
								TIMER2_COUNTER_Register=(0xFFFF-1)-1000;*/
								
							}
							//Stop timer
							SET_VAlUE_IN_POSTION_FROM_TO(0,2,TIMER2_CNTRL_Register,NO_CLOCK_TIMER_2);
						}
						
						else if(TimerMode[TIMER2]==COUNTER_MODE)
						{
							if(Copy_uint32_TickCounts>TIMER2_OVERFLOW) return ERROR_NOK;
							//Set the initial value of prescaler external as we count events
							SET_VAlUE_IN_POSTION_FROM_TO(0,2,TIMER2_CNTRL_Register,Prescaler[TIMER2]);
							//Stay until count is finished
							while(TIMER2_COUNTER_Register!=(Copy_uint32_TickCounts) );
							SET_VAlUE_IN_POSTION_FROM_TO(0,2,TIMER2_CNTRL_Register,NO_CLOCK_TIMER_1);
							
						}
						
					}				
				
			}
			break;
            default:
			{
				return ERROR_NOK;
			}
			break;			
		}
		return ERROR_OK;
}

uint8_t Timer_Stop(uint8_t Copy_uint8_TimerChannel)
{ 

		switch(Copy_uint8_TimerChannel)
		{
			case TIMER0:
			{
				//Stop the clock
				SET_VAlUE_IN_POSTION_FROM_TO(0,2,TIMER0_CNTRL_Register,NO_CLOCK_TIMER_0);
			}
			break;
			case TIMER1:
			{
				//Stop the clock
				SET_VAlUE_IN_POSTION_FROM_TO(0,2,TIMER1_CNTRL_Register_B,NO_CLOCK_TIMER_1);
			}
			break;
			case TIMER2:
			{
				//Stop the clock
				SET_VAlUE_IN_POSTION_FROM_TO(0,2,TIMER2_CNTRL_Register,NO_CLOCK_TIMER_2);				
			}
			break;
            default:
            {
	            return ERROR_NOK;
            }
            break;
            }
            return ERROR_OK;
			
}

uint8_t Timer_Get_TickTime(uint8_t Copy_uint8_TimerChannel, void volatile*Copy_uint8Ptr_TimerTickTime)
{
		switch(Copy_uint8_TimerChannel)
		{
			case TIMER0:
			{
				Copy_uint8Ptr_TimerTickTime=&TIMER0_COUNTER_Register;
			}
			break;
			case TIMER1:
			{
				Copy_uint8Ptr_TimerTickTime=&TIMER1_COUNTER_Register;
			}
			break;
			case TIMER2:
			{
				Copy_uint8Ptr_TimerTickTime=&TIMER2_COUNTER_Register;
			}
			break;
            default:
            {
	            return ERROR_NOK;
            }
            break;
            }
            return ERROR_OK;			
}

uint8_t Timer_Get_FlagStatus(uint8_t Copy_uint8_TimerChannel, void volatile*Copy_uint8Ptr_FlagStatus)
{
	    static uint8_t OVF_FLAG=0;
	    
	    switch(Copy_uint8_TimerChannel)
	    {
		    case TIMER0:
		    {
			    OVF_FLAG=GET_BIT(TIMER_EVENT_FLAGS_REGISTER,TIMER0_OVERFLOW_FLAG_BIT);
			    Copy_uint8Ptr_FlagStatus=&OVF_FLAG;
		    }
		    break;
		    case TIMER1:
		    {
			    OVF_FLAG=GET_BIT(TIMER_EVENT_FLAGS_REGISTER,TIMER1_OVERFLOW_FLAG_BIT);
			    Copy_uint8Ptr_FlagStatus=&OVF_FLAG;
		    }
		    break;
		    case TIMER2:
		    {
			    OVF_FLAG=GET_BIT(TIMER_EVENT_FLAGS_REGISTER,TIMER2_OVERFLOW_FLAG_BIT);
			    Copy_uint8Ptr_FlagStatus=&OVF_FLAG;
		    }
		    break;
            default:
            {
	            return ERROR_NOK;
            }
            break;
            }
            return ERROR_OK;
}

uint8_t Timer_Reset(uint8_t Copy_uint8_TimerChannel)
{
		switch(Copy_uint8_TimerChannel)
		{
			case TIMER0:
			{
				CLR_PORT(TIMER0_COUNTER_Register);
			}
			break;
			case TIMER1:
			{
				CLR_PORT(TIMER1_COUNTER_Register);
			}
			break;
			case TIMER2:
			{
				CLR_PORT(TIMER2_COUNTER_Register);
			}
			break;
            default:
            {
	            return ERROR_NOK;
            }
            break;
            }
            return ERROR_OK;
}



