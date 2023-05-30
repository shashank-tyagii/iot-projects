//htmlIndex() is called everytime somebody access the address of the board in the browser and sends back a message.
void htmlIndex() 
{
  server.send(200, "text/html", page);
}

void refresh()
{ 
  //create a char array
  char messageFinal[100];

  char container[100] = 
  R"(
    {
      "temperature":  %d,
      "humidity": %d
    }
  )";
  
  //put the values in messageFinal
  sprintf(messageFinal, container, temperature, humidity);

  //send data to user
  server.send(200, "application/javascript", messageFinal);
}