const awsIot = require('aws-iot-device-sdk');
const fs = require('fs');

// Set up the connection options
const options = {
    privateKey: fs.readFileSync('C:/Users/user/Documents/aws_certificates/private.pem'),
    clientCert: fs.readFileSync('C:/Users/user/Documents/aws_certificates/device_certificate.pem'),
    caCert: fs.readFileSync('C:/Users/user/Documents/aws_certificates/AmazonRootCA1.pem'),
    clientId: 'iotconsole-abcdefgh',
    host: 'aaaaaaaaaaa.iot.eu-north-1.amazonaws.com',
    // keepAlive: 60,
    // baseReconnectTimeMs: 500
    // offlineQueueing : true,
    // offlineQueueMaxSize : "0",
    // offlineQueueDropBehavior : "newest"

  };

// Create an instance of the device
const device = awsIot.device(options);

device
  .on('connect', function() {
    console.log('connect');
    device.subscribe('esp8266/pub');
    //device.publish('topic_2', JSON.stringify({ test_data: 1}));
  });

device
  .on('message', function(topic, payload) {
    console.log("Message : ")
    console.log( topic, payload.toString());
  });

  device
      .on('reconnect', function() {
         console.log('reconnect');
      });
   device
      .on('offline', function() {
         console.log('offline');
      });
 

// Handle errors
device.on('error', (error) => {
  console.error('AWS IoT error:', error);
});