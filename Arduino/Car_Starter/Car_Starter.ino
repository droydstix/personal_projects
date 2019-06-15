/*
  Smart Car
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
int led = 5;
#define MyApiKey "560e04cb-bdf7-4d80-809f-aa3ed34b86d0" // API Key is displayed on sinric.com dashboard
#define MySSID "Droydstix 2.4" // only works on 2.4 ghz network 
#define MyWifiPassword "1csi2012" // password for network
#define HEARTBEAT_INTERVAL 300000 // 5 Minutes 

uint64_t heartbeatTimestamp = 0;
bool isConnected = false;


// deviceId is the ID assgined to your smart-home-device in sinric.com dashboard. Copy it from dashboard and paste it here

void turnOn(String deviceId) {
  if (deviceId == "5d04354d3f488654235a215f") // Unlock Button ID
  {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(led, HIGH);

  }
  else if (deviceId == "5d0435833f488654235a2162") // Lock Button ID
  {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
  }
  else if (deviceId == "5d0436323f488654235a2164") // Trunk Button ID
  {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
  }
  else if (deviceId == "5d0436ca3f488654235a2166") // Starter Button ID
  {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
  }
  else if (deviceId == "5d0436ee3f488654235a2168") // Panic Button ID
  {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
  }
  else {
    Serial.print("Turn on for unknown device id: ");
    Serial.println(deviceId);
  }
}

void turnOff(String deviceId) {
  if (deviceId == "5d04354d3f488654235a215f") // Unlock Button ID
  {
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
    digitalWrite(led, LOW);

  }
  else if (deviceId == "5d0435833f488654235a2162") // Lock Button ID
  {
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
  }
  else if (deviceId == "5d0436323f488654235a2164") // Trunk Button ID
  {
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
  }
  else if (deviceId == "5d0436ca3f488654235a2166") // Starter Button ID
  {
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
  }
  else if (deviceId == "5d0436ee3f488654235a2168") // Panic Button ID
  {
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
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

        // For Light device type
        // Look at the light example in github

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
  Serial.begin(9600);
  pinMode(led, OUTPUT);


  WiFiMulti.addAP(MySSID, MyWifiPassword);
  Serial.println();
  Serial.print("Connecting to Wifi: ");
  Serial.println(MySSID);

  // Waiting for Wifi connect
  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
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

    // Send heartbeat in order to avoid disconnections during ISP resetting IPs over night. Thanks @MacSass
    if ((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
      heartbeatTimestamp = now;
      webSocket.sendTXT("H");
    }
  }
}

// If you want a push button: https://github.com/kakopappa/sinric/blob/master/arduino_examples/switch_with_push_button.ino

