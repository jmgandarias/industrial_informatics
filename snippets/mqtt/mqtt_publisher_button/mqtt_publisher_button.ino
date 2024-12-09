#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

# define BUTTON_PIN 14

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6

const char *MQTT_BROKER_ADRESS = "mqtt.eclipseprojects.io";
const uint16_t MQTT_PORT = 1883;
const char *MQTT_CLIENT_NAME = "ESP32_test_pub";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

String payload; 

volatile bool button_released = false;


void IRAM_ATTR buttonReleased(){
  button_released = true;
}

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
}

void ConnectMqtt()
{
  while (!mqttClient.connected())
  {
    Serial.print("Starting MQTT connection...");
    if (mqttClient.connect(MQTT_CLIENT_NAME))
    {
      Serial.print("Client connected");
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

void PublishMqtt(bool data) 
{
  payload = "";
  payload = String(data);
  mqttClient.publish("/button_released", (char *)payload.c_str());
}

void setup(void)
{
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt((BUTTON_PIN)), buttonReleased, FALLING);
  ConnectWiFi();
  InitMqtt();
}

void loop()
{
  HandleMqtt();

  if (button_released){
    PublishMqtt(true);
    Serial.println("Publishing button data");
    button_released = false;
  }

  delay(10);
}