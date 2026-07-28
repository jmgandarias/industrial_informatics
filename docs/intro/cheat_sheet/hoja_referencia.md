---
title: Cheatsheet - Programación ESP32
author: Juan M. Gandarias
institution: Grado en Ingeniería Electrónica Industrial - Universidad de Málaga
---

# 📋 Cheatsheet de Programación ESP32

> Guía rápida de instrucciones y funciones para la asignatura de Informática Industrial  
> Por [Juan M. Gandarias](https://jmgandarias.com) | [jmgandarias@uma.es](mailto:jmgandarias@uma.es)

---

## 0️⃣ Configuración Inicial y Setup

### Estructura Básica de un Programa

```cpp

const int LED_PIN = 2;

void setup() {
    Serial.begin(115200);
    delay(1000);
    pinMode(LED_PIN, OUTPUT);
    Serial.println("ESP32 iniciado");
}

void loop() {
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
}
```

---

## 📡 Comunicación Serial (Debug)

| Función | Descripción |
| :--- | :--- |
| **`Serial.begin(baudrate)`** | Inicializa puerto serie (115200 recomendado) |
| **`Serial.print()`** | Imprime sin salto de línea |
| **`Serial.println()`** | Imprime con salto de línea |
| **`Serial.printf()`** | Imprime con formato |
| **`Serial.available()`** | Bytes disponibles en buffer |
| **`Serial.read()`** | Lee un byte |
| **`Serial.readString()`** | Lee línea completa |

---

## 1️⃣ Entrada y Salida Digital, Analógica y PWM (LEDC)

### 🔌 GPIOs y Lectura Analógica

| Función | Descripción |
| :--- | :--- |
| **`pinMode(pin, mode)`** | Configura un pin como `INPUT`, `OUTPUT` o `INPUT_PULLUP` (activa resistencia interna pull-up) |
| **`digitalWrite(pin, val)`** | Establece estado de salida digital (`HIGH` o `LOW`) |
| **`digitalRead(pin)`** | Lee el estado lógico de un pin → `HIGH` (1) o `LOW` (0) |
| **`analogRead(pin)`** | Conversión A/D → Devuelve entero entre `0`-`4095` (12 bits por defecto) |

**Ejemplo:**
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

### ⚡ Control PWM con LEDC

La gestión PWM con LEDC simplifica la configuración: frecuencia y resolución se enlazan directamente al pin sin necesidad de gestionar canales explícitamente.

```cpp
// Configurar e iniciar PWM en un pin
ledcAttach(pin, frequency, resolution_bits);

// Establecer el ciclo de trabajo (duty cycle)
ledcWrite(pin, duty_value);
```

| Función | Parámetros | Ejemplo |
| :--- | :--- | :--- |
| **`ledcAttach(pin, freq, res)`** | Asigna PWM al pin directamente | `ledcAttach(5, 8000, 12)` → 8kHz, 12 bits (0-4095) |
| **`ledcWrite(pin, duty)`** | Establece ciclo de trabajo | `ledcWrite(5, 2048)` → 50% duty cycle |

**Resolución:** Por defecto 12 bits (0-4095)

---

## 2️⃣ Interrupciones y Timers Hardware

### 🔔 Interrupciones Externas (GPIO)

| Elemento | Descripción |
| :--- | :--- |
| **`IRAM_ATTR`** | Atributo obligatorio en funciones ISR. Guarda la función en RAM interna rápida (IRAM) |
| **`attachInterrupt(...)`** | `attachInterrupt(digitalPinToInterrupt(pin), ISR_callback, mode)` |
| **Modos disponibles** | `RISING` (flanco ↑) • `FALLING` (flanco ↓) • `CHANGE` (cualquier cambio) |

**Ejemplo de botón con anti-rebote:**
```cpp
const int BUTTON_PIN = 4;
volatile int contador = 0;

void IRAM_ATTR handleButtonPress() {
    contador++;
}

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    
    // Configurar interrupción en flanco de bajada
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonPress, FALLING);
}

void loop() {
    Serial.printf("Pulsaciones: %d\n", contador);
    delay(500);
}
```

⚠️ **Importante en ISR:**
- Mantener código rápido y simple
- No usar Serial.print() (es lento)
- Usar variables `volatile` para datos compartidos

### ⏱️ Timers Hardware

Los temporizadores por hardware en ESP32 utilizan una API orientada a frecuencia con temporizaciones en microsegundos.

**Configuración típica:**
```cpp
hw_timer_t *timer = NULL;

// 1. Inicializar a frecuencia de conteo en Hz
timer = timerBegin(timer_frequency);

// 2. Enlazar función ISR
timerAttachInterrupt(timer, &timerInterruptISR);

// 3. Configurar alarma (microsegundos)
timerAlarm(timer, period_us, autoreload, reload_count); 

// 4. Control de ejecución
timerStart(timer);
timerStop(timer);
```

| Función | Descripción |
| :--- | :--- |
| **`timerBegin(freq_hz)`** | Crea timer a frecuencia en Hz. Ej: `1000000` Hz = 1 tick/µs |
| **`timerAttachInterrupt(timer, &ISR)`** | Enlaza función ISR a ejecutar en cada alarma |
| **`timerAlarm(timer, period, reload, count)`** | Configura alarma: `period` (µs), `reload` (boolean periódico), `count` (0=indefinido) |
| **`timerStart(timer)`** | Inicia la cuenta del timer |
| **`timerStop(timer)`** | Detiene la cuenta del timer |

**Ejemplo completo - Timer periódico:**
```cpp
hw_timer_t *timer = NULL;
volatile int contador = 0;

void IRAM_ATTR onTimerAlarm() {
    contador++;
}

void setup() {
    Serial.begin(115200);
    
    // Timer a 1 MHz (1 tick = 1 microsegundo)
    timer = timerBegin(1000000);
    timerAttachInterrupt(timer, &onTimerAlarm);
    
    // Alarma cada 1,000,000 µs (1 segundo)
    timerAlarm(timer, 1000000, true, 0);
    timerStart(timer);
}

void loop() {
    if (contador > 0) {
        Serial.printf("Contador: %d\n", contador);
        contador = 0;
        delay(100);
    }
}
```

---

## 3️⃣ Temporizadores por Software (`Ticker.h`)

Ejecuta tareas periódicas de manera asíncrona mediante temporizaciones software.

| Función | Descripción | Ejemplo |
| :--- | :--- | :--- |
| **`Ticker ticker;`** | Declara un objeto Ticker | - |
| **`attach(segundos, callback)`** | Ejecuta callback periódicamente (soporta decimales) | `ticker.attach(0.5, myFunction)` |
| **`attach_ms(milisegundos, callback)`** | Equivalente en milisegundos | `ticker.attach_ms(500, myFunction)` |
| **`detach()`** | Detiene la ejecución periódica | `ticker.detach()` |

**Ejemplo de uso:**
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
    // Ticker funciona en background
}
```

---

### ✅ Checklist para ISR (Interrupt Service Routines)

**✓ Hacer:**
- Operaciones rápidas y simples
- Usar `IRAM_ATTR` obligatoriamente
- Usar variables `volatile`
- Usar `xSemaphoreGiveFromISR()` para señalización

**✗ NO hacer:**
- Operaciones lentas (Serial, WiFi)
- Llamadas a `delay()`
- Allocación de memoria
- printf() o funciones pesadas

---


## 4️⃣ Multitarea y FreeRTOS 

El ESP32 integra **dos núcleos CPU** (Core 0 y Core 1). FreeRTOS permite gestionar hilos concurrentes en ambos.

### 🚀 Creación y Paginación de Tareas

```cpp
xTaskCreatePinnedToCore(
    TaskFunction,   // void task(void *param)
    "TaskName",     // Etiqueta de depuración
    StackSize,      // Memoria RAM (palabras de 4 bytes)
    Parameters,     // Parámetros entrada (típicamente NULL)
    Priority,       // Prioridad (0=más baja)
    &TaskHandle,    // Manejador de la tarea
    CoreID          // Núcleo (0 o 1)
);
```

| Parámetro | Descripción |
| :--- | :--- |
| **TaskFunction** | Función `void nombreTarea(void *pvParameters)` |
| **StackSize** | Memoria en bytes (ej: `2048` = 2KB) |
| **Priority** | 0-24 (mayor valor = mayor prioridad) |
| **CoreID** | `0` = Core 0 • `1` = Core 1 |

### ⏱️ Funciones Útiles de FreeRTOS

```cpp
// Retardo preciso en tareas periódicas (sin deriva temporal)
vTaskDelayUntil(&xLastWakeTime, xPeriod);

