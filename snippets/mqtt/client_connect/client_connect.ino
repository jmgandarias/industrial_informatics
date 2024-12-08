#include <WiFi.h>
#include <WiFiClient.h> // (1)!
#include <PubSubClient.h> // (2)!

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6

const char *MQTT_BROKER_ADRESS = "test.mosquitto.org"; // (3)!
const uint16_t MQTT_PORT = 1883;
const char *MQTT_CLIENT_NAME = "ESP32_test"; // (4)!

WiFiClient espClient; // (5)!
PubSubClient mqttClient(espClient); // (6)!

void ConnectWiFi() // (7)!
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

void InitMqtt() // (8)!
{
  mqttClient.setServer(MQTT_BROKER_ADRESS, MQTT_PORT); 
}

void ConnectMqtt() // (9)!
{
  while (!mqttClient.connected())
  {
    Serial.print("Starting MQTT connection...");
    if (mqttClient.connect(MQTT_CLIENT_NAME))
    {
      Serial.println("Client connected!");
    }
    else
    {
      Serial.print("Failed MQTT connection, rc=");
      Serial.print(mqttClient.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

void HandleMqtt() // (10)!
{
  if (!mqttClient.connected())
  {
    ConnectMqtt();
  }
  mqttClient.loop();
}

void setup(void)
{
  Serial.begin(115200);
  ConnectWiFi();
  InitMqtt(); // (11)!
}

void loop()
{
  HandleMqtt(); // (12)!
  delay(10);
}