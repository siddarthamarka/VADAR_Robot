# 🚗 VADAR: Vehicle Accident Detection with Analytics and Response

A cutting-edge IoT-based safety system designed to detect vehicular accidents in real-time, capture contextual video evidence, and immediately notify emergency responders with precise GPS location — revolutionizing post-crash response and insurance forensics.


## 🔍 Overview

VADAR is an intelligent accident detection system that integrates sensing, communication, and video logging in one compact embedded platform. It goes beyond traditional alert systems by capturing a 20-second video of the accident scene via an ESP32-CAM and uploading it directly to Google Drive for secure storage and further analysis.

This project empowers:
- 🚑 Emergency teams with rapid location-based alerts
- 📹 Insurance providers with real-time incident video
- 🚘 Vehicle occupants with better post-incident support


## 🧠 Features

- ✅ Real-time accident detection using ultrasonic sensor
- 🌐 GPS-based geolocation with NEO-6M GPS module
- 📲 Automatic emergency SMS using SIM800L GSM module
- 🎥 20-second contextual video logging with ESP32-CAM
- ☁️ Seamless video upload to Google Drive via Apps Script
- 🔋 Battery-efficient, modular and robust architecture


## ⚙️ Hardware Used

| Component        | Purpose                            |
|------------------|-------------------------------------|
| Arduino Uno      | Main controller for sensing logic   |
| SIM800L          | Sends SMS alerts on accident        |
| NEO-6M GPS       | Provides precise accident location  |
| HC-SR04          | Detects sudden proximity drop       |
| ESP32-CAM        | Records and uploads video evidence  |
| Servo Motor      | Rotates ultrasonic sensor (180°)    |
| TT Motors + L298N| Robot movement and control          |
| Li-Ion Battery   | Portable power source               |


## 🏗️ Architecture

1. Detection Phase: Ultrasonic sensor monitors distance in real-time.
2. Trigger Phase: If critical threshold is breached, it is considered a crash.
3. Response Phase:
    - SMS with GPS location is sent to emergency contact.
    - ESP32-CAM captures and stores a 20-second video.
    - Video is uploaded to cloud (Google Drive).
4. Recovery Phase: Returns to monitoring state.


## 📂 Folder Structure

VADAR_Project/
├── arduino/
│ └── vadar_main.ino # Arduino Uno logic
├── esp32-cam/
│ ├── camera_capture_and_upload.ino # ESP32 video upload logic
│ └── config.h # WiFi and Drive settings
├── google_drive_script/
│ └── Code.gs # Google Apps Script
├── docs/
│ ├── CircuitDiagram.png
│ └── VADAR_UserGuide.pdf
└── README.md # This file


## 🚀 Getting Started

### 1. 🧠 Arduino Setup
- Upload `vadar_main.ino` to Arduino Uno using Arduino IDE
- Connect HC-SR04, GPS, and GSM as per circuit diagram

### 2. 🎥 ESP32-CAM Setup
- Upload `camera_capture_and_upload.ino` using ESP32 board manager
- Update Wi-Fi credentials and Google Drive WebApp URL in `config.h`

### 3. ☁️ Google Drive Integration
- Open [Google Apps Script](https://script.google.com)
- Paste `Code.gs` and deploy as Web App
- Set permissions to "Anyone" and copy the `exec` URL
- Replace `DRIVE_UPLOAD_URL` in `config.h`

### 4. ⚡ Powering Up
- Power ESP32-CAM (5V@2A), Arduino (7–12V) separately
- Test crash scenario by placing obstacle close to ultrasonic sensor


## 🧪 Results Snapshot

| Metric            | Result                          |
|-------------------|---------------------------------|
| Detection Accuracy| 98% (24/25 test cases)          |
| SMS Delay         | ~6.8 seconds                    |
| Video Upload Time | 15–25 seconds                   |
| GPS Accuracy      | ±5 meters                       |

All video clips are tagged with timestamp and location metadata for insurance/legal review.

## 💡 Future Enhancements

- AI-based crash severity detection on ESP32
- Voice-triggered alerts or deactivation
- Real-time navigation aid to ambulances
- Integration with hospital databases for auto-alerts
