---
title: Cheatsheet - ESP32 Programming
author: Juan M. Gandarias
institution: University of Málaga
---

# 📋 ESP32 Programming Cheatsheet

> Quick reference guide for instructions and functions for the Industrial Informatics course  
> By [Juan M. Gandarias](https://jmgandarias.com) | [jmgandarias@uma.es](mailto:jmgandarias@uma.es)

---

## 0️⃣ Initial Setup and Configuration

### Basic Program Structure

```cpp

const int LED_PIN = 2;

void setup() {
    Serial.begin(115200);
    delay(1000);
    pinMode(LED_PIN, OUTPUT);
    Serial.println("ESP32 initialized");
}

void loop() {
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
}
```

---

## 📡 Serial Communication (Debug)

| Function | Description |
| :--- | :--- |
| **`Serial.begin(baudrate)`** | Initializes serial port (115200 recommended) |
| **`Serial.print()`** | Prints without newline |
| **`Serial.println()`** | Prints with newline |
| **`Serial.printf()`** | Prints with format |
| **`Serial.available()`** | Bytes available in buffer |
| **`Serial.read()`** | Reads one byte |
| **`Serial.readString()`** | Reads complete line |

---

## 1️⃣ Digital, Analog I/O and PWM (LEDC)

### 🔌 GPIOs and Analog Reading

| Function | Description |
| :--- | :--- |
| **`pinMode(pin, mode)`** | Configures pin as `INPUT`, `OUTPUT` or `INPUT_PULLUP` (activates internal pull-up resistor) |
| **`digitalWrite(pin, val)`** | Sets digital output state (`HIGH` or `LOW`) |
| **`digitalRead(pin)`** | Reads pin logic state → `HIGH` (1) or `LOW` (0) |
| **`analogRead(pin)`** | A/D conversion → Returns integer between `0`-`4095` (default 12 bits) |

**Example:**
```cpp
const int BUTTON = 4;
const int LED = 2;

void setup() {
    pinMode(BUTTON, INPUT_PULLUP);
    pinMode(LED, OUTPUT);
}

void loop() {
    if (digitalRead(BUTTON) == LOW) {
        digitalWrite(LED, HIGH);
    } else {
        digitalWrite(LED, LOW);
    }
}
```

### ⚡ PWM Control with LEDC

PWM management with LEDC simplifies configuration: frequency and resolution are linked directly to the pin without managing channels explicitly.

```cpp
// Configure and start PWM on a pin
ledcAttach(pin, frequency, resolution_bits);

// Set the duty cycle
ledcWrite(pin, duty_value);
```

| Function | Parameters | Example |
| :--- | :--- | :--- |
| **`ledcAttach(pin, freq, res)`** | Assigns PWM to pin directly | `ledcAttach(5, 8000, 12)` → 8kHz, 12 bits (0-4095) |
| **`ledcWrite(pin, duty)`** | Sets duty cycle | `ledcWrite(5, 2048)` → 50% duty cycle |

**Resolution:** Default 12 bits (0-4095)

---

## 2️⃣ Interrupts and Hardware Timers

### 🔔 External Interrupts (GPIO)

| Element | Description |
| :--- | :--- |
| **`IRAM_ATTR`** | Mandatory attribute in ISR functions. Stores function in fast internal RAM (IRAM) |
| **`attachInterrupt(...)`** | `attachInterrupt(digitalPinToInterrupt(pin), ISR_callback, mode)` |
| **Available modes** | `RISING` (rising edge ↑) • `FALLING` (falling edge ↓) • `CHANGE` (any change) |

**Button example with debouncing:**
```cpp
const int BUTTON_PIN = 4;
volatile int counter = 0;

void IRAM_ATTR handleButtonPress() {
    counter++;
}

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    
    // Configure interrupt on falling edge
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonPress, FALLING);
}

void loop() {
    Serial.printf("Button presses: %d\n", counter);
    delay(500);
}
```

⚠️ **Important in ISR:**
- Keep code fast and simple
- Don't use Serial.print() (it's slow)
- Use `volatile` variables for shared data

### ⏱️ Hardware Timers

ESP32 hardware timers use a frequency-oriented API with microsecond timing.

