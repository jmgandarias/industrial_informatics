
# Laboratory Session 7: TFT Screen Programming with M5Core2

**Estimated time:** 1.5 h (1 session)

## 1. Working with real hardware

### Part 1: Register the pixel that was touched

- The program must check whether the screen has been touched or not.
- If touched, obtain the X, Y coordinates of the pixel that was pressed. To do this, you will need to use the following functions:
    - `bool screen_pressed = M5.Touch.ispressed()`: Returns `true` if the screen was touched and `false` otherwise.
    - `TouchPoint_t pixel_pos = M5.Touch.getPressPoint()`: Returns the coordinates of the pixel that was touched.
- The pixel position has 2 coordinates (X,Y). To store both coordinates, you need to use the variable type `TouchPoint_t`. The coordinates are stored as follows:
  
  ```
  TouchPoint_t coordinates:
    int16_t coordinates.x
    int16_t coordinates.y
  ```

- The following example code writes the touched pixels to the serial port:

    ```cpp
    #include <M5Core2.h>

    // Variable of type TouchPoint_t to store the pixel touched on the screen
    TouchPoint_t pixel_pos;

    void setup()
    {
        // Initialize serial port
        Serial.begin(115200);

        M5.begin();

        M5.Lcd.setTextColor(YELLOW, BLACK); // Set text color to yellow
        M5.Lcd.setTextSize(2);              // Set text size to 2
        M5.Lcd.println("Register pixel");

        // Fill the screen background with black
        M5.Lcd.fillScreen(BLACK);
    }

    void loop()
    {
        M5.update();

        // If the screen has been touched
        if (M5.Touch.ispressed())
        {
            pixel_pos = M5.Touch.getPressPoint(); // Save the touched pixel
            Serial.printf("x:%d, y:%d \r\n", pixel_pos.x, pixel_pos.y); // Print the pixel position to the serial port
        }
    }
    ```

- When testing the above code, you will notice that the same pixel is repeatedly printed. To fix this, modify the code to store the current touched pixel position and the last touched position. If they are the same, do not print.

!!! warning
    Don't forget to include the `M5.update();`

### Part 2: Create a script for M5Core2 that allows drawing on the screen with your finger

Starting from the code in Part 1, once you have verified that the screen was pressed, that the pressed pixel is different from the one pressed in the previous loop iteration, and that it has been stored in a `TouchPoint_t` variable, you must:

- At that same position, draw using one of the following functions:
  - `M5.Lcd.drawPixel(int16_t x0, int16_t y0, uint16_t color);` Fills the pixel at coordinates (x0, y0) with a color (e.g., WHITE).
  - `M5.Lcd.fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);` Draws a filled circle centered at point X0 and Y0, with radius r and a color (e.g., WHITE).

### Part 3: Add the option to clear the screen content when button A is pressed

To do this, you will need to use the functions `M5.Lcd.fillScreen()` or `M5.Lcd.clear()`.


## Working in simulation

To perform the exercise in simulation, you need to use a TFT screen in Wokwi.  
[Here](https://wokwi.com/projects/415787025818634241) is an example that solves Part 1 of the exercise in Wokwi using the _ILI9341_ screen and its corresponding libraries.

In that example, you can see the similarities in the code structure and the differences in syntax due to using libraries other than `M5Core2.h`.

Modify the example to solve Parts 2 and 3 in simulation. For Part 3, you will need to add an external button.

!!! info
    Working with this screen is computationally expensive, so Wokwi does not achieve near 100% real-time performance.
