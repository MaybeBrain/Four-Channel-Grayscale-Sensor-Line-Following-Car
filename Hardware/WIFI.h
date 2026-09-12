#ifndef _WIFI_H
#define _WIFI_H
#include "stm32f10x.h"

extern uint8_t USART1_RX_BUF[200];
extern uint8_t USART1_RX_CNT;

void WIFI_Init(void);
void Print(void);











#endif