// Obtiene el tick actual del sistema
xLastWakeTime = xTaskGetTickCount();

// Convierte milisegundos a ticks de FreeRTOS
TickType_t xPeriod = pdMS_TO_TICKS(333); 

// Devuelve el núcleo en ejecución (0 o 1)
int coreID = xPortGetCoreID();
```

| Función | Propósito | Nota |
| :--- | :--- | :--- |
| **`vTaskDelayUntil()`** | Retardo preciso periódico | Prefiere a `delay()` en tareas |
| **`xTaskGetTickCount()`** | Obtiene tick actual | Para sincronización |
| **`pdMS_TO_TICKS(ms)`** | Convierte ms a ticks | Reutilizable |
| **`xPortGetCoreID()`** | Núcleo actual | Útil para debug |


### 🗑️ Gestión del Ciclo de Vida de Tareas

| Función | Descripción |
| :--- | :--- |
| **`vTaskDelete(NULL)`** | Elimina la tarea actual. `NULL` = tarea propia |
| **`vTaskDelete(xTaskHandle)`** | Elimina una tarea específica |

**Tareas que se ejecutan UNA SOLA VEZ:**
```cpp
void vTaskOneShot(void *pvParameters) {
  // Hacer trabajo
  Serial.println("Tarea ejecutada una sola vez");
  
  // Eliminar la tarea para liberar stack
  vTaskDelete(NULL);
}

