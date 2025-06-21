# LoRa-Distance-Transmission
LoRa-powered ultrasonic distance sensing with ESP8266 — tested up to 600m with visual connection feedback

A practical project exploring long-range wireless communication using LoRa SX1278 (433 MHz) modules paired with a waterproof ultrasonic sensor and ESP8266 boards.

📦 Project Overview
This project demonstrates transmitting real-time distance data from an ultrasonic sensor over LoRa, monitoring the range and reliability under real-world conditions.

Bonus:
An LED indicator on the receiver side acts as a visual connection status indicator — it stays ON as long as valid packets are received.

🔧 Hardware Used
2 × LoRa SX1278 (433 MHz) modules

2 × ESP8266 (NodeMCU)

1 × Waterproof Ultrasonic Sensor (JSN-SR04T)

433 MHz quarter-wave whip/SMA antennas

LED + 220Ω resistor (for RX indicator)

Breadboard / Zero PCB

5V Power Source

📖 Features
Real-time ultrasonic distance measurement

Long-range LoRa communication (tested up to 600 meters)

Visual connection indicator using an LED

SPI protocol interfacing between ESP8266 and LoRa

Adjustable LoRa parameters for optimizing range
