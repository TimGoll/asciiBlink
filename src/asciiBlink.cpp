#include "asciiBlink.h"

// PUBLIC

void AsciiBlink::begin() {
    this->begin(200);
}

void AsciiBlink::begin(uint16_t maxSymbols) {
    this->maxSymbols    = maxSymbols;
    this->lastCharId    = 0;
    this->displayCharId = 0;
    this->frameList     = malloc(sizeof(uint8_t*) * maxSymbols);
    this->frameTime     = 1000;
    this->pauseTime     = 50;
    this->displayBreak  = 0;
}

void AsciiBlink::enableDebug() {
    Serial.begin(115200);
}

bool AsciiBlink::registerNewString(char* string) {
    for (uint8_t i = 0; string[i] != '\0'; i++) {
        if (this->lastCharId >= this->maxSymbols) {
            return false;
        }

        this->frameList[this->lastCharId] = register8bitBinaryArray( getAsciiCode( string[i] ) );

        for (uint8_t bit = 0; bit < 8; bit++) {
            Serial.print(this->frameList[this->lastCharId][bit]);
        }

        this->lastCharId++;
    }
    return true;
}

bool AsciiBlink::registerNewDelay() {
    if (this->lastCharId >= this->maxSymbols) {
        return false;
    }

    this->frameList[this->lastCharId] = register8bitBinaryArray( 0 );

    this->lastCharId++;
}

bool AsciiBlink::registerNewOnDelay() {
    if (this->lastCharId >= this->maxSymbols) {
        return false;
    }

    this->frameList[this->lastCharId] = register8bitBinaryArray( 255 );

    this->lastCharId++;
}

bool AsciiBlink::test() {
    for (int i = 0; i < 8; i++) {
        if (this->lastCharId >= this->maxSymbols) {
            return false;
        }

        this->frameList[this->lastCharId] = register8bitBinaryArray( pow(2, i) + 0.5);

        this->lastCharId++;
    }

    return true;
}

void AsciiBlink::setFrameTime(uint16_t milliseconds) {
    this->frameTime = milliseconds;
}

void AsciiBlink::setPauseTime(uint16_t milliseconds) {
    this->pauseTime = milliseconds;
}

void AsciiBlink::definePins(uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6, uint8_t p7) {
    pins[0] = p0; pinMode(p0, OUTPUT); digitalWrite(p0, LOW);
    pins[1] = p1; pinMode(p1, OUTPUT); digitalWrite(p1, LOW);
    pins[2] = p2; pinMode(p2, OUTPUT); digitalWrite(p2, LOW);
    pins[3] = p3; pinMode(p3, OUTPUT); digitalWrite(p3, LOW);
    pins[4] = p4; pinMode(p4, OUTPUT); digitalWrite(p4, LOW);
    pins[5] = p5; pinMode(p5, OUTPUT); digitalWrite(p5, LOW);
    pins[6] = p6; pinMode(p6, OUTPUT); digitalWrite(p6, LOW);
    pins[7] = p7; pinMode(p7, OUTPUT); digitalWrite(p7, LOW);
}

void AsciiBlink::update() {
    if (millis() >= this->nextFrameTime) {
        //little displayBreak
        if (this->displayBreak) {
            for (uint8_t i = 0; i < 8; i++) {
                digitalWrite(pins[i], LOW);
            }
            this->nextFrameTime+=this->pauseTime;
        }

        //display character
        if (!this->displayBreak) {
            if (this->frameList[this->displayCharId][0] <= 1) {
                //render to LEDs
                Serial.print("[");
                for (uint8_t i = 0; i < 8; i++) {
                    digitalWrite(pins[i], this->frameList[this->displayCharId][i]);
                    Serial.print(this->frameList[this->displayCharId][i]);
                }
                Serial.println("]");
                this->nextFrameTime += this->frameTime;
            }
            //display special frame
            else {

            }

            this->displayCharId++;
            if (this->displayCharId == this->lastCharId) {
                this->displayCharId = 0;
            }
        }

        this->displayBreak = !this->displayBreak;
    }
}

// PRIVATE

uint8_t AsciiBlink::getAsciiCode(char input) {
    return (uint8_t) input;
}

uint8_t* AsciiBlink::register8bitBinaryArray(uint8_t input) {
    uint8_t* arr = malloc(sizeof(uint8_t) * 8);

    uint8_t buf = input;
    uint8_t div = 128;
    for (uint8_t i = 0; i < 8; i++) {
        arr[i] = buf / div;
        buf = buf % div;
        div /= 2;
    }

    Serial.print("Register Char ID: ");
    Serial.print(input);
    Serial.print(" - ");
    Serial.print("[");
    for (uint8_t i = 0; i < 8; i++) {
        Serial.print(arr[i]);
    }
    Serial.println("]");

    return arr;
}

AsciiBlink asciiBlink;
