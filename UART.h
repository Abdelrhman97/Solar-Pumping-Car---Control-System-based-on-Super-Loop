/*
 * UART.h
 *
 * Created: 10/13/2020 8:59:23 AM
 *  Author: star
 */ 


#ifndef UART_H_
#define UART_H_

#include "HW_UART.h"
#include "Config.h"
#include "Macros.h"

#define USART_BAUDRATE 9600

typedef enum
{
	Disabled,Even = 2,Odd
}UART_Parity;

typedef enum
{
	_1_bit,_2_bit
}UART_StopBit;

typedef enum
{
	_5_bit,_6_bit,_7_bit,_8_bit
}UART_Bits;

typedef struct
{
	UART_Parity		parity;
	UART_StopBit	stop_bit;
	UART_Bits		bits;
}UART_ConfigType;

void UART_init(const UART_ConfigType * Config_Ptr);
void UART_sendByte(uint8 data);
void UART_sendString(const uint8 * Str_Ptr);
uint8 UART_recieveByte(void);
void UART_recieveString(uint8 * Str_Ptr);



#endif /* UART_H_ */