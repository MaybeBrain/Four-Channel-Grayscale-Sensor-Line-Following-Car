#ifndef _SENSOR_H
#define _SENSOR_H
#include "stm32f10x.h"

extern uint8_t auto_mode;
void Sensor_Init(void);
uint8_t Sensor_Read(void);
void Auto_Delivery(void);


















#endif
