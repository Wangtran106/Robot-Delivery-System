/*
 * MPU6050.h
 *
 *  Created on: Apr 15, 2025
 *      Author: Wangtran
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "main.h"

// Functions
void MPU6050_Init(void);
void MPU6050_Read_Accel(float *Ax, float *Ay, float *Az);
void MPU6050_Read_Gyro(float *Gx, float *Gy, float *Gz);
void MPU6050_Update(float *roll, float *pitch, float *yaw);
void MPU6050_CalculateError(void);


#endif /* INC_MPU6050_H_ */
