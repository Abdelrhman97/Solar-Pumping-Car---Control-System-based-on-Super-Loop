/*
 * LCD.c
 *
 * Created: 10/11/2020 7:59:21 AM
 *  Author: Abdelrhman Shaban
 */ 

#include "LCD.h"

void lcd_init(const LCD_PinsCnfg_t * ptr)
{   
	uint8 i; 
	for (i = 0; i < DATA_PINS; i++)
	{
		SetPinDirection(ptr->DataPort,ptr->DataPins[i],OUTPUT);
	}
	SetPinDirection(ptr->CommandPort,ptr->EnablePin,OUTPUT);
	SetPinDirection(ptr->CommandPort,ptr->RegSelect,OUTPUT);               
    
	#ifdef _4BIT_MODE
		lcd_command2(0x33);
		lcd_command2(0x32);
		lcd_command2(ptr,BIT_4);	
	#endif
	
	#ifdef _8BIT_MODE
		_delay_us(2000);
		lcd_command2(ptr,BIT_8); 
	#endif
	
	lcd_command2(ptr,CURSOR_OFF);                         
	lcd_command2(ptr,CLEAR_SCREEN);                         
	_delay_us(2000);
	lcd_command2(ptr,ENTRY_MODE);                        
}



void lcd_command2(const LCD_PinsCnfg_t * ptr, uint8 cmd)
{  
	WriteOnpin(ptr->CommandPort,ptr->RegSelect,LOW);
	
	#ifdef _8BIT_MODE 
		WriteOnPort(ptr->DataPort,cmd);
		WriteOnpin(ptr->CommandPort,ptr->EnablePin,HIGH);
		_delay_ms(1);
		WriteOnpin(ptr->CommandPort,ptr->EnablePin,LOW);
		_delay_us(100);		
	#endif
	
	#ifdef _4BTT_MODE
		WriteOnPort(ptr->DataPort,cmd&0xf0);  //SEND the command high nibble to D4:D7
		WriteOnpin(ptr->CommandPort,ptr->EnablePin,HIGH);
		_delay_ms(1);
		WriteOnpin(ptr->CommandPort,ptr->EnablePin,LOW);
		_delay_us(100);
		WriteOnPort(ptr->DataPort,(cmd<<4)); //send the Low nibble to D4:D7
	#endif	
}





void WriteChar(const LCD_PinsCnfg_t * ptr, uint8 ch)
{
		WriteOnpin(ptr->CommandPort,ptr->RegSelect,HIGH);
		
		#ifdef _8BIT_MODE
		WriteOnPort(ptr->DataPort,ch);
		WriteOnpin(ptr->CommandPort,ptr->EnablePin,HIGH);
		_delay_ms(1);
		WriteOnpin(ptr->CommandPort,ptr->EnablePin,LOW);
		_delay_us(100);
		#endif
		
		#ifdef _4BTT_MODE
		WriteOnPort(ptr->DataPort,ch&0xf0);  //SEND the command high nibble to D4:D7
		WriteOnpin(ptr->CommandPort,ptr->EnablePin,HIGH);
		_delay_ms(1);
		WriteOnpin(ptr->CommandPort,ptr->EnablePin,LOW);
		_delay_us(100);
		WriteOnPort(ptr->DataPort,(ch<<4)); //send the Low nibble to D4:D7
		#endif
}


void WriteString (const LCD_PinsCnfg_t * ptr, String str)
{
	uint8 i = 0;
	while(str[i]!='\0'){WriteChar(ptr,str[i]) ; i++;}

}

void GotoXY(const LCD_PinsCnfg_t * ptr, uint8 row, uint8 col)
{
	if (row == 0)
	{
		lcd_command2(ptr,(unsigned) 0x80 | col);
	}
	else if (row == 1)
	{
		lcd_command2(ptr,(unsigned) 0xc0 | col);
	}
	#ifdef _LCD_16_4_
	else if (row==2)
	{
		lcd_command2(ptr,(unsigned) 0x90  | col);
	}
	else if (row==3)
	{
		lcd_command2(ptr,(unsigned) 0xD0 | col);
	}
	#endif // _LCD_16_4_
}

void Display_intgerToString(const LCD_PinsCnfg_t * ptr,uint16 data)
{
	uint16 buff[16]; /* String to hold the ascii result */
	itoa(data,buff,10); /* 10 for decimal */
	WriteString(ptr,buff);
}
void lcd_clear(const LCD_PinsCnfg_t* ptr)
{
	lcd_command2(ptr,CLEAR_SCREEN); // do the same as a command
}



