#include<DHT11.h>

sbit  P2_0  = P1^2 ;



typedef unsigned char  U8;       /* defined for unsigned 8-bits integer variable 	  无符号8位整型变量  */
// typedef unsigned int   U16;      /* defined for unsigned 16-bits integer variable 	  无符号16位整型变量 */
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
     //大致延时1mS
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
	   	//超时则跳出for循环		  
	   	 if(U8FLAG==1)break;
	   	//判断数据位是0还是1	 
	   	   
		// 如果高电平高过预定0高电平值则数据位为 1 
	   	 
		   U8comdata<<=1;
	   	   U8comdata|=U8temp;    
	     }
	   
	}

	//--------------------------------
	//-----湿度读取子程序 ------------
	//--------------------------------
	//----以下变量均为全局变量--------
	//----温度高8位== U8T_data_H------
	//----温度低8位== U8T_data_L------
	//----湿度高8位== U8RH_data_H-----
	//----湿度低8位== U8RH_data_L-----
	//----校验 8位 == U8checkdata-----
	//----调用相关子程序如下----------
	//---- Delay();, Delay_10us();,COM(); 
	//--------------------------------

	void RH()
	{
	  //主机拉低18ms 
       P2_0=0;    
	  DelayMs(18);		        //延时180ms
	   P2_0=1;

       Delay_10us();
	   Delay_10us();
	   Delay_10us();
	   Delay_10us();

	 //主机设为输入 判断从机响应信号 
	   P2_0=1;
	 //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行	  
	   if(!P2_0)		 //T !	  
	   {
	   U8FLAG=2;
	 //判断从机是否发出 80us 的低电平响应信号是否结束	 
	   while((!P2_0)&&U8FLAG++);
	   U8FLAG=2;
	 //判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
	   while((P2_0)&&U8FLAG++);
	 //数据接收状态		 
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
	 //数据校验 
	 
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
	write_word("空气湿度");
	write_cmd(0x90+5);
	write_date(shidu_shi);
//	write_cmd(0x90+6);
	write_date(shidu_ge);
//	 write_cmd(0x90+7);
	write_word("%");
   	write_cmd(0x88);
	write_word("空气温度");
	write_cmd(0x88+5);
	write_date(wendu_shi);
//	write_cmd(0x88+6);
	write_date(wendu_ge);
 //   write_cmd(0x88+7);
	write_word("C");

}
void gprs_senDHT11()
{
	Uart1Send(wendu_shi);		 //空气温度十位
	Uart1Send(wendu_ge);		     //空气温度个位
	Uart1Send(shidu_shi);		 //空气湿度十位
	Uart1Send(shidu_ge);		     //空气湿度个位


}



	