#ifndef TMU_H_
#define TMU_H_
/*________________________________________________________________*/
/******************************************************************/
/*                        INCLUDES                                */
/******************************************************************/

#include"DATA_types.h"

/*________________________________________________________________*/
/******************************************************************/
/*                    Struct Function Input                       */
/******************************************************************/

/*_________________________________________________________________*/
//Defines
/******************************************************************/
/*              TMU_TIMER_Structure_Config                        */
/******************************************************************/
#define     StrTMU_Configuration_t     StrTimerConfiguration_t
#define     TMU_TIMER_IDS              Timer_Channel
#define     TMU_TIMER_ID0              TIMER0
#define     TMU_TIMER_ID1              TIMER1
#define     TMU_TIMER_ID2              TIMER2
#define     TMU_TIMER_PSC              Timer_Psc  
#define     TMU_TIMER_MODE             Timer_Mode 
#define     TMU_TIMER_MODE_MICRO       TIMER_MODE_MICRO  
#define     TMU_TIMER_MODE_MILIE       TIMER_MODE_MILIE    
#define     TMU_TIMER_COUNTER_MODE     COUNTER_MODE  
#define     TMU_TIMER_INT_Mode         Interrupt_Mode
#define     TMU_TIMER_INT              INTERRUPT


/*________________________________________________________________*/
/******************************************************************/
/*              TMU_TIMER_Prescaler                               */
/******************************************************************/

/*_______TMU_TIMER0__________________________________*/
#define NO_CLOCK_TMU_TIMER_0     					0U
#define F_CPU_CLOCK_TMU_TIMER_0   					1U
#define F_CPU_CLOCK_8_TMU_TIMER_0 					2U
#define F_CPU_CLOCK_64_TMU_TIMER_0					3U
#define F_CPU_CLOCK_256_TMU_TIMER_0					4U
#define F_CPU_CLOCK_1024_TMU_TIMER_0				5U
#define F_EXTERNAL_CLOCK_FALLING_TMU_TIMER_0		6U
#define F_EXTERNAL_CLOCK_RISING_TMU_TIMER_0			7U

/*_______TMU_TIMER1__________________________________*/
#define NO_CLOCK_TMU_TIMER_1     					0U
#define F_CPU_CLOCK_TMU_TIMER_1   					1U
#define F_CPU_CLOCK_8_TMU_TIMER_1 					2U
#define F_CPU_CLOCK_64_TMU_TIMER_1					3U
#define F_CPU_CLOCK_256_TMU_TIMER_1					4U
#define F_CPU_CLOCK_1024_TMU_TIMER_1				5U
#define F_EXTERNAL_CLOCK_FALLING_TMU_TIMER_1		6U
#define F_EXTERNAL_CLOCK_RISING_TMU_TIMER_1			7U

/*_______TMU_TIMER2__________________________________*/
#define NO_CLOCK_TMU_TIMER_2     					0U
#define F_CPU_CLOCK_TMU_TIMER_2   					1U
#define F_CPU_CLOCK_8_TMU_TIMER_2 					2U
#define F_CPU_CLOCK_32_TMU_TIMER_2					3U
#define F_CPU_CLOCK_64_TMU_TIMER_2					4U
#define F_CPU_CLOCK_128_TMU_TIMER_2					5U
#define F_CPU_CLOCK_256_TMU_TIMER_2		 			6U
#define F_CPU_CLOCK_1024_TMU_TIMER_2				7U

#define TMU_NO_NEED_PSC                             0U
/******************************************************************/
/*                        TMU_TIMER_IDS                          */
/******************************************************************/
#define TMU_TIMER0 0U
#define TMU_TIMER1 1U
#define TMU_TIMER2 2U

/*________________________________________________________________*/
#define TMU_Counts_One_mili_TIMER_ID_ZERO 125
/*________________________________________________________________*/
/******************************************************************/
/*                        ERROR                                   */
/******************************************************************/
#define Error_OK   0
#define Error_NOK  1
/*________________________________________________________________*/
/******************************************************************/
/*                        FUNCTIONS PROTOTYPES                    */
/******************************************************************/
/*_______________________________________________________________________________________________________________________________*/
/*Description: TMU Initialization
 * Input     : StrTMU_Configuration_t* pTMU_Init_Config->Configuration structure
               that configure the TMU and the timer of it also
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t TMU_Init();
/*_______________________________________________________________________________________________________________________________*/
/*Description: TMU Start
 * Input     : void(*PntrToFunc)(void)->Pointer to function,Periodicity_MS->Periodicity milisecond
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t TMU_Start(PntrToFunc_t PntrToFunc,uint16_t Periodicity_MS,uint16_t Periodic_or_not);
/*_______________________________________________________________________________________________________________________________*/
/*Description: TMU Initialization
 * Input     : Without input
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t TMU_Dispatch(void);
/*_______________________________________________________________________________________________________________________________*/
/*Description: TMU Stop
 * Input     : void(*PntrToFunc)(void)->Pointer to function
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t TMU_Stop(PntrToFunc_t PntrToFunc);


#endif /* TMU_H_ */