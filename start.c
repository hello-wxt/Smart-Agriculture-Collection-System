#include<start.h>

void start_display()
{
 
   	    write_cmd(0x80+1);
	    write_word("农业环境信息");
		write_cmd(0x90+1);
	    write_word("采集检测系统");
	    write_cmd(0x88);   
		write_word("作者：吴小同");
		 write_cmd(0x98);   
		write_word("指导老师：黄为勇");
}

void all_Display()
{
	 
       display_BH1750();
       DHT11_Display();
	   tu_display();

}

