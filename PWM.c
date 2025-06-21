#include "stm32f10x.h"                  // Device header


void PWM_Init(void)
{	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_BaseInitStructure.TIM_CounterMode =TIM_CounterMode_Down ;
	TIM_BaseInitStructure.TIM_Period = 20000 - 1 ;
	TIM_BaseInitStructure.TIM_Prescaler = 72 -1 ;
	TIM_BaseInitStructure.TIM_RepetitionCounter  =  0;
	TIM_TimeBaseInit(TIM2,&TIM_BaseInitStructure);
	

	
	TIM_OCInitTypeDef OCInitSturcture;
	TIM_OCStructInit(&OCInitSturcture);
	OCInitSturcture.TIM_OCMode =TIM_OCMode_PWM1;
	OCInitSturcture.TIM_OCPolarity=TIM_OCPolarity_High;
	OCInitSturcture.TIM_OutputState=TIM_OutputState_Enable;
	OCInitSturcture.TIM_Pulse= 0 ;
	TIM_OC2Init(TIM2,&OCInitSturcture);
	
	TIM_Cmd(TIM2,ENABLE);
}
void PWM_SetCompare2(u16 ccr)
{
	TIM_SetCompare2(TIM2,ccr);

}
void Servo_SetAngle(float Angle)
{
	PWM_SetCompare2(Angle/180 *2000+500);
	
}

