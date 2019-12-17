/*
 * DIO.c
 *
 * Created: 02/11/2019 00:35:26
 *  Author: Native_programmer
 */ 
#include "DIO.h"


u8 DIO_INIT_PORT(u8 Port_Name,u8 direction)
{
	
    switch(Port_Name)
    {
    case 'A':
       if(direction==0){DirectionRegisterA=0x00;}else{DirectionRegisterA=0xFF;}
       break;

    case 'B':
        if(direction==0){DirectionRegisterB=0x00;}else{DirectionRegisterB=0xFF;}
        break;

    case 'C':
        if(direction==0){DirectionRegisterC=0x00;}else{DirectionRegisterC=0xFF;}
        break;

    case 'D':
        if(direction==0){DirectionRegisterD=0x00;}else{DirectionRegisterD=0xFF;}
        break;
#if ATMEGA == 128	
	case 'E':
		if(direction==0){DDRE=0x00;}else{DDRE=0xFF;}
		break;
	case 'F':
		if(direction==0){DDRF=0x00;}else{DDRF=0xFF;}
		break;
	case 'G':
		if(direction==0){DDRG=0x00;}else{DDRG=0xFF;}
		break;
#endif		
    default :
	           return ERROR_NOK;
        break;
    }
	return ERROR_OK;
}
u8 DIO_Init_Nibble(u8 por,u8 nibble,u8 direction)
{
	switch(por)
	{
	case 'A': if (nibble==LOWER_NIBBLE)
               {
	             if(direction==INPUT)
				 {
					 CLR_LOWER_NIBBLE(DirectionRegisterA);
				 }
				 else if(direction==OUTPUT)
				 {
					 SET_LOWER_NIBBLE(DirectionRegisterA);
				 }					 					 
			   }
			   else if(nibble==HIGHER_NIBBLE)
			   {
				      if(direction==INPUT)
				      {
					      CLR_HIGHER_NIBBLE(DirectionRegisterA);
				      }
				      else if(direction==OUTPUT)
				      {
					      SET_HIGHER_NIBBLE(DirectionRegisterA);
				      }
			   }				   
	          break;

    case 'B': if (nibble==LOWER_NIBBLE)
			  {
					if(direction==INPUT)
					{
						CLR_LOWER_NIBBLE(DirectionRegisterB);
					}
					else if(direction==OUTPUT)
					{
						SET_LOWER_NIBBLE(DirectionRegisterB);
					}
			  }
			else if(nibble==HIGHER_NIBBLE)
			{
					if(direction==INPUT)
					{
						CLR_HIGHER_NIBBLE(DirectionRegisterB);
					}
					else if(direction==OUTPUT)
					{
						SET_HIGHER_NIBBLE(DirectionRegisterB);
					}
			}
              break;

    case 'C':  if (nibble==LOWER_NIBBLE)
	         {
		         if(direction==INPUT)
		         {
			         CLR_LOWER_NIBBLE(DirectionRegisterC);
		         }
		         else if(direction==OUTPUT)
		         {
			         SET_LOWER_NIBBLE(DirectionRegisterC);
		         }
	         }
	         else if(nibble==HIGHER_NIBBLE)
	         {
		         if(direction==INPUT)
		         {
			         CLR_HIGHER_NIBBLE(DirectionRegisterC);
		         }
		         else if(direction==OUTPUT)
		         {
			         SET_HIGHER_NIBBLE(DirectionRegisterC);
		         }
	         }
              break;

    case 'D': if (nibble==LOWER_NIBBLE)
	          {
		          if(direction==INPUT)
		          {
			          CLR_LOWER_NIBBLE(DirectionRegisterD);
		          }
		          else if(direction==OUTPUT)
		          {
			          SET_LOWER_NIBBLE(DirectionRegisterD);
		          }
	          }
	          else if(nibble==HIGHER_NIBBLE)
	          {
		          if(direction==INPUT)
		          {
			          CLR_HIGHER_NIBBLE(DirectionRegisterD);
		          }
		          else if(direction==OUTPUT)
		          {
			          SET_HIGHER_NIBBLE(DirectionRegisterD);
		          }
	          }
			  break;
#if ATMEGA == 128
	    case 'E': if (nibble==LOWER_NIBBLE)
	    {
		    if(direction==INPUT)
		    {
			    CLR_LOWER_NIBBLE(DDRE);
		    }
		    else if(direction==OUTPUT)
		    {
			    SET_LOWER_NIBBLE(DDRE);
		    }
	    }
	    else if(nibble==HIGHER_NIBBLE)
	    {
		    if(direction==INPUT)
		    {
			    CLR_HIGHER_NIBBLE(DDRE);
		    }
		    else if(direction==OUTPUT)
		    {
			    SET_HIGHER_NIBBLE(DDRE);
		    }
	    }
	    break;
	    case 'F': if (nibble==LOWER_NIBBLE)
	    {
		    if(direction==INPUT)
		    {
			    CLR_LOWER_NIBBLE(DDRF);
		    }
		    else if(direction==OUTPUT)
		    {
			    SET_LOWER_NIBBLE(DDRF);
		    }
	    }
	    else if(nibble==HIGHER_NIBBLE)
	    {
		    if(direction==INPUT)
		    {
			    CLR_HIGHER_NIBBLE(DDRF);
		    }
		    else if(direction==OUTPUT)
		    {
			    SET_HIGHER_NIBBLE(DDRF);
		    }
	    }
	    break;
	    case 'G': if (nibble==LOWER_NIBBLE)
	    {
		    if(direction==INPUT)
		    {
			    CLR_LOWER_NIBBLE(DDRG);
		    }
		    else if(direction==OUTPUT)
		    {
			    SET_LOWER_NIBBLE(DDRG);
		    }
	    }
	    else if(nibble==HIGHER_NIBBLE)
	    {
		    if(direction==INPUT)
		    {
			    CLR_HIGHER_NIBBLE(DDRG);
		    }
		    else if(direction==OUTPUT)
		    {
			    SET_HIGHER_NIBBLE(DDRG);
		    }
	    }
	    break;
#endif
		default :
		return ERROR_NOK;
		break;
}
return ERROR_OK;
}
u8 DIO_INIT_Pin(u8 pin, u8 direction)
{
	u8 por;

	if(pin>=PinsNeeded || pin>=No_of_pins ) return 0;
    else
	{
	por='A'+pin/PortSize;
	pin=pin%PortSize;
	}
	
    switch(por)
    {
    case 'A': if(direction==0){CLR_BIT(DirectionRegisterA,pin);}else{SET_BIT(DirectionRegisterA,pin);}
              break;

    case 'B': if(direction==0){CLR_BIT(DirectionRegisterB,pin);}else{SET_BIT(DirectionRegisterB,pin);}
              break;

    case 'C': if(direction==0){CLR_BIT(DirectionRegisterC,pin);}else{SET_BIT(DirectionRegisterC,pin);}
              break;

    case 'D': if(direction==0){CLR_BIT(DirectionRegisterD,pin);}else{SET_BIT(DirectionRegisterD,pin);}
#if ATMEGA == 128		
			  break;
	case 'E': if(direction==0){CLR_BIT(DDRE,pin);}else{SET_BIT(DDRE,pin);}
			  break;
	case 'F': if(direction==0){CLR_BIT(DDRF,pin);}else{SET_BIT(DDRF,pin);}
			  break;
	case 'G': if(direction==0){CLR_BIT(DDRG,pin);}else{SET_BIT(DDRG,pin);}
			  break;
#endif
	default :
	return ERROR_NOK;
	break;
	}
return ERROR_OK;
}

