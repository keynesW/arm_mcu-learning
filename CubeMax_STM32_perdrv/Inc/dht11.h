#ifndef __DHT11_H__
#define __DHT11_H__

#include "main.h" 



extern   uint8_t ucharT_data_H,ucharT_data_L,ucharRH_data_H,ucharRH_data_L,ucharcheckdata;
extern void HAL_Delay_1us(uint8_t Delay);
void DHT11_TEST(void);   //ÎÂÊª´«¸ÐÆô¶¯
void test_dht11(void);
void DHT11_TEST1(void);
#endif