void setup() {
  xTaskCreatePinnedToCore(vTaskOneShot, "OneShot", 2048, NULL, 1, NULL, 0);
}

void loop() {
  vTaskDelete(NULL);  // Eliminar loop() en FreeRTOS
}
```

---

## 5️⃣ Conectividad (WiFi y MQTT)

### 📡 Gestión de WiFi (`WiFi.h`)

| Función | Descripción | Devuelve |
| :--- | :--- | :--- |
| **`WiFi.begin(SSID, PASSWORD)`** | Inicializa conexión al Punto de Acceso | - |
| **`WiFi.status()`** | Estado del enlace de red | `WL_CONNECTED`, `WL_DISCONNECTED`, etc. |
| **`WiFi.localIP()`** | Dirección IP local asignada | Objeto `IPAddress` |
| **`WiFi.disconnect()`** | Desconecta de la red WiFi | - |
| **`WiFi.RSSI()`** | Intensidad de señal (dBm) | Negativo, más cercano a 0 = mejor |

**Ejemplo con reconexión automática:**
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
        Serial.println("\nConexion fallida");
    }
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Reconectando WiFi...");
        WiFi.reconnect();
        delay(5000);
    }
}
```

### 📨 Protocolo MQTT (`PubSubClient.h`)

Comunicación cliente/broker bajo patrón **Publicación/Suscripción**.

