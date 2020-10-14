#ifndef PWM_H_
#define PWM_H_

#include "Macros.h"



typedef enum
{
	TIMER0,
	TIMER2,
}timerType;

typedef enum
{
	NORMAL_OC0,
	REVERSED_OC0,
	CLEAR_OC0,
	SET_OC0,
}modeType;

typedef enum
{
	NO_CLOCK,
	F_CPU_CLOCK,
	F_CPU8,
	F_CPU64,
	F_CPU_256,
	F_CPU_1024,
	EXTERNAL_CLOCK_FALLING,
	EXTERNAL_CLOCK_RISING,
}ClockType;

typedef struct
{
	timerType Timer;
	modeType  mode;
	ClockType clock;
}configType;



void PWM_init(const configType * config_Ptr);
void PWM_Duty(const configType * config_Ptr,uint8 duty);

#endif
