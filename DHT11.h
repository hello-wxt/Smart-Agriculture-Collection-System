#ifndef __DHT11_h__
#define __DHT11_h__


	    #include  <REG52.H>	
        #include <intrins.h>
		#include<12864.h>
		#include<STC_BH1750.h>
		#include<GPRS.h>  
 
	 	    extern	 void  Delay_10us(void);
			extern	     void  COM();
			extern		 	void RH();
			extern	  void DHT11_Display();
			extern		 void gprs_senDHT11();
			extern			   void DelayUs2x(unsigned char t);
					extern		  void DelayMs(unsigned char t);

#endif