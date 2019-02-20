#include<12864.h>

void delay(uint z)
{
	uint i,j;
	for(i=z;i>0;i--)
		for(j=110;j>0;j--);
}

void write_cmd(uchar cmd)
{
	RS=0;
	RW=0;
	EN=0;
	P0=cmd;
	EN=1;
	delay(5);
	EN=0;
	delay(5);
}

void write_date(uchar date)
{
	RS=1;
	RW=0;
	EN=0;
	P0=date;
	EN=1;
	delay(5);
	EN=0;
	delay(5);	
}

void write_word(unsigned char *s)
{
	while(*s>0)
	{
		write_date(*s);
		s++;
	}
}

void lcd_init()
{
	PSB=1;
	write_cmd(0x30);		  //基本操作指令
	delay(5);				  
	write_cmd(0x0c);		  //显示开关光标
	delay(5);
	write_cmd(0x01);		  //清除LCD显示内容
	delay(5);
}

/*------------------------------------------------
                      清屏
------------------------------------------------*/
void ClrScreen()
{ 
    write_cmd(0x01);
    delay(5);
}


// void main()
//{	
//	lcd_init();
//
//	while(1)
//	{
//		write_cmd(0x80+2);	//第1行

//	write_date(wen);
//	write_word("吴小同");
//		write_cmd(0x90);  //第二行
//		write_word("吴小童2");
//		write_cmd(0x88);  //第三行
//		write_word("吴小童3");
//		write_cmd(0x98);   //第四行
//		write_word("吴小童4");	
		
//	}
//}