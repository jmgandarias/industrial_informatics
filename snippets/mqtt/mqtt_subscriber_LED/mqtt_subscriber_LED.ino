#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#define LED_PIN 26       

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6

const char *MQTT_BROKER_ADRESS = "mqtt.eclipseprojects.io";
const uint16_t MQTT_PORT = 1883;
const char *MQTT_CLIENT_NAME = "ESP32_test_sub";

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
    if (mqttClient.connect(MQTT_CLIENT_NAME))
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
  mqttClient.subscribe("/button_released");
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

  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void setup(void)
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  ConnectWiFi();
  InitMqtt();
}

void loop() 
{
  HandleMqtt();
  delay(10);
}