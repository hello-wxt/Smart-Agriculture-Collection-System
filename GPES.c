#include<GPRS.h>

void SerialInti()
{
//	TMOD=0x20;//��ʱ��1����ģʽ2:8λ�Զ����ض�ʱ��
    TMOD=0x21;
#ifdef FOSC_12M		   //��������ݾ����С���ò�ͬ����ֵ��ʼ������
	TH1=0xf3;//װ���ֵ��������2400
	TL1=0xf3;	
#else 	
	TH1=0xfd;//װ���ֵ��������9600
	TL1=0xfd;
#endif //end of SOC_12M
	
	TR1=1;//�򿪶�ʱ��
	SM0=0;//���ô���ͨѶ����ģʽ����10Ϊһ�����ͣ������ʿɱ䣬�ɶ�ʱ��1������ʿ��ƣ�
	SM1=1;//(ͬ��)�ڴ�ģʽ�£���ʱ�����һ�ξͷ���һ��λ������
	REN=1;//���н�������λ��Ҫ������sm0sm1�ٿ���������
	EA=1;//�����ж�
	ES=1;//�����п��ж�

	ET0=1;
	TR0=1;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
		
}

/*����ͨѶ�жϣ��շ���ɽ�������ж�*/
void Serial_interrupt() interrupt 4 
{
//	a=SBUF;
	P2=SBUF;
	RI=0;//�����ж��ź����㣬��ʾ����������
//	flag=1;//�����жϵı�־����
}


void Uart1Send(uchar c)
{
	SBUF=c;
	while(!TI);//�ȴ���������źţ�TI=1������
	TI=0;	
}

//���п���������char�����飬������ֹ��/0��ֹͣ
void Uart1Sends(uchar *str)
{
	while(*str!='\0')
	{
		SBUF=*str;
		while(!TI);//�ȴ���������źţ�TI=1������
		TI=0;
		str++;
	}
}

//��ʱ���������1s�ӣ�������ʱ��Ļ���׼...
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
//		DelaySec(3);//��ʱ3��
//		Uart1Sends("AT+CMGF=1\r\n");
//		DelaySec(3);//��ʱ3��
//		Uart1Sends("AT+CMGS=\"18051361936\"\r\n");//�˴��޸�Ϊ�Է��ĵ绰��	//18051361936
//		DelaySec(5);//��ʱ3��
//	//	Uart1Sends(str);//�޸Ķ�������
//		Uart1Send(str);
//		Uart1Send(0x1a);
//		DelaySec(10);//��ʱ20��
//		Uart1Sends("AT+CMGD=1\r\n");//ɾ��SIM���е�����
//		DelaySec(3);//��ʱ3��
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
//		DelaySec(3);//��ʱ3��
//		Uart1Sends("AT+CMGF=1\r\n");
//		DelaySec(3);//��ʱ3��
//		Uart1Sends("AT+CMGS=\"15605229508\"\r\n");//�˴��޸�Ϊ�Է��ĵ绰��
//		DelaySec(5);//��ʱ3��
//		Uart1Sends(str);//�޸Ķ�������
//	//	Uart1Send(str);
//		Uart1Send(0x1a);
//		DelaySec(10);//��ʱ20��
//		Uart1Sends("A+CMGD=1\r\nT");//ɾ��SIM���е�����
//		DelaySec(3);//��ʱ3��
//	
//
//}
