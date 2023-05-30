#include <SimpleDHT.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);   //create an instance of the ESP8266WebServer library

const int dht_pin = D2;

SimpleDHT11 dht11;
byte temperature = 0;
byte humidity = 0;


String page =
R"(
<html>  
  <head> 
    <script src='https://code.jquery.com/jquery-3.3.1.min.js'></script>
    <title>Plusivo</title> 
  </head> 

  <body> 
    <h2>Today's weather!</h2> 
    <table style='font-size:20px'>  

      <tr>  
          <td> 
              <div>Temperature:  </div>
          </td>
          <td> 
              <div id='Temperature'></div> 
          </td>
      </tr> 

      <tr>  
          <td> 
              <div>Humidity:  </div>
          </td>
          <td> 
              <div id='Humidity'></div> 
          </td>
       </tr> 
    </table>  
  </body> 
  
  <script> 
   $(document).ready(function(){ 
     setInterval(refreshFunction,1000); 
   });

   function refreshFunction(){ 
     $.getJSON('/refresh', function(e){  
       $('#Temperature').html(e.temperature);  
       $('#Humidity').html(e.humidity);  
     }); 
   }      
  </script> 
</html> 
)";

void setupServer()
{ 
  //the method "server.on()" is to call a function when the user access the location. The default location is "/"
  server.on("/", htmlIndex);
  server.on("/refresh", refresh);
 
  //start the server
  server.begin();
  
  //print in serial manager that the HTTP server is started
  Serial.println("HTTP server started");
}

void setup() 
{
  Serial.begin(115200);

  connectToWiFi();
  setupServer();

  delay(4000);
}

void loop()
{
  server.handleClient();
  
  //read the values
  dht11.read(dht_pin, &temperature, &humidity, NULL);

  //display the values in Serial Monitor
  Serial.print("Temperature: ");  Serial.print(temperature);  Serial.println(" *C");
  Serial.print("Humidity: ");  Serial.print(humidity); Serial.println(" H");
  Serial.println();

  delay(100);
}

