#ifndef __GPRS_H__
#define __GPRS_H__


	   #include  <REG52.H>	
	   #define FOSC_110592M
	   
	   #define uchar unsigned char
       #define uint unsigned int
//#define FOSC_12M

//以下是开机后发送到手机的内容，发送的号码在程序中修改。
//uchar sms_text[] = "abc123";
//uchar nihao=5+0x30;
 
	// extern   uchar sms_text[];
	extern   void SerialInti();
//extern	  void Serial_interrupt() interrupt 4 ;
extern	  void Uart1Send(uchar c);
extern	  void Uart1Sends(uchar *str);
extern	  void DelaySec(int sec);
extern void send_massage_byte(unsigned char str);
extern void send_massage(unsigned char *str);


#endif
