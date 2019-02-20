#include<DHT11.h>

sbit  P2_0  = P1^2 ;



typedef unsigned char  U8;       /* defined for unsigned 8-bits integer variable 	  �޷���8λ���ͱ���  */
// typedef unsigned int   U16;      /* defined for unsigned 16-bits integer variable 	  �޷���16λ���ͱ��� */
 U8  U8FLAG;
U8  U8count,U8temp;
U8  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
U8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
U8  U8comdata; 
unsigned char shidu_shi,shidu_ge,wendu_shi,wendu_ge;

void Delay18ms()		//@11.0592MHz
{
	unsigned char i, j, k;
	_nop_();
	_nop_();
	i = 1;
	j = 194;
	k = 159;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} 
	while (--i);
}

 void  Delay_10us(void)
      {
        U8 i;
        i--;
        i--;
        i--;
        i--;
        i--;
        i--;
       }
void DelayUs2x(unsigned char t)
{   
 while(--t);
}


void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //������ʱ1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}
	
  void  COM()
      {
     
	        U8 i;
          
       for(i=0;i<8;i++)	   
	    {
		
	   	    U8FLAG=2;	
	   	while((!P2_0)&&U8FLAG++);

Delay_10us();
Delay_10us();
Delay_10us();
	  		U8temp=0;
	     if(P2_0)U8temp=1;
		    U8FLAG=2;
		 while((P2_0)&&U8FLAG++);
	   	//��ʱ������forѭ��		  
	   	 if(U8FLAG==1)break;
	   	//�ж�����λ��0����1	 
	   	   
		// ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1 
	   	 
		   U8comdata<<=1;
	   	   U8comdata|=U8temp;    
	     }
	   
	}

	//--------------------------------
	//-----ʪ�ȶ�ȡ�ӳ��� ------------
	//--------------------------------
	//----���±�����Ϊȫ�ֱ���--------
	//----�¶ȸ�8λ== U8T_data_H------
	//----�¶ȵ�8λ== U8T_data_L------
	//----ʪ�ȸ�8λ== U8RH_data_H-----
	//----ʪ�ȵ�8λ== U8RH_data_L-----
	//----У�� 8λ == U8checkdata-----
	//----��������ӳ�������----------
	//---- Delay();, Delay_10us();,COM(); 
	//--------------------------------

	void RH()
	{
	  //��������18ms 
       P2_0=0;    
	  DelayMs(18);		        //��ʱ180ms
	   P2_0=1;

       Delay_10us();
	   Delay_10us();
	   Delay_10us();
	   Delay_10us();

	 //������Ϊ���� �жϴӻ���Ӧ�ź� 
	   P2_0=1;
	 //�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������	  
	   if(!P2_0)		 //T !	  
	   {
	   U8FLAG=2;
	 //�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����	 
	   while((!P2_0)&&U8FLAG++);
	   U8FLAG=2;
	 //�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
	   while((P2_0)&&U8FLAG++);
	 //���ݽ���״̬		 
	   COM();
	   U8RH_data_H_temp=U8comdata;
	   COM();
	   U8RH_data_L_temp=U8comdata;
	   COM();
	   U8T_data_H_temp=U8comdata;
	   COM();
	   U8T_data_L_temp=U8comdata;
	   COM();
	   U8checkdata_temp=U8comdata;
	   P2_0=1;
	 //����У�� 
	 
	   U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
	   if(U8temp==U8checkdata_temp)
	   {
	   	  U8RH_data_H=U8RH_data_H_temp;
	   	  U8RH_data_L=U8RH_data_L_temp;
		  U8T_data_H=U8T_data_H_temp;
	   	  U8T_data_L=U8T_data_L_temp;
	   	  U8checkdata=U8checkdata_temp;
	   }
	   }

	}
  void DHT11_Display()
{

	RH();
	shidu_shi=0x30+U8RH_data_H/10; 
	shidu_ge=0x30+U8RH_data_H%10; 
	wendu_shi=0x30+U8T_data_H/10; 
	wendu_ge=0x30+U8T_data_H%10; 

	write_cmd(0x90);
	write_word("����ʪ��");
	write_cmd(0x90+5);
	write_date(shidu_shi);
//	write_cmd(0x90+6);
	write_date(shidu_ge);
//	 write_cmd(0x90+7);
	write_word("%");
   	write_cmd(0x88);
	write_word("�����¶�");
	write_cmd(0x88+5);
	write_date(wendu_shi);
//	write_cmd(0x88+6);
	write_date(wendu_ge);
 //   write_cmd(0x88+7);
	write_word("C");

}
void gprs_senDHT11()
{
	Uart1Send(wendu_shi);		 //�����¶�ʮλ
	Uart1Send(wendu_ge);		     //�����¶ȸ�λ
	Uart1Send(shidu_shi);		 //����ʪ��ʮλ
	Uart1Send(shidu_ge);		     //����ʪ�ȸ�λ


}



	