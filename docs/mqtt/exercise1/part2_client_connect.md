---
title: "2. Create a client and connect to a MQTT broker"
--- 

Let's extend the code from the previous entry and connect the ESP32 to a broker. 

!!! Info
    The ESP32 is a simulated device in wokwi, so you won't be able to use your own broker (see [1. Install Mosquitto](./../getting_started/part1_install_mosquitto.md)) unless you have allowed access to your network over the internet (this wasn't explained in thi course). Hence, let's use use a third party broker: the broker [test.mosquitto.org](httpss://test.mosquitto.org). 

!!! Danger "Public MQTT Broker"
    Be aware that you're going to use a third party broker which is completely open. This implies that, first, you should not share relevant or sensitive information through that broker and use it only to test your MQTT application.

!!! Warning "Client and Topic names" 
    This broker is used by many people simultaneously. Hence, you must choose the clients and topics name with this in mind. I.e., avoid using generic names as a `test` or `example`. Also, emember that the client name is unique.

1. Open a new project in wokwi and load the following diagram.json.

    <details>
        <summary>Show diagram.json</summary>
        ```json title="diagram.json"
        --8<-- "snippets/mqtt/client_connect/diagram.json"
        ```
    </details>

2. Run the following code


    ```arduino title="client_connect.ino"
    --8<-- "snippets/mqtt/client_connect/client_connect.ino"
    ```

    1. [WiFiClient](https://docs.arduino.cc/language-reference/en/functions/wifi/client/) allows the creation of a client that can connect to to a specified internet IP address and port. In this case, you will use it to create a client connected to the [test.mosquitto.org](httpss://test.mosquitto.org) broker (server).
    2. [PubSubClient](https://github.com/knolleary/pubsubclient) allows a client for doing simple publish/subscribe messaging with a server that supports MQTT.
    3. You need to specify the **broker address** ([test.mosquitto.org](httpss://test.mosquitto.org)). If you want to use it with another broker, you need to specify the IP of the broker here (e.g., 192.168.0.12). You need to specify the **broker port** (by default, 1883 in MQTT).  **NOTE THE \* !!**
    4. You need to specify the client name. **Don't use a generic name**, this name is the one that will be use the broker and other devices of the MQTT network. **NOTE THE \* !!**
    5. Create the client. This name is not the client name in the network, but the name of the object in the script. I.e., you can choose the name freely as it won't be seen by anyone. 
    6. Create the MQTT client.
    7. This functions is the same as the one in [connect_wifi](./part1_connect_wifi.md).
    8. This function initializes the client in the MQTT broker (you need to specify the IP address and port of the broker=server). I know there's only one line of code inside the function, it's been done on purpose. You'll see the reason in [subscriber](./part4_subscriber.md).
    9. This function connects the client to the broker. If the client isn't connected, it will try to connect every 5 seconds. If the client connects, it'l display it through the serial port.
    10. This function handles the connection to the broker. If the connection is lost, it calls the `ConnectMqtt()` function. If the client is connected, it uses the `mqtt.loop()` to check for new messages.
    11. The function `InitMqtt()` is called in the `setup()`.
    12. The funcion `HandleMqtt()` is called in the loop to keep the client connected and constantly check for new messages.