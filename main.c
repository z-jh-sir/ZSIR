#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "HCSR04.h"
#include "PWM.h"

u32 d;


int main(void)
{
	OLED_Init();
	HCSR04_Init();
	PWM_Init();
	
	OLED_ShowString(1,1,"D:");
	
	
	while(1)
	{
		HCSR04_GetData(&d);
		OLED_ShowNum(1,3,d,7);
		Delay_ms(100); 
	}
}

