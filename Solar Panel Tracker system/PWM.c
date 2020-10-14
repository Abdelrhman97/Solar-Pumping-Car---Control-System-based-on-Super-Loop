#include "PWM.h"




void PWM_init(const configType * config_Ptr)
{
	if((config_Ptr->Timer) == TIMER0)
	{
		SetBit(DDRB,PB3);
		TCNT0 = 0;
		OCR0  = 0;
		SetBit(TCCR0,WGM01);
		SetBit(TCCR0,WGM00);
		TCCR0 = (TCCR0 & 0xCF) | ((config_Ptr->mode)<<4);
		TCCR0 = (TCCR0 & 0xF8) | (config_Ptr->clock);
	}		
	else if((config_Ptr->Timer) == TIMER2)
	{
		SetBit(DDRD,PD7);
		TCNT2 = 0;
		OCR2  = 0;
		SetBit(TCCR2,WGM21);
		SetBit(TCCR2,WGM20);
		TCCR2 = (TCCR2 & 0xCF) | ((config_Ptr->mode)<<4);
		TCCR2 = (TCCR2 & 0xF8) | (config_Ptr->clock);
	}
}
void PWM_Duty(const configType * config_Ptr,uint8 duty)
{
	if((config_Ptr->Timer) ==TIMER0)
	{
		OCR0 = duty;
	}
	else if((config_Ptr->Timer) ==TIMER2)
	{
		OCR2 = duty;
	}
}