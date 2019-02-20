#ifndef __STC_BH1750_H__
#define __STC_BH1750_H__


#include  <INTRINS.H>
#include  <REG52.H>	
#include<12864.h>
#include<GPRS.h>    	
 
 
 extern   Multiple_Read_BH1750();       //连续读出数据，存储在BUF中  


  extern void Init_BH1750(void);
  extern void delay_nms(unsigned int k);
  extern  void  Single_Write_BH1750(uchar REG_Address);               //单个写入数据
  extern  uchar Single_Read_BH1750(uchar REG_Address);  
 extern	 void display_BH1750();
  extern void gprs_senBH1750();

#endif