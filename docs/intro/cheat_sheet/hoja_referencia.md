---
title: Hoja de referencia rápida - Programación ESP32
author: Juan M. Gandarias
institution: Universidad de Málaga
---

# 📋 Hoja de referencia rápida de programación ESP32

> Guía de referencia rápida para instrucciones y funciones del curso de Informática Industrial  
> Por [Juan M. Gandarias](https://jmgandarias.com) | [jmgandarias@uma.es](mailto:jmgandarias@uma.es)

---

## 0️⃣ Configuración inicial y preparación

### Estructura básica del programa

```cpp

const int LED_PIN = 2;

void setup() {
    Serial.begin(115200);
    delay(1000);
    pinMode(LED_PIN, OUTPUT);
    Serial.println("ESP32 inicializado");
}

void loop() {
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
}
```

---

## 📡 Comunicación serie (depuración)

| Función | Descripción |
| :--- | :--- |
| **`Serial.begin(baudrate)`** | Inicializa el puerto serie (se recomienda 115200) |
| **`Serial.print()`** | Muestra texto sin salto de línea |
| **`Serial.println()`** | Muestra texto con salto de línea |
| **`Serial.printf()`** | Muestra texto con formato |
| **`Serial.available()`** | Bytes disponibles en el buffer |
| **`Serial.read()`** | Lee un byte |
| **`Serial.readString()`** | Lee una línea completa |

---

## 1️⃣ E/S digitales, analógicas y PWM (LEDC)

### 🔌 GPIO y lectura analógica

| Función | Descripción |
| :--- | :--- |
| **`pinMode(pin, mode)`** | Configura el pin como `INPUT`, `OUTPUT` o `INPUT_PULLUP` (activa la resistencia interna pull-up) |
| **`digitalWrite(pin, val)`** | Establece el estado de salida digital (`HIGH` o `LOW`) |
| **`digitalRead(pin)`** | Lee el estado lógico del pin → `HIGH` (1) o `LOW` (0) |
| **`analogRead(pin)`** | Conversión A/D → Devuelve un entero entre `0` y `4095` (12 bits por defecto) |

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

La gestión del PWM con LEDC simplifica la configuración: la frecuencia y la resolución quedan ligadas directamente al pin sin gestionar canales explícitamente.

```cpp
// Configura y activa PWM en un pin
ledcAttach(pin, frequency, resolution_bits);

// Establece el ciclo de trabajo
ledcWrite(pin, duty_value);
```

| Función | Parámetros | Ejemplo |
| :--- | :--- | :--- |
| **`ledcAttach(pin, freq, res)`** | Asigna PWM al pin directamente | `ledcAttach(5, 8000, 12)` → 8 kHz, 12 bits (0-4095) |
| **`ledcWrite(pin, duty)`** | Establece el ciclo de trabajo | `ledcWrite(5, 2048)` → 50% de ciclo de trabajo |

**Resolución:** 12 bits por defecto (0-4095)

---

## 2️⃣ Interrupciones y temporizadores hardware

### 🔔 Interrupciones externas (GPIO)

| Elemento | Descripción |
| :--- | :--- |
| **`IRAM_ATTR`** | Atributo obligatorio en funciones ISR. Guarda la función en RAM interna rápida (IRAM) |
| **`attachInterrupt(...)`** | `attachInterrupt(digitalPinToInterrupt(pin), ISR_callback, mode)` |
| **Modos disponibles** | `RISING` (flanco ascendente ↑) • `FALLING` (flanco descendente ↓) • `CHANGE` (cualquier cambio) |

**Ejemplo con botón y antirrebote:**
```cpp
const int BUTTON_PIN = 4;
volatile int counter = 0;

void IRAM_ATTR handleButtonPress() {
    counter++;
}

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    
    // Configura la interrupción en flanco descendente
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonPress, FALLING);
}

void loop() {
    Serial.printf("Pulsaciones del botón: %d\n", counter);
    delay(500);
}
```

⚠️ **Importante en la ISR:**
- Mantén el código rápido y sencillo
- No uses `Serial.print()` (es lento)
- Usa variables `volatile` para datos compartidos

### ⏱️ Temporizadores hardware

Los temporizadores hardware del ESP32 usan una API orientada a la frecuencia y al tiempo en microsegundos.

**Configuración típica:**
```cpp
hw_timer_t *timer = NULL;

// 1. Inicializar a una frecuencia de conteo en Hz
timer = timerBegin(timer_frequency);

// 2. Vincular la función ISR
timerAttachInterrupt(timer, &timerInterruptISR);

// 3. Configurar la alarma (microsegundos)
timerAlarm(timer, period_us, autoreload, reload_count); 

// 4. Control de ejecución
timerStart(timer);
timerStop(timer);
```

| Función | Descripción |
| :--- | :--- |
| **`timerBegin(freq_hz)`** | Crea un temporizador a una frecuencia en Hz. Ej: `1000000` Hz = 1 tick/µs |
| **`timerAttachInterrupt(timer, &ISR)`** | Vincula la ISR para ejecutarse en cada alarma |
| **`timerAlarm(timer, period, reload, count)`** | Configura la alarma: `period` (µs), `reload` (bool periódico), `count` (0=indefinido) |
| **`timerStart(timer)`** | Inicia la cuenta del temporizador |
| **`timerStop(timer)`** | Detiene la cuenta del temporizador |

**Ejemplo completo - Temporizador periódico:**
```cpp
hw_timer_t *timer = NULL;
volatile int counter = 0;

void IRAM_ATTR onTimerAlarm() {
    counter++;
}

void setup() {
    Serial.begin(115200);
    
    // Temporizador a 1 MHz (1 tick = 1 microsegundo)
    timer = timerBegin(1000000);
    timerAttachInterrupt(timer, &onTimerAlarm);
    
    // Alarma cada 1.000.000 µs (1 segundo)
    timerAlarm(timer, 1000000, true, 0);
    timerStart(timer);
}

void loop() {
    if (counter > 0) {
        Serial.printf("Contador: %d\n", counter);
        counter = 0;
        delay(100);
    }
}
```

---

## 3️⃣ Temporizadores software (`Ticker.h`)

Ejecuta tareas periódicas de forma asíncrona mediante temporización software.

| Función | Descripción | Ejemplo |
| :--- | :--- | :--- |
| **`Ticker ticker;`** | Declara un objeto `Ticker` | - |
| **`attach(seconds, callback)`** | Ejecuta la callback periódicamente (acepta decimales) | `ticker.attach(0.5, myFunction)` |
| **`attach_ms(milliseconds, callback)`** | Equivalente en milisegundos | `ticker.attach_ms(500, myFunction)` |
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
    // Ticker se ejecuta en segundo plano
}
```

---

### ✅ Lista de comprobación de ISR (Interrupt Service Routines)

**✓ HACER:**
- Operaciones rápidas y sencillas
- Usar `IRAM_ATTR` de forma obligatoria
- Usar variables `volatile`
- Usar `xSemaphoreGiveFromISR()` para señalizar

**✗ NO HACER:**
- Operaciones lentas (Serial, WiFi)
- Llamadas a `delay()`
- Asignación de memoria
- `printf()` o funciones pesadas

---

## 4️⃣ Multitarea y FreeRTOS

El ESP32 integra **dos núcleos de CPU** (Core 0 y Core 1). FreeRTOS permite gestionar hilos concurrentes en ambos.

### 🚀 Creación de tareas y anclaje a un núcleo

```cpp
xTaskCreatePinnedToCore(
    TaskFunction,   // void task(void *param)
    "TaskName",     // Etiqueta de depuración
    StackSize,      // Memoria RAM (palabras de 4 bytes)
    Parameters,     // Parámetros de entrada (normalmente NULL)
    Priority,       // Prioridad (0 = menor)
    &TaskHandle,    // Handle de la tarea
    CoreID          // Núcleo (0 o 1)
);
```

| Parámetro | Descripción |
| :--- | :--- |
| **TaskFunction** | Función `void taskName(void *pvParameters)` |
| **StackSize** | Memoria en bytes (ej: `2048` = 2 KB) |
| **Priority** | 0-24 (cuanto mayor, mayor prioridad) |
| **CoreID** | `0` = Core 0 • `1` = Core 1 |

### ⏱️ Funciones útiles de FreeRTOS

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

| Función | Finalidad | Nota |
| :--- | :--- | :--- |
| **`vTaskDelayUntil()`** | Retardo periódico preciso | Preferible a `delay()` en tareas |
| **`xTaskGetTickCount()`** | Obtiene el tick actual | Para sincronización |
| **`pdMS_TO_TICKS(ms)`** | Convierte ms a ticks | Reutilizable |
| **`xPortGetCoreID()`** | Núcleo actual | Útil para depuración |

### 🗑️ Gestión del ciclo de vida de tareas

| Función | Descripción |
| :--- | :--- |
| **`vTaskDelete(NULL)`** | Elimina la tarea actual. `NULL` = propia tarea |
| **`vTaskDelete(xTaskHandle)`** | Elimina una tarea concreta |

**Tareas de ejecución única:**
```cpp
void vTaskOneShot(void *pvParameters) {
  // Realizar trabajo
  Serial.println("Tarea ejecutada una vez");
  
  // Eliminar tarea para liberar la pila
  vTaskDelete(NULL);
}

