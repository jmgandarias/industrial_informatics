# Lab Session 1: Introduction to Microcontroller Programming

**Estimated time:** 1.5 hours (1 session)

## 1. Working with Real Hardware

### 1.1. Prepare the Arduino IDE

Follow the installation steps described in this guide.

!!! note
    Please note that you only need to complete these steps once, and only on your own computer. If you are going to use the department PC, you do not need to follow these steps.

1. Install the Arduino IDE by downloading it from [this link](https://www.arduino.cc/en/software/).
2. Install the M5Stack board family:

    <img src="images/board_install_1.png" width="70%"/>

    You need to copy and paste the following text to add the board package URL:

    ```txt
    https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json
    ```

    <img src="images/board_install_2.png" width="80%"/>

    Once the board package URL has been configured, you can install it from the Boards Manager.

    <img src="images/board_install_3.png" width="80%"/>


    !!! tip
        Updated instructions for installing the M5Core2 can be found [here](https://docs.m5stack.com/en/arduino/m5core2/program).

    !!! warning
        Please be aware of the recent updates to the ESP32 Core library for Arduino. In 2024, the Arduino-ESP32 core was upgraded from version 2.x (based on ESP-IDF 4.4) to version 3.x (based on ESP-IDF 5.1). The underlying API and build system changed several behaviors. Much of the code you may find online was written for the older 2.x version. All the lab sessions and programs in this course have been updated to the most recent version. More information about versions 2.x and 3.x can be found [here](../arduino_esp32_core).

    Once installed, you can select M5Core2 from the board selection menu.

    <img src="images/board_selection.png" width="100%"/>

3. Install the Arduino libraries for M5Core2:

    <img src="images/m5core2_library.png" width="80%"/>

    !!! warning
        When you click *Install*, you will see a list of dependencies. You *MUST* install all of them as well.

    !!! danger
        If you encounter the following error during installation, it means that you do not have write permission for the library folder:

        <img src="images/error_library_installation.png" width="100%"/>

        You can solve this problem in one of two ways:

        1. Open the Arduino IDE as an administrator:

            <img src="images/open_IDE_admin.png" width="80%"/>

        2. Change the library folder to a location where you have write permission:

            <img src="images/change_library_location.png" width="100%"/>


4. Install the CP2104 driver (USB driver):

    Download it from one of the following links:  
    - [Windows](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/drivers/CP210x_VCP_Windows.zip)  (Unzip the file and launch the file `CP210xVCPInstaller_Win7_v5.40.24.exe`)  
    - [MacOS](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/drivers/CP210x_VCP_MacOS.zip)  (Unzip the file and launch the file `SiLabsUSBDriverDisk.dmg`)  
    - [Linux](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/drivers/CP210x_VCP_Linux.zip)  (Unzip the file and follow the building instructions in the file `CP210x_VCP_Linux_4.x_Release_Notes.txt`)  

    More information about USB driver installation can be found [here](https://docs.m5stack.com/en/arduino/m5core2/program#2.usb%20driver%20installation).

    Now, when you connect the M5Core2 to the PC with the USB cable, you can select the port in the Arduino IDE.

    <img src="images/select_serial_port.png" width="80%"/>

    !!! info
        - On Windows, the port is named *COMX*, where *X* is a number that may vary, for example *COM5*.
        - On Linux, the port is named *ttyUSBX* or *ttyACMX*, where *X* is a number that may vary, for example *ttyUSB2*.

    !!! warning
        If you see several devices and are not sure which one is the M5Core2, you can try one of the following:

        1. Connect and disconnect the device and check which device appears and disappears from the list. Note that to update the list of connected devices, you need to close and reopen the `Tools` menu in the Arduino IDE.
        2. Check the connected devices in the Device Manager:

            <img src="images/device_manager.png" width="70%"/>

            <img src="images/device_COM.png" width="70%"/>

    !!! note
        You also need to select the correct board, as in step 2. Remember that you should always verify the board and port before uploading a program to the device.

5. Compile and upload the `hello_world.ino` example:

    ```Arduino
    #include<M5Unified.h>

    void setup() {

    // Begin M5Unified.
    M5.begin();

    // Print to the LCD screen.
    M5.Display.print("Hello World");

    }

    void loop() {
    }
    ```

    !!! note
        The first time you compile a program for the M5Core2, it may take some time.

    You can press the *Upload* button (red) to compile and upload the program to the device. Note that the *Verify* button (green) compiles the program but does not upload it.

    <img src="images/compile.png" width="70%"/>


!!! tip "Additional resources"
    You can find more documentation about some of the basic functions of the M5Core2 [here](https://docs.m5stack.com/en/core/core2).

**Pinout and Important Notes**
Below is the M5Core2 pinout. The pins marked in red are the ones we will use in the exercises.

<img src="images/pinout_M5Core2.png" width="30%"/>

!!! warning
    - Some pins on the M5Core2 are preconfigured, so pay attention when connecting external components.
    - The ESP32 inside the M5Core2 has three serial ports:
          - `Serial1` is reserved for the display (do not use it).
          - `Serial0` can be configured (pins `G3 – RXD0` and `G1 – TXD0`), but it is reserved for USB connection to the PC.
          - `Serial2` is free and can be configured (pins `G13 – RXD2` and `G14 – TXD2`) as regular GPIO using `pinMode()`.

### 1.2. Turn an LED On and Off

Connect an LED as follows:

<img src="images/LED_M5Core2.png" width="60%"/>

Run the following program:
```Arduino
#include<M5Unified.h>
#define LED_PIN 14

void setup() {
  M5.begin(); // Initialize M5Core2
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
```

!!! question
    - What does the [```#define```](https://docs.arduino.cc/language-reference/en/structure/further-syntax/define/) directive do?
    - What does the [```pinMode()```](https://docs.arduino.cc/language-reference/en/functions/digital-io/pinMode/) function do?
    - What does the [```digitalWrite()```](https://docs.arduino.cc/language-reference/en/functions/digital-io/digitalwrite/) function do?

!!! question
    Note that you had to include the ```#include <M5Unified.h>``` line and the ```M5.begin(); // Initialize M5Core``` statement.
    Why did you need to do that? What are these instructions for?

### 1.3. Additional Exercises

#### 1.3.1. Blink at a Certain Frequency

- Using the same circuit as in the previous exercise, write a script that blinks the LED at a frequency of 10 Hz.

    !!! question
        - For how long should the LED be ON or OFF in each cycle?

#### 1.3.2. Blink and Stop

- Using the same circuit as in the previous exercise, write a script that blinks the LED at a frequency of 2 Hz and stops blinking after 5 seconds.

    !!! question
        - How many times does the LED blink?
        - What is the final state of the LED when blinking stops: does it remain ON or OFF?

    !!! tip
        You may need to use the [```for```](https://docs.arduino.cc/language-reference/en/structure/control-structure/for/) loop, or the [```if...else```](https://docs.arduino.cc/language-reference/en/structure/control-structure/else/) condition.

## 2. Working in Simulation

### 2.1. Microcontroller Simulation

#### Launch an Example

- Access the Wokwi simulation environment via [this link](https://wokwi.com/).
- Select the ESP32 template.

    <img src="images/select_esp32_1.png" width="55%"/>
    <img src="images/select_esp32_2.png" width="80%"/>

    !!! warning
        Open the ESP32 template from `Starter Templates`, not from `ESP-IDF Templates`. The former is based on the Arduino IDE, while the latter is based on the ESP-IDF environment, which will not be used in this course.

- Simulate the example sketch:

    ```Arduino
    void setup() {
    // Put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("Hello, ESP32!");
    }

    void loop() {
    // Put your main code here, to run repeatedly:
    delay(10); // This speeds up the simulation.
    }
    ```

    !!! warning
        Here you are *simulating* the behavior of the system, including the code. You are not *compiling* the code, meaning you are not generating the machine-readable code that will be executed by a processor. However, the code still MUST be compilable, meaning it will be verified to ensure that it can compile.

    !!! info
        - Note that the real-time factor in the top-right corner should be as close as possible to 100%. This value is a simulation performance metric. The closer it gets to 100%, the better the simulation. A value of 100% means the simulation is running in real time. If the value drops, the timing in the simulation is no longer reliable.
        - Note the instruction `delay(10); // this speeds up the simulation`. Try commenting out this line and see what happens. What if you use `delay(1);` or `delay(5);`?

    !!! question
        - What is the purpose of the [`setup()`](https://docs.arduino.cc/language-reference/en/structure/sketch/setup/) function?
        - What is the purpose of the [`loop()`](https://docs.arduino.cc/language-reference/en/structure/sketch/loop/) function?
        - What does the [`delay()`](https://docs.arduino.cc/language-reference/en/functions/time/delay/) function do?
        - Why do we need to put the `delay(10)` inside the `loop()` function?

#### Add Hardware Components

- First, check the `diagram.json` file. What information do you see there?

- Connect an LED to `GPIO 21` with a resistor, as shown in the diagram (rotate the components with `r` and flip them with `p` if necessary).

    <img src="images/circuito_1.png" width="40%"/>

    !!! question
        - Check the `diagram.json` again. What happened? Can you change the color of the LED to *green* from this file?
        - What do you think you can do with the *Library Manager*?

### 2.2. Turn an LED On and Off

Connect an LED as follows:

<img src="images/circuito_1.png" width="40%"/>

Run the following program:
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

### 2.3. Control the LED State with a Push Button

- Implement the circuit shown in the following diagram and simulate a program that:
    - Turns the LED ON when the button is pressed.
    - Turns the LED OFF when the button is not pressed.

    !!! tip
        - Use the [```digitalRead()```](https://docs.arduino.cc/language-reference/en/functions/digital-io/digitalread/) function to read the status of the button.
        - You may need to use the [```if...else```](https://docs.arduino.cc/language-reference/en/structure/control-structure/else/) condition.

    <img src="images/button_diagram.png" width="50%"/>

    !!! warning
        When you place the button, do not forget to deselect the *bounce* option to avoid [bouncing issues](https://www.luisllamas.es/en/debouncing-arduino-interrupts/).

        <img src="images/bounce.png" width="30%"/>

    !!! question
        - What information is included in the `diagram.json` file? Did it change compared with the previous exercise?
        - Can you complete the exercise without using the [```if...else```](https://docs.arduino.cc/language-reference/en/structure/control-structure/else/) condition? How?

### 2.4. Additional Exercises

#### 2.4.1. Blink

- Using the same circuit as in the previous exercise, write a script that blinks the LED while the button is pressed.

    !!! tip
        You may need to use the [```millis()```](https://docs.arduino.cc/language-reference/en/functions/time/millis/) function.

#### 2.4.2. Short Press vs. Long Press

- Using the same circuit as in the previous exercise, write a script that does the following:
    - Short press (< 500 ms): Toggle the LED (if the LED is ON, turn it OFF, and vice versa).
    - Long press (≥ 500 ms): Blink the LED.

    !!! tip
        You may need to use the [```millis()```](https://docs.arduino.cc/language-reference/en/functions/time/millis/) function and the [```if...else```](https://docs.arduino.cc/language-reference/en/structure/control-structure/else/) condition.

