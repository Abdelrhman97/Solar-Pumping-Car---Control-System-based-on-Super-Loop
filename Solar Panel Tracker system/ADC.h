/*
 * ADC.h
 *
 * Created: 10/12/2020 11:10:04 PM
 *  Author: star
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "Macros.h"
// ADC Registers 
#define ADMUX_R		(*(volatile uint8 * const)0x0027)

#define MUX0_B		0
#define MUX1_B		1
#define MUX2_B		2
#define MUX3_B		3
#define MUX4_B		4
#define ADLAR_B		5
#define REFS0_B		6
#define REFS1_B		7

#define ADCSRA_R	(*(volatile uint8 * const)0x0026)

#define ADPS0_B		0
#define ADPS1_B		1
#define ADPS2_B		2
#define ADIE_B		3
#define ADIF_B		4
#define ADATE_B		5
#define ADSC_B		6
#define ADEN_B		7

#define ADCL_R		(*(volatile uint8 * const)0x0024)
#define ADCH_R		(*(volatile uint8 * const)0x0025)

#define ADC_R		(*(volatile uint16 * const)0x0024)

#define SFIOR_R		(*(volatile uint8 * const)0x0050)

#define ADTS0_B		5
#define ADTS1_B		6
#define ADTS2_B		7

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */

extern volatile uint16 g_ADC_value;

typedef enum
{
	AREF,AVCC,INTERNAL = 3
}ADC_Voltage;

typedef enum
{
	NO_PRESCALING,_2,_4,_8,_16,_32,_64,_128
}ADC_Prescalar;

typedef enum
{
	Polling,Interrupt
}ADC_Mode;

typedef struct
{
	ADC_Voltage   voltage;
	ADC_Prescalar prescalar;
	ADC_Mode      mode;
}ADC_ConfigType;

void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
void ADC_readChannel(uint8 channel_num,const ADC_ConfigType * Config_Ptr);

#endif /* ADC_H_ */