void setup() {
  xTaskCreatePinnedToCore(vTaskOneShot, "OneShot", 2048, NULL, 1, NULL, 0);
}

void loop() {
  vTaskDelete(NULL);  // Eliminar loop() en FreeRTOS
}
```

### 🔐 Sincronización y mutex (protección de recursos compartidos)

#### 🛡️ Conceptos básicos

**Sección crítica:** Bloque de código donde una tarea accede a un recurso compartido.

**Mutex:** Mecanismo que permite que solo UNA tarea acceda a un recurso a la vez.

**Condición de carrera:** Problema que ocurre cuando dos tareas acceden simultáneamente al mismo recurso sin sincronización.

#### 🔒 Funciones del mutex

| Función | Descripción |
| :--- | :--- |
| **`xSemaphoreCreateMutex()`** | Crea un mutex. Devuelve `SemaphoreHandle_t` o `NULL` si falla |
| **`xSemaphoreTake(mutex, timeout)`** | Adquiere el mutex (espera si está ocupado). Timeout: `portMAX_DELAY` = espera infinita |
| **`xSemaphoreGive(mutex)`** | Libera el mutex para que lo usen otras tareas |

**Valores de retorno:**
- `pdTRUE` (1): Operación correcta
- `pdFALSE` (0): Se alcanzó el timeout sin adquirir el mutex

#### ✅ Patrón seguro - con mutex

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
      Serial.println("[TAREA 1] Finalizado");
      // --------------------------------

      // Liberar mutex
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
- ✅ Escrituras en `Serial` completas y no mezcladas
- ✅ Acceso ordenado a recursos compartidos
- ✅ Evita la corrupción de datos

---

## 5️⃣ Conectividad (WiFi y MQTT)

### 📡 Gestión de WiFi (`WiFi.h`)

| Función | Descripción | Devuelve |
| :--- | :--- | :--- |
| **`WiFi.begin(SSID, PASSWORD)`** | Inicializa la conexión al punto de acceso | - |
| **`WiFi.status()`** | Estado del enlace de red | `WL_CONNECTED`, `WL_DISCONNECTED`, etc. |
| **`WiFi.localIP()`** | Dirección IP local asignada | Objeto `IPAddress` |
| **`WiFi.disconnect()`** | Desconecta de la red WiFi | - |
| **`WiFi.RSSI()`** | Intensidad de la señal (dBm) | Negativa, cuanto más cerca de 0 mejor |

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
        Serial.println("\nConexión fallida");
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

Comunicación cliente/broker bajo el patrón **Publish/Subscribe**.

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

// Bucle de mantenimiento (llamado en setup() o loop())
client.loop();
```