**Typical configuration:**
```cpp
hw_timer_t *timer = NULL;

// 1. Initialize at counting frequency in Hz
timer = timerBegin(timer_frequency);

// 2. Attach ISR function
timerAttachInterrupt(timer, &timerInterruptISR);

// 3. Configure alarm (microseconds)
timerAlarm(timer, period_us, autoreload, reload_count); 

// 4. Execution control
timerStart(timer);
timerStop(timer);
```

| Function | Description |
| :--- | :--- |
| **`timerBegin(freq_hz)`** | Creates timer at frequency in Hz. E.g: `1000000` Hz = 1 tick/µs |
| **`timerAttachInterrupt(timer, &ISR)`** | Binds ISR function to execute at each alarm |
| **`timerAlarm(timer, period, reload, count)`** | Configures alarm: `period` (µs), `reload` (periodic boolean), `count` (0=indefinite) |
| **`timerStart(timer)`** | Starts timer counting |
| **`timerStop(timer)`** | Stops timer counting |

**Complete example - Periodic timer:**
```cpp
hw_timer_t *timer = NULL;
volatile int counter = 0;

void IRAM_ATTR onTimerAlarm() {
    counter++;
}

void setup() {
    Serial.begin(115200);
    
    // Timer at 1 MHz (1 tick = 1 microsecond)
    timer = timerBegin(1000000);
    timerAttachInterrupt(timer, &onTimerAlarm);
    
    // Alarm every 1,000,000 µs (1 second)
    timerAlarm(timer, 1000000, true, 0);
    timerStart(timer);
}

void loop() {
    if (counter > 0) {
        Serial.printf("Counter: %d\n", counter);
        counter = 0;
        delay(100);
    }
}
```

⚠️ **Warning: real ESP32 timer limits**

The ESP32 hardware timer does not accept any arbitrary frequency. In the Arduino ESP32 implementation, the divider used by the timer must stay between `2` and `65536`, and the timer source is typically `80 MHz` on ESP32.

Therefore, the real range of `timerBegin(freq_hz)` is approximately:

- Minimum practical frequency: `80,000,000 / 65536 ≈ 1220.7 Hz`
- Maximum practical frequency: `80,000,000 / 2 = 40,000,000 Hz = 40 MHz`

This means that a frequency like `500 Hz` is below the minimum supported range for a direct timer configuration. In other words, `timerBegin(500)` is not a valid direct hardware setting for the ESP32 timer.

A valid approach is to configure the timer at a higher base frequency and then generate the desired period in software. For example:

```cpp
// Use 1 MHz timer resolution
timer = timerBegin(1000000);

// 500 Hz = 2 ms = 2000 us
// Therefore the alarm period is 2000 microseconds
timerAlarm(timer, 2000, true, 0);
```

So for a target of `500 Hz`, the correct configuration is usually `timerBegin(1000000)` and `timerAlarm(timer, 2000, true, 0)`, not `timerBegin(500)`.

For `timerAlarm(...)`, the period is expressed in microseconds, so the same rule applies: the hardware timer is configured with a supported base frequency, and the desired period is produced by choosing the right alarm value.

---

## 3️⃣ Software Timers (`Ticker.h`)

Executes periodic tasks asynchronously through software timing.

| Function | Description | Example |
| :--- | :--- | :--- |
| **`Ticker ticker;`** | Declares a Ticker object | - |
| **`attach(seconds, callback)`** | Executes callback periodically (supports decimals) | `ticker.attach(0.5, myFunction)` |
| **`attach_ms(milliseconds, callback)`** | Equivalent in milliseconds | `ticker.attach_ms(500, myFunction)` |
| **`detach()`** | Stops periodic execution | `ticker.detach()` |

**Usage example:**
```cpp
#include <Ticker.h>

Ticker blinker;

void blinkLED() {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    blinker.attach(0.5, blinkLED);
}

void loop() {
    // Ticker runs in background
}
```

---

### ✅ ISR (Interrupt Service Routines) Checklist

**✓ DO:**
- Fast and simple operations
- Use `IRAM_ATTR` mandatory
- Use `volatile` variables
- Use `xSemaphoreGiveFromISR()` for signaling

**✗ DON'T:**
- Slow operations (Serial, WiFi)
- Calls to `delay()`
- Memory allocation
- printf() or heavy functions

---

## 4️⃣ Multitasking and FreeRTOS