**Inicialización y conexión:**
```cpp
WiFiClient espClient;
PubSubClient client(espClient);

// Asignar broker y puerto
client.setServer("broker.example.com", 1883);

// Registrar callback para mensajes recibidos
client.setCallback(OnMqttReceived);

// Conectar con autenticación (opcional)
client.connect("clientID", "user", "password");

// Loop de mantenimiento (llamar en setup() o loop())
client.loop();
```

**Publicación y Suscripción:**
```cpp
// Publicar mensaje
client.publish("topic/name", "payload_text");

// Suscribirse a tópico
client.subscribe("topic/name");

// Callback para mensajes recibidos
void OnMqttReceived(char *topic, byte *payload, unsigned int length) {
    char message[length + 1];
    memcpy(message, payload, length);
    message[length] = '\0';
    
    Serial.printf("Topic: %s | Payload: %s\n", topic, message);
}
```

| Función | Descripción |
| :--- | :--- |
| **`setServer(host, port)`** | Define broker MQTT y puerto |
| **`setCallback(function)`** | Registra función para mensajes recibidos |
| **`connect(id, [user], [pass])`** | Conecta y autentica con broker |
| **`loop()`** | Mantiene conexión y procesa paquetes |
| **`publish(topic, payload)`** | Publica mensaje en tópico |
| **`subscribe(topic)`** | Se suscribe a tópico |
| **`connected()`** | Verifica si está conectado |
| **`disconnect()`** | Desconecta del broker MQTT |

**Patrón con reconexión automática:**
```cpp
#include <PubSubClient.h>
#include <WiFi.h>

WiFiClient espClient;
PubSubClient client(espClient);

void reconnectMQTT() {
    if (client.connected()) return;
    
    Serial.print("Conectando MQTT...");
    if (client.connect("ESP32", "user", "password")) {
        Serial.println(" OK");
        client.subscribe("sensor/temperatura");
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
        client.publish("sensor/temperatura", String(temp).c_str());
        lastTime = millis();
    }
}
```

---

## 6️⃣ M5Stack Core2: Hardware, Pantalla e IMU

La librería `#include <M5Core2.h>` abstrae el hardware integrado de la placa M5Core2.

### 🔌 Inicialización y Alimentación

| Función | Descripción |
| :--- | :--- |
| **`M5.begin()`** | Inicializa bus I²C, pantalla, chip AXP192 y periféricos |
| **`M5.update()`** | Actualiza estado de botones y eventos táctiles (llamar en `loop()`) |
| **`M5.Axp.SetVibration(bool)`** | Activa (`true`) o desactiva (`false`) el motor de vibración |

### 📱 Pantalla LCD TFT

```cpp
// Pintar fondo
M5.Lcd.fillScreen(BLACK);

// Configurar color de texto y fondo
M5.Lcd.setTextColor(WHITE, BLACK);

// Escala del texto (enteros: 1, 2, 3, etc.)
M5.Lcd.setTextSize(2);

// Posicionar cursor en píxeles (x, y)
M5.Lcd.setCursor(10, 20);

// Escribir texto formateado
M5.Lcd.printf("Valor: %d\n", 42);
M5.Lcd.println("Hola Mundo");
```

| Función | Descripción |
| :--- | :--- |
| **`fillScreen(color)`** | Pinta pantalla del color indicado |
| **`setTextColor(text, bg)`** | Define colores de texto y fondo |
| **`setTextSize(size)`** | Escala del texto |
| **`setCursor(x, y)`** | Posición en píxeles (origen arriba-izquierda) |
| **`printf()` / `println()`** | Escribe texto formateado |

**Colores disponibles:** `BLACK`, `WHITE`, `RED`, `GREEN`, `BLUE`, `YELLOW`, `CYAN`, `MAGENTA`

### 👆 Pantalla Táctil Capacitiva

