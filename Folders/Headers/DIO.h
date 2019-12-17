/*
 * DIO.h
 *
 * Created: 02/11/2019 00:35:59
 *  Author: Native_programmer
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "BitManipulation.h"
#include "Data_Types.h"
#include "DIOConfig.h"


/***************************************************************/
/******************GENERAL_PARPOUS_INPUT_OUTPUT*****************/
/***************************************************************/



/*_____________________________DIO_DIRECTION________________________________*/
#define OUTPUT 1
#define INPUT 0

/*______________________________DIO_DATA__________________________________*/
#define HIGH 1
#define LOW 0

/*________________________________________________________________*/
/******************************************************************/
/*                        ERROR STATUS                            */
/******************************************************************/
#define ERROR_OK     0
#define ERROR_NOK    1

#define LOWER_NIBBLE  0
#define HIGHER_NIBBLE 1

#define SHIFTED_LEFT 0
#define NOT_SHIFTED  1

//Macro
#define  EnableGeneralInterrupt()    SET_BIT(CPU_FLAG_Register,INT_BIT)

//Functions
u8 DIO_INIT_PORT(u8 por,u8 direction); // function used to initiate data direction of a given port.....  ex:- fun(LCD_PORT,INPUT)

u8 DIO_INIT_Pin(u8 pin, u8 direction); // function used to initiate data direction a single pin in a given register.....ex:- fun(KEY_BAD_PORT,6,INPUT)

u8 DIO_Init_Nibble(u8 por,u8 nibble,u8 direction); // function to initiate data direction of nibble in a given port.....  ex:- fun(SEVEN_SEGGMENT_PORT,LOWER_NIBBLE,OUTPUT)

u8 DIO_Read_Port (u8 por, u8 * ReadData); // function returns port state.....  ex:- fun(LCD_PORT)

u8 DIO_Read_Pin (u8 pin, u8 * ReadData); // function that returns the value of a pin in a register.....  ex:- fun(LCD_PORT,LCD_RS_PIN)

u8 DIO_Read_Nibble(u8 por,u8 nibble,u8 shifted_left_or_not); // this function is used to read a nibble ....ex:- fun(LCD_DATA_PORT,HIGHER_NIBBLE,NOT_SHIFTED)

u8 DIO_Write_Port (u8 por,u8 Data); // function to write data to given port.....  ex:- fun(LCD_PORT,99)

u8 DIO_Write_Pin(u8 pin,u8 BitValue); // function used to.....  ex:- fun(LCD_PORT,LCD_ENABLE_PIN,1)

u8 DIO_Write_Nibble(u8 por ,u8 lower_or_higher_nibble,u8 data); // this function is used to write on nibble ... ex:- fun(LCD_DATA_PORT,LOWER_NIBBLE,'M')

u8 DIO_Toggle_Port(u8 por); // this function is used to toggle defined port.....  ex:- fun(LED_LINE_PORT)

u8 DIO_Toggle_Pin(u8 pin); // this function is used to toggle pin in a defined port .....  ex:- fun(LED_PORT,LED_PIN)

u8 DIO_Activate_Pullup (u8 Pin_Number);






#endif/* DIO_H_ */

 