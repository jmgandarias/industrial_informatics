/*
Author: Juan M. Gandarias
Date: 03/11/2023
Description: ejemplo_IMU
*/

#include <M5Core2.h>

// IMU variables
float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;
float pitch = 0.0F;
float roll = 0.0F;
float yaw = 0.0F;

void setup()
{
	Serial.begin(115200);

	M5.begin();

	M5.IMU.Init(); // Init IMU sensor.

	M5.Lcd.setTextColor(YELLOW, BLACK); // Poner el color de texto en amaruillo
	M5.Lcd.setTextSize(2);				// Poner el tamaño de las letras en 2
}

void loop()
{
	// Get IMU Data
	M5.IMU.getAccelData(&accX, &accY, &accZ); // Get the triaxial accelerometer.
	M5.IMU.getAhrsData(&pitch, &roll, &yaw);  // Get the inertial sensor attitude.

	M5.Lcd.setCursor(0, 30);	  // Mover el cursor a la posición (x, y) = (30, 10)
	M5.Lcd.println("IMU DATA: "); // Escrbir en esa posición y salto de línea

	// //Print acc data
	M5.Lcd.setCursor(0, 70);
	M5.Lcd.print("accX,   accY,  accZ");
	M5.Lcd.setCursor(0, 92);
	M5.Lcd.printf("%5.2f  %5.2f  %5.2f G", accX, accY, accZ);

	// //Print orientation data
	M5.Lcd.setCursor(0, 120);
	M5.Lcd.print("pitch,  roll,  yaw");
	M5.Lcd.setCursor(0, 142);
	M5.Lcd.printf("%5.2f  %5.2f  %5.2f deg", pitch, roll, yaw);

	M5.update();
	delay(1000 / 25);
}
