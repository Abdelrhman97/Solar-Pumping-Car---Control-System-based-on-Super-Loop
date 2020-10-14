/*
 * Remote-Controller.c
 *
 * Created: 10/13/2020 8:51:27 AM
 * Author : Abdelrhman Shaban (Scar)
 */ 

#include "main.h"


volatile CarStatus_t _Car_status_new = 0,_Car_status_old=Stop;

/* - Create configuration structure for ADC driver - */
ADC_ConfigType ADC_Config = {AVCC,_8,Polling};
	
/* - Create configuration structure for UART driver - */
UART_ConfigType UART_Config = {Disabled,_1_bit,_8_bit};	
	
/* - Create configuration structure for LCD driver - */
LCD_PinsCnfg_t mylcd = {C,{0,1,2,3,4,5,6,7},D,2,3};

int main(void)
{

	SystemInit(); 
	  
    while (1) 
    {
		InputDispatcher(); 
		
		switch (_Car_status_new)
		{
			case Stop:
			{
				DisplayInfo("Stop",0);
				UART_sendByte('S');
				_delay_ms(1);
				UART_sendByte(0);
				break;
			}
			case Forward:
			{
				
				DisplayInfo("Forward",MotorSpeed);
				UART_sendByte('F');
				_delay_ms(1); 
				UART_sendByte(MotorSpeed); 
			
				break;
			}
			case Backward:
			{
				
				DisplayInfo("Backward",MotorSpeed);
				UART_sendByte('B');
				_delay_ms(1);
				UART_sendByte(MotorSpeed);
				
				break;
			}
			case Right:
			{
				
				DisplayInfo("Right",MotorSpeed);
				UART_sendByte('R');
				_delay_ms(1);
				UART_sendByte(MotorSpeed);
				break;
			}
			case Left:
			{
			
				DisplayInfo("Left",MotorSpeed);
				UART_sendByte('L');
				_delay_ms(1);
				UART_sendByte(MotorSpeed);
				break;
			}
										
		}
	

    }
}


void SystemInit()
{

		/* - GPIO initialization - */
		SetPinDirection(B,0,INPUT);
		SetPinDirection(B,1,INPUT);
		SetPinDirection(B,2,INPUT);
		SetPinDirection(B,3,INPUT);
		
		/* - ADC initialization - */
		ADC_init(&ADC_Config);
		
		/* - UART initialization - */
		UART_init(&UART_Config);
	
		/* - LCD initialization - */
		lcd_init(&mylcd);
}
void ButtonDispatcher()
{
	
	if (ReadPin(B,0)) //forward
	{
		_Car_status_new = Forward;
	}
	else if (ReadPin(B,1))//backward
	{
		_Car_status_new = Backward;
	}
	else if (ReadPin(B,2))//Right
	{
		_Car_status_new = Left;
	}
	else if (ReadPin(B,3))//Left
	{
		_Car_status_new = Right;
	}
	else
	{
		_Car_status_new = Stop;
	}
	
	if (_Car_status_new != _Car_status_old)
	{

		_Car_status_old = _Car_status_new ;
	}
}



void AdcDispatcher()
{
	ADC_readChannel(0,&ADC_Config);
	MotorSpeed = (uint8)(g_ADC_value/4);
}
void InputDispatcher()
{
	ButtonDispatcher();
	AdcDispatcher(); 
}
void DisplayInfo(String Direction,uint8 Speed)
{
	
	GotoXY(&mylcd,0,0);
	WriteString(&mylcd,"Direction: "); 
	GotoXY(&mylcd,1,5);
	WriteString(&mylcd,Direction); 
	GotoXY(&mylcd,2,0);
	WriteString(&mylcd,"Speed: ");
	GotoXY(&mylcd,3,5);
	Display_intgerToString(&mylcd,Speed); 
	
}
