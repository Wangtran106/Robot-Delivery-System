/*
 * hx711.h
 *
 *  Created on: May 16, 2025
 *      Author: Wangtran
 */

#ifndef INC_HX711_H_
#define INC_HX711_H_

#include "main.h"

#define DT_PIN GPIO_PIN_13
#define DT_PORT GPIOC
#define SCK_PIN GPIO_PIN_14
#define SCK_PORT GPIOC

void HX711_Init(void);
int weigh(void);

#endif /* INC_HX711_H_ */
