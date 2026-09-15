# 基于STM32的隐私保护无人配送原型系统

## 项目简介
针对外卖配送中用户地址泄露的问题，设计并实现了一款末端无人配送原型系统。

## 实物展示
<div align="center">
  <img src="./images/car_overview.jpg" width="500" alt="整车调试图">
  <p>图1：无人车整体外观</p>
</div>

<div align="center">
  <img src="./images/car_top_view.jpg" width="500" alt="俯视接线图">
  <p>图2：主控板及外设接线细节（俯视图）</p>
</div>

<div align="center">
  <img src="./images/car_bottom_view.jpg" width="500" alt="底盘供电与驱动图">
  <p>图3：底盘供电系统与电机驱动布局（底部图）</p>
</div>


## 开发工具
硬件清单：STM32F103C8T6、ESP8266、L298N、18650电池等。
开发环境：Keil MDK、C语言。

## 硬件接线表

| 模块 | 引脚 | STM32引脚 | 说明 |
| :--- | :---: | :---: | :--- |
| ESP8266 | TX | PA10 (RX) | 串口1接收 |
| ESP8266 | RX | PA9 (TX) | 串口1发送 |
| L298N | IN1 | PA0 | 电机A方向控制 |
| L298N | IN2 | PA1 | 电机A方向控制 |
| L298N | IN3 | PA2 | 电机B方向控制 |
| L298N | IN4 | PA3 | 电机B方向控制 |
| 灰度传感器 | OUT1 | PA4 | 循迹通道1 |
| 灰度传感器 | OUT2 | PA5 | 循迹通道2 |
| 灰度传感器 | OUT3 | PA7 | 循迹通道3 |
| 灰度传感器 | OUT4 | PA6 | 循迹通道4 |
| OLED | SCL | PB8 | I2C时钟线 |
| OLED | SDA | PB9 | I2C数据线 |

## 文件功能说明

| 文件       | 功能 | 核心内容 |
| --- | --- | --- |
| `main.c` | 主逻辑 | 初始化、指令解析、模式切换 |
| `Motor.c/h` | 电机驱动 | GPIO控制、正反转、差速转弯 |
| `WIFI.c/h` | WiFi通信 | AT指令封装、串口中断接收、缓冲区管理 |
| `OLED.c/h` | 显示驱动 | I2C通信、字符串显示 |
| `Sensor.c/h` | 循迹传感 | GPIO读取、状态组合、自动循迹逻辑 |
| `Delay.c/h` | 延时函数 | 毫秒级延时 |

## 核心功能实现
1. **通信设计**：基于ESP8266搭建TCP服务器，通过UART中断+环形缓冲区接收数据，设计 `+IPD` 前缀解析算法解决串口数据时序问题。
2. **寻迹算法**：实现4路灰度传感器直线巡线及路口检测。
3. **状态显示**：集成OLED实时显示WiFi连接状态及配送进度。



