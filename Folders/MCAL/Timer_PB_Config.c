/*
 * TimerConfig.c
 *
 * Created: 23/11/2019 04:07:28
 *  Author: Native_programmer
 */ 


#include "TimerConfig.h"

/*
 *
 * Let's suppose i have two case the 1st one i want to delay for 4ms and we will initiate for 1st case structure
 *              from type called TimerConfig called u_DelayConfig and let us define it 
 *
 *
 */

//Initialization for structure
TimerConfig m_DelayConfig,CountConfig;

void TimerConfiguration(void )
{


m_DelayConfig.Ch=Timer1;//I choose timer 1
m_DelayConfig.TimerMode=Timer_Mode;//Timer not counter mode
m_DelayConfig.Mode=Timer_Polling;//Use pooling
m_DelayConfig.Delay=1000;//1000 millisecond+
                               /* The second configuration for counting event on pin T1 */


CountConfig.Ch=Timer1;//I choose timer 1
CountConfig.TimerMode=Timer_Mode;//Timer not counter mode
CountConfig.Mode=Timer_Polling;//Use pooling
CountConfig.Count=1000;//50 millisecond

}