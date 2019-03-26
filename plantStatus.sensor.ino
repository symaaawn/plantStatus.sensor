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

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

#include "credentials.h"

#define REDPIN 12
#define GREENPIN 13
#define BLUEPIN 14

#define LED_BUILTIN 2

const char* ssid = WIFI_SSD;
const char* password = WIFI_PWD;

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************/
void displaySensorDetails(void)
{
    sensor_t sensor;
    tsl.getSensor(&sensor);
    Serial.println("------------------------------------");
    Serial.print  ("Sensor:       "); Serial.println(sensor.name);
    Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
    Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
    Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" lux");
    Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" lux");
    Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" lux");  
    Serial.println("------------------------------------");
    Serial.println("");
    delay(500);
}

/**************************************************************************/
/*
    Configures the gain and integration time for the TSL2561
*/
/**************************************************************************/
void configureSensor(void)
{
    /* You can also manually set the gain or enable auto-gain support */
    // tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
    // tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
    tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
    
    /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
    tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
    // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
    // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */

    /* Update these values depending on what you've set above! */  
    Serial.println("------------------------------------");
    Serial.print  ("Gain:         "); Serial.println("Auto");
    Serial.print  ("Timing:       "); Serial.println("13 ms");
    Serial.println("------------------------------------");
}

// the setup function runs once when you press reset or power the board
void setup() {
    pinMode(GREENPIN, OUTPUT);
    pinMode(REDPIN, OUTPUT);
    pinMode(BLUEPIN, OUTPUT);

    Serial.begin(9600);
    Serial.println("Light Sensor Test"); Serial.println("");
    
    /* Initialise the sensor */
    //use tsl.begin() to default to Wire, 
    //tsl.begin(&Wire2) directs api to use Wire2, etc.
    if(!tsl.begin())
    {
        /* There was a problem detecting the TSL2561 ... check your connections */
        Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
        while(1);
    }
    
    /* Display some basic information on this sensor */
    displaySensorDetails();
    
    /* Setup the sensor gain and integration time */
    configureSensor();
    
    /* We're ready to go! */
    Serial.println("");
}

// the loop function runs over and over again forever
void loop() {
    /* Get a new sensor event */ 
    sensors_event_t event;
    tsl.getEvent(&event);
    
    /* Display the results (light is measured in lux) */
    if (event.light)
    {
        Serial.print(event.light); Serial.println(" lux");
        if(event.light < 50){
            digitalWrite(BLUEPIN, HIGH);
            digitalWrite(REDPIN, HIGH);
        }else{
            digitalWrite(BLUEPIN, LOW);
            digitalWrite(REDPIN, LOW);
        }
    }
    else
    {
        /* If event.light = 0 lux the sensor is probably saturated
        and no reliable data could be generated! */
        Serial.println("Sensor overload");
    }
    delay(250);
    /*digitalWrite(BLUEPIN, HIGH);
    digitalWrite(REDPIN, HIGH);
    delay(1000);     
    digitalWrite(BLUEPIN, LOW);
    digitalWrite(REDPIN, LOW);
    delay(1000);*/                
}