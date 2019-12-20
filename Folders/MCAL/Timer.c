/*********************************
 *  Timer.c                      *
 *  Created: 05/11/2019 18:34:27 *
 *  Author: Asaad                *
 *********************************/ 
 
/*- INCLUDES ----------------------------------------------*/
#include "Timer.h"
#include "BitManipulation.h"


/*- LOCAL MACROS ------------------------------------------*/

#define  EnableGeneralInterrupt()      SET_BIT(CPU_FLAG_Register,INT_BIT)
#define  Timer_0_OVF_INT_EN()          SET_BIT(TIMER_ENABLE_INTERRUPT_REGISTER,TIMER0_OVF_COUNT_INT_EN_BIT)
#define  Timer_1_OVF_INT_EN()          SET_BIT(TIMER_ENABLE_INTERRUPT_REGISTER,TIMER1_OVF_COUNT_INT_EN_BIT)
#define  Timer_2_OVF_INT_EN()          SET_BIT(TIMER_ENABLE_INTERRUPT_REGISTER,TIMER2_OVF_COUNT_INT_EN_BIT)

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/



/*- GLOBAL STATIC VARIABLES -------------------------------*/

static uint8_t sgau8_Interrupt_Mode[NO_OF_CHANNELS]={0},sgau8_TIMERMode[NO_OF_CHANNELS]={0},sgau8_TIMERChannel[NO_OF_CHANNELS]={0},sgau8_TIMERPrescaler[NO_OF_CHANNELS]={0};
static volatile PntrToFunc_t sgPntrToFunc_TIMER_OVF=0;
static volatile uint16_t sgu16_TIMER_COUNTER_REG_BUFFER=0;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/س

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/


/*- APIs IMPLEMENTATION -----------------------------------*/
	
uint8_t Timer_Init(StrTimerConfiguration_t* ps_Copy_TIMER_Init_Config)
{
	
	if(NullPointer!=ps_Copy_TIMER_Init_Config)
	{
		
		/*To Check whether the structure values that have been passed is in the scope of configuration nor not*/
		if(sgau8_TIMERChannel[ps_Copy_TIMER_Init_Config->Timer_Channel]==Enable)           return ERROR_NOK;	
		if(ps_Copy_TIMER_Init_Config->Timer_Channel >TIMER2  )                              return ERROR_NOK;	
		if(ps_Copy_TIMER_Init_Config->Timer_Mode>TIMER_MODE_MILIE )                         return ERROR_NOK;
		if(ps_Copy_TIMER_Init_Config->Interrupt_Mode>INTERRUPT)                             return ERROR_NOK;
		if(ps_Copy_TIMER_Init_Config->Timer_Psc >  Max_Prescaler_possiblities   )           return ERROR_NOK;
	
		/*Adjust the configurations*/
		
		sgau8_TIMERChannel[ps_Copy_TIMER_Init_Config->Timer_Channel]=Enable;		
		sgau8_TIMERMode[ps_Copy_TIMER_Init_Config->Timer_Channel]=ps_Copy_TIMER_Init_Config->Timer_Mode;
		sgau8_Interrupt_Mode[ps_Copy_TIMER_Init_Config->Timer_Channel]=ps_Copy_TIMER_Init_Config->Interrupt_Mode;
		sgau8_TIMERPrescaler[ps_Copy_TIMER_Init_Config->Timer_Channel]=ps_Copy_TIMER_Init_Config->Timer_Psc;
		
    
		
		/*In the mode of counter mode the prescaler is entered by the user */
		if((ps_Copy_TIMER_Init_Config->Timer_Mode)==COUNTER_MODE)
		{
				
			switch(ps_Copy_TIMER_Init_Config->Timer_Channel)
			{
				case TIMER0:
				{
					/*Set the initial value of Prescaler*/
					TIMER0_CNTRL_REG  |=ps_Copy_TIMER_Init_Config->Timer_Psc;

				}
				break;
				case TIMER1:
				{
					/*Set the initial value of Prescaler*/
					TIMER1_CNTRL_REG_B|=ps_Copy_TIMER_Init_Config->Timer_Psc;

				}
				break;
				case TIMER2:
				{
					/*Set the initial value of Prescaler*/
				     TIMER2_CNTRL_REG|=ps_Copy_TIMER_Init_Config->Timer_Psc;

				}
				break;
				default:
				{
					return ERROR_NOK;
				}
				break;
			}
		}
		else
		{
			/*************************************************************************
			 * Timer mode the prescaler value is left for the program according if
			 * the delay is in micro or milie
			 *************************************************************************/
		}

		/*Check IF mode of Interrupt is enabled*/
		if(ps_Copy_TIMER_Init_Config->Interrupt_Mode==INTERRUPT)
		{
				  /*Enable Interrupt if it is chosen in the mode*/
				  EnableGeneralInterrupt();
                  
		}
	}
	else
	{
		
	}
	return ERROR_OK;
}

