# 🩺 AI-Enabled Patient Proximity & Comfort Monitoring System  
### ESP32 | Edge AI | Healthcare IoT

---

## 📌 Overview

This project presents a low-cost AI-enabled healthcare monitoring system built using an ESP32 microcontroller.

The system continuously monitors:

- patient proximity
- room temperature
- room humidity

and intelligently raises alerts when abnormal behaviour is detected.

Unlike conventional rule-based systems, this project integrates a lightweight online learning model that runs directly on the ESP32, enabling real-time anomaly detection without cloud connectivity.

---

## ✨ Key Features

- Patient proximity detection using ultrasonic sensor
- Temperature and humidity monitoring using DHT11
- Real-time status display on I2C LCD
- Buzzer-based alert system
- On-device AI using online anomaly detection
- No cloud or server dependency

---

## 🧠 AI Component (What makes this project unique)

A lightweight online statistical learning model is implemented on the ESP32.

It is used to:

- learn normal temperature behaviour
- learn normal humidity behaviour
- learn normal proximity behaviour
- adapt automatically to the surrounding environment
- detect abnormal patterns using an anomaly score

This allows the system to perform real-time edge intelligence without sending data to any external server.

---

## ⚙️ Hardware Components

- ESP32 development board
- HC-SR04 ultrasonic sensor
- DHT11 temperature and humidity sensor
- 16×2 I2C LCD display
- Active buzzer
- Breadboard and jumper wires

---

## 🔁 System Behaviour

- When the patient is within the monitoring zone  
  - Display: PATIENT IN – OK

- When the patient leaves the zone for a fixed duration  
  - Display: PATIENT OUT – ALERT

- When temperature or humidity exceeds the comfort threshold  
  - Display: BAD COMFORT

- When abnormal environmental or proximity behaviour is detected by the AI model  
  - Display: AI ALERT – ENV CHANGE

---

## 🧩 Software and Tools

- Arduino IDE
- ESP32 board support package
- Embedded C (Arduino framework)
- LiquidCrystal_I2C library
- DHT sensor library

---

## 📈 Applications

- Hospital ward patient monitoring
- Home-care safety systems
- Assisted living environments
- Smart healthcare IoT platforms

---

## 🚀 Future Enhancements

- Patient inactivity detection using movement variance
- Long-term data logging and visualization
- Wireless dashboard integration
- Comparison with cloud-based ML models

---


## ⭐ Note

This project demonstrates a hybrid embedded intelligence approach by combining:

- rule-based decision logic
- on-device online learning

for practical healthcare monitoring applications.
