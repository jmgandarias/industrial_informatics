# Lab Session 8: IoT with M5Core2

**Estimated time:** 1.5h (1 session)

## 1. Working with real hardware

### General considerations

In this lab session, an MQTT network will be implemented consisting of two M5Core2 devices connected through a common broker. Within the network, one device will have the role of publisher and will publish to a topic when a button is pressed. The other device will act as a subscriber and, depending on the message received from the publisher, will change the screen color as described below.

- The WiFi network that the devices must connect to will be the local network:
    - SSID: InfInd
    - Password: InfIndMQTT
- As a broker, you can use one of the following options:
    - A public broker such as `test.mosquitto.org` or `mqtt.eclipseprojects.io`.
    - A private broker created with *mosquitto* if you have followed the steps on [this page](../getting_started/README.md).

!!! warning 
    Be careful with names! If you are going to work on a public broker, you must be careful with the client name and topic names: 
        - On the same broker, there cannot be two clients with the same name.
        - If you use a very generic name on a public broker (e.g., "test" or "topic"), it is very likely that there is another client publishing or subscribing to those topics. In this case, it is advisable to use non-generic names (e.g., using your name) to avoid interfering with other network clients.

### Part 1: Publisher

Create a script for M5Core2 (publisher) that does the following:

- If button A (`\texttt{M5.BtnA}`) is pressed, it publishes the message *"Red"* to a topic (e.g.: `\M5\color`).
- If button B (`\texttt{M5.BtnB}`) is pressed, it publishes the message *"Yellow"* to a topic (e.g.: `\M5\color`).
- If button C (`\texttt{M5.BtnC}`) is pressed, it publishes the message *"Green"* to a topic (e.g.: `\M5\color`).

!!! note
    To check if a button has been pressed, you can use the `wasReleased()` function (e.g., `M5.BtnA.wasReleased()`).

### Part 2: Subscriber

Create a script for M5Core2 (subscriber) that does the following:

- Subscribe to the topic where the other M5Core2 publishes (e.g.: `\M5\color`)
- The screen changes to the color of the message that has been received. You can use the `\texttt{fillScreen()` function (e.g., `M5.Lcd.fillScreen(RED)`).

### Part 3: Extension

- On the publisher: The message is not published until button A is pressed for more than one second. That is, the last button that has been pressed (A, B, or C) must be stored, but the message is not sent until button A is pressed for more than one second. You can use the `pressedFor()` function.
- On the subscriber: If the message is none of the above, the screen turns black.
- On the subscriber: Publish to the topic `\confirmacion` the message *"Message received"* when a message has been received and the screen color has been changed. This way, the device will be both subscriber and publisher at the same time.
- On both: Write on the screen of the device acting as publisher the options (e.g.: *Press A for "Red"*, or *Message "Red" sent*). Write on the screen of the device acting as subscriber the status of received messages (e.g.: *Message "Red" received, color changed*).

## 2. Working in simulation

The exercise can be done in simulation following the instructions described on [this page](../exercise1/part5_exercise.md)