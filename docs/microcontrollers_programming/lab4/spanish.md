 Lab Session 3: PWM

**Estimated time:** 1.5h (1 session)

## Descripción

Para conocer la posición en la que se encuentra el eje de un motor se suelen emplear encoders incrementales. El objetivo de esta práctica es la programación de la lectura de este tipo de sensores, de manera que podamos conocer la posición exacta en la que se encuentra el eje del motor en cada instante de tiempo.

El encoder incremental, normalmente posee 4 señales:

- GND: Masa.
- Vcc: Alimentación (3-5V)
- Canal A: Canal A del encoder
- Canal B: Canal B del encoder.



Si conectamos estos dos canales a un osciloscopio, y movemos el eje del motor, 
podremos apreciar que la señal que se generan en estos dos canales es como la que se 
muestra en la imagen.

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.5\linewidth]{images/p4/osciloscopio.png}
\end{figure}


\subsection*{Parte 1 - Identificación de señales}

Identificar el color de cada una de señales descritas anteriormente en el motor que se va a emplear. Apuntar esta relación color-señal para poder usarla posteriormente con el microcontrolador. Conectar las señales de los canales A y B, así como la masa al osciloscopio y comprobar que la respuesta de los dos canales es idéntica a la imagen.

Conectar la masa del encoder (GND) al microcontrolador, y los canales A y B a dos entradas digitales

\subsection*{Parte 2 - Contador de pulsos en el encoder}

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