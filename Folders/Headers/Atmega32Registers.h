/*
 * Atmega32Registers.h
 *
 * Created: 04/11/2019 01:15:54
 *  Author: Native_programmer
 */ 


#ifndef ATMEGA32REGISTERS_H_
#define ATMEGA32REGISTERS_H_

#include "Data_Types.h"
#define  ATMEGA     32

#define  DataBus    8
#define  PortSize   DataBus
#define  No_of_ports 4


//TWI Registers
#define TWBR    ( *((volatile u8* )(0X20)) )
#define TWSR    ( *((volatile u8* )(0X21)) )
#define TWAR    ( *((volatile u8* )(0X22)) )
#define TWDR    ( *((volatile u8* )(0X23)) )
//ADC Registers
#define ADCL    ( *((volatile u8* )(0X24)) )
#define ADCH    ( *((volatile u8* )(0X25)) )
#define ADCSRA  ( *((volatile u8* )(0X26)) )          
#define ADMUX   ( *((volatile u8* )(0X27)) )
//Analog Comparator Registers
#define ACSR    ( *((volatile u8* )(0X28)) )
//UART Registers
#define UBRRL   ( *((volatile u8* )(0X29)) )
#define UCSRB   ( *((volatile u8* )(0X2A)) )
#define UCSRA   ( *((volatile u8* )(0X2B)) )
#define UDR     ( *((volatile u8* )(0X2C)) )
//SPI Registers
#define SPCR    ( *((volatile u8* )(0X2D)) )
#define SPSR    ( *((volatile u8* )(0X2E)) )
#define SPDR    ( *((volatile u8* )(0X2F)) )
//DIO Registers
#define PIND    ( *((volatile u8* )(0X30)) )
#define DDRD    ( *((volatile u8* )(0X31)) )
#define PORTD   ( *((volatile u8* )(0X32)) )
#define PINC    ( *((volatile const u8* )(0X33)) )
#define DDRC    ( *((volatile u8* )(0X34)) )
#define PORTC   ( *((volatile u8* )(0X35)) )
#define PINB    ( *((volatile const u8* )(0X36)) )
#define DDRB    ( *((volatile u8* )(0X37)) )
#define PORTB   ( *((volatile u8* )(0X38)) )
#define PINA    ( *((volatile const u8* )(0X39)) )
#define DDRA    ( *((volatile u8* )(0X3A)) )
#define PORTA   ( *((volatile u8* )(0X3B)) )
//EEPROM Registers
#define EECR    ( *((volatile u8* )(0X3C)) )
#define EEDR    ( *((volatile u8* )(0X3D)) )
#define EEARL   ( *((volatile u8* )(0X3E)) )
#define EEARH   ( *((volatile u8* )(0X3F)) )
//The rest of UART Registers
#define UCSRC   ( *((volatile u8* )(0X40)) )
#define UBRRH   ( *((volatile u8* )(0X40)) )
#define WDTCR   ( *((volatile u8* )(0X41)) )
//Asynchronous Timer Registers
#define ASSR    ( *((volatile u8* )(0X42)) )
#define OCR2    ( *((volatile u8* )(0X43)) )
#define TCNT2   ( *((volatile u8* )(0X44)) )
#define TCCR2   ( *((volatile u8* )(0X45)) )
//Timer1 Registers
#define ICR1	( *((volatile u16* )(0X46)) )
#define ICR1L	( *((volatile u8* )(0X46)) )
#define ICR1H   ( *((volatile u8* )(0X47)) )
#define OCR1B   ( *((volatile u16*)(0X48)) )
#define OCR1BL  ( *((volatile u8* )(0X48)) )
#define OCR1BH  ( *((volatile u8* )(0X49)) )
#define OCR1A   ( *((volatile u16* )(0X4A)) )
#define OCR1AL  ( *((volatile u8* )(0X4A)) )
#define OCR1AH  ( *((volatile u8* )(0X4B)) )
#define TCNT1   ( *((volatile u16* )(0X4C)) )
#define TCNT1L  ( *((volatile u8* )(0X4C)) )
#define TCNT1H  ( *((volatile u8* )(0X4D)) )
#define TCCR1B  ( *((volatile u8* )(0X4E)) )
#define TCCR1A  ( *((volatile u8* )(0X4F)) )
//Special Function Register
#define SFIOR   ( *((volatile u8* )(0X50)) )
//On-Chip Debug Register
#define OCDR    ( *((volatile u8* )(0X51)) )
////On-Chip Debug Register
#define OSCCAL  ( *((volatile u8* )(0X51)) )
//Timer0 Registers
#define TCNT0   ( *((volatile u8* )(0X52)) ) 
#define TCCR0   ( *((volatile u8* )(0X53)) )
//MCU Status and Control Registers
#define MCUCSR  ( *((volatile u8* )(0X54)) )
#define MCUCR   ( *((volatile u8* )(0X55)) )
//Register of TWO WIRE Control Register
#define TWCR    ( *((volatile u8* )(0X56)) )

#define SPMCR   ( *((volatile u8* )(0X57)) )
//Timer's Interrupt Flags
#define TIFR    ( *((volatile u8* )(0X58)) )
#define TOV0    0
#define TOV1    2
#define TOV2    6
#define OCF0    1
#define TIMSK   ( *((volatile u8* )(0X59)) )
#define TOIE0   0
#define OCIE0   1
#define TOIE1   2
//General Interrupt Flags
#define GIFR    ( *((volatile u8* )(0X5A)) )
#define GICR    ( *((volatile u8* )(0X5B)) )
#define INT1    7
#define INT0    6
#define INT2    5
//Timer0 Output Compare Register
#define OCR0    ( *((volatile u8* )(0X5C)) )
//Stack pointer Register
#define SPL     ( *((volatile u8* )(0X5D)) )
#define SPH     ( *((volatile u8* )(0X5E)) )
//Status Register
#define SREG    ( *((volatile u8* )(0X5F)) )
#define I       7

/*
#define A           0
#define B           1
#define C           2
#define D           3
#define PORT(PORT_NAME)    ( *((volatile INT8U* )      (0X3B-3(PORT_NAME)) )
#define DDRA(PORT_NAME)    ( *((volatile INT8U* )      (0X3A-3(PORT_NAME)) )
#define PINA(PORT_NAME)    ( *((volatile const INT8U* )(0X39-3(PORT_NAME)) )
*/

//Timer Registers


#endif /* ATMEGA32REGISTERS_H_ */