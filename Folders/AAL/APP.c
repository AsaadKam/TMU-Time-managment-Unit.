/*
 * APP.C
 *
 * Created: 17/12/2019 18:33:53
 *  Author: Asaad
 */ 

/*- INCLUDES ----------------------------------------------*/

#include"TMU.h"
#include<stdio.h>
#include<assert.h>

/*- LOCAL MACROS ------------------------------------------*/

/*- LOCAL Dataypes ----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/

/*- GLOBAL STATIC VARIABLES -------------------------------*/

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
void print(void)
{
	printf("print");
}
void get(void)
{
	printf("get");
}
void send(void)
{
	printf("send");
}
int main()
{
	/****TMU Initiate****/
	
	/****TMU start ****/
	assert(TMU_Start(print,5)==Error_OK);
	assert(TMU_Start(get,3)==Error_OK);
	assert(TMU_Start(send,7)==Error_OK);
	assert(TMU_Stop(print)==Error_OK);
/*    while(1)
	{*/
		/***TMU  dispatch ***/
		assert(TMU_Dispatch()==Error_OK   );
	    assert(TMU_Stop(get)==Error_OK); 
		assert(TMU_Dispatch()==Error_OK   );
	    assert(TMU_Start(get,3)==Error_OK);	
		assert(TMU_Dispatch()==Error_OK   );		
/*	}*/
}
/*- APIs IMPLEMENTATION -----------------------------------*/


