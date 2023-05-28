//htmlIndex() is called everytime somebody access the address of the board in the browser and sends back a message.
void htmlIndex() 
{
  server.send(200, "text/html", file);

}

//function for controlling the red LED
void redFunction()
{
  int value1 = server.arg("state1").toInt();
  value1 = map(value1, 0, 100, 0, 1023);

  if(value1 == 0)
     digitalWrite(red, LOW);//turn of the led
  else
     analogWrite(red, value1);//change the brightness of red
  
  server.send(200, "text/html", "red");
}

//function for controlling the green LED
void greenFunction()
{
  int value2 = server.arg("state2").toInt();
  value2 = map(value2, 0, 100, 0, 1023);

  if(value2 == 0)
     digitalWrite(green, LOW);//turn of the led
  else
     analogWrite(green, value2);//change the brightness of green
  
  server.send(200, "text/html", "green");
}

//function for controlling the blue LED
void blueFunction()
{
  int value3 = server.arg("state3").toInt();
  value3 = map(value3, 0, 100, 0, 1023);

  if(value3 == 0)
     digitalWrite(blue, LOW);//turn of the led
  else
     analogWrite(blue, value3);//change the brightness of blue
  
  server.send(200, "text/html", "blue");
}

//function for controlling the blue LED
void json_sample()
{
  const char input[] = "{\"result\":true,\"count\":42,\"foo\":\"bar\"}";
  //JSONVar myObject = JSON.parse(input);
  
  server.send(200, "text/json", input );
}