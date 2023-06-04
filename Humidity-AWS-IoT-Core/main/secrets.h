
#include <pgmspace.h>
 
#define SECRET                    
 
#define THINGNAME "Temp_humidity"
 
int8_t TIME_ZONE = +5;                                           //India: +5:30 UTC
 
//AWS MQTT host from AWS Settings.........................................................................
const char MQTT_HOST[] = "avglbvv7vep02-ats.iot.eu-north-1.amazonaws.com";      //Your host ID here. Get it from AWS settings
 
// Root CA1 Certificate will be here ▼.......................................................................
static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 

//Device Certificate will be here..................................................................................
// Copy contents from XXXXXXXX-certificate.pem.crt here ▼
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAL5r4ruDm1ZcjQqNiNeV1MJedt4PMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzA1MzAxMzE2
MDdaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDakbkr/e3RgS9eh/zR
kgQkVUr7qiCy40O5U4KYXkdCG5pLXMXaoien8cV7+DoZAsWfo/4xZRrb+S1ZXHAC
4qM24+cVT6lMfx+0bklz5THJ5j10eboR27Jc8lrBoN3h69IudDbopiUYJtiVR/cb
bujwUcR9Qr7xQ1U0eGQ8EfwZv6foy/i8dw6Z9x/XbJaCPvdOjShgD8Gi++b8PzW4
/Ha7k5bYsvZWHeYY9zBiXvAz6j/Aj3rIr5YogJwSOzBxpLIQRQDlC5iZgwJnDLJY
+JPHhFLl/g/egYb7/NemL6pbRHNvljXASMWUulhRX0hxhIynS7ROO/ab4hLyf5DE
AOcxAgMBAAGjYDBeMB8GA1UdIwQYMBaAFCxxlNiw5l5YCqSTX58W2jb6XZQbMB0G
A1UdDgQWBBRM2A5jGsEezkJQIVxLUjvms0VgFTAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAxoAfXYUvzakuVslistIc3Fx8
nk2pddUxY6+dNWZC/PcRjF0zMO0mr/xsuhu6fOcD7AJlwhue/DNwANTK6V8CcX13
blmVx77YI6YjrjPAPj3GXmglka7Y/9sF9jmyaliHG8hASaNd5TyVbTozYqUFfxWv
lcUljwjK/KgTLBMntpWi+p3RsTVaoIGsZrss9BGaEAMBBqrNxpTStmWSAG8Bz4bN
OBHDVCyVZHdL+sffOrztNiuxF/RjSURc0CB9RSuadbIitquWgqQp98+YnDtlo0JB
b1aH8/iW/5xW8XSjMsQPyrhJwTAQpF0pXIwaRPFlg9bhGEvOLqvj/bH62BnHOQ==
-----END CERTIFICATE-----
)KEY";
 
// Private Key Certificate will be here......................................................................
// Copy contents from  XXXXXXXX-private.pem.key here ▼
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpgIBAAKCAQEA2pG5K/3t0YEvXof80ZIEJFVK+6ogsuNDuVOCmF5HQhuaS1zF
2qInp/HFe/g6GQLFn6P+MWUa2/ktWVxwAuKjNuPnFU+pTH8ftG5Jc+UxyeY9dHm6
EduyXPJawaDd4evSLnQ26KYlGCbYlUf3G27o8FHEfUK+8UNVNHhkPBH8Gb+n6Mv4
vHcOmfcf12yWgj73To0oYA/Bovvm/D81uPx2u5OW2LL2Vh3mGPcwYl7wM+o/wI96
yK+WKICcEjswcaSyEEUA5QuYmYMCZwyyWPiTx4RS5f4P3oGG+/zXpi+qW0Rzb5Y1
wEjFlLpYUV9IcYSMp0u0Tjv2m+IS8n+QxADnMQIDAQABAoIBAQDVVidHqTLXqyBx
RIqgg8VHMXle60+/S9Rur/RohJ1JCWgw5vy3yk6qvnHj7wXGI86BY7BYxjbRPwXk
kzVBm7Vzfj+vrXGyGOL5WiyX0r4mM3UIm0fi5m3SCzxKgpoQSf19GjH+Iy1RxZjh
HL01Kaxz5VvEZ8G3++DOtjQf7e4DsiACGz8fCdX08XOUvSHwYF5G25Gf2ShmyCiB
00jVfaETWD2OPpL//ZTSYRoNIUGJAFn5kdLHG3ZdmVqNGAwHtRaU27xoJ9gvXSrm
r2/ScPnhiG7+dM+uUH5HrAMVuACS2Xbop84WsrQ88Ucf1qE9yL9alTpkHuurq3r0
8KRvgpuBAoGBAPhHZQ22eO34YmUpDJfowjrtgNAPK+UlemPElhaMciClt9JLrHY6
Nrs8jKo5JVRlQWf6ZIUtU9xjGe2o9MG/RNEQdIThI6NKVko25voQbm1JcJ1V87Ai
CFLu+lkeRjHuDA1Mp5uo+bGsEZd/dJNYzecOLsj4ky+YWyogZjWpwFYvAoGBAOFd
zZ7ZImnjgRnvnulJcCB/CjKu+VfQ7/h774OrTENR8n7brBUNnxy1x/YINAsNyZ2H
f03fDBR33AT06yZ4Op5+hkQp7JEyyX4o3s90lyngSvd88ZndYp0YPPn6SvdLb21t
eG+UbJ3mNDLbRkTUq+akLBMwa18ciO6U91E9sqCfAoGBAIgVEcVnW3cLqlrKGhX1
ROhpny3q8uNBHIksihtH1ZIhYtTIF3ohxDfyIyN1+Qj+CtCEBK6ePpXQV7jU33qG
bKCuhT8D67WnnA5Hc2hiszQBidEi+FN1A9z5EYzhNBZP5Jkxh7ig8GM67dV8zZep
mAnp0yjiXkI7HtTDN2J4bWyPAoGBAMb0CJIzHi5cqZw77g4ExvfpLxePYJAl47N5
tfiHQMwti+ZyB3iOjejKkbyhgVBA27w14izcu81WAuZdUTqk6RsCl4WVfUKxky/M
5OZABzLwzz2tD5zF1EjbHPmR/JxT/AqembPnU/wRPgOnkGEzXo4+YKqQFDni9v+o
gq01ynwBAoGBAMkmDqkj6A2Ab43umQ3o+MRg4zCrylxQaoe55VspHBo6sd48n6fn
PmKFQc5sd7jjelKNXW5/yh/aJiN3hQDXZed78APZ+4DTEPOQ4qV76f0emwh+9U1a
SXoTtxaQ0vloGbET8Gxiwmp96QO6h600vXYT76SOxHR7o/K77MD0zIwd
-----END RSA PRIVATE KEY-----
)KEY";