**Publicación y suscripción:**
```cpp
// Publicar mensaje
client.publish("topic/name", "payload_text");

// Suscribirse al tema
client.subscribe("topic/name");

// Callback para mensajes recibidos
void OnMqttReceived(char *topic, byte *payload, unsigned int length) {
    char message[length + 1];
    memcpy(message, payload, length);
    message[length] = '\0';
    
    Serial.printf("Tema: %s | Carga útil: %s\n", topic, message);
}
```

| Función | Descripción |
| :--- | :--- |
| **`setServer(host, port)`** | Define el broker y el puerto MQTT |
| **`setCallback(function)`** | Registra la función para mensajes recibidos |
| **`connect(id, [user], [pass])`** | Conecta y autentica con el broker |
| **`loop()`** | Mantiene la conexión y procesa paquetes |
| **`publish(topic, payload)`** | Publica un mensaje en un tema |
| **`subscribe(topic)`** | Se suscribe a un tema |
| **`connected()`** | Comprueba si está conectado |
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

## 6️⃣ M5Stack Core2: Hardware, pantalla e IMU

La librería `#include<M5Unified.h>` abstrae el hardware integrado de la placa de desarrollo M5Core2.

### 🔌 Inicialización y gestión de energía

| Función | Descripción |
| :--- | :--- |
| **`M5.begin()`** | Inicializa el bus I²C, la pantalla, el chip AXP192 y los periféricos |
| **`M5.update()`** | Actualiza el estado de los botones y los eventos táctiles (llamar en `loop()`) |
| **`M5.Axp.SetVibration(bool)`** | Activa (`true`) o desactiva (`false`) el motor de vibración |