u8 DIO_Read_Port (u8 por, u8 * ReadData)
{
    switch(por)
    {
    case 'A': return WriteRegisterA;
              break;

    case 'B': return WriteRegisterB;
              break;

    case 'C': return WriteRegisterC;
              break;

    case 'D': return WriteRegisterD;
			  break;
			  
#if ATMEGA == 128

	case 'E': return PORTE;
			  break;
			  
	case 'F': return PORTF;
			  break;
			  
	case 'G': return PORTG;
			  break;			  
#endif

    default : return 0;
              break;
    }
}
u8 DIO_Write_Port(u8 por,u8 Data)
{
    switch(por)
    {
    case 'A': WriteRegisterA=Data;
			  break;
			  
    case 'B': WriteRegisterB=Data;
              break;

    case 'C': WriteRegisterC=Data;
              break;

    case 'D': WriteRegisterD=Data;
              break;
			  
#if ATMEGA == 128

	case 'E': PORTE=Data;
			  break;
	case 'F': PORTF=Data;
			  break;
	case 'G': PORTG=Data;
			  break;			  
	#endif
	default :
	return ERROR_NOK;
	break;
	}
return ERROR_OK;
}
u8 DIO_Read_Pin (u8 pin, u8 * ReadData)
{
	u8 por;
	if(pin>=PinsNeeded || pin>=No_of_pins ) return -1;
	else
	{
		por='A'+pin/PortSize;
		pin=pin%PortSize;
	}
		
    switch(por)
    {
   case 'A': return GET_BIT(ReadRegisterA,pin);
              break;

    case 'B': return GET_BIT(ReadRegisterB,pin);
			  break;

    case 'C': return GET_BIT(ReadRegisterC,pin);
              break;
			  
	case 'D': return GET_BIT(ReadRegisterD,pin);
	          break;		  
#if ATMEGA == 128


	case 'E': return GET_BIT(PINE,pin);
			  break;			  
	case 'F': return GET_BIT(PINF,pin);
			  break;			  
	case 'G': return GET_BIT(PING,pin);
			  break;	
			  		  
	#endif
	default :
	return ERROR_NOK;
	break;
	}
return ERROR_OK;
}
u8 DIO_Write_Pin(u8 pin,u8 BitValue)
{
	u8 por;
 	if(pin>=PinsNeeded || pin>=No_of_pins ) return ERROR_NOK;
 	else
 	{
	 	por='A'+pin/PortSize;
	 	pin=pin%PortSize;
 	}
	 
    switch(por)
    {
   case 'A': if(BitValue==0){CLR_BIT(WriteRegisterA,pin);}else{SET_BIT(WriteRegisterA,pin);}
              break;

    case 'B': if(BitValue==0){CLR_BIT(WriteRegisterB,pin);}else{SET_BIT(WriteRegisterB,pin);}
              break;

    case 'C': if(BitValue==0){CLR_BIT(WriteRegisterC,pin);}else{SET_BIT(WriteRegisterC,pin);}
              break;

    case 'D': if(BitValue==0){CLR_BIT(WriteRegisterD,pin);}else{SET_BIT(WriteRegisterD,pin);}
              break;

#if ATMEGA == 128
			  
	case 'E': if(BitValue==0){CLR_BIT(PORTE,pin);}else{SET_BIT(PORTE,pin);}
			  break;	
			  		  
	case 'F': if(BitValue==0){CLR_BIT(PORTF,pin);}else{SET_BIT(PORTF,pin);}
			  break;
			  
	case 'G': if(BitValue==0){CLR_BIT(PORTG,pin);}else{SET_BIT(PORTG,pin);}
			  break;	
			  
	#endif
	default :
	return ERROR_NOK;
	break;
	}
	return ERROR_OK;
}
u8 DIO_Toggle_Port(u8 por)
{
	switch(por)
	{
		case 'A':TOGGLE_PORT(WriteRegisterA);
			  break;
		case 'B':TOGGLE_PORT(WriteRegisterB);
		      break;
		case 'C':TOGGLE_PORT(WriteRegisterC);
			  break;
		case 'D':TOGGLE_PORT(WriteRegisterD);
		      break;
#if ATMEGA == 128
		case 'E':TOGGLE_PORT(PORTE);
			  break;
		case 'F':TOGGLE_PORT(PORTF);
			 break;
		case 'G':TOGGLE_PORT(PORTG);
			 break;
		#endif
		default :
		return ERROR_NOK;
		break;
		}
return ERROR_OK;
}
u8 DIO_Toggle_Pin(u8 pin)
{
	u8 por;
	if(pin>=PinsNeeded || pin>=No_of_pins ) return ERROR_NOK;
	else
	{
		por='A'+pin/PortSize;
		pin=pin%PortSize;
	}
	
	switch(por)
	{
		case 'A':TOGGLE_BIT(WriteRegisterA,pin);
			 break;
		case 'B':TOGGLE_BIT(WriteRegisterB,pin);
			 break;
		case 'C':TOGGLE_BIT(WriteRegisterC,pin);
			 break;
		case 'D':TOGGLE_BIT(WriteRegisterD,pin);
			 break;
#if ATMEGA == 128		
		case 'E':TOGGLE_BIT(PORTE,pin);
			 break;
		case 'F':TOGGLE_BIT(PORTF,pin);
			 break;
		case 'G':TOGGLE_BIT(PORTG,pin);
			 break;
#endif
		default :
		return ERROR_NOK;
		break;
		
	}
	return ERROR_OK;
}
u8 DIO_Read_Nibble(u8 por,u8 nibble,u8 shifted_left_or_not)
{
	switch(por)
	{
		case 'A': if (nibble==HIGHER_NIBBLE)
					{
			          if (shifted_left_or_not==NOT_SHIFTED)
			          {
						  return GET_HIGHER_NIBBLE_AT_LOW_BITS(WriteRegisterA);
			          }
					  else if(shifted_left_or_not==SHIFTED_LEFT)
					  {
						  return GET_HIGHER_NIBBLE_AT_HIGH_BITS(WriteRegisterA);
					  }
					}
					else if (nibble==LOWER_NIBBLE)
					{
						if(shifted_left_or_not==NOT_SHIFTED)
						 {
							 return GET_LOWER_NIBBLE_AT_LOW_BITS(WriteRegisterA);
						 }
						 else if(shifted_left_or_not==SHIFTED_LEFT)
						 {
							 return GET_LOWER_NIBBLE_AT_HIGH_BITS(WriteRegisterA);
						 }
					}
		break;

		case 'B': if (nibble==HIGHER_NIBBLE)
		{
			if (shifted_left_or_not==NOT_SHIFTED)
			{
				return GET_HIGHER_NIBBLE_AT_LOW_BITS(WriteRegisterB);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				return GET_HIGHER_NIBBLE_AT_HIGH_BITS(WriteRegisterB);
			}
		}
		else if (nibble==LOWER_NIBBLE)
		{
			if(shifted_left_or_not==NOT_SHIFTED)
			{
				return GET_LOWER_NIBBLE_AT_LOW_BITS(WriteRegisterB);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				return GET_LOWER_NIBBLE_AT_HIGH_BITS(WriteRegisterB);
			}
		}
		break;

		case 'C': if (nibble==HIGHER_NIBBLE)
		{
			if (shifted_left_or_not==NOT_SHIFTED)
			{
				return GET_HIGHER_NIBBLE_AT_LOW_BITS(WriteRegisterC);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				return GET_HIGHER_NIBBLE_AT_HIGH_BITS(WriteRegisterC);
			}
		}
		else if (nibble==LOWER_NIBBLE)
		{
			if(shifted_left_or_not==NOT_SHIFTED)
			{
				return GET_LOWER_NIBBLE_AT_LOW_BITS(WriteRegisterC);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				return GET_LOWER_NIBBLE_AT_HIGH_BITS(WriteRegisterC);
			}
		}
		break;

		case 'D': if (nibble==HIGHER_NIBBLE)
		{
			if (shifted_left_or_not==NOT_SHIFTED)
			{
				return GET_HIGHER_NIBBLE_AT_LOW_BITS(WriteRegisterD);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				return GET_HIGHER_NIBBLE_AT_HIGH_BITS(WriteRegisterD);
			}
		}
		else if (nibble==LOWER_NIBBLE)
		{
			if(shifted_left_or_not==NOT_SHIFTED)
			{
				return GET_LOWER_NIBBLE_AT_LOW_BITS(WriteRegisterD);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				return GET_LOWER_NIBBLE_AT_HIGH_BITS(WriteRegisterD);
			}
		}
		break;
		
		#if ATMEGA == 128

		case 'E': if (nibble==HIGHER_NIBBLE)
		{
			if (shifted_left_or_not==NOT_SHIFTED)
			{
				return GET_HIGHER_NIBBLE_AT_LOW_BITS(PORTE);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				return GET_HIGHER_NIBBLE_AT_HIGH_BITS(PORTE);
			}
		}
		else if (nibble==LOWER_NIBBLE)
		{
			if(shifted_left_or_not==NOT_SHIFTED)
			{
				return GET_LOWER_NIBBLE_AT_LOW_BITS(PORTE);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				return GET_LOWER_NIBBLE_AT_HIGH_BITS(PORTE);
			}
		}
		break;
		
		case 'F': if (nibble==HIGHER_NIBBLE)
		{
			if (shifted_left_or_not==NOT_SHIFTED)
			{
				return GET_HIGHER_NIBBLE_AT_LOW_BITS(PORTF);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				return GET_HIGHER_NIBBLE_AT_HIGH_BITS(PORTF);
			}
		}
		else if (nibble==LOWER_NIBBLE)
		{
			if(shifted_left_or_not==NOT_SHIFTED)
			{
				return GET_LOWER_NIBBLE_AT_LOW_BITS(PORTF);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				return GET_LOWER_NIBBLE_AT_HIGH_BITS(PORTF);
			}
		}
		break;
		
		case 'G': if (nibble==HIGHER_NIBBLE)
		{
			if (shifted_left_or_not==NOT_SHIFTED)
			{
				return GET_HIGHER_NIBBLE_AT_LOW_BITS(PORTG);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				return GET_HIGHER_NIBBLE_AT_HIGH_BITS(PORTG);
			}
		}
		else if (nibble==LOWER_NIBBLE)
		{
			if(shifted_left_or_not==NOT_SHIFTED)
			{
				return GET_LOWER_NIBBLE_AT_LOW_BITS(PORTG);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				return GET_LOWER_NIBBLE_AT_HIGH_BITS(PORTG);
			}
		}
		break;
		#endif

		default :
		return ERROR_NOK;
		break;
		
	}
	return ERROR_OK;
}
u8 DIO_Write_Nibble(u8 por ,u8 lower_or_higher_nibble,u8 data)
{
	switch(por)
	{
		case 'A':
				if (lower_or_higher_nibble==LOWER_NIBBLE)
				{
					WriteRegisterA&=0xf0;
					WriteRegisterA|=(data&0x0f);
				}
				else if(lower_or_higher_nibble==HIGHER_NIBBLE)
				{
					WriteRegisterA&=0x0f;
					WriteRegisterA|=((data<<4)&0xf0);
				}
				break;
		case 'B':
				if (lower_or_higher_nibble==LOWER_NIBBLE)
				{
					WriteRegisterB&=0xf0;
					WriteRegisterB|=(data&0x0f);
				}
				else if(lower_or_higher_nibble==HIGHER_NIBBLE)
				{
					WriteRegisterB&=0x0f;
					WriteRegisterB|=((data<<4)&0xf0);
				}
				break;
		case 'C':
				if (lower_or_higher_nibble==LOWER_NIBBLE)
				{
					WriteRegisterC&=0xf0;
					WriteRegisterC|=(data&0x0f);
				}
				else if(lower_or_higher_nibble==HIGHER_NIBBLE)
				{
					WriteRegisterC&=0x0f;
					WriteRegisterC|=((data<<4)&0xf0);
				}
				break;
		case 'D':
				if (lower_or_higher_nibble==LOWER_NIBBLE)
				{
					WriteRegisterD&=0xf0;
					WriteRegisterD|=(data&0x0f);
				}
				else if(lower_or_higher_nibble==HIGHER_NIBBLE)
				{
					WriteRegisterD&=0x0f;
					WriteRegisterD|=((data<<4)&0xf0);
				}
				break;
        #if ATMEGA == 128				
		case 'E':
				if (lower_or_higher_nibble==LOWER_NIBBLE)
				{
					PORTE&=0xf0;
					PORTE|=(data&0x0f);
				}
				else if(lower_or_higher_nibble==HIGHER_NIBBLE)
				{
					PORTE&=0x0f;
					PORTE|=((data<<4)&0xf0);
				}
				break;
		case 'F':
				if (lower_or_higher_nibble==LOWER_NIBBLE)
				{
					PORTF&=0xf0;
					PORTF|=(data&0x0f);
				}
				else if(lower_or_higher_nibble==HIGHER_NIBBLE)
				{
					PORTF&=0x0f;
					PORTF|=((data<<4)&0xf0);
				}
				break;
		case 'G':
				if (lower_or_higher_nibble==LOWER_NIBBLE)
				{
					PORTG&=0xf0;
					PORTG|=(data&0x0f);
				}
				else if(lower_or_higher_nibble==HIGHER_NIBBLE)
				{
					PORTG&=0x0f;
					PORTG|=((data<<4)&0xf0);
				}
				break;
				#endif
				default :
				return ERROR_NOK;
				break;
				}
return ERROR_OK;
}
