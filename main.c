#include  <REG52.H>	
#include  <math.h>      
#include  <stdio.h>   	
#include  <INTRINS.H>
#include<12864.h>
#include<STC_BH1750.h>
#include<GPRS.h>
#include<DHT11.h>
#include<send_all.h>
#include<key.h>
#include<start.h>
#include<tu.h>
 //extern unsigned char flag,flag1=0;
unsigned int tt;
// extern unsigned int temperature,temp; 
void main()
{  

   Init_BH1750();       //��ʼ��BH1750
   lcd_init();
   SerialInti(); // gprs��ʼ��
   // Uart1Sends("AT+CMGD=1\r\n");//ɾ��SIM���е�����
  //	DelaySec(3);//��ʱ3��
  while(1)             
  { 

//	if(flag1==1)
//	{
//	flag1=0;
//	send_all();
//	}

     key();
  	 key_display();
 
  

//	all_Display();
  }

}
void tinmer0 () interrupt 1
{

    TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	  
	tt++;
	if(tt==500)
	{
	  tt=0;	 
	  send_all();  

	}
  
} 













