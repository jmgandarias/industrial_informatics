/*
Author: Juan M. Gandarias
Date: 03/11/2023
Description: ejemplo_vibracion.ino
*/

#include <M5Core2.h>

void setup()
{
	Serial.begin(115200);

	M5.begin();
}

void loop()
{
	M5.Axp.SetVibration(true);
	delay(100);
	M5.Axp.SetVibration(false);
	delay(500);
}
