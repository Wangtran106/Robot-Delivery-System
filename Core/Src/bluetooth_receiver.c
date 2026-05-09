/*
 * bluetooth_receiver.c
 *
 *  Created on: May 10, 2025
 *      Author: Wangtran
 */
#include "bluetooth_receiver.h"
#include "global.h"
#include "usart.h"
#include "path_planning.h"
#include "bluetooth_transmitter.h"


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
    	if (r_data == 'b') {
    	    currentRoute = ROUTE_B;
    	    isDriving = true;
    	    statusText = "ĐANG CHỜ hàng hóa B";
    	    state = STATE_WAIT_PACKAGE_B;
    	} else if (r_data == 'c') {
    	    currentRoute = ROUTE_C;
    	    isDriving = true;
    	    statusText = "ĐANG CHỜ hàng hóa C";
    	    state = STATE_WAIT_PACKAGE_C;
    	}
        HAL_UART_Receive_IT(&huart1, &r_data, 1);
    }
}

