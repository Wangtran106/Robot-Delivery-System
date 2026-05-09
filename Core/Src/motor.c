#include "stm32f1xx_hal.h"
#include "motor.h"

//extern TIM_HandleTypeDef htim3;  // TIM3 cho PWM PB0 (CH3), PB1 (CH4)

// Định nghĩa chân điều khiển cho 4 motor
#define MOTOR1_IN1_PORT GPIOB
#define MOTOR1_IN1_PIN  GPIO_PIN_5
#define MOTOR1_IN2_PORT GPIOB
#define MOTOR1_IN2_PIN  GPIO_PIN_4

#define MOTOR2_IN1_PORT GPIOB
#define MOTOR2_IN1_PIN  GPIO_PIN_3
#define MOTOR2_IN2_PORT GPIOA
#define MOTOR2_IN2_PIN  GPIO_PIN_15

#define MOTOR3_IN1_PORT GPIOA
#define MOTOR3_IN1_PIN  GPIO_PIN_4
#define MOTOR3_IN2_PORT GPIOA
#define MOTOR3_IN2_PIN  GPIO_PIN_5

#define MOTOR4_IN1_PORT GPIOA
#define MOTOR4_IN1_PIN  GPIO_PIN_6
#define MOTOR4_IN2_PORT GPIOA
#define MOTOR4_IN2_PIN  GPIO_PIN_7

// Hàm tiện ích điều khiển từng motor
static void SetMotor(GPIO_TypeDef* IN1_PORT, uint16_t IN1_PIN, GPIO_TypeDef* IN2_PORT, uint16_t IN2_PIN, int8_t dir) {
    if (dir > 0) { // Forward
        HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_SET);
    } else if (dir < 0) { // Backward
        HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET);
    } else { // Stop
        HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET);
    }
}

void Motor_Straight(void) {
    SetMotor(GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, 1);
    SetMotor(GPIOB, GPIO_PIN_3, GPIOA, GPIO_PIN_15, 1);
    SetMotor(GPIOA, GPIO_PIN_4, GPIOA, GPIO_PIN_5, 1);
    SetMotor(GPIOA, GPIO_PIN_6, GPIOA, GPIO_PIN_7, 1);
}
void Motor_Backward(void) {
    SetMotor(GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, -1);
    SetMotor(GPIOB, GPIO_PIN_3, GPIOA, GPIO_PIN_15, -1);
    SetMotor(GPIOA, GPIO_PIN_4, GPIOA, GPIO_PIN_5, -1);
    SetMotor(GPIOA, GPIO_PIN_6, GPIOA, GPIO_PIN_7, -1);
}
void Motor_SidewayLeft(void) {
    SetMotor(GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, -1);
    SetMotor(GPIOB, GPIO_PIN_3, GPIOA, GPIO_PIN_15, 1);
    SetMotor(GPIOA, GPIO_PIN_4, GPIOA, GPIO_PIN_5, -1);
    SetMotor(GPIOA, GPIO_PIN_6, GPIOA, GPIO_PIN_7, 1);
}
void Motor_SidewayRight(void) {
    SetMotor(GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, 1);
    SetMotor(GPIOB, GPIO_PIN_3, GPIOA, GPIO_PIN_15, -1);
    SetMotor(GPIOA, GPIO_PIN_4, GPIOA, GPIO_PIN_5, 1);
    SetMotor(GPIOA, GPIO_PIN_6, GPIOA, GPIO_PIN_7, -1);
}
void Motor_DiagonalLeft(void) {
    SetMotor(GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, 0);
    SetMotor(GPIOB, GPIO_PIN_3, GPIOA, GPIO_PIN_15, -1);
    SetMotor(GPIOA, GPIO_PIN_4, GPIOA, GPIO_PIN_5, 0);
    SetMotor(GPIOA, GPIO_PIN_6, GPIOA, GPIO_PIN_7, -1);
}
void Motor_DiagonalRight(void) {
    SetMotor(GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, 0);
    SetMotor(GPIOB, GPIO_PIN_3, GPIOA, GPIO_PIN_15, -1);
    SetMotor(GPIOA, GPIO_PIN_4, GPIOA, GPIO_PIN_5, -1);
    SetMotor(GPIOA, GPIO_PIN_6, GPIOA, GPIO_PIN_7, 0);
}
void Motor_TurnRound(void) {
    SetMotor(GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, 1);
    SetMotor(GPIOB, GPIO_PIN_3, GPIOA, GPIO_PIN_15, -1);
    SetMotor(GPIOA, GPIO_PIN_4, GPIOA, GPIO_PIN_5, 1);
    SetMotor(GPIOA, GPIO_PIN_6, GPIOA, GPIO_PIN_7, -1);
}
void Motor_Concerning(void) {
    SetMotor(GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, 1);
    SetMotor(GPIOB, GPIO_PIN_3, GPIOA, GPIO_PIN_15, -1);
    SetMotor(GPIOA, GPIO_PIN_4, GPIOA, GPIO_PIN_5, -1);
    SetMotor(GPIOA, GPIO_PIN_6, GPIOA, GPIO_PIN_7, 1);
}
void Motor_TurnRearAxis(void) {
    SetMotor(GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, 0);
    SetMotor(GPIOB, GPIO_PIN_3, GPIOA, GPIO_PIN_15, 0);
    SetMotor(GPIOA, GPIO_PIN_4, GPIOA, GPIO_PIN_5, 1);
    SetMotor(GPIOA, GPIO_PIN_6, GPIOA, GPIO_PIN_7, -1);
}
void Motor_Stop(void) {
    SetMotor(GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, 0);
    SetMotor(GPIOB, GPIO_PIN_3, GPIOA, GPIO_PIN_15, 0);
    SetMotor(GPIOA, GPIO_PIN_4, GPIOA, GPIO_PIN_5, 0);
    SetMotor(GPIOA, GPIO_PIN_6, GPIOA, GPIO_PIN_7, 0);
}
void Motor_SetSpeed4(uint8_t speed1, uint8_t speed2, uint8_t speed3, uint8_t speed4) {
    // Hàm này sẽ được hiện thực nếu có PWM cho từng motor
    // Tạm thời để trống hoặc điều chỉnh theo timer/PWM thực tế
}

//void Motor_Init(void)
//{
//    // Đặt tất cả chân điều khiển mức thấp ban đầu
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);
//
//    // Khởi động PWM cho ENA (PB0) và ENB (PB1)
//    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);  // ENA
//    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);  // ENB
//
//    // Mặc định tốc độ tối đa
//    Motor_SetSpeed(225, 225);
//}

//void Motor_SetSpeed(uint8_t speedLeft, uint8_t speedRight)
//{
//    uint32_t pwm_right = (htim3.Init.Period + 1) * speedRight / 100;
//    uint32_t pwm_left  = (htim3.Init.Period + 1) * speedLeft / 100;
//
//    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, pwm_right);  // ENA - Motor phải
//    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pwm_left);   // ENB - Motor trái
//}
