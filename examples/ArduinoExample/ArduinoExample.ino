#include <Arduino.h>
#include "SWUART.hpp"
#define PIN_LED 13
#define BAUD_RATE 115200
SWUART swuart(Serial);

void packetReceived(uint8_t *data, uint8_t len) {
    digitalWrite(PIN_LED,!digitalRead(PIN_LED));
}
void setup(){
  Serial.begin(BAUD_RATE);
  swuart.onPacketReceived(packetReceived);
  pinMode(PIN_LED,OUTPUT);
}
void loop(){
    swuart.update();
    swuart.sendNum('A',random()); //send one uint8_t with packet id
    swuart.sendNum2('B',random(),random()); //send two uint8_t with packet id
    swuart.sendStr('C',"Hello World!");//send string
    const char* packettosend = "MY PACKET DATA"; 
    swuart.sendPacket(packettosend,strlen(packettosend));
}