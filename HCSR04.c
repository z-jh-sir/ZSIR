#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"

#define Trig_Pin GPIO_Pin_10
#define Echo_Pin GPIO_Pin_9

void HCSR04_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Trig_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);						//将PA1和PA2引脚初始化为推挽输出
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = Echo_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	/*设置GPIO初始化后的默认电平*/

	GPIO_ResetBits(GPIOA, Trig_Pin | Echo_Pin);

}

void HCSR04_Trig(void)
{
	GPIO_SetBits(GPIOA, Trig_Pin);
	Delay_us(10);
	GPIO_ResetBits(GPIOA, Trig_Pin);
}
u32 HCSR04_Echo(void)
{
	u32 i = 0;
	while(GPIO_ReadInputDataBit(GPIOA,Echo_Pin) == 0);
	while(GPIO_ReadInputDataBit(GPIOA,Echo_Pin) == 1)
	{
		Delay_us(1);
		i++;
		if(i>=70000 && i<1)
		{
			return 0;
		}
	}

	return (i*340)/2;
}
void HCSR04_GetData(u32 *d)
{
	HCSR04_Trig();
	*d = HCSR04_Echo();
	if (*d <= 200000)
	{
		Servo_SetAngle(180);
	}
	else{Servo_SetAngle(90);}
}

