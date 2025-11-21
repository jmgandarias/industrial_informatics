# Sesión de Laboratorio 6-I: Multitarea en sistemas de tiempo real de pequeña escala

**Tiempo estimado:** 1,5 h (1 sesión)

## 1. Trabajando con hardware real

### Parte 1 - Interacción con botones
El dispositivo M5Core2 tiene 3 botones táctiles definidos como `M5.BtnA`, `M5.BtnB` y `M5.BtnC`.

- Compila y prueba el programa de ejemplo [`button_example.ino`](https://jmgandarias.com/industrial_informatics/real-time_embedded_systems/lab6_1/button_example/button_example.ino).
- En [este enlace](https://docs.m5stack.com/en/arduino/m5core2/button) puedes encontrar la documentación sobre las funciones que se pueden realizar con los botones.

**Importante:**
La documentación del enlace anterior corresponde a la nueva librería `M5Unified.h`, que es muy reciente y no está demasiado probada.
Algunas funciones de esa documentación no están incluidas en la librería antigua `M5Core2.h`. Concéntrate solo en las funciones usadas en `button_example.ino`.

**Pregunta:**
- ¿Cómo se comportan los botones?
- ¿Qué hacen las funciones `wasReleased` y `pressedFor`?

### Parte 2 - Código secreto
El programa tendrá 4 estados:

- Estado 0: No se ha pulsado ningún botón.
- Estado 1: Se ha pulsado correctamente el primer botón.
- Estado 2: Se ha pulsado correctamente el segundo botón.
- Estado 3: Se ha pulsado correctamente el tercer botón.

Los botones deben presionarse en la secuencia A, B, C.

- Si se pulsa el botón correcto, el programa avanza al siguiente estado.
- Si se pulsa un botón incorrecto, se vuelve al Estado 0.

**Ejemplo:**
Cada vez que cambie el estado, debe imprimirse un mensaje en la pantalla. Por ejemplo:
- Si el programa está en el Estado 1:
```cpp
    M5.Lcd.println("Primer botón correcto");
```
- Si el programa está en el Estado 3:
```cpp
M5.Lcd.println("¡CÓDIGO CORRECTO!");
```

## 2. Trabajando en simulación

Puedes hacer un [ejercicio similar](https://jmgandarias.com/industrial_informatics/real-time_embedded_systems/lab6_1/enunciado_ejercicio_codigo_secreto.pdf) en simulación.