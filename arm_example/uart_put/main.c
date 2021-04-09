/*
  功能:   实现通过串口com2 输出字符显示

  1. 看电路图找到CPU对应的控制管脚   GPA1_1  GPA1_0
  2. 看芯片手册，找到对应寄存器
     a. 配置管脚为串口模式
     b. 功能块设置
  3. 编程   

*/

#define GPA1CON  (*(volatile unsigned int *)0x11400020) 
#define ULCON2   (*(volatile unsigned int *)0x13820000) 
#define UCON2    (*(volatile unsigned int *)0x13820004) 
#define UBRDIV2  (*(volatile unsigned int *)0x13820028) 
#define UFRACVAL2  (*(volatile unsigned int *)0x1382002c) 
#define UTXH2      (*(volatile unsigned int *)0x13820020) 
#define UTRSTAT2   (*(volatile unsigned int *)0x13820010) 
void delay()
{
	volatile int i,j;
	for(i=0;i<1000;i++)
		for(j=0;j<1000;j++)	 
}
void uart_init(void)
{
  //1. config pin  GPA1_1 GPA1_0  uart mode
  GPA1CON = GPA1CON & ~(0xff<<0) | (0x22<<0);
  //2. set uart function block
  ULCON2  =  0x03;  // data bit =8  parity=none  stop bit=1
  UCON2 = 0x05; //set polling mode
  /*
   * set Baud-Rate = 115200
   * DIV_VAL = (100000000/(115200 *16)) - 1 = 53.253
     UBRDIV2  =50
    UFRACVAL2 = 0x253*16=4
   * 
   */
   UBRDIV2 = 53;  
   UFRACVAL2  = 4;
}

void putc(char c)
{
  while(!(UTRSTAT2&0x02));
  
   UTXH2 = c; 

}
int main(void) 
{
	uart_init();
	while(1)
	{
	  putc('b');
	  delay1s();
	}
	return 0;
}
