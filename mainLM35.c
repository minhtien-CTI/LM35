#include <REGX52.H>
#include "functionLM35.h"
sbit start=P3^0;
sbit stop=P3^2;
sbit ALARM=P3^3;
sbit set_lim=P3^4;
sbit increase=P3^5;
sbit decrease=P3^6;
sbit enter=P3^7;
bit ready=0;
unsigned char T_lim=1;
void SET_Tlim();
/*-------------------------
chuong trình ngat dung do
---------------------------*/
void INT_EX0()interrupt 0
	{
		LCD_clear();
		LCD_pstr(" --DUNG DO--");
		delay_ms(500);
		LCD_clear();
		ready=0;
		ALARM=0;
	}
	
/*----------------------------*--
	CHUONG TRINH CHINH
-------------------------------*/
void main()
{

	unsigned char Tdo;
	ALARM=0;
	LCD_init();// khoi tao LCD
	EX0_init();
	TIMER_init(); //khoi tao timer cap xung cho ADC0808

	while(1)
	{
		LCD_pstr("  LM35 PROJECT");
		LCD_gotoxy(0,1);
		LCD_display_Tlim(T_lim);
		if(set_lim==0)
			{
				while(!set_lim);
				SET_Tlim();
			}
		if(start==0)
			{
				while(!start);
				LCD_clear();
				ready=1;
			}
		while(ready==1)
		{
			Tdo=ADC_read(); //doc nhiet do tu LM35 qua ADC0808
			LCD_sendCMD(0x02);
			LCD_temp(Tdo,T_lim);;//hien thi nhiet do len LCD
			if(Tdo>=T_lim) ALARM=1; // kiem tra gioi han nhiet do
			else ALARM=0;;
		 }
	}
}

/*--------------------------------*--
cai dat nhiet do canh bao
--*---------------------------------*/
void SET_Tlim()
	{
		LCD_clear();
		while(1)
			{
				if(enter==0)
					{
						while(!enter); 
						break;
					}		
				if(increase==0)
					{
						while(!increase);
						T_lim=T_lim+1;
						if(T_lim>145) T_lim=0;
					}
				if(decrease==0)
					{
						while(!decrease);
						T_lim=T_lim-1;
						if (T_lim==255) T_lim=145;
					}
				LCD_gotoxy(0,0);
				LCD_display_Tlim(T_lim);
			}
		LCD_clear();
	}