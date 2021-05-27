#include <REGX52.H>
#include "functionLM35.h"
#define ADC_OUT P0
sbit LCD_RS	= P3^1;
sbit LCD_EN	= P3^3;
sbit LCD_D4	= P1^0;
sbit LCD_D5 = P1^1;
sbit LCD_D6 = P1^2;
sbit LCD_D7 = P1^3;
sbit ADC_A	= P2^0;
sbit ADC_B	= P2^1;
sbit ADC_C  = P2^2;
sbit ADC_ALE= P2^3;
sbit ADC_START=P2^4;
sbit ADC_EOC= P2^5;
sbit ADC_OE = P2^6;
sbit ADC_CLK= P2^7;

void delay_us(unsigned int us){
	unsigned int i;
	for(i=0;i<us;i++);
}
void delay_ms(unsigned int ms){
	unsigned int i, j;
	for(i=0;i<ms;i++)
		for(j=0;j<123;j++);
}
/*-------------------------------------*-
	Lcd_ENABLE function
-*-------------------------------------*/
void LCD_enable()
{
	LCD_EN = 1u;
	delay_us(3u);
	LCD_EN=0;
	delay_us(30u);
}
/*-------------------------------------*-
	Lcd_Write_High_Nibble - Local Function
-*-------------------------------------*/
void LCD_send4bit_high(unsigned char b)
{
	LCD_D7 = b & 0x80;
	LCD_D6 = b & 0x40;
	LCD_D5 = b & 0x20;
	LCD_D4 = b & 0x10; 	
}

/*-------------------------------------*-
	Lcd_Write_Low - Local Function
-*-------------------------------------*/
void LCD_send4bit_low(unsigned char b)
{
 	LCD_D7 = b & 0x08;
	LCD_D6 = b & 0x04;
	LCD_D5 = b & 0x02;
	LCD_D4 = b & 0x01;
}

void LCD_sendCMD(unsigned char cmd){
	LCD_send4bit_high(cmd);
	LCD_enable();
	LCD_send4bit_low(cmd);
	LCD_enable();
}
void LCD_clear(){
	LCD_RS=0;
	LCD_sendCMD(0x01);
	delay_us(10u);
}
void LCD_init(){
	LCD_send4bit_low(0x00);
	delay_ms(20u);
	LCD_RS=0;
	LCD_send4bit_low(0x03);
	LCD_enable();
	delay_ms(5u);
	LCD_enable();
	delay_us(100u);
	LCD_send4bit_low(0x02);
	LCD_enable();
	LCD_sendCMD(0x28); //giao tiep 4bit, 2 hang, ky tu 5x8
	LCD_sendCMD(0x0c); // cho phep hien thi man hinh
	LCD_sendCMD(0x06); 
	LCD_sendCMD(0x01);
}

void LCD_gotoxy(unsigned int x, unsigned int y){
	unsigned char add;
	if(!y) add=(0x80+x);
	else add=(0xc0+x);
	LCD_sendCMD(add);
	delay_us(10);
}

void LCD_pchar(unsigned char c){
	LCD_RS=1;
	LCD_sendCMD(c);
	LCD_RS=0;
}
void LCD_pstr(char* str){
	while (*str){
	LCD_pchar(*str);
	str++;
	}
}

void LCD_display_Tlim(unsigned char T)
	{
		/*LCD_pstr(" ---CAI DAT---");
		LCD_gotoxy(0,1);
		delay_us(5);*/
		LCD_pstr(" SET ALARM:");
		LCD_pchar((T/100)+48);
		LCD_pchar(((T%100)/10)+48);
		LCD_pchar((T%10)+48);
		LCD_pstr("*C");
		delay_ms(100);
	}
void LCD_temp(unsigned char temp, unsigned char lim)
	{
		LCD_pstr(" NHIET DO: ");
		LCD_pchar((temp/100)+48);
		LCD_pchar(((temp%100)/10)+48);
		LCD_pchar((temp%10)+48);
		LCD_pstr("*C");
		LCD_gotoxy(0,1);
		LCD_pstr(" alarm: ");
		LCD_pchar((lim/100)+48);
		LCD_pchar(((lim%100)/10)+48);
		LCD_pchar((lim%10)+48);
		LCD_pstr("*C");
		delay_ms(100);
	}
	/*----------------------------------------*-
ADC 0808 FUNCTION
-*----------------------------------------*/

unsigned char ADC_read()
{
	unsigned char kq; 
	ADC_A=0;
	ADC_B=0;
	ADC_C=0;
	ADC_ALE=1;
	ADC_START=1;
	ADC_ALE=0;
	ADC_START=0;
	while(ADC_EOC);
	while(!ADC_EOC);
	ADC_OE=1;
	kq=ADC_OUT;
	ADC_OE=0;
	return kq;
}

void TIMER_init()
	{		
		TMOD = 0x02;
		TH0=236;
		TL0=236;
		TR0=1;
		ET0=1;
		EA=1;
	}
void EX0_init()
	{
		EX0=1;
		IT0=1;
		EA=1;
	}
	void INT_Timer0()interrupt 1
	{
		ADC_CLK=~ADC_CLK;
	}
