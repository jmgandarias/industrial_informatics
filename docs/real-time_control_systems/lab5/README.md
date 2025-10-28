# Lab 5: Real-time Systems Control

**Estimated time:** 3 h (2 sessions)

Using the code from Labs 2, 3 and 4 and the material from Lecture 4, implement a PID controller inside the microcontroller to perform position control of the DC motor.

!!! warning
    Ensure that the direction considered as positive when sending the PWM matches the positive rotation direction when reading the encoder. Otherwise you would be implementing the equivalent of a control loop with positive feedback.

!!! tip
    Carry out the lab following these steps:

    1. Assemble the circuit from Lab 3.
    2. Test the Lab 3 code and verify it works correctly.
    3. Without dissasembling the existing wiring, assemble the circuit from Lab 4 and verify it works correctly.
    4. Work on the Lab 5 software only after verifying that the hardware is correct and both PWM output and encoder reading work properly.

The serial port must be programmed to receive the reference (desired position) from the PC using the Serial Monitor. You can use the following snippet in `loop()`:

```cpp
int readRef = Serial.parseInt(); // Introduces a delay in the loop, replaces a delay()
if (readRef != 0) {
    ref = readRef;
}
```

Adjust the PID parameters manually to minimize overshoot.

!!! tip
    To properly tune the PID controller, start with the proportional gain `Kp`, leaving the other parameters at zero. Once Kp is tuned, try adjusting the derivative `Kd`. To reduce possible steady-state error, assign a small value to the integrator `Ki` to compensate for any motor deadband.