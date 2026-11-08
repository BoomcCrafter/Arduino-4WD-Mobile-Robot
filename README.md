
# Arduino 4WD Mobile Robot 🚗

A custom-built autonomous mobile robot designed using **Autodesk Inventor**, manufactured with **3D printing**, and programmed with **Arduino Uno**.

The robot uses four DC motors, two BTS7960 motor drivers, and three HC-SR04 ultrasonic sensors to navigate and avoid obstacles.

## Features

- Custom-designed 3D-printed chassis and components
- Four-wheel drive (4WD) with differential steering
- PWM motor speed control
- Three ultrasonic distance sensors
- Automatic obstacle detection and avoidance
- Autonomous navigation using rule-based algorithms

## Hardware

| Component | Quantity |
|---|---|
| Arduino Uno | 1 |
| DC geared motors 12 V | 4 |
| BTS7960 motor drivers | 2 |
| HC-SR04 ultrasonic sensors | 3 |
| Battery 12 V | 1 |
| DC-DC converter 12 V / 5 V | 1 |

## Arduino Programs

The project includes four Arduino programs demonstrating different stages of robot development:

1. **Basic Movements** — forward, backward, turning and PWM control.
2. **Obstacle Detection** — automatic stopping before obstacles.
3. **Obstacle Avoidance** — choosing a direction based on sensor measurements.
4. **Autonomous Driving** — continuous navigation, speed adjustment and obstacle avoidance.

📂 [Arduino source code](arduino/)

## 3D Models

All mechanical components are available in three formats:

- [STL](3d_models/STL/) — ready for 3D printing
- [IPT](3d_models/IPT/) — Autodesk Inventor source files
- [STEP](3d_models/STEP/) — compatible with various CAD programs

## Assembly Instructions

The repository contains a **48-page illustrated assembly manual**, documenting the mechanical construction, electronics and wiring.

📖 [View Assembly Manual (PDF)](documentation/StworzRobota_instrukcja_montazu_kompresja.pdf)

📷 [Robot Photos](images/)

## Technologies

**Arduino • C++ • Autodesk Inventor • CAD • 3D Printing • Electronics • Mobile Robotics**

## About the Project

This project combines mechanical design, embedded programming and electronics into a complete mobile robotic platform.

The robot was designed, assembled and programmed as a practical engineering project. AI tools assisted in preparing the assembly documentation.

The autonomous navigation uses classical rule-based control rather than machine learning.
