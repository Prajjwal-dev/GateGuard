# GateGuard 🚪🔒

## Overview  
**GateGuard** is an Arduino-based RFID access control system designed for secure and automated gate management. Built using the **MFRC522 RFID module**, **servo motor**, **I2C LCD display**, and a **5V buzzer**, it provides a simple yet effective way to verify identity and control physical access.

Originally developed as a microcontroller project, GateGuard ensures that only authorized RFID cards can trigger gate access, with real-time status updates and buzzer alerts.

## Key Features  
- 📶 **RFID Authentication**: Scans MFRC522 RFID tags to verify access.  
- ⚙️ **Automated Gate Control**: Uses a servo motor to open/close the gate for authorized users.  
- 📟 **Real-Time Display**: I2C LCD shows system status and access messages.  
- 🔊 **Audio Alerts**: 5V buzzer gives feedback on card acceptance or denial.  
- ✅ **Secure and Efficient**: Ensures only registered IDs gain access, enhancing security.

## Technical Details  
- **Platform**: Arduino UNO  
- **Modules Used**:
  - MFRC522 RFID Reader  
  - Servo Motor  
  - I2C LCD Display (16x2)  
  - 5V Buzzer  
- **Programming Language**: C++ (Arduino)

## Repository  
- **GitHub**: [Prajjwal-dev/GateGuard](https://github.com/Prajjwal-dev/GateGuard)  

## Project Structure  
The project is organized into the following components:

- **CardScanner**: Handles RFID card scanning and UID matching  
- **ServoControl**: Controls servo motor based on access status  
- **LCDManager**: Displays system messages using I2C LCD  
- **BuzzerAlert**: Activates buzzer on specific events  
- **Main Logic**: Coordinates the access flow and integrates all modules

## Installation and Usage  
1. Clone the repository:
   ```bash
   git clone https://github.com/Prajjwal-dev/GateGuard.git
