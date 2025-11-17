# Event-driven multi-tasking

## Example exercise

A button and an LED are connected to an ESP32, create a script that does the following:

- If the button is pressed for less than 1s, the LED changes state.
- If it is pressed for more than 1s, the LED blinks (500ms ON, 500ms OFF)
- If the button is pressed again, it turns off and deactivates the blinking (regardless of the state it is in).

### Exercise 6: FSM hardware solution

For this solution we need to use an extra cable and GPIO pin for the button.

<img src="images/exercise_06.png" width="50%"/>

<img src="images/fsm_06.png" width="80%"/>


**<span style="color : green">
&uarr; b:
</span>**
```cpp
activate timer_t
state = 1
```

**<span style="color : blue">
timer_t:
</span>**
```cpp
long_press = true
```

**<span style="color : magenta">
&darr; b:
</span>**
```cpp
deactivate timer_t
if (long_press)
    state = 3
    activate timer_blink
    long_press = false
else
    state = 2
    LED ON
```

**<span style="color : red">
timer_blink:
</span>**

```cpp
LED = !LED
```

**<span style="color : aqua">
&darr; b:
</span>**

```cpp
LED OFF
state = 0
deactivate timer_blink
```

Download the solution [here](exercises_solution/06_fsm_hardware_solution.zip)


### Exercise 7: FSM method 1

<img src="images/exercise_07.png" width="50%"/>

<img src="images/fsm_07.png" width="80%"/>ç


**<span style="color : green">
&uarr; &darr; b:
</span>**
```cpp
if (state == 0 && b)            // before it was green
    activate timer_t
    state = 1
else if (state == 1 && !b)      // before it was magenta
    deactivate timer_t
    if (long_press)
        state = 3
        activate timer_blink
        long_press = false
    else
        state = 2
        LED ON
else                            // before it was light blue
    LED OFF
    state = 0
    deactivate timer_blink
```

**<span style="color : blue">
timer_t:
</span>**
```
long_press = true
```

**<span style="color : red">
timer_blink:
</span>**

```
LED = !LED
```

Download the solution [here](exercises_solution/07_fsm_method_1.zip)


### Exercise 7: FSM method 2

The FSM design is the same as in exercise 7, but the software implementation is different: in this case there is a a prior FSM state evaluation.

Download the solution [here](exercises_solution/07_fsm_method_2.zip)