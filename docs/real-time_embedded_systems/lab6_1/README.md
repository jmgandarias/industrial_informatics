# Lab Session 6-I: Small-scale RT multitasking

**Estimated time:** 1.5h (1 session)

## 1. Working with real hardware

### Part 1 - Buttons interaction
The M5Core2 device has 3 touch buttons defined as `M5.BtnA`, `M5.BtnB`, and `M5.BtnC`.

- Compile and test the example program [`button_example.ino`](https://jmgandarias.com/industrial_informatics/real-time_embedded_systems/lab6_1/button_example/button_example.ino).
- At [this link](https://docs.m5stack.com/en/arduino/m5core2/button) you can find the documentation about the functions that can be performed with the buttons.

!!! danger 
    The documentation in the link before is for the new library `M5Unified.h`, which is very new and not very well tested. 
    Some of the functions in that documentation where not included in the old `M5Core2.h` library. Focus only on the functions used in `button_example.ino`

!!! question 
    - How do the buttons behave?
    - What do the `wasReleased` and `pressedFor` functions do?

### Part 2 - Secret code
The program will have 4 states:

- State 0: No button has been pressed.
- State 1: The first button has been pressed correctly.
- State 2: The second button has been pressed correctly.
- State 3: The third button has been pressed correctly.

The buttons must be pressed in the sequence A, B, C.

- If the correct button is pressed, the program moves to the next state.
- If an incorrect button is pressed, it returns to State 0.

!!! note
    Each time the state changes, a message should be printed on the screen. For example:
    - If the program is in State 1:
    ```cpp
       M5.Lcd.println("First button correct");
    ```
    - If the program is in State 3:
    ```cpp
    M5.Lcd.println("CODE CORRECT!");
    ```

## 2. Working in simulation

You can do a [similar exercise](https://jmgandarias.com/industrial_informatics/real-time_embedded_systems/lab6_1/enunciado_ejercicio_codigo_secreto.pdf) in sumation. 