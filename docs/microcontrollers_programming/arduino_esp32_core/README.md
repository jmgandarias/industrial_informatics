# Arduino ESP32 core 2.x and 3.x

 In 2024, the Arduino‑ESP32 core was upgraded from versions 2.x (based on ESP-IDF 4.4) to versions 3.x (based on ESP-IDF 5.1). The underlying API and build system (usually called API or builder) changed some behaviour around several functionalities.

 As you'll use PWM and timers extensively in this course, which suffered breaking changes from this update, it's necessary to consider which version are you using when developing your programs. Below are the most relevant points, practical guidance and short code examples you can use when porting or writing your code.

For more information about this migration you can check [this website](https://docs.espressif.com/projects/arduino-esp32/en/latest/migration_guides/2.x_to_3.0.html).

First of all, you need to know that even if the code sinatxis and structure has suffered some changes, the results in reality that can be achieved using one or another (at least, for what you'll do in this course) are not affected by this migration (considering that the code is well developed independently of the API version).

## Timers

In this course you'll need to program hardware timers. Although the functionalities when using the API versions 2.x or 3.x are basically the same, the code sintaxis and structure changes a bit.

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

More about the Timers in version 2 [here.](https://github.com/espressif/arduino-esp32/blob/release/v2.x/docs/source/api/timer.rst)

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

- Declares a pointer named `timer_name` whose type is `hw_timer_t` (a handle/opaque struct representing a hardware timer on the ESP32) and initializes it to NULL to avoid an uninitialized/dangling pointer. Typical usage: assign the pointer the value returned by `timerBegin(...)`, then use it with API calls such as `timerAttachInterrupt(...)` or `timerAlarmWrite(...)`. Here you just need to change the *timer_name* (don't forget the *).

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

More about the Timers in version 3 [here.](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/timer.html)


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

In this course you'll need to use PWM signals. Although the functionalities when using the API versions 2.x or 3.x are basically the same, the code sintaxis and structure changes a bit.

### Using Arduino ESP32 core 2.x

#### List of instructions

```cpp
void ledcSetup(uint8_t channel, uint32_t frequency, uint8_t resolution);
```

- channel: LEDC channel number (use a free channel, typically 0..15).
- frequency: PWM frequency in Hz.
- resolution: PWM resolution in bits; duty values range 0 .. ($2^{resolution} - 1$).

```cpp
void ledcAttachPin(uint8_t pin, uint8_t channel);
```

Connects (maps) the specified GPIO `pin` to the given LEDC PWM `channel` so the channel's PWM output is driven on that pin.

```cpp
void ledcWrite(uint8_t channel, uint32_t duty);
```

Sets the PWM `duty` cycle (from 0 to $2^{resolution} - 1$)  for a configured LEDC output — updates the output on the `channel` so the pin associated to that channel changes its PWM duty cycle.

More about the PWM in version 2 [here.](https://github.com/espressif/arduino-esp32/blob/release/v2.x/docs/source/api/ledc.rst)

#### Minimal example

```cpp
#define LED_PIN 26

const int led_channel = 0;
const int frequency = 8000;
const int resolution = 12;

int duty = 0;

// ...some code...

void setup() {
    // Configure the LEDC PWM channel with specified frequency and resolution
    ledcSetup(led_channel, frequency, resolution);

    // Attach the configured PWM channel to the LED pin
    ledcAttachPin(LED_PIN, led_channel);

    // Example: write an initial duty value to the channel
    // ledcWrite(channel, duty) accepts values in range 0..(2^resolution - 1)
    ledcWrite(led_channel, duty);
}

// ...some code...

```

#### Full example

You can find a full example [here](https://wokwi.com/projects/443448920632974337).

### Using Arduino ESP32 core 3.x

#### List of instructions

```cpp
void ledcAttach(uint8_t pin, uint32_t frequency, uint8_t resolution);
```

- pin: GPIO pin number to use for PWM (can be treated as int in sketches).
- frequency: PWM frequency in Hz.
- resolution: PWM resolution in bits (duty range 0 .. $2^{resolution} - 1$).

```cpp
void ledcWrite(uint8_t pin, uint32_t duty); 
```

- Sets the PWM `duty` cycle (from 0 to $2^{resolution} - 1$)  for a configured LEDC output — updates the output on the the pin and changes its PWM duty cycle.

More about the PWM in version 3 [here.](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/ledc.html)


#### Minimal example

```cpp
#define LED_PIN 26

// PWM configuration for Arduino-ESP32 v3.x example
const int ledc_freq = 8000;         // PWM frequency in Hz
const int ledc_resolution = 12;     // PWM resolution in bits (0..(2^resolution - 1))
int duty = 0;

// ...some code...

void setup() {
    // Attach/configure PWM on LED_PIN using the new ledc attach API
    // Parameters: (pin, frequency, resolution)
    // After this call the pin is configured for PWM with the specified frequency/resolution.
    ledcAttach(LED_PIN, ledc_freq, ledc_resolution);

    // Write an initial duty value to the PWM channel tied to LED_PIN.
    // The valid duty range is 0 .. (2^ledc_resolution - 1). For 12-bit resolution that is 0..4095.
    ledcWrite(LED_PIN, duty);

    // ...some code...
}
// ...some code...


```

#### Full example

You can find a full example [here](https://wokwi.com/projects/443449136939563009).


## Working in Simulation with the Arduino ESP32 core 2.x

When you open a new project in wokwi, by default the core 3.x is used. Therefore, if you try to use instructions that correspond to core 2.x, you'll receive a compilation error. 

If you want to use core 2.x in wokwi you can do it by configuring the `diagram.json`. You need to include `"builder": "esp32-core-2.0.3"`in the `"attrs": { }`.

**Example of `diagram.json` with builder 3.x in wokwi:**

```json
{
  "version": 1,
  "author": "Juan M. Gandarias",
  "editor": "wokwi",
  "parts": [
    {
      "type": "board-esp32-devkit-c-v4",
      "id": "esp",
      "top": -19.2,
      "left": -33.56,
      "attrs": { }
    }
  ],
  "connections": [ [ "esp:TX", "$serialMonitor:RX", "", [] ], [ "esp:RX", "$serialMonitor:TX", "", [] ] ],
  "dependencies": {}
}
```

**Example of `diagram.json` with builder 2.x in wokwi:**

```json
{
  "version": 1,
  "author": "Juan M. Gandarias",
  "editor": "wokwi",
  "parts": [
    {
      "type": "board-esp32-devkit-c-v4",
      "id": "esp",
      "top": -19.2,
      "left": -33.56,
      "attrs": { "builder": "esp32-core-2.0.3" }
    }
  ],
  "connections": [ [ "esp:TX", "$serialMonitor:RX", "", [] ], [ "esp:RX", "$serialMonitor:TX", "", [] ] ],
  "dependencies": {}
}
```



<!-- 

## Working in real Hardware

### Using the M5Core2

### Using the ESP32





## Troubleshooting

### Using the wrong builder in simulation

### Using the wrong builder with M5Core2 real hardware

### Using the wrong builder with ESP32 real hardware

 -->
