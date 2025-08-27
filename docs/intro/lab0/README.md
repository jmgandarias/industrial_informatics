# Lab Session 0: Microcontrollers simulation with Wokwi

**Estimated time:** 1.5h (1 session)

## 1. Launch an example

- Access the Wokwi simulation environment via [this link](https://wokwi.com/).
- Select the ESP32 template.

    !!! warning
        Open the ESP32 template from ```Starter Templates```, not from ```ESP-IDF Templates```. The former is based on the Arduino IDE while the latter is based on the ESP-IDF environment that will not be used in the course.


- Connect an LED to ```GPIO 21``` with a resistor, as shown in the diagram (rotate - ```R``` and flip - ```P``` components if necessary).
- Simulate the following sketch:
  
    ```Arduino
    #define LED_PIN 21
    #define BUTTON_PIN 35

    void setup() {
        pinMode(LED_PIN, OUTPUT);
        pinMode(BUTTON_PIN, INPUT_PULLUP);
    }

    void loop() {
        digitalWrite(LED_PIN, HIGH);
        delay(500);
        digitalWrite(LED_PIN, LOW);
        delay(500);
    }
    ```

    !!! question
        - What is the purpose of the ```setup()``` function?
        - What is the purpose of the ```loop()```function?
        - What does the ```#define``` do?

## 2. Control the LED State with a Push Button

- 
!!! question
    - What information is included in the ```diagram.json```? Did it change with respect to the previous exercise?  
