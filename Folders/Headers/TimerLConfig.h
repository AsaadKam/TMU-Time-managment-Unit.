/*
 * TimerConfig.h
 *
 * Created: 05/11/2019 18:35:37
 *  Author: Native_programmer
 */ 


#ifndef TIMERCONFIG_H_
#define TIMERCONFIG_H_

#include "Atmega32Registers.h"
#include "DIO.h"

           
#define CPU_FLAG_Register                         SREG
#define INT_BIT                                   I

#define TIMER0_COUNTER_Register                   TCNT0
#define TIMER0_CNTRL_Register                     TCCR0
#define TIMER0_COMPARE_Register                   OCR0
#define TIMER0_DATA_DIRCETION_Register            DDRB
#define TIMER0_Wave_Out_BIT                       D11

#define TIMER1_COMPARE_A_Register                 OCR1A
#define TIMER1_COUNTER_Register                   TCNT1

#define TIMER2_COUNTER_Register                   TCNT2
#define TIMER2_CNTRL_Register                     TCCR2
#define TIMER2_COMPARE_Register                   OCR2

#define TIMER_EVENT_FLAGS_REGISTER                TIFR
#define TIMER_ENABLE_INTERRUPT_REGISTER           TIMSK

#define TIMER0_OVERFLOW_FLAG_BIT                  TOV0
#define TIMER1_OVERFLOW_FLAG_BIT                  TOV1
#define TIMER2_OVERFLOW_FLAG_BIT                  TOV2
#define TIMER0_Compare_FLAG_BIT                   OCF0
#define TIMER0_OVERFLOW_INT_EN_BIT                TOIE0
#define TIMER0_Compare_INT_EN_BIT                 OCIE0 		
#define TIMER1_CNTRL_Register_B                   TCCR1B
#define TIMER1_OVERFLOW_INT_EN_BIT                TOIE1									  



#endif /* TIMERCONFIG_H_ */