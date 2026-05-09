/*
 * encoder.c
 *
 *  Created on: May 10, 2025
 *      Author: Wangtran
 */
#include "encoder.h"
#include "global.h"

// ========== Hàm khởi tạo ==========
void Encoder_Init(void)
{
    circumference_mm = (PI_TIMES_100 * WHEEL_DIAMETER_MM) / 100;
    distance_per_pulse_mm = circumference_mm / PULSES_PER_REV;
}

// ========== Hàm cập nhật ==========
void Encoder_Update(void)
{
    velocity = (rpm * circumference_mm) / (60 * 10); // cm/s
    total_distance = (counter * distance_per_pulse_mm) / 10; // cm
}