uint8_t Timer_Start(uint8_t u8_Copy_TIMER_Start_TIMERChannel,uint32_t u32_Copy_TIMER_Start_tickCounts,PntrToFunc_t PntrToFunc_Copy_TIMER_Start_ISR)//with sgau8_Prescaler
{
	
	uint16_t u16_Count_TIMER_Start=0;
	
	switch(u8_Copy_TIMER_Start_TIMERChannel)
	{
		case TIMER0:
		{
			/*Check whether it is counter or timer*/
			if(sgau8_TIMERMode[TIMER0]!=COUNTER_MODE)
			{
				/* Check whether it is time delay in mili or in micro */
				if(sgau8_TIMERMode[TIMER0]==TIMER_MODE_MICRO)
				{ 
						/************************************************************
						 * The prescale divide by 8 and  make count =1 and  the 
						 * counter =255-1 to get overflow every micro
						 ************************************************************/
						TIMER0_CNTRL_REG|=F_CPU_CLOCK_8_TIMER_0;	
						/*Check whether it is polled or not*/
						if(sgau8_Interrupt_Mode[TIMER0]==POLLING)
						{                            
							/*Loop  until it get the time of delay in micro*/
							while(u32_Copy_TIMER_Start_tickCounts!=u16_Count_TIMER_Start)
							{
								/************************************************************
								 * The prescale divide by 64 and  make count =1 and  the 
								 * counter =255-1 to get overflow every micro
								 ************************************************************/
								SET_BIT(TIMER_EVENT_FLAGS_REG,TIMER0_OVF_COUNT_FLAG_BIT);								 
								TIMER0_COUNTER_REG=(TIMER0_OVF_COUNT-1U);
								/*Loop  until overflow happens*/
								while( BIT_IS_CLR(TIMER_EVENT_FLAGS_REG,TIMER0_OVF_COUNT_FLAG_BIT) );
								u16_Count_TIMER_Start++;
							}
							
						}
			
						else if(sgau8_Interrupt_Mode[TIMER0]==INTERRUPT)
						{

						     SET_BIT(TIMER_EVENT_FLAGS_REG,TIMER0_OVF_COUNT_FLAG_BIT);								 
							 TIMER0_COUNTER_REG=(TIMER0_OVF_COUNT-1U);
							 sgu16_TIMER_COUNTER_REG_BUFFER=TIMER0_COUNTER_REG;
							/*Enable OverFlow Interrupt for TIMER (0)*/
				             Timer_0_OVF_INT_EN();			  
				 
							/*****************************************************
							 *Let the ISR execute the increment of count of delay
							 *Note that we will extern the value of count of delay 
							 ****************************************************/
							 sgPntrToFunc_TIMER_OVF=PntrToFunc_Copy_TIMER_Start_ISR;													
						}
						else
						{
						}

					
				}/*Check whether it is time delay in mili or in micro */
				else if(sgau8_TIMERMode[TIMER0]==TIMER_MODE_MILIE)
				{
						/************************************************************
						 * The prescale divide by 64 and  make count =125 and  the 
						 * counter =255-125 to get overflow every mili
						 ************************************************************/
						TIMER0_CNTRL_REG|=F_CPU_CLOCK_64_TIMER_0;	
						/*Check whether it is polled or not*/
						if(sgau8_Interrupt_Mode[TIMER0]==POLLING)
						{                            
							/*Loop  until it get the time of delay in mili*/
							while(u32_Copy_TIMER_Start_tickCounts!=u16_Count_TIMER_Start)
							{
								/************************************************************
								 * The prescale divide by 64 and  make count =125 and  the 
								 * counter =255-125 to get overflow every mili
								 ************************************************************/
								SET_BIT(TIMER_EVENT_FLAGS_REG,TIMER0_OVF_COUNT_FLAG_BIT);								 
								TIMER0_COUNTER_REG=(TIMER0_OVF_COUNT-125U);
								/*Loop  until overflow happens*/
								while( BIT_IS_CLR(TIMER_EVENT_FLAGS_REG,TIMER0_OVF_COUNT_FLAG_BIT) );
								u16_Count_TIMER_Start++;
							}
							
						}
						else if(sgau8_Interrupt_Mode[TIMER0]==INTERRUPT)
						{
							 
						     SET_BIT(TIMER_EVENT_FLAGS_REG,TIMER0_OVF_COUNT_FLAG_BIT);								 
							 TIMER0_COUNTER_REG=(TIMER0_OVF_COUNT-125U);
							 sgu16_TIMER_COUNTER_REG_BUFFER=TIMER0_COUNTER_REG;
							/*Enable OverFlow Interrupt for TIMER (0)*/
				             Timer_0_OVF_INT_EN();			  
				 
							/*****************************************************
							 *Let the ISR execute the increment of count of delay
							 *Note that we will extern the value of count of delay 
							 ****************************************************/
							 sgPntrToFunc_TIMER_OVF=PntrToFunc_Copy_TIMER_Start_ISR;												
						}
						else
						{
						}

					

					
				}
				else
				{
				}
					
			}/*Check whether it is counter or timer*/
			else if(sgau8_TIMERMode[TIMER0]==COUNTER_MODE)
			{

				/*Check whether it is polled or not*/
				if(sgau8_Interrupt_Mode[TIMER0]==POLLING)
				{ 
                    SET_BIT(TIMER_EVENT_FLAGS_REG,TIMER0_OVF_COUNT_FLAG_BIT);
				    TIMER0_COUNTER_REG=TIMER0_OVF_COUNT-u32_Copy_TIMER_Start_tickCounts;
					/*Loop  until overflow happens*/
					while( BIT_IS_CLR(TIMER_EVENT_FLAGS_REG,TIMER0_OVF_COUNT_FLAG_BIT) );

				}
				else if(sgau8_Interrupt_Mode[TIMER0]==INTERRUPT)
				{
					 SET_BIT(TIMER_EVENT_FLAGS_REG,TIMER0_OVF_COUNT_FLAG_BIT);								 
					 TIMER0_COUNTER_REG=(TIMER0_OVF_COUNT-1U);
					/*Enable OverFlow Interrupt for TIMER (0)*/
					 Timer_0_OVF_INT_EN();			  
		 	
					/*Let the ISR execute the called back function*/
					sgPntrToFunc_TIMER_OVF=PntrToFunc_Copy_TIMER_Start_ISR;						
				}
				else
				{
				}
			}
			else
			{
			}
		}
		break;
		
		case TIMER1:
		{
			/*Check whether it is counter or timer*/
			if(sgau8_TIMERMode[TIMER1]!=COUNTER_MODE)
			{
				/* Check whether it is time delay in mili or in micro */
				if(sgau8_TIMERMode[TIMER1]==TIMER_MODE_MICRO)
				{ 
					/************************************************************
					 * The prescale divide by 8 and  make count =1 and  the 
					 * counter =65,535-1 to get overflow every micro
					 ************************************************************/
					TIMER1_CNTRL_REG_B|=F_CPU_CLOCK_8_TIMER_1;
					/*Check whether it is polled or not*/
					if(sgau8_Interrupt_Mode[TIMER1]==POLLING)
					{  

						/*Loop  until it get the time of delay in micro*/
						while(u32_Copy_TIMER_Start_tickCounts!=u16_Count_TIMER_Start)
						{
							/************************************************************
							 * The prescale divide by 8 and  make count =1 and  the 
							 * counter =65,535-1 to get overflow every micro
							 ************************************************************/
							SET_BIT(TIMER_EVENT_FLAGS_REG,TIMER1_OVF_COUNT_FLAG_BIT);
							TIMER1_COUNTER_REG=(TIMER1_OVF_COUNT-1U);
							/*Loop  until overflow happens*/
							while( BIT_IS_CLR(TIMER_EVENT_FLAGS_REG,TIMER1_OVF_COUNT_FLAG_BIT) );
							u16_Count_TIMER_Start++;
						}
						
						
					}
				
					else if(sgau8_Interrupt_Mode[TIMER1]==INTERRUPT)
					{
						/*****************************************************
						 *Let the ISR execute the increment of count of delay
						 *Note that we will extern the value of 
						 ****************************************************/
						 sgPntrToFunc_TIMER_OVF=PntrToFunc_Copy_TIMER_Start_ISR;													
					}
					else
					{
					}

				}/*Check whether it is time delay in mili or in micro */
				else if(sgau8_TIMERMode[TIMER1]==TIMER_MODE_MILIE)
				{
					/************************************************************
					 * The prescale divide by 64 and  make count =1 and  the 
					 * counter =65,535-125 to get overflow every mili
					 ************************************************************/

					TIMER1_CNTRL_REG_B|=F_CPU_CLOCK_64_TIMER_1;
					/*Check whether it is polled or not*/
					if(sgau8_Interrupt_Mode[TIMER1]==POLLING)
					{  

						/*Loop  until it get the time of delay in micro*/
						while(u32_Copy_TIMER_Start_tickCounts!=u16_Count_TIMER_Start)
						{
							/************************************************************
							 * The prescale divide by 64 and  make count =1 and  the 
							 * counter =65,535-125 to get overflow every mili
							 ************************************************************/	
							SET_BIT(TIMER_EVENT_FLAGS_REG,TIMER1_OVF_COUNT_FLAG_BIT);							 
							TIMER1_COUNTER_REG=(TIMER1_OVF_COUNT-125U);
							/*Loop  until overflow happens*/
							while( BIT_IS_CLR(TIMER_EVENT_FLAGS_REG,TIMER1_OVF_COUNT_FLAG_BIT) );
							u16_Count_TIMER_Start++;
						}
						
					}
					else if(sgau8_Interrupt_Mode[TIMER1]==INTERRUPT)
					{
						/*****************************************************
						 *Let the ISR execute the increment of count of delay
						 *Note that we will extern the value of 
						 ****************************************************/
						 sgPntrToFunc_TIMER_OVF=PntrToFunc_Copy_TIMER_Start_ISR;													
					}
					else
					{
						
					}
						
			    }
            }				
			else if(sgau8_TIMERMode[TIMER1]==COUNTER_MODE)
			{

				/*Check whether it is polled or not*/
				if(sgau8_Interrupt_Mode[TIMER1]==POLLING)
				{ 
                    SET_BIT(TIMER_EVENT_FLAGS_REG,TIMER1_OVF_COUNT_FLAG_BIT);
				    TIMER1_COUNTER_REG=TIMER1_OVF_COUNT-u32_Copy_TIMER_Start_tickCounts;
					/*Loop  until overflow happens*/
					while( BIT_IS_CLR(TIMER_EVENT_FLAGS_REG,TIMER1_OVF_COUNT_FLAG_BIT) );

				}
				else if(sgau8_Interrupt_Mode[TIMER1]==INTERRUPT)
				{
				    TIMER1_COUNTER_REG=TIMER1_OVF_COUNT-u32_Copy_TIMER_Start_tickCounts;
					/*Let the ISR execute the called back function*/
					sgPntrToFunc_TIMER_OVF=PntrToFunc_Copy_TIMER_Start_ISR;						
				}
				else
				{
				}
			}
			else
			{
			}
		}
		break;		
		case TIMER2:
		{
			/*Check whether it is counter or timer*/
			if(sgau8_TIMERMode[TIMER2]!=COUNTER_MODE)
			{
				/* Check whether it is time delay in mili or in micro */
				if(sgau8_TIMERMode[TIMER2]==TIMER_MODE_MICRO)
				{ 
					TIMER2_CNTRL_REG|=F_CPU_CLOCK_8_TIMER_2;
					/*Check whether it is polled or not*/
					if(sgau8_Interrupt_Mode[TIMER2]==POLLING)
					{                            
						/*Loop  until it get the time of delay in micro*/
						while(u32_Copy_TIMER_Start_tickCounts!=u16_Count_TIMER_Start)
						{
							/************************************************************
							 * The prescale divide by 8 and  make count =1U and  the 
							 * counter =255-1U to get overflow every micro
							 ************************************************************/
							TIMER2_COUNTER_REG=(uint8_t)(TIMER2_OVF_COUNT-1U);
							/*Loop  until overflow happens*/
							while( BIT_IS_CLR(TIMER_EVENT_FLAGS_REG,TIMER2_OVF_COUNT_FLAG_BIT) );
							SET_BIT(TIMER_EVENT_FLAGS_REG,TIMER2_OVF_COUNT_FLAG_BIT);
							u16_Count_TIMER_Start++;
						}
						
					}
					else if(sgau8_Interrupt_Mode[TIMER2]==INTERRUPT)
					{
						/*****************************************************
						 *Let the ISR execute the increment of count of delay
						 *Note that we will extern the value of 
						 ****************************************************/
						 sgPntrToFunc_TIMER_OVF=PntrToFunc_Copy_TIMER_Start_ISR;													
					}
					else
					{
					}

				}/*Check whether it is time delay in mili or in micro */
				else if(sgau8_TIMERMode[TIMER2]==TIMER_MODE_MILIE)
				{
					 

					TIMER2_CNTRL_REG|=F_CPU_CLOCK_64_TIMER_2;
					/*Check whether it is polled or not*/
					if(sgau8_Interrupt_Mode[TIMER2]==POLLING)
					{                            
						/*Loop  until it get the time of delay in micro*/
						while(u32_Copy_TIMER_Start_tickCounts!=u16_Count_TIMER_Start)
						{
							/************************************************************
							 * The prescale divide by 64 and  make count =125U and  the 
							 * counter =255-125U to get overflow every mili
							 ************************************************************/
							TIMER2_COUNTER_REG=(uint8_t)(TIMER2_OVF_COUNT-125U);
							/*Loop  until overflow happens*/
							while( BIT_IS_CLR(TIMER_EVENT_FLAGS_REG,TIMER2_OVF_COUNT_FLAG_BIT) );
							SET_BIT(TIMER_EVENT_FLAGS_REG,TIMER2_OVF_COUNT_FLAG_BIT);
							u16_Count_TIMER_Start++;
						}
						
					}
					else if(sgau8_Interrupt_Mode[TIMER2]==INTERRUPT)
					{
						/*****************************************************
						 *Let the ISR execute the increment of count of delay
						 *Note that we will extern the value of 
						 ****************************************************/
						 sgPntrToFunc_TIMER_OVF=PntrToFunc_Copy_TIMER_Start_ISR;													
					}
					else
					{
					}
					
					
				}
				else
				{
				}

			}/*Check whether it is counter or timer*/
			else if(sgau8_TIMERMode[TIMER2]==COUNTER_MODE)
			{

				/*Check whether it is polled or not*/
				if(sgau8_Interrupt_Mode[TIMER2]==POLLING)
				{ 
                    SET_BIT(TIMER_EVENT_FLAGS_REG,TIMER2_OVF_COUNT_FLAG_BIT);
				    TIMER2_COUNTER_REG=TIMER2_OVF_COUNT-u32_Copy_TIMER_Start_tickCounts;
					/*Loop  until overflow happens*/
					while( BIT_IS_CLR(TIMER_EVENT_FLAGS_REG,TIMER2_OVF_COUNT_FLAG_BIT) );					
				}
				else if(sgau8_Interrupt_Mode[TIMER2]==INTERRUPT)
				{
					/*Let the ISR execute the called back function*/
					sgPntrToFunc_TIMER_OVF=PntrToFunc_Copy_TIMER_Start_ISR;						
				}
				else
				{
				}
			}
			else
			{
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

uint8_t Timer_Stop(uint8_t u8_Copy_TIMER_Start_TIMERChannel)
{ 
	switch(u8_Copy_TIMER_Start_TIMERChannel)
	{
		case TIMER0:
		{
			//Stop the clock
			SET_VAlUE_IN_POSTION_FROM_tO(0,2,TIMER0_CNTRL_REG,NO_CLOCK_TIMER_0);
		}
		break;
		case TIMER1:
		{
			//Stop the clock
			SET_VAlUE_IN_POSTION_FROM_tO(0,2,TIMER1_CNTRL_REG_B,NO_CLOCK_TIMER_1);
		}
		break;
		case TIMER2:
		{
			//Stop the clock
			SET_VAlUE_IN_POSTION_FROM_tO(0,2,TIMER2_CNTRL_REG,NO_CLOCK_TIMER_2);				
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

uint8_t Timer_Get_tickCount(uint8_t u8_Copy_TIMER_Start_TIMERChannel, void volatile*Copy_uint8Ptr_TIMERTickTime)
{
	switch(u8_Copy_TIMER_Start_TIMERChannel)
	{
		case TIMER0:
		{
			Copy_uint8Ptr_TIMERTickTime=&TIMER0_COUNTER_REG;
		}
		break;
		case TIMER1:
		{
			Copy_uint8Ptr_TIMERTickTime=&TIMER1_COUNTER_REG;
		}
		break;
		case TIMER2:
		{
			Copy_uint8Ptr_TIMERTickTime=&TIMER2_COUNTER_REG;
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

uint8_t Timer_Get_FlagStatus(uint8_t u8_Copy_TIMER_Start_TIMERChannel, void volatile*Copy_uint8Ptr_FlagStatus)
{
	static uint8_t OVF_FLAG=0;
	
	switch(u8_Copy_TIMER_Start_TIMERChannel)
	{
		case TIMER0:
		{
			OVF_FLAG=GET_BIT(TIMER_EVENT_FLAGS_REG,TIMER0_OVF_COUNT_FLAG_BIT);
			Copy_uint8Ptr_FlagStatus=&OVF_FLAG;
		}
		break;
		case TIMER1:
		{
			OVF_FLAG=GET_BIT(TIMER_EVENT_FLAGS_REG,TIMER1_OVF_COUNT_FLAG_BIT);
			Copy_uint8Ptr_FlagStatus=&OVF_FLAG;
		}
		break;
		case TIMER2:
		{
			OVF_FLAG=GET_BIT(TIMER_EVENT_FLAGS_REG,TIMER2_OVF_COUNT_FLAG_BIT);
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

uint8_t Timer_Reset(uint8_t u8_Copy_TIMER_Start_TIMERChannel)
{
	switch(u8_Copy_TIMER_Start_TIMERChannel)
	{
		case TIMER0:
		{
			CLR_PORT(TIMER0_COUNTER_REG);
		}
		break;
		case TIMER1:
		{
			CLR_PORT(TIMER1_COUNTER_REG);
		}
		break;
		case TIMER2:
		{
			CLR_PORT(TIMER2_COUNTER_REG);
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

Timer_ISR(TIMER0_OVF_vect_num)
{

	TIMER0_COUNTER_REG=sgu16_TIMER_COUNTER_REG_BUFFER;
    sgPntrToFunc_TIMER_OVF();
}
Timer_ISR(TIMER1_OVF_vect_num)
{
    TIMER1_COUNTER_REG=sgu16_TIMER_COUNTER_REG_BUFFER;
	sgPntrToFunc_TIMER_OVF();
}

Timer_ISR(TIMER2_OVF_vect_num)
{
    TIMER2_COUNTER_REG=sgu16_TIMER_COUNTER_REG_BUFFER;
	sgPntrToFunc_TIMER_OVF();
}