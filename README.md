# 📘 LCD Control Module using ESP32 (16x2 Character LCD)

## 🎯 Objective
This project demonstrates how to interface a 16x2 HD44780-based LCD with an ESP32 microcontroller using **ESP-IDF**. The LCD is operated in 4-bit mode, and all control is done via low-level GPIO logic — no prebuilt LCD libraries are used.

---

## 🧠 Features

- ✅ LCD Initialization in 4-bit mode
- ✅ Custom display message: **"Melvin Joshua"**
- ✅ Modular code (lcd.h / lcd.c)
- ✅ Scrolling (optional feature)

---

## 🛠️ Hardware Required

- ESP32 Dev Board
- 16x2 LCD Display (HD44780)
- Breadboard
- Jumper Wires
- USB Cable for ESP32
- 220Ω 10kΩ Resistor (for contrast control)

---

## ⚙️ Wiring Instructions

### 📌 LCD Pinout and ESP32 Connections

| LCD Pin | Name  | Connect To        |
|---------|--------|-------------------|
| 1       | VSS   | ESP32 GND         |
| 2       | VDD   | ESP32 5V          |
| 3       | VO    | GND 10kΩ resistor |
| 4       | RS    | GPIO4           |
| 5       | RW    | GND               |
| 6       | EN    | GPIO5            |
| 11      | D4    | GPIO18            |
| 12      | D5    | GPIO19            |
| 13      | D6    | GPIO21            |
| 14      | D7    | GPIO22            |
| 15      | LED+  | 5V 220Ω resistor |
| 16      | LED-  | ESP32 GND         |

> ✅ **Important Notes**:
- **Do not connect VO (pin 3) directly to GND.** Use a **10kΩ resistor** to control contrast.
- Always connect **RW (pin 5)** to **GND** for write-only operation.
- Supply **5V to LCD VCC and LED+**. Using 3.3V may cause dim or no display.

---

## 🧑‍💻 How to Use

### Step 1: Clone & Open Project
git clone https://github.com/yourusername/esp-lcd.git
cd esp-lcd

### Step 2: Build the Project
idf.py build

### Step 3: Flash to ESP32
idf.py -p /dev/ttyUSB0 flash monitor

### Step 4: Output
If wired correctly and flashed successfully, the LCD will display:
Melvin Joshua 

---

🧭 Expected Output
On power-up: LCD backlight ON

After init: "Melvin Joshua" appears on row 1

No random symbols if properly grounded and powered

-----

📸 Output Pictures and Video 
Circuit conncetion picture
![LCD Output](https://github.com/melvinjoshua-emblock/esp32-lcd-drive/blob/71609fe1e5abb49ab01d52949db0abef8ff01380/Connection%20setup.jpg)

LCD display output 
![LCD Output](https://github.com/melvinjoshua-emblock/esp32-lcd-drive/blob/71609fe1e5abb49ab01d52949db0abef8ff01380/LCD%20txt%20.jpg)

LCD display output video
![LCD Output](https://github.com/melvinjoshua-emblock/esp32-lcd-drive/blob/71609fe1e5abb49ab01d52949db0abef8ff01380/Video%20of%20LCD%20text.mp4)

----
## 🔧 Troubleshooting

| **Symptom**             | **Possible Cause**                     | **Solution**                                         |
|------------------------|----------------------------------------|------------------------------------------------------|
| Blocks (▒▒▒▒▒) only     | Contrast too high or low               | Use 2.2kΩ resistor to VO (pin 3)                     |
| Random characters       | Incorrect timing or floating RW pin   | Ground RW (pin 5)                                    |
| Nothing displays        | LCD not powered or improper wiring    | Check VCC/GND and data pin order                     |
| Dim display             | Using 3.3V instead of 5V               | Use USB 5V from ESP32 VIN pin                        |

-----

✅ Author

Melvin Joshua

Embedded Systems Intern

April 2025
