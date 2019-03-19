#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiUdp.h>
#include "credentials.h"

#define REDPIN 12
#define GREENPIN 14
#define BLUEPIN 13

#define LED_BUILTIN 2

const char* ssid = WIFI_SSD;
const char* password = WIFI_PWD;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(GREENPIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(GREENPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(GREENPIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}