ESP32 integrates **two CPU cores** (Core 0 and Core 1). FreeRTOS enables managing concurrent threads on both.

### 🚀 Task Creation and Pinning

```cpp
xTaskCreatePinnedToCore(
    TaskFunction,   // void task(void *param)
    "TaskName",     // Debug label
    StackSize,      // RAM memory (4-byte words)
    Parameters,     // Input parameters (typically NULL)
    Priority,       // Priority (0=lowest)
    &TaskHandle,    // Task handle
    CoreID          // Core (0 or 1)
);
```

| Parameter | Description |
| :--- | :--- |
| **TaskFunction** | Function `void taskName(void *pvParameters)` |
| **StackSize** | Memory in bytes (e.g: `2048` = 2KB) |
| **Priority** | 0-24 (higher value = higher priority) |
| **CoreID** | `0` = Core 0 • `1` = Core 1 |

### ⏱️ Useful FreeRTOS Functions

```cpp
// Precise delay in periodic tasks (without temporal drift)
vTaskDelayUntil(&xLastWakeTime, xPeriod);

// Gets current system tick
xLastWakeTime = xTaskGetTickCount();

// Converts milliseconds to FreeRTOS ticks
TickType_t xPeriod = pdMS_TO_TICKS(333); 

// Returns executing core ID (0 or 1)
int coreID = xPortGetCoreID();
```

| Function | Purpose | Note |
| :--- | :--- | :--- |
| **`vTaskDelayUntil()`** | Precise periodic delay | Prefer over `delay()` in tasks |
| **`xTaskGetTickCount()`** | Gets current tick | For synchronization |
| **`pdMS_TO_TICKS(ms)`** | Converts ms to ticks | Reusable |
| **`xPortGetCoreID()`** | Current core | Useful for debug |

### 🗑️ Task Lifecycle Management

| Function | Description |
| :--- | :--- |
| **`vTaskDelete(NULL)`** | Deletes current task. `NULL` = own task |
| **`vTaskDelete(xTaskHandle)`** | Deletes specific task |

**One-time execution tasks:**
```cpp
void vTaskOneShot(void *pvParameters) {
  // Do work
  Serial.println("Task executed once");
  
  // Delete task to free stack
  vTaskDelete(NULL);
}

void setup() {
  xTaskCreatePinnedToCore(vTaskOneShot, "OneShot", 2048, NULL, 1, NULL, 0);
}

void loop() {
  vTaskDelete(NULL);  // Delete loop() in FreeRTOS
}
```


### 🔐 Synchronization and Mutex (Shared Resource Protection)

#### 🛡️ Basic Concepts

**Critical Section:** Code block where a task accesses a shared resource.

**Mutex:** Mechanism allowing only ONE task to access a resource at a time.

**Race Condition:** Problem occurring when two tasks simultaneously access the same resource without synchronization.

#### 🔒 Mutex Functions

| Function | Description |
| :--- | :--- |
| **`xSemaphoreCreateMutex()`** | Creates a mutex. Returns `SemaphoreHandle_t` or NULL if failed |
| **`xSemaphoreTake(mutex, timeout)`** | Acquires mutex (waits if busy). Timeout: `portMAX_DELAY` = infinite wait |
| **`xSemaphoreGive(mutex)`** | Releases mutex for other tasks to use |

**Return values:**
- `pdTRUE` (1): Operation successful
- `pdFALSE` (0): Timeout reached without acquiring mutex

#### ✅ Safe Pattern - With Mutex

```cpp
#include <Arduino.h>

SemaphoreHandle_t xMutexSerial;

void vTask1(void *pvParameters) {
  for (;;) {
    // Try to take mutex
    if (xSemaphoreTake(xMutexSerial, portMAX_DELAY) == pdTRUE) {
      
      // --- PROTECTED CRITICAL SECTION ---
      Serial.println("[TASK 1] Using Serial...");
      vTaskDelay(pdMS_TO_TICKS(100));
      Serial.println("[TASK 1] Finished");
      // --------------------------------

      // Release mutex
      xSemaphoreGive(xMutexSerial);
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void vTask2(void *pvParameters) {
  for (;;) {
    if (xSemaphoreTake(xMutexSerial, portMAX_DELAY) == pdTRUE) {
      
      // --- PROTECTED CRITICAL SECTION ---
      Serial.println("  [TASK 2] Writing...");
      vTaskDelay(pdMS_TO_TICKS(50));
      Serial.println("  [TASK 2] Done");
      // --------------------------------

      xSemaphoreGive(xMutexSerial);
    }

    vTaskDelay(pdMS_TO_TICKS(700));
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Create mutex BEFORE tasks
  xMutexSerial = xSemaphoreCreateMutex();

  if (xMutexSerial != NULL) {
    xTaskCreatePinnedToCore(vTask1, "Task_1", 2048, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(vTask2, "Task_2", 2048, NULL, 1, NULL, 1);
  }
}

void loop() {
  vTaskDelete(NULL);
}
```

