#include "stm32f10x.h"                  // Device header


void Motor_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2|GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 拉低所有 IN 引脚，让电机保持停止
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);
    GPIO_ResetBits(GPIOA, GPIO_Pin_3);
}



void Motor_Forward(void) {
    GPIO_SetBits(GPIOA, GPIO_Pin_0);    // IN1 高
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);  // IN2 低
	GPIO_SetBits(GPIOA, GPIO_Pin_2);    // IN3 高
    GPIO_ResetBits(GPIOA, GPIO_Pin_3);  // IN4 低
}

void Motor_Backward(void) {
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);  // IN1 低
    GPIO_SetBits(GPIOA, GPIO_Pin_1);    // IN2 高
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);  // IN3 低
    GPIO_SetBits(GPIOA, GPIO_Pin_3);    // IN4 高
}

void Motor_Stop(void) {
    GPIO_ResetBits(GPIOA, GPIO_Pin_0); // IN1 低
    GPIO_ResetBits(GPIOA, GPIO_Pin_1); // IN2 低
	GPIO_ResetBits(GPIOA, GPIO_Pin_2); // IN3 低
	GPIO_ResetBits(GPIOA, GPIO_Pin_3); // IN4 低
}

void Motor_TurnLeft(void)   // 左转：左轮停，右轮转
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);  // 控制左轮 IN1
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);  // 左轮 IN2，都低 = 停
    GPIO_SetBits(GPIOA, GPIO_Pin_2);    // PA2 控制右轮 IN3，高
    GPIO_ResetBits(GPIOA, GPIO_Pin_3);  // 右轮 IN4，低，正转
}

void Motor_TurnRight(void)   // 左转：左轮停，右轮转
{
    GPIO_SetBits(GPIOA, GPIO_Pin_0);    // PA0 控制左轮 IN1
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);  // 左轮 IN2，都低 = 停
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);  // PA2 控制右轮 IN3，高
    GPIO_ResetBits(GPIOA, GPIO_Pin_3);  // 右轮 IN4，低，正转
}



















