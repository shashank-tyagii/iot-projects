#include <ESP8266WiFi.h>
const char* ssid = "Shashank Tyagi-2.4G";
const char* password = "Shashank@1234";

BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);

//------------------------------------------------------Add certificates and secure Wifi----------------------------------------------
void secureWiFiClient(){
  delay(3000);
  net.setTrustAnchors(&cert);
  net.setClientRSACert(&client_crt, &key);
}

//----------------------------------------------------Connect to WiFi-----------------------------------------------------------------
void connectToWiFi()
{ 
  Serial.println("Connecting to the WiFi");
  //set the WiFi mode to WiFi_STA
  //the WiFi_STA means that the board will act as a station,
  //similar to a smartphone or laptop
  WiFi.mode(WIFI_STA);

  //connect to the WiFi network using the ssid and password strings
  WiFi.begin(ssid, password);

  //below we check the status of the WiFi and wait until the
  //board is connected to the network
  Serial.println("Waiting for connection");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //when the board is successfully connected to the network,
  //display the IP assigned to it in the serial monitor.
  Serial.println("");
  Serial.print("Connected to "); Serial.println(ssid);
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
}
