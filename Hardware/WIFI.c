#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include "Delay.h"
#include "OLED.h"

uint8_t USART1_RX_BUF[200];
uint8_t USART1_RX_CNT = 0;

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        USART1_RX_BUF[USART1_RX_CNT] = USART_ReceiveData(USART1);
        USART1_RX_CNT++;
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}


int fputc(int ch,FILE *f)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);

		USART_SendData(USART1,(uint8_t)ch);
	
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	
	return ch;
}

void WIFI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	USART_InitTypeDef USART_Initstructure;
	USART_Initstructure.USART_BaudRate=115200;
	USART_Initstructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Initstructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	USART_Initstructure.USART_Parity=USART_Parity_No;
	USART_Initstructure.USART_StopBits=USART_StopBits_1;
	USART_Initstructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_Initstructure);
	
	USART_Cmd(USART1,ENABLE);
	Delay_ms(2000);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_Initstructure;
	NVIC_Initstructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Initstructure);
}

void Print(void)
{
	
	printf("AT+RST\r\n");
    Delay_ms(3000);
	printf("AT\r\n");
	Delay_ms(1000);
	printf("AT+CWMODE=1\r\n");
	printf("AT+CWJAP=\"test\",\"123456789\"\r\n");
	Delay_ms(5000);
	printf("AT+CIFSR\r\n");
	Delay_ms(1000);
	printf("AT+CIPSERVER=0\r\n");
    Delay_ms(1000);
	printf("AT+CIPMUX=1\r\n");
	Delay_ms(1000);
	printf("AT+CIPSERVER=1,8080\r\n");
	Delay_ms(1000);
}