**Advantages:**
- ✅ Complete and unmixed Serial writes
- ✅ Ordered resource access
- ✅ Prevents data corruption

---

## 5️⃣ Connectivity (WiFi and MQTT)

### 📡 WiFi Management (`WiFi.h`)

| Function | Description | Returns |
| :--- | :--- | :--- |
| **`WiFi.begin(SSID, PASSWORD)`** | Initializes connection to Access Point | - |
| **`WiFi.status()`** | Network link state | `WL_CONNECTED`, `WL_DISCONNECTED`, etc. |
| **`WiFi.localIP()`** | Assigned local IP address | `IPAddress` object |
| **`WiFi.disconnect()`** | Disconnects from WiFi network | - |
| **`WiFi.RSSI()`** | Signal strength (dBm) | Negative, closer to 0 = better |

**Example with automatic reconnection:**
```cpp
const char *ssid = "MySSID";
const char *password = "MyPassword";
const int TIMEOUT = 10000;

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < TIMEOUT) {
        delay(500);
        Serial.print(".");
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("\nIP: %s | RSSI: %d dBm\n", 
            WiFi.localIP().toString().c_str(), WiFi.RSSI());
    } else {
        Serial.println("\nConnection failed");
    }
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Reconnecting WiFi...");
        WiFi.reconnect();
        delay(5000);
    }
}
```

### 📨 MQTT Protocol (`PubSubClient.h`)

Client/broker communication under **Publish/Subscribe** pattern.

**Initialization and connection:**
```cpp
WiFiClient espClient;
PubSubClient client(espClient);

// Assign broker and port
client.setServer("broker.example.com", 1883);

// Register callback for received messages
client.setCallback(OnMqttReceived);

// Connect with authentication (optional)
client.connect("clientID", "user", "password");

// Maintenance loop (call in setup() or loop())
client.loop();
```

**Publishing and Subscription:**
```cpp
// Publish message
client.publish("topic/name", "payload_text");

// Subscribe to topic
client.subscribe("topic/name");

// Callback for received messages
void OnMqttReceived(char *topic, byte *payload, unsigned int length) {
    char message[length + 1];
    memcpy(message, payload, length);
    message[length] = '\0';
    
    Serial.printf("Topic: %s | Payload: %s\n", topic, message);
}
```

| Function | Description |
| :--- | :--- |
| **`setServer(host, port)`** | Defines MQTT broker and port |
| **`setCallback(function)`** | Registers function for received messages |
| **`connect(id, [user], [pass])`** | Connects and authenticates with broker |
| **`loop()`** | Maintains connection and processes packets |
| **`publish(topic, payload)`** | Publishes message to topic |
| **`subscribe(topic)`** | Subscribes to topic |
| **`connected()`** | Checks if connected |
| **`disconnect()`** | Disconnects from MQTT broker |

**Pattern with automatic reconnection:**
```cpp
#include <PubSubClient.h>
#include <WiFi.h>

WiFiClient espClient;
PubSubClient client(espClient);

void reconnectMQTT() {
    if (client.connected()) return;
    
    Serial.print("Connecting MQTT...");
    if (client.connect("ESP32", "user", "password")) {
        Serial.println(" OK");
        client.subscribe("sensor/temperature");
    } else {
        Serial.printf(" Error: %d\n", client.state());
        delay(5000);
    }
}

void loop() {
    if (!client.connected()) {
        reconnectMQTT();
    }
    client.loop();
    
    static unsigned long lastTime = 0;
    if (millis() - lastTime > 10000) {
        float temp = 25.5;
        client.publish("sensor/temperature", String(temp).c_str());
        lastTime = millis();
    }
}
```

