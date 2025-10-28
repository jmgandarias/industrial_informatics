# Práctica 5: Control de sistemas en tiempo real

**Tiempo estimado:** 3h (2 sesiones)

Usando los códigos de las prácticas 2, 3 y 4 y lo expuesto en el Tema 4, implementar un controlador PID dentro del microcontrolador de forma que se realice un control en posición del motor CC.

**Importante**: Asegurarse de que lo que se considera sentido de giro positivo a la hora de enviar el PWM coincide con el sentido de giro positivo a la hora de leer del encóder. De lo contrario, se estaría haciendo el equivalente a un bucle de control con realimentación positiva.

**Recomendación**: Realizar la práctica siguiendo los siguientes pasos:

1. Montar el circuito de la práctica 3.
2. Probar el código de la práctica 3 y verificar que funciona correctamente.
3. Sin desmontar lo que ya tienes, montar el circuito de la práctica 4 y verificar que funciona correctamente.
4. Trabajar en el software de la práctica 5 habiendo verificado que el hardware es correcto y que tanto el envío de PWM como la lectura del encóder funciona correctamente.

Se debe programar el puerto serie para recibir la referencia (posición deseada) a través del ordenador empleando el “Monitor serie”. Para ello se puede hacer uso del siguiente trozo de código en el `loop()`:

```cpp
int readRef = Serial.parseInt(); //Introduce el retraso en el bucle, sustituye a un delay
if(readRef != 0){  
    ref = readRef;
}
```

Ajustar los parámetros PID manualmente de forma que se minimice la sobreoscilación.

**Recomendación**: Para ajustar correctamente el controlador PID, comenzar con la
ganacia proporcional `Kp`, dejando el resto de parámetros a cero. Una vez ajustado este parámetro, probar a modificar el derivador `Kd`. Con el fin de reducir el posible error en régimen permanente, se puede asignar un valor pequeño al integrador `Ki` para anular la posible zona muerta que pudiera tener el motor.

