#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6

const char *MQTT_BROKER_ADRESS = "mqtt.eclipseprojects.io";
const uint16_t MQTT_PORT = 1883;
const char *MQTT_CLIENT_NAME = "ESP32_test_sub";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

String payload;
String content = ""; // (1)!

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
  SuscribeMqtt(); // (2)!
  mqttClient.setCallback(OnMqttReceived); // (3)!
}

void ConnectMqtt()
{
  while (!mqttClient.connected())
  {
    Serial.print("Starting MQTT connection...");
    if (mqttClient.connect(MQTT_CLIENT_NAME))
    {
      Serial.println("Client connected!");
      SuscribeMqtt(); // (4)!
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

void SuscribeMqtt() // (5)!
{
  mqttClient.subscribe("/testing_topic");
}

void OnMqttReceived(char *topic, byte *payload, unsigned int length) // (6)!
{
  Serial.print("Received on ");
  Serial.print(topic);
  Serial.print(": ");

  content = ""; 
  for (size_t i = 0; i < length; i++) // (7)!
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

void loop() // (8)!
{
  HandleMqtt();
  delay(10);
}