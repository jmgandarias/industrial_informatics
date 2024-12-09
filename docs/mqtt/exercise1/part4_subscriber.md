---
title: "4. Create a subscriber"
--- 

This entry shows how you can create a _subscriber_ with an ESP32 in wokwi that can subscribe to topics. 

!!! Warning "Client and Topic names" 
    You're going to use a public broker that is used by many people simultaneously. Hence, you must choose the clients and topics name with this in mind. I.e., avoid using generic names as a `test` or `example`. Also, emember that the client name is unique.

1. Open a new project in wokwi and load the following diagram.json.

    <details>
        <summary>Show diagram.json</summary>
        ```json title="diagram.json"
        --8<-- "snippets/mqtt/client_subscriber/diagram.json"
        ```
    </details>

2. Run the following code


    ```arduino title="client_subscriber.ino"
    --8<-- "snippets/mqtt/client_subscriber/client_subscriber.ino"
    ```

    1. As the message received in the topic will be a `char`, you'll use this variable to convert it to `String` for easier manipulation.
    2. Now, after setting the server, we need to call the function `SubscribeMqtt()`. This functions establishes the topics to which the client will be subscribed. This operation is a function for two reasons: 
        1. If the client is disconnected, it needs to subscribe to the topics again. So the function can be called multiple times in the code.
        2. If there is (or could be in the future) more than one topics to subscribe to, it can be easily addressed by simply modifying the code inside this function.
    3. We need to set the function (callback) that will be called everytime a message is received. This function has been named `OnMqttReceived`.
    4. `SubscribeMqtt()` is called again if the connection to the broker is lost.
    5. `SubscribeMqtt()` defines the topics to which the client will subscribe. In this case, it will only subscribe to the topic `/testing_topic`, but there could be more than one inside the function. The client is subscribed to a topic using the method  [`subscribe()`](https://github.com/knolleary/pubsubclient/blob/master/src/PubSubClient.cpp) from the `PubSubClient.h` library. 
    5. This function is a callback that will be called everytime a message is published in **any of the topics** that the client is subscribed to (similar to an interruption). Inside the callback, you get access to the `topic` where the message was published, the content of the message throught the variable `payload`, and the `length` of that message. 
    6. The content of `payload` will be casted into `String`. In this case, `payload` is an array of _bytes_. These `bytes` need to be first casted into characters and then concatenated to form the final `String`. To do this, we first need to go through all the positions of the array (i.e., we use a `for` loop). This loop will go from the first element (`i=0`) to the last one (`i=length`). In every step of the loop, we first cast the element `i` of the array `payload` to `char`: `(char)payload[i]`. The data of this element should be concatenated to the string of `content` to form the final message. To do that we can use the method [`concat()`](https://www.arduino.cc/reference/es/language/variables/data-types/string/functions/concat/). When the loop finishes, the `content` of the message is displayed through the serial port.
    7. This client works as a subscriber only. It means it won't do anything until a message is received. Hence, there's nothing inside the `loop()` (apart from the `HandleMqtt()` funcion that was explained in a [previous entry](./part2_client_connect.md)).  


3. If you have done it correctly, you should see that the ESP32 prints the content of the messages received in the topic `/testing_topic`. You can test it from the _MQTT Explorer_ or the terminal.

    ![](images/part4_1.png)

!!! success "CONGRATULATIONS!"
    Now you're able to subscribe to a MQTT topic with an ESP32.