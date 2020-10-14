/*
 * LCD.h
 *
 * Created: 10/11/2020 7:58:26 AM
 *  Author: star
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "Config.h"
#include "LCD_Config.h"

#ifdef _4BIT_MODE
	#define DATA_PINS 4
#else
	#define DATA_PINS 8
#endif // _DEBUG

typedef struct
{
	uint8 DataPort; 
	uint8 DataPins [DATA_PINS];
	uint8 CommandPort;
	uint8 EnablePin;
	uint8 RegSelect; 
}LCD_PinsCnfg_t;

#define ENTRY_MODE   0x06
#define CLEAR_SCREEN 0x01
#define BIT_4        0x28
#define BIT_8        0x38
#define CURSOR_BLINK 0x0f
#define CURSOR_ON    0x0e
#define CURSOR_OFF   0x0c
#define DISPLAY_OFF  0x08

void lcd_init(const LCD_PinsCnfg_t * ptr);
void lcd_command2(const LCD_PinsCnfg_t * ptr, uint8 cmd);
void WriteChar(const LCD_PinsCnfg_t * ptr, uint8 ch);
void WriteString (const LCD_PinsCnfg_t * ptr,String str);
void GotoXY(const LCD_PinsCnfg_t * ptr, uint8 row, uint8 col);
void Display_intgerToString(const LCD_PinsCnfg_t * ptr,uint8 data);


#endif /* LCD_H_ */