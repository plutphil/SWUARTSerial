# SWUARTSerial
Singe Wire Half Duplex UART using two pins on arduino and esp32

# Hints
Additional circuitry required. One Diode (I use 1n4004) - pole/cathode at tx pin other at rx pin. 4k7 Ohm resistor between rx and 5V (3.3V also works). Same at the other microcontroller but you don't need a resistor there. One is enough. 
```
                         5V
                         |
                        .-.
   .------------.       | |4k7
   |MCU1        |1n4004 | |               1n4004 .---------------.
   |ESP32       |       '-'                      |           MCU2|
   |            |        |                       |        Arduino|
   |      17  TX|---|<---o--------------o-->|----|TX    Atmega328|
   |            |        |              |        |               |
   |            |        |              |        |               |
   |      16  RX|--------'              '--------|RX             |
   |            |                                |               |
   '------------'                                |               |
                                                 '---------------'
(created by AACircuit v1.28.7 beta 10/23/16 www.tech-chat.de)

```
### Credits/References
http://www.gheinz.de/techdocs/hardware/swart/index.htm Single-Wire UART (SWART) 

https://github.com/paulbobin/SWUART

https://github.com/pxdelta/SWUART

https://deepbluembedded.com/stm32-uart-half-duplex-single-wire-tutorial-example/

https://controllerstech.com/stm32-uart-6-communication-using-single-wire/

https://forum.arduino.cc/t/half-duplex-uart-over-a-single-wire/924148
