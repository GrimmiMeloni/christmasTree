#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

class Rocket 
{
    public:
    Rocket(Adafruit_NeoMatrix* _matrix);
    void update();
    bool hasFaded();

    private:
    void init();
    bool isRising();

    bool rising;
    uint8_t column;
    uint8_t height;
    uint8_t flareCycle;
    Adafruit_NeoMatrix *matrix;
    uint16_t color;
};