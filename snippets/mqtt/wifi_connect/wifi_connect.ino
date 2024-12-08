#include <WiFi.h> // (1)!

#define WIFI_SSID "Wokwi-GUEST" // (2)!
#define WIFI_PASSWORD "" // (3)!
#define WIFI_CHANNEL 6 // (4)!

void ConnectWiFi() // (5)!
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL); // (6)!
  Serial.print("Connecting to WiFi ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) // (7)!
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup(void) 
{
  Serial.begin(115200);
  ConnectWiFi(); // (8)!
}

void loop()
{
  delay(10); // (9)!
}