### 📱 Pantalla TFT LCD

```cpp
// Pintar fondo
M5.Lcd.fillScreen(BLACK);

// Establecer color de texto y fondo
M5.Lcd.setTextColor(WHITE, BLACK);

// Escala de texto (enteros: 1, 2, 3, etc.)
M5.Lcd.setTextSize(2);

// Posicionar cursor en píxeles (x, y)
M5.Lcd.setCursor(10, 20);

// Escribir texto formateado
M5.Lcd.printf("Valor: %d\n", 42);
M5.Lcd.println("Hola Mundo");
```

| Función | Descripción |
| :--- | :--- |
| **`fillScreen(color)`** | Pinta la pantalla con el color indicado |
| **`setTextColor(text, bg)`** | Establece el color de texto y fondo |
| **`setTextSize(size)`** | Escala del texto |
| **`setCursor(x, y)`** | Posición en píxeles (origen arriba-izquierda) |
| **`printf()` / `println()`** | Escribe texto formateado |

**Colores disponibles:** `BLACK`, `WHITE`, `RED`, `GREEN`, `BLUE`, `YELLOW`, `CYAN`, `MAGENTA`

### 👆 Pantalla táctil capacitiva

```cpp
TouchPoint_t pixel_pos;

if (M5.Touch.ispressed()) {
    pixel_pos = M5.Touch.getPressPoint();
    int16_t x = pixel_pos.x;  // Coordenada X (0-319)
    int16_t y = pixel_pos.y;  // Coordenada Y (0-239)
    
    Serial.printf("Tacto: (%d, %d)\n", x, y);
}
```

| Función | Descripción |
| :--- | :--- |
| **`M5.Touch.ispressed()`** | ¿Se está tocando la pantalla? |
| **`M5.Touch.getPressPoint()`** | Obtiene las coordenadas del toque (x, y) |

### 🎯 Sensor inercial (IMU de 6 ejes)

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
| **`getAccelData(&x, &y, &z)`** | punteros float | Aceleración en **G** |
| **`getAhrsData(&p, &r, &y)`** | punteros float | Ángulos en **grados** |
| **`getGyroData(&x, &y, &z)`** | punteros float | Velocidad angular en **°/s** |

**Ejes de referencia:** X (lateral), Y (frontal), Z (vertical)

---

## 🔧 Funciones útiles

### 📐 Mapeo y limitación de valores

| Función | Descripción | Ejemplo |
| :--- | :--- | :--- |
| **`map(value, fromLow, fromHigh, toLow, toHigh)`** | Mapea un valor de un rango a otro | `map(500, 0, 4095, 0, 320)` |
| **`constrain(value, min, max)`** | Limita el valor entre unos límites | `constrain(x, 0, 319)` |
| **`abs(value)`** | Valor absoluto | `abs(-50)` → `50` |
| **`min(a, b)`** | Mínimo de dos valores | `min(10, 20)` → `10` |
| **`max(a, b)`** | Máximo de dos valores | `max(10, 20)` → `20` |

---

## 📌 Consejos, buenas prácticas y patrones

### 🔐 Sincronización y mutex

- **CREA siempre el mutex ANTES de las tareas** que lo van a usar
- **Secciones críticas cortas**: Minimiza el tiempo entre `xSemaphoreTake()` y `xSemaphoreGive()`
- **Usa `portMAX_DELAY`** cuando necesites espera infinita en un mutex crítico
- **Evita anidar mutex**: No tomes el mutex A mientras mantienes el B (deadlock)

### ⚙️ Optimización y FreeRTOS

