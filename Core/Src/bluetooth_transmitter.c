/*
 * bluetooth_transmitter.c
 *
 *  Created on: May 10, 2025
 *      Author: Wangtran
 */
#include "bluetooth_transmitter.h"
#include "string.h"
#include "stdio.h"
#include "usart.h"
#include "HCSR04.h"
#include "global.h"

void Bluetooth_SendStatus(const char* statusText, uint16_t Distance)
{
    char buffer[128];
    snprintf(buffer, sizeof(buffer),"%s;%d",statusText, Distance);
    HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), 100);
}
