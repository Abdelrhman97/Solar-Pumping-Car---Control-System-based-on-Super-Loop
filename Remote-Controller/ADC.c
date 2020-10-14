/*
 * ADC.c
 *
 * Created: 10/12/2020 11:11:17 PM
 *  Author: star
 */ 

#include "ADC.h"

volatile uint16 g_ADC_value = 0;

ISR(ADC_vect)
{
	g_ADC_value = ADCL_R;
}

void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX_R = ((Config_Ptr -> voltage) << 6) & 0xC0;

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 1 Enable ADC Interrupt
	 * ADPS2:0 = 011 to choose ADC_Clock=F_CPU/8=1Mhz/8=125Khz --> ADC must operate in range 50-200Khz
	 */

	/* Check if we are using polling mode */
	if(Config_Ptr -> mode == 0)
	{
		ADCSRA_R = (1 << ADEN_B) | (Config_Ptr -> prescalar & 0x07);
	}
	/* Check if we are using interrupt mode */
	else if(Config_Ptr -> mode == 1)
	{
		ADCSRA_R = (1 << ADEN_B) | (1 << ADIE_B) | (Config_Ptr -> prescalar & 0x07);
	}

}

void ADC_readChannel(uint8 channel_num,const ADC_ConfigType * Config_Ptr)
{
	ADMUX_R = (ADMUX_R & 0xE0) | (channel_num & 0x07) ;

	/* start conversion write '1' to ADSC */
	SetBit(ADCSRA_R,ADSC_B);

	if(Config_Ptr -> mode == 0)
	{
		/* wait for conversion to complete ADIF becomes '1' */
		while(BitIsClear(ADCSRA_R,ADIF_B));

		/* clear ADIF by write '1' to it */
		SetBit(ADCSRA_R,ADIF_B);

		/* return the data register */
		g_ADC_value = ADC_R;
	}
}