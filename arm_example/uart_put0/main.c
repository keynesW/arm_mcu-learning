/*
  功能:   实现通过串口com2 输出字符显示

  1. 看电路图找到CPU对应的控制管脚   GPA1_1  GPA1_0
  2. 看芯片手册，找到对应寄存器
     a. 配置管脚为串口模式
     b. 功能块设置
  3. 编程   
     

*/

#define  GPA1CON    (*(volatile unsigned int *)0x11400020)
#define  ULCON2     (*(volatile unsigned int *)0x13820000) 
#define  UCON2      (*(volatile unsigned int *)0x13820004) 
#define  UBRDIV2    (*(volatile unsigned int *)0x13820028) 
#define  UFRACVAL2  (*(volatile unsigned int *)0x1382002C) 
#define  UTXH2      (*(volatile unsigned int *)0x13820020) 
#define  UTRSTAT2   (*(volatile unsigned int *)0x13820010) 
#define  URXH2      (*(volatile unsigned int *)0x13820024) 
void uart_init(void)
{
  //-----外: 配置管脚的工作模式
  GPA1CON = 0x22;  //配置GPA1_1 GPA10 为uart串口模式
  //GPA1CON = (GPA1CON & ~0xff) | 0x22;
  //-----内: 功能块设置
  //1.  uart 通讯协议格式的设置
  ULCON2 = 0x03;  //设置协议格式(  无校验位  1个停止位 8个数据位)
  UCON2 = 0x05;   //设置串口发送接收模式为polling模式
  
  /*2.  设置uart 的速度为115200
  DIV_VAL = (100000000/(115200 *16)) - 1 = 53.253
  UBRDIVn =  53
  UFRACVALn/16 = 0.253
  Therefore, UFRACVALn = 4
  */
  UBRDIV2 = 53;
  UFRACVAL2 = 4;
    
}


void putc(char c)
{
   while(!(UTRSTAT2&0x02));
   
   UTXH2 = c;  //发送字符
}

char getc()
{
   char c;
   c = (char)URXH2;
   return c;
}
int main(void) 
{
	char c;
    uart_init();
	#if 1
	while(1)
	{
      putc('f');
	  delay1s();
	}
	#else
	while(1)
    {
        while(UTRSTAT2&0x01)	
        {
            c =  getc();
            if (c == 0x0d)
            {
                UTXH2 = 0x0a;
                delay1s(1);
                UTXH2 = 0x0d;
            }
            else
            {
               putc(c);
            }
            delay1s(1);
        } 

    }
	#endif 
	return 0;
}
