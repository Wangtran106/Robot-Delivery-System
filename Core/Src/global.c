#include "global.h"

// Các biến toàn cục định nghĩa thật
double angle;
double targetAngle = 0;
bool isDriving = false;
bool prevIsDriving = false;
uint8_t r_data ;
//*----Động cơ trái-----*//
int leftSpeedVal1 ;
int leftSpeedVal2 ;
//*----Động cơ phải-----*//
int rightSpeedVal1;
int rightSpeedVal2;
int equilibriumSpeed = 100;
int target_distance = 30;

int distance_reference = 0;

//======HX711======//
int weight ;
//uint32_t tare = 8794099;
//float knownOriginal = 174000;
//float knownHX711 = 24796;

uint32_t tare = 8159350;
float knownOriginal = 174000;
float knownHX711 = 2147483647;
//*------Encoder-------*//
uint32_t counter = 0;
int speed = 0;
int rpm = 0;

uint16_t circumference_mm;
uint16_t distance_per_pulse_mm;

int velocity = 0;
uint32_t total_distance = 0;

const char* statusText = "KHOI DONG";

