const awsIot = require('aws-iot-device-sdk');
const fs = require('fs');
const http = require('http'); // Import HTTP module
const port = 8000;
const express = require ('express');              // Import the express library file
const path = require ('path');
const bodyParser = require('body-parser');
const app = express();  

app.use(express.urlencoded({}));                   // Parsing form data from URL - Middleware, not for URL 

var sensorData = {
  temperature : "0.00",
  humidity : "0.00"
};

// Set up the connection options
const options = {
    privateKey: fs.readFileSync('C:/Users/user/Documents/aws_certificates/private.pem'),
    clientCert: fs.readFileSync('C:/Users/user/Documents/aws_certificates/device_certificate.pem'),
    caCert: fs.readFileSync('C:/Users/user/Documents/aws_certificates/AmazonRootCA1.pem'),
    clientId: 'iotconsole-20a97fe2-5b20-4e74-b77a-5378ab8aced0',
    host: 'avglbvv7vep02-ats.iot.eu-north-1.amazonaws.com',

  };

// Create an instance of the device
const device = awsIot.device(options);

device.on('connect', function() {
    console.log('Connected to ESP8266 Device');
    device.subscribe('esp8266/pub');
    
  });

device.on('message', function(topic, payload) {
    console.log("Message : ")
    console.log( topic, payload.toString());
    sensorData = JSON.parse(payload.toString());
    console.log(sensorData.humidity + "%")
    console.log(sensorData.temperature + "DegC")

  });

device .on('reconnect', function() {
         console.log('reconnect');
      });
device.on('offline', function() {
         console.log('offline');
      });
device.on('error', (error) => {
  console.error('AWS IoT error:', error);
});

app.get('/sensor_data', function(req,res){
  return res.status(200).json( {
    temperature : sensorData.temperature ,
    humidity : sensorData.humidity,
})
});

app.post('/LEDcontrol' , function(req,res){
  let data = req.body;
  console.log(data);
  device.publish('esp8266/sub', JSON.stringify(data));
})

// Server start code
app.listen(port, function(err){
  if (err){
      console.log('Error in running the server ', err); return;
  }
  console.log('My server is running on port : ', port);
})