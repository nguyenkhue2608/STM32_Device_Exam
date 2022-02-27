/******************************************************************************************************************
@File:  	DHT Sensor
@Author:  Khue Nguyen
@Website: khuenguyencreator.com
@Youtube: https://www.youtube.com/channel/UCt8cFnPOaHrQXWmVkk-lfvg
Huong dan su dung:
- Su dung thu vien HAL
- Khoi tao bien DHT : DHT_Name DHT1;
- Khoi tao chan DHT:
	DHT_Init(&DHT1, DHT11, &htim4, DHT_GPIO_Port, DHT_Pin);
- Su dung cac ham phai truyen dia chi cua DHT do: 
	DHT_ReadTempHum(&DHT1);
******************************************************************************************************************/
#ifndef __DHT_H
#define __DHT_H

#include "stm32f1xx_hal.h"
#define DHT11_STARTTIME 18000
#define DHT22_STARTTIME 12000
#define DHT11 0x01
#define DHT22 0x02
typedef struct
{	
	uint8_t Respone;
	uint16_t Type;
	TIM_HandleTypeDef* Timer;
	uint16_t Pin;
	GPIO_TypeDef* Port;
	float Temp;
	float Humi;
}DHT_Name;

void DHT_Init(DHT_Name* DHT, uint8_t DHT_Type, TIM_HandleTypeDef* Timer, GPIO_TypeDef* DH_PORT, uint16_t DH_Pin);
uint8_t DHT_ReadTempHum(DHT_Name* DHT);
#endif

