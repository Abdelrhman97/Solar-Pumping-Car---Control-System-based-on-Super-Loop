/*
 * ACD.c
 *
 * Created: 10/12/2020 7:06:47 PM
 *  Author: star
 */ 
#include "ADC.h"

#define  ADC_BUSY BitIsClear((ADCCON+ADCBASE),4)
#define  V_IN	 AccessReg16Bit((ADCLOW+ADCBASE))

static void (*S_CallBackFun)(uint16);

ISR(ADC_vect)
{
	S_CallBackFun(V_IN);
}


void adc_init(Vref_Select vref,Mode_Select mode,Clk_Select clk)
{
	AccessReg8Bit((ADCCON+ADCBASE))    = 0;
	AccessReg8Bit((ADCMUX+ADCBASE))    = 0;
	AccessReg8Bit((ADCMUX+ADCBASE))	|= (vref<<6);										// set vref
	AccessReg8Bit((ADCCON+ADCBASE))	|= (clk <<0);									// set clock + set type of trigger
	AccessReg8Bit((ADCSFIOR+ADCBASE)) |= (mode <<5);
	if (mode != FREE_RUNNING_MODE)
	{
		SetBit((ADCCON+ADCBASE),5);
	}
	SetBit((ADCCON+ADCBASE),7);														// enable adc
}

uint16 adc_read(Channel_Select channel)
{
	AccessReg8Bit((ADCMUX+ADCBASE)) &= ~0x1f;              // clear channels value
	AccessReg8Bit((ADCMUX+ADCBASE)) |= channel;				// set channel
	SetBit((ADCCON+ADCBASE),6);									// start conversion for one shoot
	while(ADC_BUSY);											    // stay here while adc is busy
	return  V_IN;
}

void adc_IntEnable(void (*F_callBack)(uint16 val),Channel_Select channel)
{
	S_CallBackFun = F_callBack;
	SetBit((ADCCON+ADCBASE),3);
	AccessReg8Bit((ADCMUX+ADCBASE)) |= (channel<<0);				// set channel
	SetBit((ADCCON+ADCBASE),6);									// start conversion for one shoot
}