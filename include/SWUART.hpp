#ifndef SWUART_H
#define SWUART_H

#include <Arduino.h>
#include <CRC8.h>

#define PACKET_START ' '
#define PACKET_END '\n'

class SWUART {
public:
    SWUART(HardwareSerial &serial) : serial(serial) {}

    void begin(unsigned long baudrate) {
        serial.begin(baudrate);
    }

    void sendPacket(uint8_t *data, uint8_t len) {
        CRC8 crc;
        crc.reset();
        crc.add(data, len);
        uint8_t checksum = crc.getCRC();

        serial.write(PACKET_START);
        serial.write(len);
        serial.write(data, len);
        serial.write(checksum);
        serial.write(PACKET_END);
        serial.flush();
        while (serial.available()) {
            uint8_t byte = serial.read();
        }
    }

    void update() {
        while (serial.available()) {
            uint8_t byte = serial.read();
            processByte(byte);
        }
    }

    void onPacketReceived(void (*callback)(uint8_t *, uint8_t)) {
        packetCallback = callback;
    }

    void sendStr(uint8_t type,String& str){
        uint8_t buf[100];
        buf[0]=type;
        memcpy(buf+1,(uint8_t*)str.c_str(),str.length()+1);
        sendPacket(buf,str.length()+2);
    }
    void sendNum(uint8_t type,uint8_t val){
        uint8_t buf[2];
        buf[0]=type;
        buf[1]=val;
        sendPacket(buf,2);
    }
    void sendNum2(uint8_t type,uint8_t val1,uint8_t val2){
        uint8_t buf[3];
        buf[0]=type;
        buf[1]=val1;
        buf[2]=val2;
        sendPacket(buf,3);
    }
private:
    HardwareSerial &serial;
    void (*packetCallback)(uint8_t *, uint8_t) = nullptr;
    uint8_t buffer[64];
    uint8_t index = 0;
    uint8_t length = 0;
    bool receiving = false;

    void processByte(uint8_t byte) {
        static CRC8 crc;
        if (byte == PACKET_START) {
            receiving = true;
            index = 0;
            length = 0;
            return;
        }
        if (!receiving) return;
        
        if (index == 0) {
            length = byte;
            if (length > sizeof(buffer)) receiving = false;
        } else if (index <= length) {
            buffer[index - 1] = byte;
        } else {
            crc.reset();
            crc.add(buffer, length);
            if (crc.getCRC() == byte && packetCallback) {
                packetCallback(buffer, length);
            }
            receiving = false;
        }
        index++;
    }
};

#endif