---

## 6️⃣ M5Stack Core2: Hardware, Display and IMU

The `#include<M5Unified.h>` library abstracts the integrated hardware of the M5Core2 development board.

### 🔌 Initialization and Power Management

| Function | Description |
| :--- | :--- |
| **`M5.begin()`** | Initializes I²C bus, display, AXP192 chip and peripherals |
| **`M5.update()`** | Updates button state and touch events (call in `loop()`) |
| **`M5.Axp.SetVibration(bool)`** | Activates (`true`) or deactivates (`false`) vibration motor |

### 📱 TFT LCD Display

```cpp
// Paint background
M5.Lcd.fillScreen(BLACK);

// Set text and background color
M5.Lcd.setTextColor(WHITE, BLACK);

// Text scale (integers: 1, 2, 3, etc.)
M5.Lcd.setTextSize(2);

// Position cursor in pixels (x, y)
M5.Lcd.setCursor(10, 20);

// Write formatted text
M5.Lcd.printf("Value: %d\n", 42);
M5.Lcd.println("Hello World");
```

| Function | Description |
| :--- | :--- |
| **`fillScreen(color)`** | Paints screen with specified color |
| **`setTextColor(text, bg)`** | Sets text and background colors |
| **`setTextSize(size)`** | Text scaling |
| **`setCursor(x, y)`** | Position in pixels (top-left origin) |
| **`printf()` / `println()`** | Write formatted text |

**Available colors:** `BLACK`, `WHITE`, `RED`, `GREEN`, `BLUE`, `YELLOW`, `CYAN`, `MAGENTA`

### 👆 Capacitive Touch Screen

```cpp
TouchPoint_t pixel_pos;

if (M5.Touch.ispressed()) {
    pixel_pos = M5.Touch.getPressPoint();
    int16_t x = pixel_pos.x;  // X coordinate (0-319)
    int16_t y = pixel_pos.y;  // Y coordinate (0-239)
    
    Serial.printf("Touch: (%d, %d)\n", x, y);
}
```

| Function | Description |
| :--- | :--- |
| **`M5.Touch.ispressed()`** | Is screen being touched? |
| **`M5.Touch.getPressPoint()`** | Gets touch coordinates (x, y) |

### 🎯 Inertial Sensor (6-Axis IMU)

Accelerometer and gyroscope integrated on the board.

```cpp
// Initialize IMU
M5.IMU.Init();

// Read accelerations (in G)
float accX, accY, accZ;
M5.IMU.getAccelData(&accX, &accY, &accZ);

// Read estimated orientation (in degrees)
float pitch, roll, yaw;
M5.IMU.getAhrsData(&pitch, &roll, &yaw);

Serial.printf("Acc: (%.2f, %.2f, %.2f) G\n", accX, accY, accZ);
Serial.printf("Ori: P=%.1f° R=%.1f° Y=%.1f°\n", pitch, roll, yaw);
```

| Function | Parameters | Units |
| :--- | :--- | :--- |
| **`M5.IMU.Init()`** | - | Initialization |
| **`getAccelData(&x, &y, &z)`** | float pointers | Acceleration in **G** |
| **`getAhrsData(&p, &r, &y)`** | float pointers | Angles in **degrees** |
| **`getGyroData(&x, &y, &z)`** | float pointers | Angular velocity in **°/s** |

**Reference axes:** X (lateral), Y (front), Z (vertical)

---


## 🔧 Utility Functions

### 📐 Value Mapping and Constraint

| Function | Description | Example |
| :--- | :--- | :--- |
| **`map(value, fromLow, fromHigh, toLow, toHigh)`** | Maps value from one range to another | `map(500, 0, 4095, 0, 320)` |
| **`constrain(value, min, max)`** | Constrains value between limits | `constrain(x, 0, 319)` |
| **`abs(value)`** | Absolute value | `abs(-50)` → `50` |
| **`min(a, b)`** | Minimum of two values | `min(10, 20)` → `10` |
| **`max(a, b)`** | Maximum of two values | `max(10, 20)` → `20` |

---

## 📌 Tips, Best Practices and Patterns

### 🔐 Synchronization and Mutex

