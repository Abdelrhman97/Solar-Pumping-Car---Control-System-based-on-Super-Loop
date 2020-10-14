#include "GPIO.h"

/*******************************************************************************
 *                      Functions-Implementation                               *
 *******************************************************************************/
void SetPortDirection (pName PortName, Direction Dir)
{
	switch (Dir)
	{
		case OUTPUT:
			(*(volatile uint8 *)(PortName+1)) = 0xFF; 
			break; 
			
		case INPUT: 
			(*(volatile uint8 *)(PortName+1)) = 0x00; 
			break; 
	}
}
/********************************************************************************/
void SetPinDirection (pName PortName, uint8 PinNumber, Direction Dir)
{
	switch (Dir)
	{
		case OUTPUT:
			(*(volatile uint8 *)(PortName+1)) |= (1<<PinNumber); 
			break; 
			
		case INPUT: 
			(*(volatile uint8 *)(PortName+1)) &= ~(1<<PinNumber); 
			break; 
	}
}
/********************************************************************************/
void WriteOnPort (pName PortName, uint8 value)
{
	(*(volatile uint8 *)(PortName+2)) = value; 	
}

void WriteOnpin (pName PortName, uint8 PinNumber, Value val)
{
	switch (val)
	{
		case HIGH:
			(*(volatile uint8 *)(PortName+2)) |= (1<<PinNumber);
			break; 
		case LOW:
			(*(volatile uint8 *)(PortName+2)) &= ~(1<<PinNumber);
			break;
	}
}
/********************************************************************************/
uint8 ReadPort (pName PortName)
{
	uint8 value = (*(volatile uint8 *)(PortName)); 
	return value;
}
/********************************************************************************/
uint8 ReadPin (pName PortName, uint8 PinNumber)
{
	uint8 value ;
	value = (*(volatile uint8 *)(PortName)) & (1<<PinNumber);
	if (value==0) return LOW ;
	else return HIGH ;
	
}