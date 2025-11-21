# Lab Session 6-II: Multitasking with FreeRTOS

**Estimated time:** 1.5 h (1 session)

## 1. Working with real hardware

### 1.1 Test the IMU (inertial sensor)

Read and run the program [`IMU.ino`](https://jmgandarias.com/industrial_informatics/real-time_embedded_systems/lab6_2/IMU/IMU.ino) to understand how to work with the M5Core2 sensor.

### 1.2 Test the vibration motor

Read and run the program [`vibration.ino`](https://jmgandarias.com/industrial_informatics/real-time_embedded_systems/lab6_2/vibration/vibration.ino) to understand how to work with the actuator on the M5Core2.

### 1.3 Multitasking with sensor and actuator

Create a sketch for the M5Core2 using FreeRTOS that does the following:

1. Use 4 tasks. Initially all tasks run on core 0.
2. Task 1 monitors button presses for buttons `A`, `B` and `C`. It has priority 2 and runs at 100 Hz.
3. Task 2 writes IMU data to the M5 screen similarly to the program [`IMU.ino`](https://jmgandarias.com/industrial_informatics/real-time_embedded_systems/lab6_2/IMU/IMU.ino). In this case, the data are displayed only when button `B` has been pressed. If pressed again, the screen remains in its current state (data are not updated). Pressing `B` again resumes updates, and so on. This task has priority 1 and runs at 25 Hz.
4. Task 3 triggers a vibration pattern as an alarm if acceleration magnitude reaches or exceeds 2 G (sqrt(accX*accX + accY*accY + accZ*accZ) > 2). The pattern should make the motor vibrate 5 times with 200 ms intervals. This task has priority 3 and runs at 5 Hz.
5. The final task writes to the serial port every change that occurs in the application. It only writes if an event has occurred (button `A`, `B` or `C` press, or a vibration alarm). The published data are:
   - How many times `A` has been pressed.
   - How many times `C` has been pressed.
   - If `B` has been pressed and IMU data are currently being displayed, write: "Using IMU data". Otherwise write: "Not using IMU data".

!!! question
    Since the device has 2 cores, you could distribute tasks between them to balance load. For the tasks above:
    - which task(s) would you assign to each core and why?
    - Try running the program with those changes and observe any differences in behavior.

## 2. Working in simulation

To do this lab in simulation you can use the ESP32 with the following substitutes:

- Three external buttons to act as buttons `A`, `B`, and `C`. Configure external interrupts for them.
- For the IMU, add an external sensor. In Wokwi you can use the `mpu6050` IMU. See its documentation [here](https://docs.wokwi.com/parts/wokwi-mpu6050). Communication between the IMU and the ESP32 is done via I2C. An Arduino example is available [here](https://wokwi.com/projects/305937248748044864).
- Wokwi does not include a vibration motor for the 2G alarm. Replace it with an LED that blinks or varies intensity using PWM duty cycle.
- To display data on screen you have two options:
  
  1. The simplest: send the data over the serial port.
  2. If you prefer, use a TFT display similar to the M5Core2 screen (covered in the next topic). Wokwi provides an ILI9341 TFT you can use. See the documentation [here](https://docs.wokwi.com/parts/wokwi-ili9341). Example projects [here](https://wokwi.com/projects/375305166758503425) and [here](https://wokwi.com/projects/308024602434470466).