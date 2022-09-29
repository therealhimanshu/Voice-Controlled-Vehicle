#define IO_USERNAME  "Adafruit_Username"
#define IO_KEY       "Adafruit_Key"
//you can find your key by clicking on the key button on adafruit page
/** WIFI Configuration ***/

#define WIFI_SSID       "WiFi_Name"
#define WIFI_PASS       "Wifi_Pass"

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

/* Main Program Starts Here **/
#include <ESP8266WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include <ArduinoHttpClient.h>

// These are used to set the direction of the bridge driver.
#define MOTORB_1 D4 //IN3
#define MOTORB_2 D5 //IN4
#define MOTORA_1 D6 //IN1
#define MOTORA_2 D3

String cmd;

AdafruitIO_Feed *command = io.feed("Your_Feed_Name"); // Set up the 'command' feed

// SETUP
void stop(){
  digitalWrite(D3,HIGH);
  digitalWrite(D4,HIGH);
  digitalWrite(D5,HIGH);
  digitalWrite(D6,HIGH);
  delay(5000);
 
}
void setup()
{
  pinMode(MOTORA_1, OUTPUT);
  pinMode(MOTORA_2, OUTPUT);
  pinMode(MOTORB_1, OUTPUT);
  pinMode(MOTORB_2, OUTPUT);
  Serial.begin(9600);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  command->onMessage(handleMessage);  

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(50);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

// MAIN CODE
void loop()
{
  io.run();
}

// this part of the code runs whenever there's a new message on Adafruit.io feed
void handleMessage(AdafruitIO_Data *data) {
 
  String commandStr = data->toString(); // store the incoming commands in a string
 
  // received message
  Serial.print("received <- ");
  Serial.println(commandStr);

 
  stop();
  
  Serial.println(commandStr);
  // perform movements
  // LEFT
 if (commandStr=="left" || commandStr=="Left"){   
    Serial.println("IN"); 
    digitalWrite(D4,HIGH);
    digitalWrite(D3,HIGH);
    digitalWrite(D5,LOW);
    digitalWrite(D6,HIGH);
    delay(5000);
    stop();
  }
  // RIGHT
  if (commandStr=="right" || commandStr=="Right" ){  
    Serial.println("IN");   
    digitalWrite(D4,LOW);
    digitalWrite(D3,HIGH);
    digitalWrite(D5,HIGH);
    digitalWrite(D6,HIGH);
    delay(5000);
    stop();
  }
  // FORWARD
  if (commandStr=="forward" || commandStr=="Forward"){    
    Serial.println("IN"); 
    digitalWrite(D4,LOW);
    digitalWrite(D3,HIGH);
    digitalWrite(D5,LOW);
    digitalWrite(D6,HIGH);
    delay(50000);
    stop();
  }
  // BACK
  if (commandStr=="backward" || commandStr=="Backward"){  
    Serial.println("IN");   
    digitalWrite(D4,HIGH);
    digitalWrite(D3,LOW);
    digitalWrite(D5,HIGH);
    digitalWrite(D6,LOW);
    delay(50000);
    stop();
  }  
}
