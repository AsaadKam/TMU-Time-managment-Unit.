/*
 * BitManipulation.h
 *
 * Created: 02/11/2019 00:43:50
 *  Author: Asaad
 */ 


#ifndef BITMANIPULATION_H_
#define BITMANIPULATION_H_

#define SET_PORT(REG)	(PortREG|=0xff)
#define CLR_PORT(REG)	(REG&=(0x00))
#define SET_BIT(REG,INDEX) (REG|=(1<<INDEX))
#define CLR_BIT(REG,INDEX) (REG&=(~(1<<INDEX)))
#define GET_BIT(REG,INDEX) ((REG>>INDEX)&0x01)
#define TOGGLE_BIT(REG,INDEX) (REG^=(1<<INDEX))
#define TOGGLE_PORT(REG) (REG^=0xff)
#define BIT_IS_SET(REG,INDEX) (REG&(1<<INDEX))
#define BIT_IS_CLR(REG,INDEX) (!(REG&(1<<INDEX)))
#define SET_LOWER_NIBBLE(REG) (REG|=0x0f)///////////////////////////////////////////////////
#define CLR_LOWER_NIBBLE(REG) (REG&=0xf0)
#define SET_HIGHER_NIBBLE(REG) (REG|=0xf0)
#define CLR_HIGHER_NIBBLE(REG) (REG&=0x0f)
#define GET_LOWER_NIBBLE_AT_LOW_BITS(REG) (REG&0x0f) /////////////////////////////////////
#define GET_HIGHER_NIBBLE_AT_LOW_BITS(REG) ((REG>>4)&0x0f)
#define GET_LOWER_NIBBLE_AT_HIGH_BITS(REG) ((REG<<4)&0xf0)
#define GET_HIGHER_NIBBLE_AT_HIGH_BITS(REG) (REG&0xf0)
#define SET_VAlUE_IN_POSTION_FROM_TO(i,j,REG,VALUE) REG=(  ( (~((~( 0XFF<<(j-i+1) ))<<i))&REG ) |   (VALUE<<i) )

#endif