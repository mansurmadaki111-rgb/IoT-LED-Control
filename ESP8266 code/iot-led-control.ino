#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// ============================================
#define WIFI_SSID "YOUR-WIFI-NAME"// Replace this line with your WiFi name
#define WIFI_PASSWORD "YOUR-WIFI-PASSWORD"// Replace this line with your WiFi 
#define DATABASE_URL "https://your-project-default-rtdb.firebaseio.com"
#define DATABASE_SECRET "YOUR_DATABASE_SECRET"  
// ============================================

#define LED_PIN D2

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool ledState = false;
unsigned long sendDataPrevMillis = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.println("WiFi Connected!");

  // Configure Firebase with database secret
  config.database_url = DATABASE_URL;
  config.signer.tokens.legacy_token = DATABASE_SECRET;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  Serial.println("Firebase Connected!");
}

void loop() {
  if (Firebase.ready()) {
    if (millis() - sendDataPrevMillis > 500 || sendDataPrevMillis == 0) {
      sendDataPrevMillis = millis();

      if (Firebase.RTDB.getBool(&fbdo, "/led")) {
        ledState = fbdo.boolData();
        digitalWrite(LED_PIN, ledState ? HIGH : LOW);
        Serial.print("LED is: ");
        Serial.println(ledState ? "ON" : "OFF");
      } else {
        Serial.println("Failed to read from Firebase");
        Serial.println(fbdo.errorReason());
      }
    }
  }
}