```cpp
TouchPoint_t pixel_pos;

if (M5.Touch.ispressed()) {
    pixel_pos = M5.Touch.getPressPoint();
    int16_t x = pixel_pos.x;  // Coordenada X (0-319)
    int16_t y = pixel_pos.y;  // Coordenada Y (0-239)
    
    Serial.printf("Touch: (%d, %d)\n", x, y);
}
```

| Función | Descripción |
| :--- | :--- |
| **`M5.Touch.ispressed()`** | ¿Se está tocando la pantalla? |
| **`M5.Touch.getPressPoint()`** | Obtiene coordenadas (x, y) del toque |

### 🎯 Sensor Inercial (IMU 6-Ejes)

Acelerómetro y giroscopio integrados en la placa.

```cpp
// Inicializar IMU
M5.IMU.Init();

// Leer aceleraciones (en G)
float accX, accY, accZ;
M5.IMU.getAccelData(&accX, &accY, &accZ);

// Leer orientación estimada (en grados)
float pitch, roll, yaw;
M5.IMU.getAhrsData(&pitch, &roll, &yaw);

Serial.printf("Acc: (%.2f, %.2f, %.2f) G\n", accX, accY, accZ);
Serial.printf("Ori: P=%.1f° R=%.1f° Y=%.1f°\n", pitch, roll, yaw);
```

| Función | Parámetros | Unidades |
| :--- | :--- | :--- |
| **`M5.IMU.Init()`** | - | Inicialización |
| **`getAccelData(&x, &y, &z)`** | Punteros float | Aceleración en **G** |
| **`getAhrsData(&p, &r, &y)`** | Punteros float | Ángulos en **grados** |
| **`getGyroData(&x, &y, &z)`** | Punteros float | Velocidad angular en **°/s** |

**Ejes de referencia:** X (lateral), Y (frontal), Z (vertical)

---

## 🔐 Sincronización y Mutex (Protección de Recursos Compartidos)

### 🛡️ Conceptos Básicos

**Sección Crítica:** Bloque de código donde una tarea accede a un recurso compartido.

**Mutex:** Mecanismo que permite que solo UNA tarea acceda a un recurso a la vez.

**Race Condition:** Problema que ocurre cuando dos tareas acceden simultáneamente al mismo recurso sin sincronización.

### 🔒 Funciones de Mutex

| Función | Descripción |
| :--- | :--- |
| **`xSemaphoreCreateMutex()`** | Crea un mutex. Devuelve `SemaphoreHandle_t` o NULL si falla |
| **`xSemaphoreTake(mutex, timeout)`** | Adquiere el mutex (espera si está ocupado). Timeout: `portMAX_DELAY` = espera infinita |
| **`xSemaphoreGive(mutex)`** | Libera el mutex para que otras tareas lo usen |

**Valores de retorno:**
- `pdTRUE` (1): Operación exitosa
- `pdFALSE` (0): Timeout alcanzado sin adquirir mutex

### ✅ Patrón Seguro - Con Mutex

