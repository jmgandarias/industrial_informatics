---
title: "5. Exercise: practical application"
--- 

An exercise is proposed to communicate two ESP32s in an MQTT netword. One of them acts as publisher while the other as subscriber. The one that has the role of publisher has a button connected and, when the button is pressed (or released), it publishes in a topic that the button has been pressed. The other ESP32 will have a LED connected and will subscribe to the topic in which the ESP32 publisher publishes. Then, each time it receives a message in the topic, it changes the state of the LED.

To test the application you can open two tabs in the browser and check that it works as follows:

![type:video](./videos/exercise1.mp4)

Try to solve the problem before seeing the solution below.

<details>
        <summary>Show publisher diagram.json</summary>
        ```json title="diagram.json"
        --8<-- "snippets/mqtt/mqtt_publisher_button/diagram.json"
        ```
    </details>

<details>
    <summary>Show publisher code</summary>
    ```arduino title="mqtt_publisher_button.ino"
    --8<-- "snippets/mqtt/mqtt_publisher_button/mqtt_publisher_button.ino"
    ```
</details>


<details>
        <summary>Show subscriber diagram.json</summary>
        ```json title="diagram.json"
        --8<-- "snippets/mqtt/mqtt_subscriber_LED/diagram.json"
        ```
    </details>

<details>
    <summary>Show subscriber code</summary>
    ```arduino title="mqtt_subscriber_LED.ino"
    --8<-- "snippets/mqtt/mqtt_subscriber_LED/mqtt_subscriber_LED.ino"
    ```
</details>