#include "navigation.h"
#include "motor.h"
#include "MPU6050.h"
#include "global.h"
#include <math.h>
#include "tim.h"
#include "encoder.h"
#include "HCSR04.h"
#include "bluetooth_receiver.h"
#include "path_planning.h"

#define Kp 2.5f    // Hệ số tỷ lệ (Proportional gain)
#define Ki 0.01f   // Hệ số tích phân (Integral gain)
#define Kd 0.5f    // Hệ số vi phân (Derivative gain)
//*---------PID for driving-------*//
static float integral = 0;
static float previous_error = 0;
			//*----------------- Hệ Thống PID -----------------*//
void controlSpeedStraight(void)
{
    double error = targetAngle - angle;  // Sai lệch hiện tại
    integral += error;                   // Tích phân lỗi
    double derivative = error - previous_error;  // Vi phân lỗi
    previous_error = error;

    // PID output
    double output = Kp * error + Ki * integral + Kd * derivative;

    // Điều chỉnh tốc độ motor theo PID output
    leftSpeedVal1  = equilibriumSpeed - output;
    leftSpeedVal2  = equilibriumSpeed - output;
    rightSpeedVal1 = equilibriumSpeed + output;
    rightSpeedVal2 = equilibriumSpeed + output;

    // Giới hạn giá trị tốc độ
    if (leftSpeedVal1 > 120) leftSpeedVal1 = 120;
    if (leftSpeedVal1 < 0)   leftSpeedVal1 = 0;
    if (rightSpeedVal1 > 120) rightSpeedVal1 = 120;
    if (rightSpeedVal1 < 0)   rightSpeedVal1 = 0;

    if (leftSpeedVal2 > 120) leftSpeedVal2 = 120;
    if (leftSpeedVal2 < 0)   leftSpeedVal2 = 0;
    if (rightSpeedVal2 > 120) rightSpeedVal2 = 120;
    if (rightSpeedVal2 < 0)   rightSpeedVal2 = 0;
}

void controlSpeedBackward(void)
{
    double error = targetAngle - angle;  // Sai lệch hiện tại
    integral += error;                   // Tích phân lỗi
    double derivative = error - previous_error;  // Vi phân lỗi
    previous_error = error;

    // PID output
    double output = Kp * error + Ki * integral + Kd * derivative;

    // Điều chỉnh tốc độ motor theo PID output
    leftSpeedVal1  = equilibriumSpeed + output;
    leftSpeedVal2  = equilibriumSpeed + output;
    rightSpeedVal1 = equilibriumSpeed - output;
    rightSpeedVal2 = equilibriumSpeed - output;

    // Giới hạn giá trị tốc độ
    if (leftSpeedVal1 > 100) leftSpeedVal1 = 100;
    if (leftSpeedVal1 < 0)   leftSpeedVal1 = 0;
    if (rightSpeedVal1 > 100) rightSpeedVal1 = 100;
    if (rightSpeedVal1 < 0)   rightSpeedVal1 = 0;

    if (leftSpeedVal2 > 100) leftSpeedVal2 = 100;
    if (leftSpeedVal2 < 0)   leftSpeedVal2 = 0;
    if (rightSpeedVal2 > 100) rightSpeedVal2 = 100;
    if (rightSpeedVal2 < 0)   rightSpeedVal2 = 0;
}
			//*------ Áp PID vào việc chạy thẳng ------*//
void drivingStraight(){
	double deltaAngle = angle - targetAngle ;
	Motor_Straight();
    if(deltaAngle !=0){
    	controlSpeedStraight();
    	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,leftSpeedVal2);
    	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,leftSpeedVal1);
    	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,rightSpeedVal2);
    	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,rightSpeedVal1);
    }
}

			//*------ Áp PID vào việc chạy lùi ------*//
void drivingBackward(){
	double deltaAngle = angle - targetAngle ;
	Motor_Backward();
    if(deltaAngle !=0){
    	controlSpeedBackward();
    	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,leftSpeedVal2);
    	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,leftSpeedVal1);
    	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,rightSpeedVal2);
    	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,rightSpeedVal1);
    }
}

			//*----- Tính toán khoảng cách đi được khi chạy thẳng -----*//
void goStraight(int distance_target_cm) {
    if (Distance < 25) {
        Motor_Stop();
        statusText = "CÓ VẬT CẢN!";
        return;  // Không tiếp tục chạy nữa
    }
	if (weight < 150000) {
		statusText = "LỖI: HÀNG RƠI!";
		Motor_Stop();
		return;
	}
	int distance_travelled = total_distance - distance_reference;
        if (distance_travelled < distance_target_cm) {
            drivingStraight();  // giữ nguyên tốc độ, PID sẽ lo việc giữ hướng
        }
        else {
            Motor_Stop();
            HAL_Delay(1000);
            isDriving = false;
        }

}

			//*----- Tính toán khoảng cách đi được khi chạy lùi -----*//
void goBackward(int distance_target_cm) {
	int distance_travelled = total_distance - distance_reference;
        if (distance_travelled < distance_target_cm) {
            drivingBackward();  // giữ nguyên tốc độ, PID sẽ lo việc giữ hướng
        }
        else {
            Motor_Stop();
            HAL_Delay(1000);
            isDriving = false;
        }

}

			//*----- Tính toán khoảng cách đi được khi chạy ngang trái -----*//
void goSideWayLeft(int distance_target_cm) {
	if (state == STATE_B_LEFT) {
	    if (weight < 150000) {
	        statusText = "LỖI: HÀNG RƠI!";
	        Motor_Stop();
	        return;
	    }
	}
	int distance_travelled = total_distance - distance_reference;
        if (distance_travelled < distance_target_cm) {
            Motor_SidewayLeft();  // giữ nguyên tốc độ, PID sẽ lo việc giữ hướng
        }
        else {
            Motor_Stop();
            HAL_Delay(1000);
            isDriving = false;
        }

}

			//*----- Tính toán khoảng cách đi được khi chạy ngang phải -----*//
void goSideWayRight(int distance_target_cm) {
	if (state == STATE_C_RIGHT) {
	    if (weight < 150000) {
	        statusText = "LỖI: HÀNG RƠI!";
	        Motor_Stop();
	        return;
	    }
	}
	int distance_travelled = total_distance - distance_reference;
        if (distance_travelled < distance_target_cm) {
            Motor_SidewayRight();  // giữ nguyên tốc độ, PID sẽ lo việc giữ hướng
        }
        else {
            Motor_Stop();
            HAL_Delay(1000);
            isDriving = false;
        }
}

