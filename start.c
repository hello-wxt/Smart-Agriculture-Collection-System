#include<start.h>

void start_display()
{
 
   	    write_cmd(0x80+1);
	    write_word("ũҵ������Ϣ");
		write_cmd(0x90+1);
	    write_word("�ɼ����ϵͳ");
	    write_cmd(0x88);   
		write_word("���ߣ���Сͬ");
		 write_cmd(0x98);   
		write_word("ָ����ʦ����Ϊ��");
}

void all_Display()
{
	 
       display_BH1750();
       DHT11_Display();
	   tu_display();

}

