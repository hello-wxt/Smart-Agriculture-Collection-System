#ifndef __tu_h__
#define __tu_h__


	    #include  <REG52.H>	
        #include <intrins.h>
		#include<12864.h>
		#include<DHT11.h>
 		 #include<GPRS.h>  
		/*------------------------------------------------
                    端口定义
------------------------------------------------*/
sbit DQ=P1^3;//ds18b20 端口

/*------------------------------------------------
                  函数声明
------------------------------------------------*/
extern unsigned int ReadTemperature(void);
extern bit Init_DS18B20(void);
extern unsigned char ReadOneChar(void);
extern void WriteOneChar(unsigned char dat);
extern void tu_display();
extern	void gprs_tu();

#endif