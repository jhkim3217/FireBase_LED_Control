

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "ledcontrol-e3123xxx.firebaseio.com" 
#define FIREBASE_AUTH "CNhyOnwUd0DPpPiks8T4W7455T3aGiBA8rAp5QePxxx"

//#define WIFI_SSID "ID"
//#define WIFI_PASSWORD "PWD"

#define LED D4
//#define LED 2

void setup() 
{
   Serial.begin(57600);
//    Serial.begin(115200);
//    Serial.begin(9600);
    
    setupWifi();
    setupFirebase();
    setupPinsMode();
}

void loop() 
{
  
  if(Firebase.getInt("LEDStatus"))
  {
      digitalWrite(LED,HIGH);
      Serial.println(Firebase.getInt("LEDStatus"));
  } 
  else  
  {
      digitalWrite(LED,LOW);
      Serial.println(Firebase.getInt("LEDStatus"));
  }
  
  if (Firebase.failed()) // Check for errors 
  {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());
      return;
  }
  
  delay(1000);
}

/////////////////////////////////////////////////
void setupWifi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("Hey I'm connecting...");
    Serial.println(WiFi.status());

    while (WiFi.status() != WL_CONNECTED) {
      Serial.println(".");
      delay(500);
    }

    Serial.println();
    Serial.println("I'm connected and my IP address: ");
    Serial.println(WiFi.localIP());
}

void setupFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void setupPinsMode() {
   pinMode(LED,OUTPUT);
   Firebase.setInt("LEDStatus",0); 
}


