#include <Arduino.h>
#include <RadioengeLoraWAN.h>

RadioengeLoraWAN loraModule = RadioengeLoraWAN();

void setup() {
    debugSerial.begin(9600);
    loraSerial.begin(9600);
    loraModule.begin();
    loraModule.send("DALE");
}

void loop() {
}