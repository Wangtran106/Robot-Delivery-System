/*
 * hx711.c
 *
 *  Created on: May 16, 2025
 *      Author: Wangtran
 */
#include <stdint.h>
#include "main.h"
#include "hx711.h"
#include "global.h"
#include "tim.h"
#include "gpio.h"


void microDelay(uint16_t delay)
{
  __HAL_TIM_SET_COUNTER(&htim1, 0);
  while (__HAL_TIM_GET_COUNTER(&htim1) < delay);
}

int32_t getHX711(void)
{
  uint32_t data = 0;
  uint32_t startTime = HAL_GetTick();
  while(HAL_GPIO_ReadPin(DT_PORT, DT_PIN) == GPIO_PIN_SET)
  {
    if(HAL_GetTick() - startTime > 100)
      return 0;
  }
  for(int8_t len = 0; len < 24; len++)
  {
    HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_SET);
    microDelay(1);
    data = data << 1;
    HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_RESET);
    microDelay(1);
    if(HAL_GPIO_ReadPin(DT_PORT, DT_PIN) == GPIO_PIN_SET)
      data++;
  }
  data = data ^ 0x800000;
  HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_SET);
  microDelay(1);
  HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_RESET);
  microDelay(1);
  return data;
}

int weigh(void)
{
  int32_t total = 0;
  int32_t samples = 5;
  int milligram = 0;
  float coefficient;

  for(uint16_t i=0; i<samples; i++)
  {
    int32_t reading = getHX711();
    if(reading == 0) {
      return -1;
    }
    total += reading;
  }

  int32_t average = total / samples;
  coefficient = knownOriginal / knownHX711;
  milligram = (int)((average - tare) * coefficient);

  if(milligram < 0) return 0;
  return milligram;
}



