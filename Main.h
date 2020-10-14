/*
 * Main.h
 *
 * Created: 10/13/2020 11:52:38 PM
 *  Author: star
 */ 


#ifndef MAIN_H_
#define MAIN_H_


#include "Config.h"
#include "Macros.h"
#include "GPIO.h"
#include "UART.h"
#include "PWM.h"


typedef struct
{
	uint8 dir;
	uint8 speed;
}Order;



void MotorDir (uint8 a, uint8 b, uint8 c, uint8 d);
void motion ();
void Get_Data();




#endif /* MAIN_H_ */