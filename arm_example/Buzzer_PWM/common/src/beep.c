#include "exynos_4412.h"
//#include "exynos_setup.h"

void beep_init(int tcnt_value,int tcmp_value)
{
		//SET_GPIO_MODE(GPD0.CON,0,0x2);

		
		GPD0.CON = (GPD0.CON & ~(0xf)) | 0x2;// GPD0_0 : TOUT_0
		
		PWM.TCFG0 &= ~(0xff << 0);
		PWM.TCFG0 |=  (199 << 0);
		
		PWM.TCFG1 &= ~(0xf << 0);
		PWM.TCFG1 |=  (0x1 << 0);
		
		PWM.TCNTB0 = tcnt_value;
		PWM.TCMPB0 = tcmp_value;
		
		PWM.TCON  |= (1 << 1);
		PWM.TCON  &= ~(1 << 1);
		
		return;
}

void beep_start(void)
{
		PWM.TCON |= (1 << 0) | (1 << 3);
		return; 	
}

void beep_stop(void)
{
		PWM.TCON &= ~(1 << 0);
		return;	
}