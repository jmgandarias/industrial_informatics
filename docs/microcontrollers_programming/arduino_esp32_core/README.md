# Arduino ESP32 core 2.x and 3.x

 In 2024, the Arduino‑ESP32 core was upgraded from versions 2.x (based on ESP-IDF 4.4) to versions 3.x (based on ESP-IDF 5.1). The underlying API and build system (usually called API or builder) changed some behaviour around several functionalities.

 As you'll use PWM and timers extensively in this course, which suffered breaking changes from this update, it's necessary to consider which version are you using when developing your programs. Below are the most relevant points, practical guidance and short code examples you can use when porting or writing your code.

For more information about this migration you can check [this website](https://docs.espressif.com/projects/arduino-esp32/en/latest/migration_guides/2.x_to_3.0.html).

First of all, you need to know that even if the code sinatxis and structure has suffered some changes, the results in reality that can be achieved using one or another (at least, for what you'll do in this course) are not affected by this migration (considering that the code is well developed independently of the API version).

## Timers

In this course you'll need to program hardware timers. Although the functionalities when using API 2.x or 3.x are the same, the code sintaxis and structure changes a bit.

### Using Arduino ESP32 core 2.x

#### List of instructions

```cpp
hw_timer_t *timer_name = NULL;
```

- Declares a pointer named `timer_name` whose type is `hw_timer_t` (a handle/opaque struct representing a hardware timer on the ESP32) and initializes it to NULL to avoid an uninitialized/dangling pointer. Typical usage: assign the pointer the value returned by `timerBegin(...)`, then use it with API calls such as `timerAttachInterrupt(...)` or `timerAlarmWrite(...)`. Here you just need to change the *timer_name* (don't forget the *).

```cpp
timer_name = timerBegin(uint8_t timer_index, uint16_t prescaler, bool count_up);
```

- timer_index: ESP32 has 4 timers. The timer index can be 0,1,2,3.
- prescaler: The default ESP32 clock runs at 80MHz. If you put `prescaler=80` you can count every µs.
- count_up: If you set `count_up=true`, the timer will count upwards (you'll usually use this mode).

```cpp
timerAttachInterrupt(hw_timer_t *timer_name, void &timer_ISR_name, bool edge‑triggered);
```

- timer_name: The first parameter is the same timer name.
- timer_ISR_name: is the name of the timer callback (don't forget the &).
- edge‑triggered: If you set `edge‑triggered=true`, the timer callback will be edge-triggered, otherwise, it'll be level-triggered (you'll usually use the first one).

```cpp
timerAlarmWrite(hw_timer_t timer_name, uint64_t num_ticks, bool autoreload);
```

- timer_name: The first parameter is the same timer name.
- num_ticks: number of timer ticks before the alarm fires (NOT necessarily microseconds; it is in ticks determined by your prescaler).
- autoreload: bool: true = automatic reload (periodic), false = one‑shot (you'll usually set it to true)

#### Minimal example

```c++
hw_timer_t *timer = NULL; // Pointer to the hardware timer.
// I called it "timer" for simplicity, but it could be named anything. e.g.:
// hw_timer_t *temporizador_0 = NULL;

// ...some code...

// ISR callback for timer interrupt
void IRAM_ATTR timerInterrupt()
{
    // ...some code...
}

// setup function
void setup()
{
    // ...some code...

    // Initialize the timer
    // Parameter 1: Timer index to use. ESP32 has 4 timers => valid values 0,1,2,3
    // Parameter 2: Prescaler. The default ESP32 clock runs at 80MHz. If we set 80, we divide the clock by 80, giving 1,000,000 ticks/s (i.e., 1 tick per µs)
    // Parameter 3: true indicates the timer counts up, false would count down
    timer = timerBegin(0, 80, true);                    // Timer 0, clock divider 80
    timerAttachInterrupt(timer, &timerInterrupt, true); // Attach the interrupt handler
    timerAlarmWrite(timer, 5e5, true);                  // Interrupt every 500ms (500000 µs), auto-reload

    // ...some code...
}

// ...some code...

```

#### Full example

When you pressed the button, the LED will blink five times every 1s (i.e., 500ms ON, 500ms OFF).
You can find a full example [here](https://wokwi.com/projects/413650184825290753).

### Using Arduino ESP32 core 3.x

#### List of instructions

```cpp
hw_timer_t *timer_name = NULL;
```

- Here you just need to change the *timer_name* (don't delete the *).

```cpp
timer_name = timerBegin(uint32_t timer_frequency);
```

- timer_frequency: desired timer tick frequency in Hz (how fast the timer counts).

```cpp
timerAttachInterrupt(hw_timer_t timer_name, void &timerInterrupt);
```

- timer_name: The first parameter is the same timer name.
- timer_ISR_name: is the name of the timer callback (don't forget the &).

```cpp
timerAlarm(hw_timer_t timer_name, uint64_t num_ticks, bool autoreload, uint32_t repeat_count);
```

- timer_name: The first parameter is the same timer name.
- num_ticks: number of timer ticks before the alarm fires (NOT necessarily microseconds; it is in ticks determined by your prescaler).
- autoreload: bool: true = automatic reload (periodic), false = one‑shot (you'll usually set it to true).
- repeat_count: 0 = run indefinitely, >0 = number of repeats.

```cpp
timerStart(timer_name);  
```

- Starts the timer.

```cpp
timerStop(timer_name);  
```

- Stops the timer.

#### Minimal example

```cpp
hw_timer_t *temporizador = NULL; // Pointer to the hardware timer.
// I named it "temporizador" for simplicity, but it can be any valid identifier. e.g.: hw_timer_t *my_timer_0 = NULL;
int timer_frequency = 1000000; // Timer frequency in Hz (how fast the timer counts)

// ...some code...

// ISR callback for timer interrupt
void IRAM_ATTR timerInterrupt()
{
    // ...some code...
}

void setup()
{
    // ...some code...

    temporizador = timerBegin(timer_frequency);          // Initialize the timer that will count at timer_frequency
    timerAttachInterrupt(temporizador, &timerInterrupt); // Attach the interrupt handler
    // Set the timer alarm (param 1) so it calls timerInterrupt every half second (param 2 - value in microseconds)
    // Set true to repeat the alarm (param 3) and 0 to run indefinitely (param 4 - 0 = indefinite)
    timerAlarm(temporizador, 500000, true, 0);

    // ...some code...
}

// ...some code...
```

#### Full example

When you pressed the button, the LED will blink five times every 500ms (i.e., 250ms ON, 250ms OFF).
You can find a full example [here](https://wokwi.com/projects/413651733967519745).

## PWM (LEDC)

### Using Arduino ESP32 core 2.x

```cpp
const int ledChannel = 0;
const int frequency = 8000;
const int resolution = 12;

// ...some code...

void setup() {
    // Configure the LEDC PWM channel with specified frequency and resolution
    ledcSetup(ledChannel, frequency, resolution);

    // Attach the configured PWM channel to the LED pin
    ledcAttachPin(LED_PIN, ledChannel);

    // Example: write an initial duty value to the channel
    // ledcWrite(channel, duty) accepts values in range 0..(2^resolution - 1)
    ledcWrite(ledChannel, duty);
}

// ...some code...

#define LED_PIN 26          // GPIO pin used for the LED

const int ledChannel2 = 0;  // LEDC channel used in the example
const int frequency2 = 8000;
const int resolution2 = 12;

int duty = 0;                // Current PWM duty (0 .. 4095 for 12-bit resolution)

void setup() {
    // Initialize PWM channel and attach pin
    ledcSetup(ledChannel2, frequency2, resolution2);
    ledcAttachPin(LED_PIN, ledChannel2);
}

void loop() {
    // Compute maximum duty for the chosen resolution (12 bits => 4095)
    const int maxDuty = (1 << resolution2) - 1;

    // Ramp the duty from 0 to maxDuty in steps to change LED brightness
    if (duty <= maxDuty) {
        ledcWrite(ledChannel2, duty); // Apply duty value to the PWM channel
        duty += 100;                  // Increase duty (step size controls smoothness/speed)
    } else {
        ledcWrite(ledChannel2, maxDuty); // Ensure max is set (optional)
        duty = 0;                         // Reset duty to start ramp again
    }

    delay(100); // Wait between updates (controls ramp speed)
}
```


### Using Arduino ESP32 core 3.x

```cpp
// PWM configuration for Arduino-ESP32 v3.x example
const int LEDC_FREQ = 8000;         // PWM frequency in Hz
const int LEDC_RESOLUTION = 12;     // PWM resolution in bits (0..(2^resolution - 1))

// ...some code...

void setup() {
    // Attach/configure PWM on LED_PIN using the new ledc attach API
    // Parameters: (pin, frequency, resolution)
    // After this call the pin is configured for PWM with the specified frequency/resolution.
    ledcAttach(LED_PIN, LEDC_FREQ, LEDC_RESOLUTION);

    // Write an initial duty value to the PWM channel tied to LED_PIN.
    // The valid duty range is 0 .. (2^LEDC_RESOLUTION - 1). For 12-bit resolution that is 0..4095.
    ledcWrite(LED_PIN, duty);

    // ...some code...
}
// ...some code...


#define LED_PIN 26

const int LEDC_FREQ = 8000;
const int LEDC_RESOLUTION = 12;

int duty = 0;

void setup() {
    // Attach PWM to pin with frequency and resolution
    ledcAttach(LED_PIN, LEDC_FREQ, LEDC_RESOLUTION);
}

void loop() {
    // For 12-bit resolution the maximum duty is 4095 (2^12 - 1).
    // The code ramps duty from 0 up to 4095 in steps, then resets to 0 to repeat.
    if (duty <= 4095) {
        ledcWrite(LED_PIN, duty); // Apply current duty to the PWM output
        duty += 100;              // Increase duty (step size controls ramp smoothness/speed)
    } else {
        ledcWrite(LED_PIN, duty); // Ensure final duty is written (optional)
        duty = 0;                 // Reset duty to start the ramp again
    }

    delay(100); // Pause between updates; controls how fast the brightness changes
}
```

<!-- 

## Working in real Hardware

### Using the M5Core2

### Using the ESP32

## Working in Simulation



## Troubleshooting

### Using the wrong builder in simulation

### Using the wrong builder with M5Core2 real hardware

### Using the wrong builder with ESP32 real hardware

 -->
