#include <SimpleDHT.h>

const int dht_pin = D2;

SimpleDHT11 dht11;

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  //declare two byte variables for temperature and humidity
  byte temperature = 0;
  byte humidity = 0;

  //read the values
  dht11.read(dht_pin, &temperature, &humidity, NULL);

  //display the values in Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature); 
  Serial.println(" *C");
  Serial.print("Humidity: "); 
  Serial.print(humidity); 
  Serial.println(" H");
  Serial.println();
  
  //wait 2 s
  delay(2000);
}

