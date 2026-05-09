/*
 * motor.h
 *
 *  Created on: Apr 10, 2025
 *      Author: Wangtran
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "stm32f1xx_hal.h"
#include <stdint.h>

// Khai báo hàm điều khiển động cơ
void Motor_Init(void);
void Motor_Forward(void);
void Motor_TurnLeft(void);
void Motor_TurnRight(void);
void Motor_Stop(void);
void Motor_SetSpeed(uint8_t speedLeft, uint8_t speedRight);
void Motor_Straight(void);
void Motor_Backward(void);
void Motor_SidewayLeft(void);
void Motor_SidewayRight(void);
void Motor_DiagonalLeft(void);
void Motor_DiagonalRight(void);
void Motor_TurnRound(void);
void Motor_Concerning(void);
void Motor_TurnRearAxis(void);
void Motor_SetSpeed4(uint8_t speed1, uint8_t speed2, uint8_t speed3, uint8_t speed4);


#endif
