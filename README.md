# Robot Delivery - Autonomous Delivery Robot System (STM32)

![Banner](robot_delivery_banner_1778305712871.png)

## Project Overview
The **Robot Delivery** project is an autonomous robot system built on the **STM32F103C8T6 (Blue Pill)** microcontroller platform. The robot is designed to perform automated delivery tasks in a defined environment, utilizing **Mecanum wheels** for omnidirectional movement and an intelligent sensor system for navigation, obstacle avoidance, and cargo management.

This project is not just about motor control; it integrates advanced signal processing from an IMU, PID algorithms, and a complex Finite State Machine (FSM).

---

## Key Features
- **Omnidirectional Movement:** Uses 4 Mecanum wheels allowing the robot to move forward, backward, sideways, and rotate on the spot with extreme flexibility.
- **Precision Navigation (PID Control):** Combines the **MPU6050** (Gyroscope/Accelerometer) with a **PID** algorithm to maintain accurate heading and automatically compensate for drift.
- **Odometry & Tracking:** Uses high-resolution **Encoders** to monitor velocity and calculate the precise distance traveled.
- **Intelligent Cargo Management:** Integrated **HX711 (Load Cell)** to detect cargo presence, confirm loading/unloading, and trigger alerts if the cargo is dropped during transit.
- **Safety & Obstacle Avoidance:** Uses an **HC-SR04** ultrasonic sensor for emergency stops when obstacles are detected in the path.
- **Wireless Communication:** Remote control and status monitoring (speed, distance, error logs) via **Bluetooth**.

---

## Hardware Components
| Component | Description | Role |
| :--- | :--- | :--- |
| **STM32F103C8T6** | Main Microcontroller | Central processing, PWM control, sensor reading |
| **Mecanum Wheels** | Movement System | 360-degree movement without turning the chassis |
| **L298N/L293D/TB6612** | Motor Drivers | Power control for 4 DC motors |
| **MPU6050** | 6-axis IMU | Directional stability and yaw control |
| **HC-SR04** | Ultrasonic Sensor | Front-facing obstacle detection |
| **HX711 + Load Cell** | Force Sensor | Cargo weight measurement and delivery logic |
| **Encoder** | Speed Sensor | Real-time distance and velocity feedback |
| **HC-05/HC-06** | Bluetooth Module | Command reception and status reporting |

---

## Software Architecture
The project is developed in C using **STM32CubeIDE** and the HAL library.

### Finite State Machine (FSM)
The robot operates based on a robust state machine:
1. **STATE_WAIT_BLUETOOTH:** Waiting for route selection command (Route B or Route C).
2. **STATE_WAIT_PACKAGE:** Waiting for the user to load the package (detected by Load Cell).
3. **STATE_FORWARD/LEFT/RIGHT:** Executing movement steps according to the pre-programmed route.
4. **STATE_WAIT_UNLOAD:** Stopping at the destination, waiting for the recipient to pick up the item.
5. **STATE_RETURNING:** Automatically returning to the starting point after unloading.
6. **STATE_ERROR_DROP:** Emergency stop and alert if the cargo is dropped mid-route.

### PID Algorithm
The `controlSpeedStraight()` function utilizes a PID controller to maintain the `targetAngle`:
- **P (Proportional):** Immediate response to heading errors.
- **I (Integral):** Eliminates steady-state errors over time.
- **D (Derivative):** Dampens oscillations for smoother directional corrections.

---

## Contact
- **Author:** [Wangtran106]
- **Email:** [trandinhquang011@gmail.com]
- **Project:** Robot Delivery System v1.0
