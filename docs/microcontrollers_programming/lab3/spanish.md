# Lab Session 3: PWM

**Estimated time:** 1.5h (1 session)

## Descripción

El objetivo de esta práctica es la generación de una señal PWM, así como el control de
un motor mediante esta señal, junto con otra que permita ajustar el sentido de giro del
motor. Para esto, se cuenta con un motor de CC, una controladora de motores basada en
el LM18200, y un M5Core2.ç

## 1. Trabajando con hardware real

### Parte 1 - Generación de PWM con LED

Realizar una prueba de generación de una señal PWM para iluminar más o menos un
LED conectado al pin 14 del M5Core2. \href{https://www.luisllamas.es/esp32-pwm/}{Este tutorial} explica cómo se puede realizar.

El LED se tienem que encender de forma progresiva desde el estado completamente apagado (PWM de 0%) hasta el estado completamente encendido (PWM de 100%). Una vez en el 100%, deberá apagarse también de forma progresiva (desde un PWM de 100% hasta un PWM de 0%), siguiendo en ambos casos un perfil tipo "rampa", primero creciente y luego decreciente.

### Parte 2 - Generación de PWM con motor CC

El esquema de la controladora empleada en el laboratorio es el siguiente:
\begin{figure}[h!]
        \centering
    \includegraphics[width=0.7\linewidth]{images/p3/esquema_controladora.png}
\end{figure}

El dibujo de la PCB muestra la ubicación de los conectores:
\begin{figure}[h!]
    \centering
    \includegraphics[width=0.5\linewidth]{images/p3/ubicacion_conectores.png}
\end{figure}


Realizar el conexionado del M5Core2 con la controladora de motores (puente H L298N) de la siguiente
manera:

- GPIO14 a pin IN1 en controladora. Esta salida digital permitirá establecer el sentido del giro del motor.
- GPIO13 a pin IN2 en controladora. Esta será la salida en la que se generará la señal PWM.
- GND y VS (en controladora) conectado a una fuente de alimentación de 9-12V. Se puede utilizar también una pila petaca.
- GND (M5Core2) a GND (Controladora). Imprescindible conectar las masas.
- Conectar el motor a la controladora en los terminales J1 que aparecen a la derecha.

Un tutorial sencillo sobre el uso de este driver puede encontrarse en [este enlace](https://naylampmechatronics.com/blog/11_tutorial-de-uso-del-modulo-l298n.html)

Una vez conectado el microcontrolador con el motor, modificar el código del tutorial,
para que la señal PWM se genere en la salida GPIO13 y hacer que el motor gire en un
sentido y en el otro.


En el \href{https://uma365-my.sharepoint.com/:v:/g/personal/carlosperez_uma_es/EXCrz4-S-dhBosXZ8PBce-sBWoLCzm-CRPONRCxCh5c1lA?e=ZdTElY}{este vídeo} se puede apreciar el resultado esperado de esta práctica.

\end{document}


## 2. Trabajando en simulación

### Parte 1 - Generación de PWM con LED

El ejercicio se puede realizar exactamente igual en simulación y en real.

!!! tip
    Para comprobar el correcto funcionamiento del código, es muy importante comporbar que ambos LEDs no están encendidos al mismo tiempo

### Parte 2 - Generación de PWM con motor CC

Este ejercicio no se puede realizar igual en simulación que en real porque en wokwi no existe el componente de motor de corriente continua. Sin embargo, existen varias formas de trabajar en simulación para hacer el prototipado del código para el motor.

Una forma sencilla sería utilizar 2 LEDs, donde el LED1 simularía el comportamiento del motor cuando gira en sentido horario, mientras el LED2 simularía el comportamiento del motor cuando gira en sentido antihorario. De esta forma, se pueden programar las señales PWM de ambos LEDs de forma similar a las señales PWM que se van a enviar a IN1 e IN2 en la controladora (que harán que el motor gire en sentido horario o antihorario).

!!! warning
    Para comprobar el correcto funcionamiento del código, es muy importante comporbar que ambos LEDs no están encendidos a la vez.

!!! tip
    Al trabajar con PWM en wokwi, el factor de tiempo real puede disminuir considerablemnte, especialmente si se generan varias PWMs y se cambia el ciclo de trabajo en cada paso del loop. Para evitar esto, es aconsejable cambiar el ciclo de trabajo de forma escalonada cada varios varios pasos del loop o con un tiempo de espera lo suficientemente grande.
