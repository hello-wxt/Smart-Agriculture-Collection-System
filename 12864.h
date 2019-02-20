#ifndef __12864_H__
#define __12864_H__


#include  <REG52.H>		
#include<intrins.h>
#include<stdlib.h>

 
#define uchar unsigned char
#define uint unsigned int

sbit RS=P2^0;
sbit RW=P2^1;
sbit EN=P2^2;

sbit wela=P2^3;
sbit dula=P2^4;
sbit PSB=P2^5;

extern 	void ClrScreen();
extern void delay(uint z);
extern void write_cmd(uchar cmd);
extern void write_date(uchar date);
extern void write_word(unsigned char *s);
extern void lcd_init();

#endif