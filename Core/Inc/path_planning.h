/*
 * path_planning.h
 *
 *  Created on: May 11, 2025
 *      Author: Wangtran
 */

#ifndef INC_PATH_PLANNING_H_
#define INC_PATH_PLANNING_H_

#include <stdint.h>
#include <stdbool.h>
#include "global.h"

// Enum định nghĩa các trạng thái robot
typedef enum {
    STATE_IDLE,
    STATE_WAIT_BLUETOOTH,   // [CHỜ LỆNH BLUETOOTH]
    STATE_WAIT_NEXT_ROUTE,  // [CHỜ LỆNH BLUETOOTH LẠI]
	STATE_ERROR_DROP,       // Nếu Hàng rơi
//========Tuyến B========//
	//*---Chiều đi---*//
    STATE_WAIT_PACKAGE_B,     // [CHỜ HÀNG]
	STATE_WAIT_UNLOAD_B,      // [CHỜ GIAO HÀNG]
    STATE_RETURNING_B,        // [QUAY VỀ]
    STATE_B_FORWARD,
    STATE_B_LEFT,
    STATE_B_FORWARD_2,
	//*---Chiều về---*//
    STATE_B_BACKWARD,
    STATE_B_RIGHT,
    STATE_B_BACKWARD_2,
//========Tuyến C========//
	//*---Chiều đi---*//
    STATE_WAIT_PACKAGE_C,     // [CHỜ HÀNG]
	STATE_WAIT_UNLOAD_C,      // [CHỜ GIAO HÀNG]
    STATE_RETURNING_C,        // [QUAY VỀ]
    STATE_C_FORWARD,
    STATE_C_RIGHT,
    STATE_C_FORWARD_2,
	//*---Chiều về---*//
    STATE_C_BACKWARD,
    STATE_C_LEFT,
    STATE_C_BACKWARD_2

} RobotState;

typedef enum {
    ROUTE_B,
    ROUTE_C,
    ROUTE_NONE
} RouteID;

// Biến trạng thái toàn cục
extern RobotState state;
extern RouteID currentRoute;

// Prototype cho hàm xử lý state
void HandleRouteA(void);
void HandleRouteB(void);
void HandleRouteC(void);
void State(void);

#endif /* INC_PATH_PLANNING_H_ */
