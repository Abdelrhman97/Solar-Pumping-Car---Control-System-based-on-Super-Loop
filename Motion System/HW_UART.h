/*
 * HW_UART.h
 *
 * Created: 10/13/2020 8:58:13 AM
 *  Author: star
 */ 


#ifndef HW_UART_H_
#define HW_UART_H_

#define	UDR_R		(*(volatile uint8 * const)0x002C)

#define UCSRA_R		(*(volatile uint8 * const)0x002B)

#define	MPCM_B		0
#define U2X_B		1
#define PE_B		2
#define DOR_B		3
#define FE_B		4
#define UDRE_B		5
#define TXC_B		6
#define RXC_B		7

#define UCSRB_R		(*(volatile uint8 * const)0x002A)

#define TXB8_B		0
#define RXB8_B		1
#define UCSZ2_B		2
#define TXEN_B		3
#define RXEN_B		4
#define UDRIE_B		5
#define TXCIE_B		6
#define RXCIE_B		7

#define UCSRC_R		(*(volatile uint8 * const)0x0040)

#define	UCPOL_B		0
#define UCSZ0_B		1
#define UCSZ1_B		2
#define USBS_B		3
#define UPM0_B		4
#define UPM1_B		5
#define UMSEL_B		6
#define URSEL_B		7

#define UBRRL_R		(*(volatile uint8 * const)0x0029)
#define UBRRH_R		(*(volatile uint8 * const)0x0040)



#endif /* HW_UART_H_ */