#ifndef __functionLM35_H__
#define __functionLM35_H__

void delay_us(unsigned int us);
void delay_ms(unsigned int ms);

// LCD function
void LCD_enable();
/*-------------------------------------*-
	Lcd_Write_High_Nibble - Local Function
-*-------------------------------------*/
void LCD_send4bit_high(unsigned char b);
/*-------------------------------------*-
	Lcd_Write_Low_Nibble - Local Function
-*-------------------------------------*/
void LCD_send4bit_low(unsigned char b);
void LCD_sendCMD(unsigned char cmd);
void LCD_clear();
void LCD_init();
void LCD_gotoxy(unsigned int x, unsigned int y);
void LCD_pchar(unsigned char c);
void LCD_pstr(char* str);
void LCD_temp(unsigned char temp,unsigned char lim);
void LCD_display_Tlim(unsigned char T);

/*----------------------------------------*-
ADC 0808 FUNCTION
-*----------------------------------------*/
unsigned char ADC_read();
/*---------------------------------------
Timer0, External Interrupt
----------------------------------------*/
void TIMER_init();
void EX0_init();

#endif