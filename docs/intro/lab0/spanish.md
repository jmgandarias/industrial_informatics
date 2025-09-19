# Sesión de Laboratorio 0: Primeros pasos

**Tiempo estimado:** 1,5 h (1 sesión)

## 1. Simulación de microcontroladores

### Ejecutar un ejemplo

- Accede al entorno de simulación Wokwi a través de [este enlace](https://wokwi.com/).
- Selecciona la plantilla ESP32.
  
    <img src="images/select_esp32_1.png" width="55%"/>
    <img src="images/select_esp32_2.png" width="80%"/>

    **NOTA:** Abre la plantilla ESP32 desde ```Starter Templates```, no desde ```ESP-IDF Templates```. La primera está basada en el IDE de Arduino, mientras que la segunda está basada en el entorno ESP-IDF que **no** se usará en el curso.

- Simula el sketch de ejemplo:
  
    ```Arduino
    void setup() {
    // código de configuración, se ejecuta una sola vez:
    Serial.begin(115200);
    Serial.println("Hello, ESP32!");
    }

    void loop() {
    // código principal, se ejecuta repetidamente:
    delay(10); // esto acelera la simulación
    }
    ```

    **NOTA:** Aquí estás *simulando* el comportamiento del sistema, incluido el código; no estás *compilando* el código (es decir, no se está generando el código máquina que ejecutará un procesador). Pero el código DEBE ser compilable (es decir, se verificará que podría compilar).

    **INFO:**
    - Observa que el factor de tiempo real en la esquina superior derecha debe estar lo más cerca posible del 100%. Este valor es una métrica de rendimiento de la simulación. Cuanto más cerca esté de 100%, mejor será la simulación. Un valor del 100% significa que la simulación se ejecuta en tiempo real. Si el valor baja, los tiempos de la simulación dejan de ser fiables.
    - Observa la instrucción ```delay(10); // esto acelera la simulación```. Prueba a comentar esta línea y observa qué ocurre. ¿Qué pasa si pones ```delay(1);``` o ```delay(5);```?

    **PREGUNTA:**
    - ¿Cuál es el propósito de la función setup()?
    - ¿Cuál es el propósito de la función loop()?
    - ¿Qué hace la función delay()?
    - ¿Por qué necesitamos poner delay(10) dentro de la función loop()?

### Añadir componentes de hardware
- Primero, revisa el archivo ```diagram.json```. ¿Qué información ves allí?

- Conecta un LED al ```GPIO 21``` con una resistencia, como se muestra en el diagrama (rota - *tecla R* y voltea - *tecla P* los componentes si es necesario).

    <img src="images/circuito_1.png" width="40%"/>


    **PREGUNTA:**
    - Revisa de nuevo el ```diagram.json```. ¿Qué ha cambiado? ¿Puedes cambiar el color del LED a *verde* desde este archivo?
    - ¿Qué crees que puedes hacer con el *Library Manager*?



## 2. Preparar el IDE de Arduino
Sigue los pasos de instalación descritos en esta guía.

1. Instala el IDE de Arduino: Descárgalo desde [este enlace](https://www.arduino.cc/en/software/):
2. Instala la familia de placas M5Stack:

    <img src="images/board_install_1.png" width="80%"/>

    Necesitas copiar/pegar este texto para descargar el paquete de placas:

    ```txt
    https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json 
    ```

    <img src="images/board_install_2.png" width="80%"/>

    Una vez configurada la dirección del paquete, puedes instalarlo desde el *gestor de placas*.
    
    <img src="images/board_install_3.png" width="80%"/>


    **IMPORTANTE:** Recuerda instalar la versión 2.1.4. Si intentas instalar la versión 3.X, no podrás realizar los ejercicios de las sesiones de laboratorio. Más adelante hablaremos sobre las versiones 2.X y 3.X y cómo migrar nuestro código de una a otra. Por ahora, utiliza únicamente la versión 2.X.

    **IMPORTANTE:** Una vez que hayas hecho esto, si más adelante abres el Arduino IDE, aparecerá un mensaje informándote de que hay actualizaciones disponibles para algunas bibliotecas y preguntándote si deseas instalarlas o no.
        No actualices las bibliotecas.

    **INFO:** Este proceso puede tardar unos minutos.

    Una vez instalado, puedes seleccionar M5Core2 desde el menú de selección de placas.

    <img src="images/board_selection.png" width="100%"/>

3. Instala las librerías de Arduino para M5Core2:

    <img src="images/m5core2_library.png" width="130%"/>

    **NOTA:** Cuando pulses *Install*, verás la lista de dependencias. *DEBES* instalar también todas las dependencias.

    **INFO:** Este es un proceso largo que puede tardar varios minutos. Ten paciencia...

    **AYUDA:** Si la lista de dependencias es tan grande que no puedes ver el botón *Install All*, puedes pulsar la tecla *tabulador dos veces para poner el cursor sobre el botón y luego pulsar *Enter* para instalar todas las dependencias.

4. Instala el driver CP2104 (controlador USB):

    Descárgalo desde [este enlace](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/drivers/CP210x_VCP_Windows.zip) si usas Windows, desde [este enlace](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/drivers/CP210x_VCP_MacOS.zip) si usas MacOS, o desde [este otro enlace](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/drivers/CP210x_VCP_Linux.zip) si usas Linux.

    Más información sobre la instalación del controlador USB [aquí](https://docs.m5stack.com/en/arduino/m5core2/program#2.usb%20driver%20installation).

    Ahora, cuando conectes el dispositivo M5Core2 al PC con el cable USB, podrás seleccionar el puerto en el IDE de Arduino.
    <img src="images/select_serial_port.png" width="80%"/>

    **INFO:**
     - En Windows, el puerto se llama *COMX*, donde *X* es un número que puede variar, por ejemplo, *COM5*.
     - En Linux, el puerto se llama "ttyUSBX" o "ttyACMX", donde *X* es un número que puede variar, por ejemplo, *ttyUSB2*.

5. Compila y sube el ejemplo ```hello_world.ino``` de la librería *M5Core2*:

    <img src="images/open_hello_world_example.png" width="80%"/>

    Puedes pulsar el botón *Upload* (en rojo) para compilar y cargar el programa en el dispositivo. Observa que el botón de la izquierda (*Verify* - en verde) compila el programa pero no lo sube al dispositivo.

    <img src="images/compile.png" width="80%"/>

6. *OPCIONAL (hazlo* **SOLO si has terminado todos los ejercicios** *de la sesión):* Puedes abrir otros ejemplos si quieres ver el potencial del M5Core2. Por ejemplo:

    <img src="images/open_floppybird_example.png" width="80%"/>


**AYUDA:** "Recursos adicionales"
    [Aquí](https://docs.m5stack.com/en/core/core2) puedes encontrar más documentación sobre algunas funciones básicas del M5Core2.

**Pinout y notas importantes**
A continuación se muestra el pinout del M5Core2. Los pines marcados en rojo son los que usaremos en los ejercicios.

<img src="images/pinout_M5Core2.png" width="30%"/>

**NOTA:**
 - Algunos *pines* del M5Core2 están preconfigurados, así que presta atención al conectar componentes externos.
 - El ESP32 dentro del M5Core2 tiene 3 puertos serie:
   - ```Serial1``` está reservado para la pantalla (no lo uses).
   - ```Serial0``` se puede configurar (pines ```G3 – RXD0``` y ```G1 – TXD0```), pero está reservado para la conexión USB al PC.
   - ```Serial2``` está libre y se puede configurar (pines G13 – RXD2 y G14 – TXD2) como GPIO normales usando ```pinMode()```.