- **ALWAYS create Mutex BEFORE tasks** that will use it
- **Short critical sections**: Minimize time between `xSemaphoreTake()` and `xSemaphoreGive()`
- **Use `portMAX_DELAY`** when infinite wait needed in critical mutex
- **Avoid mutex nesting**: Don't take mutex A while holding mutex B (deadlock)

### ⚙️ Optimization and FreeRTOS

- **Priority 0-24**: Higher number = higher priority. Higher priority tasks preempt lower ones
- **Stack size**: Minimum 2048 bytes for normal tasks. Increase if using buffers or recursion
- **`vTaskDelete(NULL)`**: Call in `loop()` in ESP32/FreeRTOS pure
- **pdMS_TO_TICKS()**: Always use for ms to ticks conversion (more portable than hardcoding)
- **vTaskDelayUntil()**: More precise than `vTaskDelay()` for demanding periodic tasks

### 🎯 Interrupt vs FreeRTOS

- **ISR (`IRAM_ATTR`)**: For critical and fast events (GPIO, timers)
- **FreeRTOS Tasks**: For long-running tasks or resource control

### 📊 Serial Debugging

- **115200 baud**: Standard. Change only if specific problems
- **`Serial.printf()`**: More flexible than multiple `Serial.print()`. Use specifiers: `%d`, `%f`, `%s`
- **Mutex in Serial**: Mandatory in multi-task for complete messages
- **Timeout in Serial**: `while (!Serial);` in setup to wait for USB connection in development

### 🚀 Recommended Patterns

**For critical applications:**
```cpp
// 1. Create mutex at startup
xMutex = xSemaphoreCreateMutex();

// 2. Use in critical sections
if (xSemaphoreTake(xMutex, pdMS_TO_TICKS(1000)) == pdTRUE) {
    // Protected code
    xSemaphoreGive(xMutex);
} else {
    // Timeout: resource busy
    Serial.println("Timeout!");
}
```

---

## 📚 Documentation and Resources

### 🌐 Official References
- [Arduino ESP32 Official Documentation](https://docs.espressif.com/projects/arduino-esp32/)
- [FreeRTOS Reference Manual](https://www.freertos.org/RTOS-task-management.html)
- [M5Stack Documentation](https://docs.m5stack.com/)
- [ESP32 Technical Reference Manual](https://www.espressif.com/en/products/socs/esp32)

### 📖 Key Topics by Section

| Section | Main Concept | Use Case |
| :--- | :--- | :--- |
| Digital/Analog GPIO | Input/Output of bits and analog values | LEDs, buttons, sensors |
| Interrupts | Quick response to hardware events | Rapid change detection |
| Timers | Hardware periodic event generation | PWM, periodic sampling |
| Ticker | Software periodic tasks | Non-critical status update |
| FreeRTOS Multitask | Controlled concurrent execution | Multiple simultaneous processes |
| Mutex/Synchronization | Shared resource protection | Safe access to Serial, LCD, GPIO |
| WiFi/MQTT | Network connectivity | Remote communication, IoT |
| M5Core2 | Integrated development platform | Applications with display and sensors |

### 💡 Recommended Learning Path

1. **Basic Level**: GPIO → Serial → Interrupts
2. **Intermediate Level**: Timers → Ticker → Basic FreeRTOS
3. **Advanced Level**: Mutex → Coordinated multi-task → WiFi/MQTT
4. **Applications**: M5Core2 → Integrating projects

### 🔗 Useful Tools

- **Arduino IDE**: Download at [arduino.cc](https://www.arduino.cc/en/software)
- **PlatformIO**: Powerful alternative in VS Code
- **Mosquitto**: Local MQTT broker for testing
- **Wokwi**: Online ESP32 simulator ([wokwi.com](https://wokwi.com))

### 🎓 Learning Advice

- **Read code before executing it**: Understand what each function does
- **Experiment with values**: Change timings, priorities, periods
- **Monitor with Serial**: Use `Serial.printf()` for continuous debug
- **Isolate problems**: Test each component separately before integrating
- **Document your work**: Comment code, understand why it works

---

**Last update:** 2026-07-28 | **Version:** 2.0 | **For:** Bachelor Degree in Industrial Electronics Engineering
- [ESP32 Datasheet](https://www.espressif.com/en/products/socs/esp32)