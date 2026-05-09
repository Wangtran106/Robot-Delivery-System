#include "path_planning.h"
#include "main.h"
#include "global.h"
#include "encoder.h"
#include "navigation.h"
#include "hx711.h"
#include "HCSR04.h"
#include "motor.h"
#include "bluetooth_receiver.h"
#include "bluetooth_transmitter.h"
RobotState state = STATE_IDLE;
RouteID currentRoute = ROUTE_NONE;



void HandleRouteB(void){
	switch (state) {
		case STATE_B_FORWARD:
			if (isDriving) {
				statusText = "ĐANG GIAO HÀNG đến trạm B";
				goStraight(60);

			} else {
				distance_reference = total_distance;
				isDriving = true;
				state = STATE_B_LEFT;
			}
			break;

		case STATE_B_LEFT:
			if (isDriving) {
				goSideWayLeft(60);
			} else {
				distance_reference = total_distance;
				isDriving = true;
				state = STATE_B_FORWARD_2;
			}
			break;
		case STATE_B_FORWARD_2:
			if (isDriving) {
				goStraight(30);
			} else {
				distance_reference = total_distance;
				isDriving = true;
				Motor_Stop();
				HAL_Delay(2000);
				statusText = "ĐÃ TỚI trạm B , Vui lòng lấy hàng!!!";
				state = STATE_WAIT_UNLOAD_B;
			}
			break;
		case STATE_B_BACKWARD:
			if (isDriving) {
				statusText = "ĐANG TRỞ LẠI điểm bắt đầu";
				goBackward(30);
			} else {
				distance_reference = total_distance;
				isDriving = true;
				state = STATE_B_RIGHT;
			}
			break;
		case STATE_B_RIGHT:
			if (isDriving) {
				goSideWayRight(60);
			} else {
				distance_reference = total_distance;
				isDriving = true;
				state = STATE_B_BACKWARD_2;
			}
			break;
		case STATE_B_BACKWARD_2:
			if (isDriving) {
				goBackward(60);
			} else {
				distance_reference = total_distance;
				isDriving = true;
				state = STATE_WAIT_NEXT_ROUTE;
			}
			break;
        default:
            break;
	}
}

void HandleRouteC(void) {
	switch (state) {
		case STATE_C_FORWARD:
			if (isDriving) {
				statusText = "ĐANG GIAO HÀNG đến trạm C";
				goStraight(30);
			} else {
				distance_reference = total_distance;
				isDriving = true;
				state = STATE_C_RIGHT;
			}
			break;

		case STATE_C_RIGHT:
			if (isDriving) {
				goSideWayRight(60);
			} else {
				distance_reference = total_distance;
				isDriving = true;
				state = STATE_C_FORWARD_2;
			}
			break;
		case STATE_C_FORWARD_2:
			if (isDriving) {
				goStraight(30);
			} else {
				distance_reference = total_distance;
				isDriving = true;
				Motor_Stop();
				HAL_Delay(2000);
				statusText = "ĐÃ TỚI trạm B , Vui lòng lấy hàng!!!";
				state = STATE_WAIT_UNLOAD_C;
			}

			break;
		case STATE_C_BACKWARD:
			if (isDriving) {
				statusText = "ĐANG TRỞ LẠI điểm bắt đầu";
				goBackward(30);
			} else {
				distance_reference = total_distance;
				isDriving = true;
				state = STATE_C_LEFT;
			}
			break;
		case STATE_C_LEFT:
			if (isDriving) {
				goSideWayLeft(60);
			} else {
				distance_reference = total_distance;
				isDriving = true;
				state = STATE_C_BACKWARD_2;
			}
			break;
		case STATE_C_BACKWARD_2:
			if (isDriving) {
				goBackward(30);
			} else {
				distance_reference = total_distance;
				isDriving = true;
				state = STATE_WAIT_NEXT_ROUTE;
			}
			break;
        default:
            break;
	}
}

void State(void) {
	switch (state) {
		case STATE_WAIT_PACKAGE_B:
			if (weight > 150000) {
				switch (currentRoute) {
					case ROUTE_B: state = STATE_B_FORWARD; break;
					default: break;
				}
				isDriving = true;
			}
			break;

		case STATE_WAIT_UNLOAD_B:
			if (weight < 150000) {
				state = STATE_RETURNING_B;
				isDriving = true;
			}
			break;

		case STATE_RETURNING_B:
			switch (currentRoute) {
				case ROUTE_B: state = STATE_B_BACKWARD; break;
				default: break;
			}
			isDriving = true;
			break;
			case STATE_WAIT_PACKAGE_C:
				if (weight > 150000) {
					switch (currentRoute) {
						case ROUTE_C: state = STATE_C_FORWARD; break;
						default: break;
					}
					isDriving = true;
				}
				break;

			case STATE_WAIT_UNLOAD_C:
				if (weight < 150000) {
					state = STATE_RETURNING_C;
					isDriving = true;
				}
				break;

			case STATE_RETURNING_C:
				switch (currentRoute) {
					case ROUTE_C: state = STATE_C_BACKWARD; break;
					default: break;
				}
				isDriving = true;
				break;

			case STATE_WAIT_NEXT_ROUTE:
				state = STATE_WAIT_BLUETOOTH;
			break;

		default:
			switch (currentRoute){
				case ROUTE_B : HandleRouteB(); break;
				case ROUTE_C : HandleRouteC(); break;
				default: break;
			}
			break;
	}
}
