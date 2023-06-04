#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "secrets.h"
#include "DHT.h"

#define DHTPIN 4                      // Digital pin GPIO4 (D2) connected to the DHT sensor.
#define DHTTYPE DHT11                 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

//create 3 variables that are used to stores the pins to which is the LED
const int red = D6;
const int green = D7;
const int blue = D8;

float humidity,temperature;

#define AWS_IOT_PUBLISH_TOPIC   "esp8266/pub"                     //Subscribe the message from AWS
#define AWS_IOT_SUBSCRIBE_TOPIC "esp8266/sub"                     //Publish the message to AWS

WiFiClientSecure net;
PubSubClient client(net);

//**********************************************SETUP*********************************************************************************
void setup()
{
  Serial.begin(9600);
  connectToWiFi();
  secureWiFiClient();
  connectAWS();
  
  dht.begin();
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

//------------------------------------------------------- Connent with AWS-------------------------------------------------------------
void connectAWS()
{
  client.setServer(MQTT_HOST, 8883);
  Serial.println(MQTT_HOST);
  client.setCallback(messageReceived);

  Serial.print("Connecting to AWS IOT Thing : "); Serial.println(THINGNAME);
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");  delay(1000);
  }

  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
  Serial.println("AWS IoT Connected!");
}


//---------------------------------------------------- Read Message from AWS -----------------------------------------------------------
void messageReceived(char *topic, byte *payload, unsigned int length)        // Topic is the subscribe topic
{
  Serial.print("Received ["); Serial.print(topic); Serial.print("]: ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  StaticJsonDocument<1000> doc;
  deserializeJson(doc, payload);

  int red_json = doc["red"];
  int green_json = doc["green"];
  int blue_json = doc["blue"];

  RGBLed(red_json,green_json,blue_json);
  
}

//----------------------------------------------------- Send Message to AWS------------------------------------------------------------
void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["humidity"] = humidity;
  doc["temperature"] = temperature;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}


//***********************************************LOOP***********************************************************
void loop()
{
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature) )  // Check if any reads failed and exit early (to try again).
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));  Serial.print(temperature); Serial.println(F("°C "));
  delay(10000);

  if (!client.connected())
  {
    connectAWS();
  }
  else
  {
    client.loop();
    publishMessage();
  }
}
