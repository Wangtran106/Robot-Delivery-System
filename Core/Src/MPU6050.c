#include "MPU6050.h"
#include "i2c.h"
#include <math.h>
#include "global.h"

#define MPU6050_ADDR 0xD0
#define ACCEL_XOUT_H_REG 0x3B
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75
#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C


static float Ax, Ay, Az, Gx, Gy, Gz;
static double AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
static double accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
static float previousTime = 0;

void MPU6050_Init(void) {
	uint8_t check, data;
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, 1000);
	if (check == 104) {
		data = 0;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &data, 1, 1000);
		data = 0x07;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &data, 1, 1000);
		data = 0x00;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &data, 1, 1000);
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &data, 1, 1000);
	}
}

void MPU6050_Read_Accel(float* aX, float* aY, float* aZ) {
	uint8_t Rec_Data[6];
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, 1000);
	int16_t rawX = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
	int16_t rawY = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
	int16_t rawZ = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);
	*aX = rawX / 16384.0f;
	*aY = rawY / 16384.0f;
	*aZ = rawZ / 16384.0f;
}

void MPU6050_Read_Gyro(float* gX, float* gY, float* gZ) {
	uint8_t Rec_Data[6];
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, 1000);
	int16_t rawX = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
	int16_t rawY = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
	int16_t rawZ = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);
	*gX = rawX / 131.0f;
	*gY = rawY / 131.0f;
	*gZ = rawZ / 131.0f;
}

void MPU6050_CalculateError(void) {
	float sumAccX = 0, sumAccY = 0;
	float sumGyroX = 0, sumGyroY = 0, sumGyroZ = 0;
	for (int i = 0; i < 200; i++) {
		MPU6050_Read_Accel(&Ax, &Ay, &Az);
		sumAccX += atan(Ay / sqrt(Ax * Ax + Az * Az)) * 180 / M_PI;
		sumAccY += atan(-Ax / sqrt(Ay * Ay + Az * Az)) * 180 / M_PI;

		MPU6050_Read_Gyro(&Gx, &Gy, &Gz);
		sumGyroX += Gx;
		sumGyroY += Gy;
		sumGyroZ += Gz;
		HAL_Delay(1);
	}
	AccErrorX = sumAccX / 200.0;
	AccErrorY = sumAccY / 200.0;
	GyroErrorX = sumGyroX / 200.0;
	GyroErrorY = sumGyroY / 200.0;
	GyroErrorZ = sumGyroZ / 200.0;
}

void MPU6050_Update(float *roll, float *pitch, float *yaw) {
	float currentTime = HAL_GetTick(); //ms
	float elapsedTime = (currentTime - previousTime) / 1000.0f;
	previousTime = currentTime;

	MPU6050_Read_Accel(&Ax, &Ay, &Az);
	accAngleX = atan(Ay / sqrt(Ax * Ax + Az * Az)) * 180 / M_PI - AccErrorX;
	accAngleY = atan(-Ax / sqrt(Ay * Ay + Az * Az)) * 180 / M_PI - AccErrorY;

	MPU6050_Read_Gyro(&Gx, &Gy, &Gz);
	Gx -= GyroErrorX;
	Gy -= GyroErrorY;
	Gz -= GyroErrorZ;

	gyroAngleX += Gx * elapsedTime;
	gyroAngleY += Gy * elapsedTime;
	gyroAngleZ += Gz * elapsedTime;

	*roll  = 0.96f * gyroAngleX + 0.04f * accAngleX;
	*pitch = 0.96f * gyroAngleY + 0.04f * accAngleY;
	*yaw   = gyroAngleZ;
	angle = *roll;
}
