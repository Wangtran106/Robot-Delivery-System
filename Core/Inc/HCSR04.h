#ifndef __HCSR04_H__
#define __HCSR04_H__

#include "main.h"
#include "tim.h"

// Định nghĩa chân Trig và Echo
#define TRIG_PIN    GPIO_PIN_14
#define TRIG_PORT   GPIOB
#define ECHO_PIN    GPIO_PIN_13
#define ECHO_PORT   GPIOB

extern uint32_t Value1 ;
extern uint32_t Value2 ;
extern uint32_t pMillis ;
extern uint16_t Distance ;

// Prototype
void HCSR04_Init();
void HCSR04_Read(void);

#endif /* __HCSR04_H__ */