- **Prioridad 0-24**: Cuanto mayor es el número, mayor prioridad. Las tareas de prioridad alta sustituyen a las más bajas
- **Tamaño de pila**: Mínimo 2048 bytes para tareas normales. Aumenta si usas buffers o recursividad
- **`vTaskDelete(NULL)`**: Llámalo en `loop()` en ESP32/FreeRTOS puro
- **pdMS_TO_TICKS()**: Úsalo siempre para convertir ms a ticks (más portable que codificar valores fijos)
- **vTaskDelayUntil()**: Más preciso que `vTaskDelay()` para tareas periódicas exigentes

### 🎯 Interrupción frente a FreeRTOS

- **ISR (`IRAM_ATTR`)**: Para eventos críticos y rápidos (GPIO, temporizadores)
- **Tareas FreeRTOS**: Para tareas largas o control de recursos

### 📊 Depuración serie

- **115200 baudios**: Estándar. Cambia solo si hay problemas concretos
- **`Serial.printf()`**: Más flexible que varios `Serial.print()`. Usa especificadores: `%d`, `%f`, `%s`
- **Mutex en Serial**: Obligatorio en multitarea para mensajes completos
- **Timeout en Serial**: `while (!Serial);` en `setup()` para esperar la conexión USB durante el desarrollo

### 🚀 Patrones recomendados

**Para aplicaciones críticas:**
```cpp
// 1. Crear mutex al inicio
xMutex = xSemaphoreCreateMutex();

// 2. Usarlo en secciones críticas
if (xSemaphoreTake(xMutex, pdMS_TO_TICKS(1000)) == pdTRUE) {
    // Código protegido
    xSemaphoreGive(xMutex);
} else {
    // Timeout: recurso ocupado
    Serial.println("Timeout!");
}
```

---

## 📚 Documentación y recursos

### 🌐 Referencias oficiales
- [Documentación oficial de Arduino ESP32](https://docs.espressif.com/projects/arduino-esp32/)
- [Manual de referencia de FreeRTOS](https://www.freertos.org/RTOS-task-management.html)
- [Documentación de M5Stack](https://docs.m5stack.com/)
- [Manual de referencia técnica de ESP32](https://www.espressif.com/en/products/socs/esp32)

### 📖 Temas clave por sección

| Sección | Concepto principal | Caso de uso |
| :--- | :--- | :--- |
| GPIO digital/analógica | Entrada/salida de bits y valores analógicos | LEDs, botones, sensores |
| Interrupciones | Respuesta rápida a eventos hardware | Detección rápida de cambios |
| Temporizadores | Generación de eventos periódicos hardware | PWM, muestreo periódico |
| Ticker | Tareas periódicas software | Actualización no crítica de estado |
| Multitarea FreeRTOS | Ejecución concurrente controlada | Múltiples procesos simultáneos |
| Mutex/Sincronización | Protección de recursos compartidos | Acceso seguro a Serial, LCD, GPIO |
| WiFi/MQTT | Conectividad de red | Comunicación remota, IoT |
| M5Core2 | Plataforma de desarrollo integrada | Aplicaciones con pantalla y sensores |

### 💡 Ruta recomendada de aprendizaje

1. **Nivel básico**: GPIO → Serial → Interrupciones
2. **Nivel intermedio**: Temporizadores → Ticker → FreeRTOS básico
3. **Nivel avanzado**: Mutex → Multitarea coordinada → WiFi/MQTT
4. **Aplicaciones**: M5Core2 → Integración de proyectos

### 🔗 Herramientas útiles

- **Arduino IDE**: Descárgalo en [arduino.cc](https://www.arduino.cc/en/software)
- **PlatformIO**: Alternativa potente en VS Code
- **Mosquitto**: Broker MQTT local para pruebas
- **Wokwi**: Simulador online de ESP32 ([wokwi.com](https://wokwi.com))

### 🎓 Consejo de aprendizaje

- **Lee el código antes de ejecutarlo**: Comprende qué hace cada función
- **Experimenta con los valores**: Cambia tiempos, prioridades y periodos
- **Monitoriza con Serial**: Usa `Serial.printf()` para depurar continuamente
- **Aísla los problemas**: Prueba cada componente por separado antes de integrarlos
- **Documenta tu trabajo**: Comenta el código y entiende por qué funciona

---

**Última actualización:** 2026-07-28 | **Versión:** 2.0 | **Para:** Grado en Ingeniería Electrónica Industrial
- [Hoja de datos del ESP32](https://www.espressif.com/en/products/socs/esp32)