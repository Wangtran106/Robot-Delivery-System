#ifndef GLOBAL_H
#define GLOBAL_H

#include "stm32f1xx_hal.h"
#include <stdbool.h>



// Các biến toàn cục
extern double angle, targetAngle;
extern bool isDriving;
extern uint8_t r_data;
//*----Động cơ trái-----*//
extern int leftSpeedVal1 ;
extern int leftSpeedVal2 ;
//*----Động cơ phải-----*//
extern int rightSpeedVal1;
extern int rightSpeedVal2;

extern int equilibriumSpeed;
extern bool isFinish;
extern bool finishRoute;
extern int target_distance;

extern int distance_reference ;
//======HX711======//
extern int weight;
extern uint32_t tare;
extern float knownOriginal;
extern float knownHX711;
//*------Encoder-------*//
#define PULSES_PER_REV 20
#define WHEEL_DIAMETER_MM 65
#define PI_TIMES_100 314  // π x 100
extern uint32_t counter;
extern int speed;
extern int rpm;

extern uint16_t circumference_mm;
extern uint16_t distance_per_pulse_mm;
extern int velocity;
extern uint32_t total_distance;

extern const char* statusText;

#endif
