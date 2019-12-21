#ifndef TMU_H_
#define TMU_H_



/*- INCLUDES -----------------------------------------------*/
#include"Timer.h"
#include"DATA_types.h"
/*-  MACROS -------------------------------------------------*/
/******************************************************************/
/*              TMU_TIMER_Structure_Config                        */
/******************************************************************/
#define     StrTMU_Configuration_t         StrTimerConfiguration_t
#define     TMU_TIMER_IDS                  Timer_Channel
#define     TMU_TIMER_ID0                  TIMER0
#define     TMU_TIMER_ID1                  TIMER1
#define     TMU_TIMER_ID2                  TIMER2
#define     TMU_TIMER_PSC                  Timer_Psc  
#define     TMU_TIMER_MODE                 Timer_Mode 
#define     TMU_TIMER_MODE_MICRO           TIMER_MODE_MICRO  
#define     TMU_TIMER_MODE_MILIE           TIMER_MODE_MILIE    
#define     TMU_TIMER_COUNTER_MODE         COUNTER_MODE  
#define     TMU_TIMER_INT_Mode             Interrupt_Mode
#define     TMU_TIMER_INT                  INTERRUPT
#define     TMU_No_Need_For_TickCounts      0
#define     TMU_Function_PERIODIC           0
#define     TMU_Function_ONESHOT            1
/*________________________________________________________________*/
/******************************************************************/
/*              TMU_TIMER_Prescaler                               */
/******************************************************************/

/*_______TMU_TIMER0__________________________________*/
#define NO_CLOCK_TMU_TIMER_ID0     					0U
#define F_CPU_CLOCK_TMU_TIMER_ID0   					1U
#define F_CPU_CLOCK_8_TMU_TIMER_ID0 					2U
#define F_CPU_CLOCK_64_TMU_TIMER_ID0					3U
#define F_CPU_CLOCK_256_TMU_TIMER_ID0					4U
#define F_CPU_CLOCK_1024_TMU_TIMER_ID0				5U
#define F_EXTERNAL_CLOCK_FALLING_TMU_TIMER_ID0		6U
#define F_EXTERNAL_CLOCK_RISING_TMU_TIMER_ID0		7U

/*_______TMU_TIMER1__________________________________*/
#define NO_CLOCK_TMU_TIMER_ID1     					0U
#define F_CPU_CLOCK_TMU_TIMER_ID1   					1U
#define F_CPU_CLOCK_8_TMU_TIMER_ID1 					2U
#define F_CPU_CLOCK_64_TMU_TIMER_ID1					3U
#define F_CPU_CLOCK_256_TMU_TIMER_ID1					4U
#define F_CPU_CLOCK_1024_TMU_TIMER_ID1				5U
#define F_EXTERNAL_CLOCK_FALLING_TMU_TIMER_ID1		6U
#define F_EXTERNAL_CLOCK_RISING_TMU_TIMER_ID1			7U

/*_______TMU_TIMER2__________________________________*/
#define NO_CLOCK_TMU_TIMER_ID2     					0U
#define F_CPU_CLOCK_TMU_TIMER_ID2   					1U
#define F_CPU_CLOCK_8_TMU_TIMER_ID2 					2U
#define F_CPU_CLOCK_32_TMU_TIMER_ID2					3U
#define F_CPU_CLOCK_64_TMU_TIMER_ID2					4U
#define F_CPU_CLOCK_128_TMU_TIMER_ID2					5U
#define F_CPU_CLOCK_256_TMU_TIMER_ID2		 			6U
#define F_CPU_CLOCK_1024_TMU_TIMER_ID2				7U

#define TMU_NO_NEED_PSC                             0U


/*__________________________________________________________*/
#define TMU_Counts_One_mili_TIMER_ID_ZERO 125
/*__________________________________________________________*/
/******************************************************************/
/**                       ERROR                                  **/
/******************************************************************/
#define TMU_Error_OK   0
#define TMU_Error_EXTRA_EVENTS  1
#define TMU_Error_Start_Null_func  2
#define TMU_Error_Nothing_To_Stop  3
#define TMU_Error_Function_type_undefined  4

/*__________________________________________________________*/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*- CONSTANTS ----------------------------------------------*/
/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t TMU_Error_t ;
/*- ENUMS --------------------------------------------------*/
/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/
/*_______________________________________________________________________________________________________________________________*/
/*Description: TMU Initialization
 * Input     : StrTMU_Configuration_t* pTMU_Init_Config->Configuration structure
               that configure the TMU and the timer of it also
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern TMU_Error_t TMU_Init();
/*_______________________________________________________________________________________________________________________________*/
/*Description: TMU Start
 * Input     : void(*PntrToFunc_Copy_TMU_Start)(void)->Pointer to function,Periodicity_MS->Periodicity milisecond
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern TMU_Error_t TMU_Start(PntrToFunc_t PntrToFunc_Copy_TMU_Start,uint16_t u16_Copy_Periodicity_MS_TMU_Start,uint16_t u16_Copy_Periodic_or_not_TMU_Start);
/*_______________________________________________________________________________________________________________________________*/
/*Description: TMU Initialization
 * Input     : Without input
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern TMU_Error_t TMU_Dispatch(void);
/*_______________________________________________________________________________________________________________________________*/
/*Description: TMU Stop
 * Input     : void(*PntrToFunc_Copy_TMU_Start)(void)->Pointer to function
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern TMU_Error_t TMU_Stop(PntrToFunc_t PntrToFunc_Copy_TMU_Start);


#endif /* TMU_H_ */