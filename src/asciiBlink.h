#ifndef ASCIIBLINK_H
#define ASCIIBLINK_H

#include "Arduino.h"

class AsciiBlink {
public:
    void begin();
    void begin(uint16_t maxSymbols);
    bool registerNewString(char* string);

    void definePins(uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6, uint8_t p7);
    void setFrameTime(uint16_t milliseconds);
    void update();
private:
    uint8_t getAsciiCode(char input);
    uint8_t* register8bitBinaryArray(uint8_t input);

    uint16_t frameTime;
    uint8_t pins[8];
    uint32_t nextFrameTime;

    uint16_t maxSymbols;
    uint16_t lastCharId;
    uint16_t displayCharId;
    uint8_t** frameList;
};

extern AsciiBlink asciiBlink;

#endif
