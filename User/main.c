#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <string.h>
#include "Delay.h"
#include "OLED.h" 
#include "WIFI.h"
#include "Motor.h"
#include "Sensor.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStrucure;
	GPIO_InitStrucure.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStrucure.GPIO_Pin =GPIO_Pin_13;
	GPIO_InitStrucure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStrucure);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	
	
	
	
	Motor_Init();
	Delay_ms(2000);
	
	Sensor_Init();
	Delay_ms(200);
	
	OLED_Init();
	OLED_ShowString(2, 1, "Waiting....");
    
	
	
	
	
	
	
	Delay_ms(500);
	WIFI_Init();
	memset(USART1_RX_BUF, 0, sizeof(USART1_RX_BUF));
	USART1_RX_CNT = 0;
	
	Print();
	
//	uint8_t connected = 0;
//	for(int i = 0; i < 100; i++)
//	{
//		if(strstr((char *)USART1_RX_BUF, "WIFI GOT IP") != NULL)
//		{
//			connected = 1;
//			break;
//		}
//		Delay_ms(100);   // 等待 100ms 再查一次
//	}

//	if(connected)
//	{
//		OLED_ShowString(2, 1, "WiFi:Connected");
//	}
	if(strstr((char *)USART1_RX_BUF, "WIFI GOT IP") != NULL)
	{
		OLED_ShowString(1, 1, "WiFi:Connected");
	}
    else
    {
        // --- 连接失败 ---
        OLED_ShowString(2, 1, "WiFi: FAILED");
        OLED_ShowString(3, 1, "Check WiFi cfg");
        OLED_ShowString(4, 1, "or Reset MCU");
	}
	
	memset(USART1_RX_BUF, 0, sizeof(USART1_RX_BUF));
    USART1_RX_CNT = 0;
	
	uint8_t phone_connected = 0;
	
	
	while(1)
	{	
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		uint8_t cmd_processed = 0;   // 标记本轮是否处理了一条命令
		
		
		if(!phone_connected && strstr((char *)USART1_RX_BUF, "0,CONNECT") != NULL)
        {
            OLED_ShowString(3, 1, "Phone:Connected");
            phone_connected = 1;
			cmd_processed = 1;
        }
		
		if(strstr((char *)USART1_RX_BUF, "+IPD") != NULL)
        {
            if(strstr((char *)USART1_RX_BUF, "GO") != NULL)
            {
				OLED_ShowString(4, 1, "Car Delivering");
				auto_mode = 1;
				cmd_processed = 1; 
            }
            else if(strstr((char *)USART1_RX_BUF, "STOP") != NULL)
            {
                Motor_Stop();
				OLED_ShowString(4, 1, "Car Stoped    ");
				auto_mode = 0;
				cmd_processed = 1; 
            }
        }
		
		if(auto_mode)
		{
			Auto_Delivery();
			Delay_ms(30);  // 循迹周期，可根据实际响应速度调整
		}
		
		if(cmd_processed==1)
		{
			memset(USART1_RX_BUF, 0, sizeof(USART1_RX_BUF));
			USART1_RX_CNT = 0;
		}
    }
}



