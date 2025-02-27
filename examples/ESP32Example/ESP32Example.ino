#include <Arduino.h>
#include "SWUART.hpp"

#define PIN_LED 2

#define UART_RX 16
#define UART_TX 17
#define BAUD_RATE 115200

SWUART swuart(Serial2);


void packetReceived(uint8_t *data, uint8_t len) {
    digitalWrite(PIN_LED,!digitalRead(PIN_LED));
}
void setup(){
  Serial.begin(115200);
  Serial2.begin(BAUD_RATE, SERIAL_8N1, UART_RX, UART_TX);
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