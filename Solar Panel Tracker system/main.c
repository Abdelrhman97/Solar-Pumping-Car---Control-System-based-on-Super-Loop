/*
 * Solar Panel Tracker-ECU.c
 *
 * Created: 10/12/2020 6:40:47 PM
 * Author : star
 */ 

#include "main.h"

TrackerStatus_t TrackerDir; 
AvgsReading Avgs; 
uint16 T_R; 
uint16 T_L;
uint16 B_R;
uint16 B_L;

ADC_ConfigType ADC_Config = {AVCC,_8,Polling}; 
	
LCD_PinsCnfg_t mylcd = {C,{0,1,2,3,4,5,6,7},D,0,1};
 configType UpDownMotor = {TIMER0,CLEAR_OC0,F_CPU8};
 configType LeftRightMotor = {TIMER2,CLEAR_OC0,F_CPU8};
int main(void)
{
	ADC_init(&ADC_Config);
	PWM_init(&UpDownMotor);
	PWM_init(&LeftRightMotor);
	lcd_init(&mylcd); 
	SetPinDirection(B,4,OUTPUT);
	SetPinDirection(B,5,OUTPUT);
	SetPinDirection(B,6,OUTPUT);
	SetPinDirection(B,7,OUTPUT);
	GotoXY(&mylcd,0,0); 
	WriteString(&mylcd,"Tracker System  ");
	GotoXY(&mylcd,1,0);
	WriteString(&mylcd,"Here We display :");
	GotoXY(&mylcd,2,0);
	WriteString(&mylcd,"LDR values");
	GotoXY(&mylcd,3,0);
	WriteString(&mylcd,"Position"); 
	while (1)
	{

		Get_data();
		Get_Avgs();
		SelectDir();

		switch (TrackerDir)
		{
			case UpRotate: 
			{
				UpDownMove(1,0);	
				break;
			}
			case DownRotate:
			{
				UpDownMove(0,1);
				break;
			}
			case ClockWise:
			{
				RightLeftMove(1,0);
				break;
			}
			case AntiClockWise:
			{
				RightLeftMove(0,1);
				break;
			}
		}
				
	}
}

void Get_data()
{
	ADC_readChannel(0,&ADC_Config);
	T_R = g_ADC_value;
	ADC_readChannel(1,&ADC_Config);
	T_L = g_ADC_value;
	ADC_readChannel(2,&ADC_Config);
	B_R = g_ADC_value;
	ADC_readChannel(3,&ADC_Config);
	B_L = g_ADC_value; 
}
void Get_Avgs()
{
	Avgs.AvgTop = ((T_R + T_L) / 2);
	Avgs.AvgBot = ((B_R + B_L) / 2);
	Avgs.AvgRight = ((T_R + B_R) / 2);
	Avgs.AvgLeft = ((T_L + B_L) / 2);
}
void SelectDir()
{
	if (Avgs.AvgTop > Avgs.AvgBot)
	{
		TrackerDir = UpRotate;
	}
	if (Avgs.AvgTop < Avgs.AvgBot)
	{
		TrackerDir = DownRotate;
	}
	if (Avgs.AvgRight > Avgs.AvgLeft)
	{
		TrackerDir = AntiClockWise; 
	}
	if (Avgs.AvgRight < Avgs.AvgLeft)
	{
		TrackerDir = ClockWise;
	}

}
void UpDownMove(uint8 a, uint8 b)
{
	WriteOnpin(B,4,a);
	WriteOnpin(B,5,b);
	PWM_Duty(&UpDownMotor,255);
}
void RightLeftMove(uint8 a, uint8 b)
{
	WriteOnpin(B,6,a);
	WriteOnpin(B,7,b);
	PWM_Duty(&LeftRightMotor,255);
}