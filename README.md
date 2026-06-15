#  IoT LED Control — ESP8266 + Firebase + Netlify

> Control a physical LED from anywhere in the world using your smartphone or browser — built with ESP8266, Firebase Realtime Database, and a hosted web interface on Netlify.

---

## Project Overview

This project is a **Remote IoT Control System** that allows a user to turn an LED ON or OFF from anywhere in the world through a web browser — without any port forwarding, static IP, or complex networking setup.

A friend in **Kano** or any state or country can control an LED physically located from anywhere in the world just by opening a webpage link!

---

##  System Architecture

```
Friend's Phone / Browser
        ↓
https://water-bender-led-control.netlify.app
        ↓
Firebase Realtime Database
   { "led": true/false }
        ↓
ESP8266 (polls every 500ms)
        ↓
LED turns ON / OFF 
```

---

## How It Works

1. The **ESP8266** connects to WiFi and authenticates with Firebase using a Database Secret
2. It **polls** (checks) the Firebase Realtime Database every **500 milliseconds**
3. A user opens the **hosted webpage** on Netlify from anywhere in the world
4. When the user clicks **TURN ON**, the webpage writes `{ "led": true }` to Firebase
5. The ESP8266 reads the new value and sets pin **D2 HIGH**, turning the LED ON
6. When the user clicks **TURN OFF**, Firebase updates to `{ "led": false }` and the LED turns OFF

---

## 🛠️ Technologies Used

| Technology | Role |
|---|---|
| **ESP8266 (NodeMCU)** | Microcontroller — reads Firebase and controls LED |
| **Firebase Realtime Database** | Cloud database — stores LED state (true/false) |
| **Netlify** | Web hosting — serves the control webpage publicly |
| **Arduino IDE** | Used to write and flash code to ESP8266 |
| **HTML / CSS / JavaScript** | Frontend control panel |
| **Firebase JS SDK** | Connects the webpage to Firebase |

---

##  Components Required

| Component | Quantity |
|---|---|
| ESP8266 NodeMCU | 1 |
| LED | 1 |
| Jumper Wires | Few |
| USB Cable (for flashing) | 1 |

---

## Circuit Diagram

```
ESP8266 Pin D2  ────  LED (+) long leg
ESP8266 GND     ────────────────────────→  LED (-) short leg
```

---

##  Getting Started

### 1. Clone this Repository

```bash
git clone https://github.com/mansurmadaki111-rgb/iot-led-control.git
cd iot-led-control
```

---

### 2. Firebase Setup

1. Go to [console.firebase.google.com](https://console.firebase.google.com)
2. Create a new project (e.g. `iot-led-control` or any other name)
3. Go to **Build → Realtime Database → Create Database**
4. Select **Test Mode** and click **Enable**
5. Add this data manually:
```json
{
  "led": false
}
```
6. Go to **Project Settings → Service Accounts → Database Secrets**
7. Copy your **Database Secret**

---

### 3. Arduino IDE Setup

#### Install Required Libraries:
- Open Arduino IDE
- Go to **Sketch → Include Library → Manage Libraries**
- Search and install: `Firebase Arduino Client Library for ESP8266 and ESP8266` by **Mobizt**

#### Flash the ESP8266:

Open `esp8266 code/iot-led-control.ino` and fill in your credentials:

```cpp
#define WIFI_SSID       "YOUR_WIFI_NAME"
#define WIFI_PASSWORD   "YOUR_WIFI_PASSWORD"
#define DATABASE_URL    "https://your-project-default-rtdb.firebaseio.com"
#define DATABASE_SECRET "YOUR_DATABASE_SECRET"
```

Upload the code to your ESP8266 and open **Serial Monitor at 115200 baud**.

You should see:
```
WiFi Connected!
IP Address: 192.168.x.x
Firebase Connected!
LED is: OFF
```

---

### 4. Web Interface Setup

The webpage is inside the `webpage/` folder.

Open `webpage/index.html` and update the Firebase config:

```javascript
const firebaseConfig = {
  apiKey:            "YOUR_API_KEY",
  authDomain:        "your-project.firebaseapp.com",
  databaseURL:       "https://your-project-default-rtdb.firebaseio.com",
  projectId:         "your-project-id",
  storageBucket:     "your-project.appspot.com",
  messagingSenderId: "YOUR_SENDER_ID",
  appId:             "YOUR_APP_ID"
};
```

---

### 5. Deploy to Netlify

1. Go to [netlify.com](https://netlify.com) and sign up
2. On the dashboard scroll down to **"Drag and drop your site folder here"**
3. Drag and drop the `webpage/` folder
4. Netlify gives you a public link like:
```
https://your-site-name.netlify.app
```
5. Share this link with anyone — they can now control your LED from anywhere! 

---

##  Project Structure

```
iot-led-control/
├── webpage/
│   └── index.html        # Web control panel
├── esp8266 code/
│   └── iot-led-control.ino          # Arduino code for ESP8266
└── README.md             # Project documentation
```

---

## Security Note

>  This project uses Firebase in **Test Mode** which means anyone with the link can control the LED. For a production project, add Firebase Security Rules:

```json
{
  "rules": {
    ".read": "auth != null",
    ".write": "auth != null"
  }
}
```

This ensures only authenticated users can read and write to the database.

---

##  Live Demo

>  [https://water-bender-led-control.netlify.app](https://water-bender-led-control.netlify.app)

---

##  Future Improvements

- [ ] Add Firebase Authentication for security
- [ ] Control multiple LEDs from the same webpage
- [ ] Add real-time feedback (confirm LED actually turned ON)
- [ ] Replace polling with WebSockets for instant response
- [ ] Add temperature/humidity sensor readings
- [ ] Build a full Smart Home dashboard
- [ ] Add mobile app using Flutter or MIT App Inventor

---

##  Author

**Mansur Isah**
- GitHub: [@mansurmadaki111](https://github.com/mansurmadaki111-rgb)
- Project: IoT LED Control System
- Stack: ESP8266 · Firebase · Netlify · Arduino · JavaScript

---

##  License

This project is licensed under the **MIT License** — feel free to use, modify and share it!

---

##  Acknowledgements

- [Firebase](https://firebase.google.com) — for the free Realtime Database
- [Netlify](https://netlify.com) — for free web hosting
- [Mobizt](https://github.com/mobizt) — for the Firebase ESP8266 Arduino library
- [Arduino](https://arduino.cc) — for the open source IDE

---

> *"From a simple LED to a full IoT system — one line of code at a time."* 
