/*
 * bluetooth_transmitter.h
 *
 *  Created on: May 10, 2025
 *      Author: Wangtran
 */

#ifndef INC_BLUETOOTH_TRANSMITTER_H_
#define INC_BLUETOOTH_TRANSMITTER_H_

#include "main.h"
#include "HCSR04.h"
#include "global.h"

void Bluetooth_SendStatus(const char* statusText, uint16_t Distance);

#endif /* INC_BLUETOOTH_TRANSMITTER_H_ */
