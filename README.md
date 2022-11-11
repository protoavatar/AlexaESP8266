# ESP8266 controlled via Amazon Alexa

This project uses [fauxmoESP](https://github.com/vintlabs/fauxmoESP) library to make ESP8266 act like a Philips Hue lightbulb. You can set a relay on ESP8266 to ON and OFF by controlling Alexa, as well as sending a value to the ESP by asking for a brightness to Alexa.

Project is managed and compiled using [PlatformIO](https://platformio.org/) (By far the best way to interact with this devices).
I’m using Arduino’s built in `ESP8266WiFi.h` library to manage the WiFi connection.
At this stage, I am only debugging via terminal, not acting on the Relay.

Resources: https://github.com/javimata/arduino/tree/master/esp8266-esp01s
