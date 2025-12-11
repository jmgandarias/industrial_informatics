---
title: "Exercise #2: MQTT with ESP32 in real world"
--- 

- Connect to a local network (e.g., InfInd).
- Connect to the broker (check the broker IP: `ipconfig` in windows and `ifconfig` in linux).
- Use the ESP32 (e.g., M5Core2) as a subscriber that subscribes to the topic `/test`. Here is the code to do that:

```cpp
#include <M5Core2.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#define WIFI_SSID "InfInd"  // Don't use a long name
#define WIFI_PASSWORD "InfIndMQTT"
#define WIFI_CHANNEL 6

const char *MQTT_BROKER_ADRESS = "192.168.1.2";
const uint16_t MQTT_PORT = 1883;
const char *MQTT_CLIENT_NAME = "M5Core2_client";

// You only have to include these if your MQTT server requires a user authentication
const char* MQTT_USER = "juanma";
const char* MQTT_PASS = "mqttjuanma";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

String payload;
String content = ""; 

void ConnectWiFi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
  Serial.print("Connecting to WiFi ");
  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void InitMqtt()
{
  mqttClient.setServer(MQTT_BROKER_ADRESS, MQTT_PORT);
  SuscribeMqtt(); 
  mqttClient.setCallback(OnMqttReceived); 
}

void ConnectMqtt()
{
  while (!mqttClient.connected())
  {
    Serial.print("Starting MQTT connection...");
    if (mqttClient.connect(MQTT_CLIENT_NAME, MQTT_USER, MQTT_PASS))
    {
      Serial.println("Client connected!");
      SuscribeMqtt(); 
    }
    else
    {
      Serial.print("Failed MQTT connection, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");

      delay(5000);
    }
  }
}

void HandleMqtt()
{
  if (!mqttClient.connected())
  {
    ConnectMqtt();
  }
  mqttClient.loop();
}

void SuscribeMqtt() 
{
  mqttClient.subscribe("/test");
}

void OnMqttReceived(char *topic, byte *payload, unsigned int length) 
{
  Serial.print("Received on ");
  Serial.print(topic);
  Serial.print(": ");

  content = ""; 
  for (size_t i = 0; i < length; i++) 
  {
    content.concat((char)payload[i]);
  }

  Serial.print(content);
  Serial.println();
}

void setup(void)
{
  Serial.begin(115200);
  ConnectWiFi();
  InitMqtt();
}

void loop() 
{
  HandleMqtt();
  delay(10);
}
```


- Open MQTTExplorer and check the data traffic in the broker.
- Connect to the broker from your phone using the app *MyMQTT*.
- Publish from your phone the message `"Hello"` in the topic `/test`.
- Check that the message arrives to the broker (in MQTTExplorer) and the M5Core2.
- Once you have done this, change the script above to do the following:
    1. Publish in the topic `/ESP32_topic` 
    2. Everytime the ESP32 receives a message in the topic `/test`, it publishes the messsage `"Message received"` in the topic `/ESP32_topic` 