/*
 * UART.c
 *
 * Created: 10/13/2020 9:00:44 AM
 *  Author: star
 */ 
#include "UART.h"

#define Baud_prescale	(((F_CPU / (USART_BAUDRATE * 8UL))) - 1)

void UART_init(const UART_ConfigType * Config_Ptr)
{
	UCSRC_R = (1 << URSEL_B)						|
	(Config_Ptr -> parity 	<< UPM0_B)	|
	(Config_Ptr -> stop_bit 	<< USBS_B) 	|
	(Config_Ptr -> bits 		<< UCSZ0_B);

	UCSRB_R = (1 << RXEN_B) | (1 << TXEN_B);

	UCSRA_R = (1 << U2X_B);

	UBRRL_R	= Baud_prescale;
	UBRRH_R = Baud_prescale >> 8;
}

void UART_sendByte(uint8 data)
{
	UDR_R = data;
	while(BitIsClear(UCSRA_R,TXC_B));
	SetBit(UCSRA_R,TXC_B);
}

void UART_sendString(const uint8 * Str_Ptr)
{
	uint8 i = 0;
	while (Str_Ptr[i] != '\0')
	{
		UART_sendByte(Str_Ptr[i]);
		i++;
	}
}

uint8
UART_recieveByte(void)
{
	while(BitIsClear(UCSRA_R,RXC_B));
	return UDR_R;
}

void UART_recieveString(uint8 * Str_Ptr)
{
	uint8 i = 0;
	do
	{
		Str_Ptr[i] = UART_recieveByte();
		i++;
	}
	while(Str_Ptr[i] != '#');

	Str_Ptr[i] = '\0';
}