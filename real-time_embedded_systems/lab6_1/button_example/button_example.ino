/* Button example
Author: https://github.com/m5stack/M5Core2
Date: 10/11/2023
Description: Ejemplo de pulsación de botones con M5Core2
*/

#include <M5Core2.h>

void setup()
{
    M5.begin();                                 // Inicializar M5Core2
    M5.Lcd.setTextColor(YELLOW);                // Poner el color de texto en amaruillo
    M5.Lcd.setTextSize(2);                      // Poner el tamaño de las letras en 2
    M5.Lcd.setCursor(65, 10);                   // Mover el cursor a la posición (x, y) = (65, 10)
    M5.Lcd.println("Button example");           // Escrbir en esa posición y salto de línea
    M5.Lcd.setCursor(3, 35);                    // Mover el cursor a la posición (3, 35)
    M5.Lcd.println("Press button B for 700ms"); // Escribir en esa posición y salto de línea
    M5.Lcd.println("to clear screen.");         // Escribir en la siguiente línea
    M5.Lcd.setTextColor(RED);                   // Poner el color de texto en rojo
}

void loop()
{
    M5.update(); // Actualiza estado de los botones

    // Los botones A, B y C ya están definidos en la clase M5.
    // Los métodos wasReleased y pressedFor están definidos para la clase Button, y se predefinen en la clase M5
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) // Si se ha soltado A o si se ha pulsado en un intervalo entre 200 y 1000 ms
    {
        M5.Lcd.print('A'); // Escribe la letra A por pantalla
    }
    else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 200))
    {
        M5.Lcd.print('B');
    }
    else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 200))
    {
        M5.Lcd.print('C');
    }
    else if (M5.BtnB.wasReleasefor(700))
    {
        M5.Lcd.clear(WHITE);    // Borra la pantalla y pon el fondo en blanco
        M5.Lcd.setCursor(0, 0); // Pon el cursor en (0.0)
    }
}