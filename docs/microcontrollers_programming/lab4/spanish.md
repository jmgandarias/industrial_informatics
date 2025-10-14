Lab Session 3: PWM

**Estimated time:** 1.5h (1 session)

## Descripción

Para conocer la posición en la que se encuentra el eje de un motor se suelen emplear encoders incrementales. El objetivo de esta práctica es la programación de la lectura de este tipo de sensores, de manera que podamos conocer la posición exacta (asumiendo el error debido a la resolución del propio sensor) en la que se encuentra el eje del motor en cada instante de tiempo.

El encoder incremental, normalmente posee 4 señales:

- GND: Masa.
- Vcc: Alimentación (3-5V).
- Canal A: Canal A del encoder
- Canal B: Canal B del encoder.

**IMPORTANTE:** En la práctica, el encóder se alimenta directamente desde un regulador interno de 5V del que dispone la electrónica del equipo. Eso quiere decir que no es necesario alimentar el encóder externamente. Sin embargo, sí es necesario tener en cuenta GND como referencia para las señales recibidas por los canales A y B.

Si conectamos estos dos canales a un osciloscopio y movemos el eje del motor, podremos apreciar que la señal que se generan en estos dos canales es como la que se muestra en la imagen.

<img src="images/osciloscopio.png" width="50%"/>

**IMPORTANTE**: Si no se mueve el eje del motor, no se verá ningún cambio en las señales.

## Trabajando con el hardware real

### Parte 1 - Identificación de señales

Conectar el osciloscopio al encoder e identificar el color de cada una de señales descritas anteriormente en el motor que se va a emplear. Apuntar esta relación color-señal para poder usarla posteriormente con el microcontrolador. Conectar las señales de los canales A y B, así como la masa al osciloscopio y comprobar que la respuesta de los dos canales es como la de la imagen anterior. Se recomienda utilizar el botón *Run/Stop* del osciloscopio para detener la lectura mientras el motor se encuentra girando y así poder observarla bien.

Conectar la masa del encoder (GND) al microcontrolador, y los canales A y B a las entradas digitales `GPIO 27` y `GPIO 19`.

**IMPORTANTE:** El encóder está alimentado a una tensión de 5V. Eso quiere decir que las señales de los canales A y B en estado alto y sin carga externa proporcionan una tensión de 5V. Sin embargo, la electrónica del ESP32 funciona a 3.3V. Es decir, no se deberían conectar los canales A y B a las entradas digitales del microcontrolador. Para resolver este problema se puede utilizar un divisor de tensión. Para implementarlo, hay que tener en cuenta la electrónica interna del encóder (ver imagen siguiente).

<img src="images/encoder_pull_up.png" width="60%"/>

Los canales A y B ya disponen de una resistencia pull-up de $3.3 k\Omega$, de forma que para realizar el divisor de tensión sólo será necesario incluir la resistencia de la parte baja del divisor de tensión.

**PREGUNTA:** ¿Cuál es el valor teórico de la resistencia que hay que colocar en la parte baja del divisor de tensión para que la tensión de los canales A y B pase de 5V a 3.3V cuando estén en estado alto?



### Parte 2 - Contador de pulsos en el encoder

Desarrollar un código Arduino que permita contar los pulsos generados por ambas señales, almacenar esta cuenta en una variable global, y tener en cuenta los cambios de sentido para incrementar o decrementar el contador. Emplear las interrupciones de las entradas digitales para ello. Ejemplo de implementación de manejador de interrupción:

\begin{lstlisting}
    ICACHE_RAM_ATTR void ISR_Ejemplo()
    {
      ...  
    }
\end{lstlisting}


El valor del contador se puede enviar a través del Puerto Serie de la siguiente forma


\begin{lstlisting}
    void setup()
    {
      ...  
      Serial.begin(9600);
    }

    void loop()
    {
      ...  
      Serial.println(contador);
    }
\end{lstlisting}


\subsection*{Parte 3 - Contar pulsos por vuelta}

Comprobar los pulsos por vueltas que genera el encoder. Buscar esta información en los 
detalles técnicos del motor y el encoder.


\subsection*{Parte 4 - Simulación con wokwi (casa)}

También se puede simular un encoder en wokwi utilizando el componente "Rotatory Encoder".
\href{https://docs.wokwi.com/parts/wokwi-ky-040/}{Aquí} está la referencia. El circuito quedaría de la siguiente forma.
¿Hay alguna diferencia entre el funcionamiento de este encoder con el del motor de las prácticas?
\begin{figure}[h!]
    \centering
    \includegraphics[width=0.5\linewidth]{images/p4/encoder_circuit.png}
\end{figure}

## Trabajando en simulación

