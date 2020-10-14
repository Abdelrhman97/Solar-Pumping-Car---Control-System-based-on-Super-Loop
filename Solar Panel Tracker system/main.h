/*
 * main.h
 *
 * Created: 10/14/2020 12:48:33 PM
 *  Author: star
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include "GPIO.h"
#include "LCD.h"
#include "ADC.h"
#include "PWM.h"

typedef enum 
{
	ClockWise, 
	AntiClockWise,
	UpRotate, 
	DownRotate, 
}TrackerStatus_t;
typedef struct
{
	uint16 AvgTop; 
	uint16 AvgBot; 
	uint16 AvgRight; 
	uint16 AvgLeft;
}AvgsReading;

void Get_data();
void Get_Avgs(); 
void SelectDir(); 
void UpDownMove(uint8 a, uint8 b);
void RightLeftMove(uint8 a, uint8 b);





#endif /* MAIN_H_ */