#include<send_all.h>



void send_all()

{
 gprs_senBH1750();
 gprs_senDHT11();
 gprs_tu(); 
 }
