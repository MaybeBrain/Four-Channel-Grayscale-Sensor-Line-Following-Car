#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "OLED.h"

uint8_t auto_mode = 0;

void Sensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t Sensor_Read(void)
{
    uint8_t val = 0;
    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0) val |= 0x01; // X1 左
    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0) val |= 0x02; // X2 中左
    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0) val |= 0x04; // X3 中右
    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 0) val |= 0x08; // X4 右
    return val;
}

void Auto_Delivery(void)
{
    uint8_t sensor = Sensor_Read();
    
    // 根据4路传感器状态决定动作
    // 假设黑线宽约等于一个传感器，正常巡线时中间两个传感器（PA4/PA5）压在黑线上
    if(sensor == 0x06)       // 0b0110，中左和中右都在黑线上，直走
    {
        Motor_Forward();
    }
    else if(sensor & 0x02)   // 中左（PA4）压线，车偏右，向左微调
    {
        Motor_TurnLeft();
    }
    else if(sensor & 0x04)   // 中右（PA5）压线，车偏左，向右微调
    {
        Motor_TurnRight();
    }
    else if(sensor == 0x00)  // 全白，脱线，停止
    {
        Motor_Stop();
    }
    else if(sensor == 0x0F)  // 全黑（0b1111），到达终点（路口），停止
    {
        Motor_Stop();
        OLED_ShowString(4, 1, "Arrived!    ");
        auto_mode = 0;  // 退出自动模式
    }
    else
    {
        Motor_Stop();   // 其他未知状态，安全停止
    }
}











