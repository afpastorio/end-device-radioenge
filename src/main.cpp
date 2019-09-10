#include <Arduino.h>
#include <RadioengeLoraWAN.h>


void setup() {
    debugSerial.begin(9600);
    loraSerial.begin(9600);
    RadioengeLoraWAN loraModule = RadioengeLoraWAN();
    loraModule.send("DALE");
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}