#include"TMU_LConfig.h"
#include"TMU.h"
#include"Timer.h"
#include"Timer_PB_Config.h"
#include<stdio.h>

TMU_Node TMU_Events_Array[TMU_Events]={0};

static u8 index=0;
u8 COUNT=0;
u8 OverFlow_Counts=0;
u8 Start_flag;


u8 TMU_Start(void(*PntrToFunc)(void),u16 Periodicity_MS)
{
    Start_flag=1;
	
	if(index>TMU_Events-1) return Error_NOK;
	
	else
	{		
	
		TMU_Events_Array[index].PntrToFunc=PntrToFunc;	
		TMU_Events_Array[index].Periodicity_MS=Periodicity_MS;

		index++;
		return Error_OK;
	
	}
}


u8 TMU_Dispatch(void)
{

	/***When Start_Stop_flag=0 ,we initialize the rearrange the queue.***/
    if(1U==Start_flag)
	{
		Start_flag=0U;
		u8 temp=0U;
		
		/***Sort the array of events by bubble sort ***/
        for(s8 j=0,i=(index-1)-j;i>=0;j++,i--)
        {			
			if(TMU_Events_Array[i-1].Periodicity_MS>TMU_Events_Array[i].Periodicity_MS)
			{
				temp=TMU_Events_Array[i].Periodicity_MS;
				TMU_Events_Array[i].Periodicity_MS=TMU_Events_Array[i-1].Periodicity_MS;
				TMU_Events_Array[i-1].Periodicity_MS=temp;
			}
			
		}
        /***print for debugging***/
	    printf("\n");		
		for( s8 i=0U;i<index;i++)
		{

				printf("%d",TMU_Events_Array[i].Periodicity_MS);
			
		}
	    printf("\n");
	}
	/***When Start_Stop_flag=1 ,we we will start the real managment by ***/
	else 
	{
	    for(u8 i=0;i<index-1;i++)
		{ 
	        /*We need to put counter increment in ISR and also add the idea of call back function to timers*/ 
			if(OverFlow_Counts!=0)
			{ 
			  if(!(TMU_Events_Array[i].Periodicity_MS%OverFlow_Counts)) TMU_Events_Array[i].PntrToFunc(); 			  
			}
		}
	}
	return Error_OK;
}


u8 TMU_Stop(void(*PntrToFunc)(void))
{

	u8 foundFlag=0;
	
	TMU_Node TMU_Node_temp={0,0};
	
	
	for(u8 i=0;i<index-1;i++)
	{
		if(TMU_Events_Array[i].PntrToFunc==PntrToFunc) 
		{
			foundFlag=1;
			TMU_Node_temp=TMU_Events_Array[i];
            while(i<index-1)
			{
				TMU_Events_Array[i]=TMU_Events_Array[i+1];
				i++;
			}
			TMU_Events_Array[index-1]=TMU_Node_temp;
			
		}
	}
	index--;
	if(foundFlag==0)          return Error_NOK;
    else                      return Error_OK;
	
}