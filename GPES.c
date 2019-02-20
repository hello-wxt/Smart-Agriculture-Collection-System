#include<GPRS.h>

void SerialInti()
{
//	TMOD=0x20;//定时器1操作模式2:8位自动重载定时器
    TMOD=0x21;
#ifdef FOSC_12M		   //在这里根据晶振大小设置不同的数值初始化串口
	TH1=0xf3;//装入初值，波特率2400
	TL1=0xf3;	
#else 	
	TH1=0xfd;//装入初值，波特率9600
	TL1=0xfd;
#endif //end of SOC_12M
	
	TR1=1;//打开定时器
	SM0=0;//设置串行通讯工作模式，（10为一部发送，波特率可变，由定时器1的溢出率控制）
	SM1=1;//(同上)在此模式下，定时器溢出一次就发送一个位的数据
	REN=1;//串行接收允许位（要先设置sm0sm1再开串行允许）
	EA=1;//开总中断
	ES=1;//开串行口中断

	ET0=1;
	TR0=1;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
		
}

/*串行通讯中断，收发完成将进入该中断*/
void Serial_interrupt() interrupt 4 
{
//	a=SBUF;
	P2=SBUF;
	RI=0;//接收中断信号清零，表示将继续接收
//	flag=1;//进入中断的标志符号
}


void Uart1Send(uchar c)
{
	SBUF=c;
	while(!TI);//等待发送完成信号（TI=1）出现
	TI=0;	
}

//串行口连续发送char型数组，遇到终止号/0将停止
void Uart1Sends(uchar *str)
{
	while(*str!='\0')
	{
		SBUF=*str;
		while(!TI);//等待发送完成信号（TI=1）出现
		TI=0;
		str++;
	}
}

//延时函数大概是1s钟，不过延时大的话不准...
void DelaySec(int sec)
{
	uint i , j= 0;

	for(i=0; i<sec; i++)
	{
		for(j=0; j<65535; j++)
		{	
		}
	}
}

//void send_massage_byte(unsigned char str)
//{
////void main()
////{
////	uchar i = 0;
////	SerialInti();
////	while(1)
//
//		Uart1Sends("AT+CSCS=\"GSM\"\r\n");
//		DelaySec(3);//延时3秒
//		Uart1Sends("AT+CMGF=1\r\n");
//		DelaySec(3);//延时3秒
//		Uart1Sends("AT+CMGS=\"18051361936\"\r\n");//此处修改为对方的电话号	//18051361936
//		DelaySec(5);//延时3秒
//	//	Uart1Sends(str);//修改短信内容
//		Uart1Send(str);
//		Uart1Send(0x1a);
//		DelaySec(10);//延时20秒
//		Uart1Sends("AT+CMGD=1\r\n");//删除SIM卡中的内容
//		DelaySec(3);//延时3秒
//	
//
//}
//void send_massage(unsigned char *str)
//{
////void main()
////{
////	uchar i = 0;
////	SerialInti();
////	while(1)
//
//		Uart1Sends("AT+CSCS=\"GSM\"\r\n");
//		DelaySec(3);//延时3秒
//		Uart1Sends("AT+CMGF=1\r\n");
//		DelaySec(3);//延时3秒
//		Uart1Sends("AT+CMGS=\"15605229508\"\r\n");//此处修改为对方的电话号
//		DelaySec(5);//延时3秒
//		Uart1Sends(str);//修改短信内容
//	//	Uart1Send(str);
//		Uart1Send(0x1a);
//		DelaySec(10);//延时20秒
//		Uart1Sends("A+CMGD=1\r\nT");//删除SIM卡中的内容
//		DelaySec(3);//延时3秒
//	
//
//}