```cpp
#include <Arduino.h>

SemaphoreHandle_t xMutexSerial;

void vTask1(void *pvParameters) {
  for (;;) {
    // Intentar tomar el mutex
    if (xSemaphoreTake(xMutexSerial, portMAX_DELAY) == pdTRUE) {
      
      // --- SECCIÓN CRÍTICA PROTEGIDA ---
      Serial.println("[TAREA 1] Usando Serial...");
      vTaskDelay(pdMS_TO_TICKS(100));
      Serial.println("[TAREA 1] Finalizó");
      // --------------------------------

      // Liberar el mutex
      xSemaphoreGive(xMutexSerial);
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void vTask2(void *pvParameters) {
  for (;;) {
    if (xSemaphoreTake(xMutexSerial, portMAX_DELAY) == pdTRUE) {
      
      // --- SECCIÓN CRÍTICA PROTEGIDA ---
      Serial.println("  [TAREA 2] Escribiendo...");
      vTaskDelay(pdMS_TO_TICKS(50));
      Serial.println("  [TAREA 2] Hecho");
      // --------------------------------

      xSemaphoreGive(xMutexSerial);
    }

    vTaskDelay(pdMS_TO_TICKS(700));
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Crear mutex ANTES de las tareas
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

**Ventajas:**
- ✅ Escrituras de Serial completas y sin mezcla
- ✅ Acceso ordenado al recurso compartido
- ✅ Evita corrupción de datos

---


## 🔧 Funciones de Utilidad

### 📐 Mapeo y Restricción de Valores

| Función | Descripción | Ejemplo |
| :--- | :--- | :--- |
| **`map(value, fromLow, fromHigh, toLow, toHigh)`** | Mapea valor de un rango a otro | `map(500, 0, 4095, 0, 320)` |
| **`constrain(value, min, max)`** | Restringe valor entre límites | `constrain(x, 0, 319)` |
| **`abs(value)`** | Valor absoluto | `abs(-50)` → `50` |
| **`min(a, b)`** | Mínimo entre dos valores | `min(10, 20)` → `10` |
| **`max(a, b)`** | Máximo entre dos valores | `max(10, 20)` → `20` |

---

## 📌 Tips, Buenas Prácticas y Patrones

### 🔐 Sincronización y Mutex

- **SIEMPRE crear Mutex ANTES de las tareas** que lo van a usar
- **Secciones críticas cortas**: Minimizar el tiempo dentro de `xSemaphoreTake()` a `xSemaphoreGive()`
- **Usar `portMAX_DELAY`** cuando se necesite espera infinita en mutex críticos
- **Evitar nesting de mutex**: No tomar mutex A mientras se sostiene mutex B (deadlock)

### ⚙️ Optimización y FreeRTOS

- **Prioridad 0-24**: Mayor número = mayor prioridad. Tareas de mayor prioridad preemption tareas bajas
- **Stack size**: Mínimo 2048 bytes para tareas normales. Aumentar si hay uso de buffers o recursión
- **`vTaskDelete(NULL)`**: Llamar en `loop()` en ESP32/FreeRTOS puro
- **pdMS_TO_TICKS()**: Siempre usar para conversión de ms a ticks (más portátil que hardcoding)
- **vTaskDelayUntil()**: Más preciso que `vTaskDelay()` para tareas periódicas exigentes

### 🎯 Interrupción vs FreeRTOS

- **ISR (`IRAM_ATTR`)**: Para eventos críticos y rápidos (GPIO, timers)
- **FreeRTOS Tasks**: Para tareas con ejecuciones de larga duración o control de recursos

### 📊 Debugging Serial

- **115200 baud**: Estándar. Cambiar solo si hay problemas específicos
- **`Serial.printf()`**: Más flexible que múltiples `Serial.print()`. Usar especificadores: `%d`, `%f`, `%s`
- **Mutex en Serial**: Imprescindible en multi-tarea para mensajes completos
- **Timeout en Serial**: `while (!Serial);` en setup para esperar conexión USB en desarrollo


### 🚀 Patrones Recomendados

**Para aplicaciones críticas:**
```cpp
// 1. Crear mutex al inicio
xMutex = xSemaphoreCreateMutex();

// 2. Usar en secciones críticas
if (xSemaphoreTake(xMutex, pdMS_TO_TICKS(1000)) == pdTRUE) {
    // Código protegido
    xSemaphoreGive(xMutex);
} else {
    // Timeout: recurso ocupado
    Serial.println("Timeout!");
}
```

---

## 📚 Documentación y Recursos

### 🌐 Referencias Oficiales
- [Arduino ESP32 Official Documentation](https://docs.espressif.com/projects/arduino-esp32/)
- [FreeRTOS Reference Manual](https://www.freertos.org/RTOS-task-management.html)
- [M5Stack Documentation](https://docs.m5stack.com/)
- [ESP32 Datasheet](https://www.espressif.com/en/products/socs/esp32)