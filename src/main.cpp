#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "fauxmoESP.h"

#define WIFI_SSID "Jacobiano"  //Cambiar por tu WIFI SSID
#define WIFI_PASS "galgogalgo"  //Cambiar por tu WIFI password
#define SERIAL_BAUDRATE 115200
#define ID_ONE "LUZ" // Es el nombre con el que lo identificará Alexa

// Used module does not work with GPIO port but with Serial Interface Commands
byte relON[] = {0xA0, 0x01, 0x01, 0xA2};  //Hex command to send to onboard serial microprocessor for open relay
byte relOFF[] = {0xA0, 0x01, 0x00, 0xA1}; //Hex command to send to serial for close relay

fauxmoESP fauxmo;

// -----------------------------------------------------------------------------
// Wifi
// -----------------------------------------------------------------------------

void wifiSetup() {

    // Set WIFI module to STA mode
    WiFi.mode(WIFI_STA);

    // Connect
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Wait
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();

    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BAUDRATE);
  Serial.write(relOFF, sizeof(relOFF)); // turns the relay OFF
    // Wifi
    wifiSetup();

    fauxmo.createServer(true); // not needed, this is the default value
    fauxmo.setPort(80); // This is required for gen3 devices

    // You have to call enable(true) once you have a WiFi connection
    // You can enable or disable the library at any moment
    // Disabling it will prevent the devices from being discovered and switched
    fauxmo.enable(true);

    // Fauxmo
    fauxmo.addDevice(ID_ONE);

    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {

        // Callback when a command from Alexa is received.
        // You can use device_id or device_name to choose the element to perform an action onto (relay, LED,...)
        // State is a boolean (ON/OFF) and value a number from 0 to 255 (if you say "set kitchen light to 50%" you will receive a 128 here).
        // Just remember not to delay too much here, this is a callback, exit as soon as possible.
        // If you have to do something more involved here set a flag and process it in your main loop.

        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

        // Checking for device_id is simpler if you are certain about the order they are loaded and it does not change.
        // Otherwise comparing the device_name is safer.
        if (state)
        {
          Serial.write(relON, sizeof(relON)); // turns the relay ON
        } else {
          Serial.write(relOFF, sizeof(relOFF)); // turns the relay OFF
        }

    });
}

void loop() {
  // put your main code here, to run repeatedly:
    fauxmo.handle();
}