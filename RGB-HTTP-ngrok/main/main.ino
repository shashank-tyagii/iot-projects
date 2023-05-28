// Port Forwarding using ngrok- https://ngrok.com/blog-post/putting-the-esp32-microcontroller-on-the-internet

#include<ESP8266WebServer.h>
#include <Arduino_JSON.h>
ESP8266WebServer server(80);

//create 3 variables that are used to stores the pins to which is the LED
const int red = D6;
const int green = D7;
const int blue = D8;

String file = R"(
<html lang='en'>
    <head>
        <title>Dim an RGB LED</title>
        <meta name='viewport' content='width=device-width, initial-scale=1'>
        <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.1.0/css/all.css'/>
        <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.1.2/css/bootstrap.min.css'/>
        <script src='https://code.jquery.com/jquery-3.3.1.min.js'></script>
    </head>
    <body>
    <div class='container-fluid text-center'>
        <div class='row'>
            <div class='col-sm-12' style='color:red;font-size:7vh'>
                <p>Use the sliders to control the brightness.</p>
            </div>
        </div>     
        <br/>
        <div class='row'>
            <div class='col-sm-12' style='color:red;font-size:3vh'>
                Red:
                <b id='status1'></b>
            </div>
        </div> 
        <div class='col-sm-12'>
              <input type='range' min='0' max='100' class='form-control-range' id='slider_red'/>
        </div>

        <div class='row'>
            <div class='col-sm-12' style='color:green;font-size:3vh'>
                Green: 
                <b id='status2'></b>
            </div>
        </div> 
        <div class='col-sm-12'>
              <input type='range' min='0' max='100' class='form-control-range' id='slider_green'/>
        </div>

        <div class='row'>
            <div class='col-sm-12' style='color:blue;font-size:3vh'>
                Blue:
                <b id='status3'></b>
            </div>
        </div> 
        <div class='col-sm-12'>
              <input type='range' min='0' max='100' class='form-control-range' id='slider_blue'/>
        </div>
    </div>
    </body>
    
    <script>
        $('#slider_red').on('change', function(){
            var state_slider_red = $('#slider_red').val();
            
            $('#status1').html(state_slider_red + ' %');

            $.ajax({
              url: '/redFunction',
              type: 'POST',
              data: {state1: state_slider_red}
            });
        });

        $('#slider_green').on('change', function(){
            var state_slider_green = $('#slider_green').val();
            
            $('#status2').html(state_slider_green + ' %');

            $.ajax({
              url: '/greenFunction',
              type: 'POST',
              data: {state2: state_slider_green}
            });
        });

        $('#slider_blue').on('change', function(){
            var state_slider_blue = $('#slider_blue').val();
            
            $('#status3').html(state_slider_blue + ' %');

            $.ajax({
              url: '/blueFunction',
              type: 'POST',
              data: {state3: state_slider_blue}
            });
        });
    </script>
</html>)";

void setup() 
{
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  
  if(!SPIFFS.begin()){
  Serial.println("An Error has occurred while mounting SPIFFS");
  return;
}

  //start the Serial communication at 9600 bits/s
  Serial.begin(9600);

  //wait 1 s until the Serial communication is started
  delay(1000);
  
  //call the two functions used to connect connect to wifi and setup the server
  connectToWiFi();
  setupServer();
}

void loop()
{
  //the method below is used to manage the incoming request from the user
  server.handleClient();
}

//setupServer() function is used to set up and organise the website
void setupServer()  // ROUTER
{ 
  //the method "server.on()" is to call a function when the user access the location and the default location is "/"
  server.on("/", htmlIndex);
  server.on("/redFunction", redFunction);
  server.on("/greenFunction", greenFunction);
  server.on("/blueFunction", blueFunction);
  server.on("/json", json_sample);

  //start the server
  server.begin();
  
  //print in Serial Monitor that the HTTP server is started
  Serial.println("HTTP server started");
}

