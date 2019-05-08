#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define TEMP A0
#define DELTA_PUBLISH 3

// Update these with values suitable for your hardware/network.
byte mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED};
IPAddress ip(10, 1, 1, 238);
IPAddress server(10, 1, 1, 219);

String deviceId = "F8F005F1DBE7"; //MAC address
int outRelay = 8;

// Expects messages on topic thermostats/<deviceId> with payload:
// {param: "paramToWrite", value: "thevalue"}
void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    char message[length];
    for (int i = 0; i < length; i++)
    {
        message[i] = (char)payload[i];
    }
    // parse JSON
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(message);
    // test if parsing succeeds.
    if (!root.success())
    {
        Serial.println("Failed to parse JSON recieved in MQTT message");
        return;
    }
    
    // create string variable for comparison
    String _topic = topic;
    // possible commands directed towards this specific device
    if (_topic == "thermostats/" + deviceId)
    {
        String param = root["param"];
       
        if (param == "out")
        {
            String value = root["value"];
            if (value == "On")
            {
                digitalWrite(outRelay, HIGH);
                mqttSendS("status", "value", value);
            }
            else if (value == "Off")
            {
                digitalWrite(outRelay, LOW);
                mqttSendS("status", "value", value);
            }
        }
    }
}

EthernetClient ethClient;
PubSubClient client(ethClient);

long lastReconnectAttempt = 0;
// last published temperature
float lastTemp = -1;

boolean reconnect()
{
    char _deviceId[deviceId.length() + 1]; //convert deviceId to char
    deviceId.toCharArray(_deviceId, deviceId.length() + 1);
    if (client.connect(_deviceId))
    {
        Serial.println("Client connected");
        String sub = "thermostats/" + deviceId; //create char for subscription call
        char _sub[sub.length() + 1];
        sub.toCharArray(_sub, sub.length() + 1);
        client.subscribe(_sub);

        String out = digitalRead(outRelay) == LOW ? "Off" : "On";
        mqttSendS("status", "value", out);
        float temp = analogRead(TEMP) * 0.48875;
        mqttSendF("temperature", "value", temp);
    }
    return client.connected();
}

// prepare mqtt message with float
// =================================================================
void mqttSendF(String type, String param, float value)
{
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root[param] = value, 1;
    String msg = "";
    root.printTo(msg);
    mqttSend(type, msg);
}

// prepare mqtt message with string
// =================================================================
void mqttSendS(String type, String param, String value)
{
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root[param] = value;
    String msg = "";
    root.printTo(msg);
    mqttSend(type, msg);
}

// send mqtt message on thermostats/<deviceId>/<type>
// =================================================================
void mqttSend(String type, String msg) {
  if (client.connected()) {
    char _msg[msg.length()+1];
    msg.toCharArray(_msg, msg.length()+1);
    String topic = createTopic(type);
    char _topic[topic.length()+1];
    topic.toCharArray(_topic, topic.length()+1);
    if (!client.publish(_topic, _msg)) {
      Serial.println("MQTT message failed. Client connected.");
    }
  } else {
    Serial.println("MQTT message failed. Client disconnected.");
    return;
  }
}

String createTopic(String type) {
  String topic = "thermostats/";
  topic.concat(deviceId);
  topic.concat("/");
  topic.concat(type);
  return topic;
}

void handleConnection(){
  
  if (!client.connected())
    {
        long now = millis();
        if (now - lastReconnectAttempt > 5000)
        {
            Serial.println("Reconnecting to MQTT client...");
            lastReconnectAttempt = now;
            // Attempt to reconnect
            if (reconnect())
            {
                lastReconnectAttempt = 0;
            }
        }
    }
    else
    {
        float temp = analogRead(TEMP) * 0.48875;
        float delta = temp > lastTemp ? temp - lastTemp : lastTemp - temp;

        // Send a temperature update just if the delta is > 0.2
        if (delta > DELTA_PUBLISH)
        {
            Serial.print("Temp = ");
            Serial.println(temp);
            lastTemp = temp;
            mqttSendF("temperature", "value", temp);
        }

        client.loop();
    }
}

void setup()
{
    Serial.begin(9600);
    client.setServer(server, 1883);
    client.setCallback(callback);

    pinMode(outRelay, OUTPUT);

    Ethernet.begin(mac, ip);
    delay(1500);
    lastReconnectAttempt = 0;
}

void loop()
{
    handleConnection();
}
