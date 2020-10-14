/*
 * Master-ECU.c
 *
 * Created: 10/11/2020 7:48:41 AM
 * Author : Abdelrhman Shaban 
 */ 


#include "Main.h"
#include "LCD.h"
Order data;


UART_ConfigType UART_Config = {Disabled,_1_bit,_8_bit};
configType Left_Motors = {TIMER0,CLEAR_OC0,F_CPU8};
configType Right_Motors = {TIMER2,CLEAR_OC0,F_CPU8};
int main(void)
{
	UART_init(&UART_Config);
	PWM_init(&Left_Motors);
	PWM_init(&Right_Motors);
	SetPinDirection(A,0,OUTPUT);
	SetPinDirection(A,1,OUTPUT);
	SetPinDirection(A,2,OUTPUT);
	SetPinDirection(A,3,OUTPUT);
	
    while (1) 
    {
		motion();
    }
}

void Get_Data()
{
	uint8 flage; 
	flage = UART_recieveByte();
	if (flage == 'F' || flage == 'B' ||flage == 'R' ||flage == 'L')
	{
		data.dir = flage;
	}
	else
	{
		data.speed = flage; 
	}
}

void MotorDir(uint8 a, uint8 b, uint8 c, uint8 d)
{
	WriteOnpin(A,0,a);
	WriteOnpin(A,1,b);
	WriteOnpin(A,2,c);
	WriteOnpin(A,3,d);
	PWM_Duty(&Left_Motors,data.speed);
	PWM_Duty(&Right_Motors,data.speed);
}
void motion ()
{
	Get_Data();
	switch (data.dir)
	{
		case 'F':
		{
			MotorDir(1,0,1,0);
			break;
		}
		
		case 'B':
		{
			MotorDir(0,1,0,1);
			break;
		}
		case 'R':
		{
			MotorDir(1,0,0,1);
			break;
		}
		case 'L':
		{
			MotorDir(0,1,1,0);
			break;
		}
		default:
		{
			
			MotorDir (0,0,0,0);
		}
	}
}


