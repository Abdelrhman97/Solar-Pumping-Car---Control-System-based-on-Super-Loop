/*
 * main.h
 *
 * Created: 10/13/2020 11:05:43 AM
 *  Author: Abdelrhman Shaban 
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include "Config.h"
#include "Macros.h"
#include "GPIO.h"
#include "ADC.h"
#include "LCD.h"
#include "UART.h"
#include <util/delay.h>



typedef enum 
{
	Forward = 0,
	Backward = 1,
	Right = 2, 
	Left = 3, 
	Stop = 4,
}CarStatus_t;

volatile uint8 MotorSpeed;

void AdcDispatcher();
void ButtonDispatcher();
void InputDispatcher();
void SystemInit();
void DisplayInfo(String Direction,uint8 Speed);
#endif /* MAIN_H_ */