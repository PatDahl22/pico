# Fall Alarm System – Embedded Prototypes (Pico 2 W)

This repository contains a series of embedded system exercises implemented on **Raspberry Pi Pico 2 W**, used as prototypes for a Fall Alarm IoT system.

Each branch demonstrates a key embedded concept that is later applicable to a full **Edge–Fog architecture**.

---

# Branch Overview

| Branch | Description |
|------|------------|
| blink | Basic LED test |
| log | Serial logging via USB |
| btn | Button input (polling) |
| interrupt | Button handling using interrupts |
| queue | Event queue system for ISR safety |
| watchdog | System recovery using watchdog timer |
| wifi | Wi-Fi connection and communication |

---

# System Architecture

              [ Sensors & Inputs ]
              ├── Accelerometer (fall detection)
              ├── Pulse / SpO2 sensor
              ├── Temperature sensor
              ├── Button (manual trigger)
              │
              ▼

| +------------------+---------------+ |
| Edge Device (Pico 2 W Prototype)     |
| ------------------------------------ |
| Interrupt handling                   |
| Queue system                         |
| Signal processing                    |
| Logging (USB serial)                 |
| Watchdog safety                      |
| Wi-Fi communication                  |
| +------------------+---------------+ |

               |
               | MQTT / Wi-Fi
               ▼

| +------------------+---------------+ |
| Fog Node (Raspberry Pi Zero 2W)      |
| ------------------------------------ |
| MQTT Broker                          |
| Device management                    |
| Alarm processing                     |
| SQLite (encrypted)                   |
| +------------------+---------------+ |

               |
               ▼
     [ Alert / Notification ]


---

# Key Embedded Concepts

## 🔹 Interrupts
Used to detect events (e.g., button press) instantly without polling.

## 🔹 Queue
Interrupts push events into a queue.  
Main loop processes them safely.

## 🔹 Watchdog
Automatically resets the system if it becomes unresponsive.

## 🔹 Logging
USB serial output for debugging and system status.

## 🔹 Wi-Fi
Connects device to network and enables communication with server.

---

# Testing with PuTTY

To enable serial output:

### In code:
`c
stdio_init_all();

### In CMake:
pico_enable_stdio_usb(${PROJECT_NAME} 1)

### PuTTY settings:
🔹 Connection type: Serial
🔹 Speed: 115200
🔹 Correct COM port

---

# Known Behaviors

## 🔹 Watchdog reset disconnects USB → PuTTY may show error

## 🔹 Serial output may be missed if PuTTY opens too late

## 🔹 Button input uses pull-up → active LOW

---

# Fall Alarm Relevance

| +------------------+---------------+ |
| Component | Purpose                   |
| --------- | ------------------------- |
| Interrupt | Fast reaction to events   |
| Queue     | Safe event handling       |
| Watchdog  | System reliability        |
| Wi-Fi     | Sends alarm data          |
| Logging   | Debug + status monitoring |
| +------------------+---------------+ |

---

# Summary

## 🔹 This project demonstrates how to build a robust embedded system using:

🔹 Event-driven design
🔹 Real-time handling
🔹 Fault recovery
🔹 Wireless communication

## 🔹 These concepts form the foundation of a reliable fall detection system.







