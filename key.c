#include<key.h>

sbit key1=P1^5;
sbit key2=P1^6;

 unsigned char flag=0;

void key()
{
if(key1==0)
	{
		 delay(3);
		if(key1==0)
		{
			while(key1==0);
			{
				flag++;
				ClrScreen();
				if(flag==2)
				{
					flag=0;
				}
			}
		}
	}
// 	if(key2==0)
//	{	
//		delay(3);
//		if(key2==0)
//		{
//			while(!key2);
//			send_all();
//		}
//	}
}
void key_display()
{					
	switch(flag)
	{		 

		case 0: start_display();break;
		case 1:	all_Display();break;
		default:break;
	}	
}
   