/*
xmass lights
*/
//SETUP ACCOUNT @ https://sinric.com/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h> //  https://github.com/kakopappa/sinric/wiki/How-to-add-dependency-libraries
#include <ArduinoJson.h> // https://github.com/kakopappa/sinric/wiki/How-to-add-dependency-libraries (use the correct version)
#include <StreamString.h>

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
WiFiClient client;
// Pin Definitions

int ls1 = 5; //D1

int ls2 = 4; //D2

int ls3 = 0; //D3

boolean Active_Show=false;

// int led = 2; //D4 might affect performance

// int starter = 14; //D5

// int panic = 12; //D6

// int led = 13; //D7

int statusled = 15; //D8
unsigned long time_passed=0;
unsigned long previousMillis = 0;
const long interval = 1330000;


#define MyApiKey "b8aae581-0a71-43a5-bc14-e5f19f553917" // API Key is displayed on sinric.com dashboard
#define MySSID "xmasslights" // only works on 2.4 ghz network 
#define MyWifiPassword "xmasslights" // password for network
#define HEARTBEAT_INTERVAL 300000 // 5 Minutes 
//#define FIRST_SHOW
//#define SECOND_SHOW

uint64_t heartbeatTimestamp = 0;

bool isConnected = false;


// deviceId is the ID assgined to your smart-home-device in sinric.com dashboard. Copy it from dashboard and paste it here

void turnOn(String deviceId) {
  if (deviceId == "5daf7898a0866720351e950f") // light show 1 ID
  {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(ls1, HIGH);
    previousMillis=time_passed;
    Serial.println(Active_Show);
    turnOff("5daf78a7a0866720351e9514");
    Active_Show=true; 
  }
  else if (deviceId == "5daf78a7a0866720351e9514") // Light show 2 ID
  {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(ls2, HIGH);
    Serial.println(Active_Show);
    turnOff("5daf7898a0866720351e950f"); 
    Active_Show=false;
  }
  else if (deviceId == "5daf78b0a0866720351e9519") // Light Show 3 ID
  {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(ls3, HIGH);
  }
  else {
    Serial.print("Turn on for unknown device id: ");
    Serial.println(deviceId);
  }
}

void turnOff(String deviceId) {
  if (deviceId == "5daf7898a0866720351e950f") // Light Show 1 ID
  {
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
    digitalWrite(ls1, LOW);
  }
  else if (deviceId == "5daf78a7a0866720351e9514") // Light Show 2 ID
  {
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
    digitalWrite(ls2, LOW);
  }
  else if (deviceId == "5daf78b0a0866720351e9519") // Light Show 3 ID
  {
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
    digitalWrite(ls3, LOW);
  }
  else {
    Serial.print("Turn off for unknown device id: ");
    Serial.println(deviceId);
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      isConnected = false;
      Serial.printf("[WSc] Webservice disconnected from sinric.com!\n");
      break;
    case WStype_CONNECTED: {
        isConnected = true;
        Serial.printf("[WSc] Service connected to sinric.com at url: %s\n", payload);
        Serial.printf("Waiting for commands from sinric.com ...\n");
      }
      break;
    case WStype_TEXT: {
        Serial.printf("[WSc] get text: %s\n", payload);
        // Example payloads

        // For Switch or Light device types
        // {"deviceId": xxxx, "action": "setPowerState", value: "ON"} // https://developer.amazon.com/docs/device-apis/alexa-powercontroller.html

        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject((char*)payload);
        String deviceId = json ["deviceId"];
        String action = json ["action"];

        if (action == "setPowerState") { // Switch or Light
          String value = json ["value"];
          if (value == "ON") {
            turnOn(deviceId);
          } else {
            turnOff(deviceId);
          }
        }
        else if (action == "SetTargetTemperature") {
          String deviceId = json ["deviceId"];
          String action = json ["action"];
          String value = json ["value"];
        }
        else if (action == "test") {
          Serial.println("[WSc] received test command from sinric.com");
        }
      }
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ls1, OUTPUT);
  pinMode(ls2, OUTPUT);
  pinMode(ls3, OUTPUT);
  pinMode(statusled, OUTPUT);

  digitalWrite(ls1, LOW);
  digitalWrite(ls2, LOW);
  digitalWrite(ls3, LOW);

  WiFiMulti.addAP(MySSID, MyWifiPassword);
  Serial.println();
  Serial.print("Connecting to Wifi: ");
  Serial.println(MySSID);

  // Waiting for Wifi connect
  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    notconnected();
  }
  if (WiFiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.print("WiFi connected. ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
  }

  // server address, port and URL
  webSocket.begin("iot.sinric.com", 80, "/");

  // event handler
  webSocket.onEvent(webSocketEvent);
  webSocket.setAuthorization("apikey", MyApiKey);

  // try again every 5000ms if connection has failed
  webSocket.setReconnectInterval(5000);   // If you see 'class WebSocketsClient' has no member named 'setReconnectInterval' error update arduinoWebSockets
}

void loop() {
  webSocket.loop();
  if (isConnected) {
    uint64_t now = millis();
    digitalWrite(statusled, HIGH);
    // Send heartbeat in order to avoid disconnections during ISP resetting IPs over night. Thanks @MacSass
    if ((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
      heartbeatTimestamp = now;
      webSocket.sendTXT("H");
    }
  }
  time_passed = millis();
  
  if(time_passed-previousMillis >= interval && Active_Show)
  {
  Serial.println("show ended");  
  turnOn("5daf78a7a0866720351e9514");     //LIGHT SHOW 2
  turnOff("5daf7898a0866720351e950f");    //LIGHT SHOW 1 
  }
  
}


void notconnected() {
  digitalWrite(statusled, HIGH);
  delay(125);
  digitalWrite(statusled, LOW);
  delay(125);
  digitalWrite(statusled, HIGH);
  delay(125);
  digitalWrite(statusled, LOW);
  delay(125);
  digitalWrite(statusled, HIGH);
  delay(125);
  digitalWrite(statusled, LOW);
  delay(125);
  digitalWrite(statusled, HIGH);
  delay(125);
  digitalWrite(statusled, LOW);
}

/*
 * 
 * 
 * 
 * Instruction & Steps of How to use:
1. Download the Arduino IDE, the latest version.
2. Install the IDE.
3. Set up your Arduino IDE as: Go to File->Preferences and copy the URL below to get the ESP board manager extensions: http://arduino.esp8266.com/stable/package_esp8266com_index.json
Placing the “http://” before the URL and let the Arduino IDE use it...otherwise it gives you a protocol error.
4. Go to Tools > Board > Board Manager> Type "esp8266" and download the Community esp8266 and install. 
5. Set up your chip:
Tools -> Board -> NodeMCU 1.0 (ESP-12E Module)
Tools -> Flash Size -> 4M (3M SPIFFS)
Tools -> CPU Frequency -> 80 Mhz
Tools -> Upload Speed -> 921600
Tools-->Port--> (whatever it is)
6. Download and run the 32 bit flasher exe at Github(Search for nodemcu/nodemcu-flasher/tree/master/ at Github) github.com/nodemcu/nodemcu-flasher/tree/master/Win32/Release
Or download and run the 64 bit flasher exe at: github.com/nodemcu/nodemcu-flasher/tree/master/Win64/Release
7. In Arduino IDE, look for the old fashioned Blink program. Load, compile and upload. 
8. Go to FILE> EXAMPLES> ESP8266> BLINK, it will start blinking. 

Package included: 
3 x ESP8266 NodeMCU LUA CP2102 WiFi Development Board


DRIVERS https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers
 * 
 *
 */
