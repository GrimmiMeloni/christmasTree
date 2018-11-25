/**
 * Name: christmasTree
 * Author: Nick Lamprianidis (paign10.ln@gmail.com)
 * Version: 1.0
 * Description: A library with some ornaments for decorating a christmas tree
                The library is based on the NeoMatrix modules
 * License: Copyright (c) 2013 Nick Lamprianidis 
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: christmasTree.h
 * File description: Definitions and methods for the christmasTree library
 */

#ifndef christmasTree_h
#define christmasTree_h

#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Arduino.h>

// Available ornaments
enum ORNAMENTS
{
    SNOW_BACK = 0x01,
    TREE = 0x02,
    GIFT = 0x04,
    CHILD = 0x08,
    HOUSE = 0x10,
    SPACE_INVADER = 0x20,
    RANDOM = 0x40,
    CANDY = 0x80,
    SNOW_FRONT = 0x100
};

// Class for the creation of ornaments
class christmasTree
{
public:
    christmasTree(uint8_t pin);
    void begin(uint8_t brightness = 5);
    void setBrightness(uint8_t brightness);
    void setOrnaments(uint16_t ornaments);
    void refresh();
    void refresh(uint16_t ornaments);

private:
    Adafruit_NeoMatrix *matrix;
    uint8_t snowPixels[8];
    uint16_t _ornaments;  // Individual set bits get specific ornaments drawn
    void dropSnow();
    void drawTree();
    void drawGift();
    void drawChild();
    void drawHouse();
    void drawIceCrystal();
    void drawSpaceInvader();
    void drawRandom();
    void drawCandy();
    void drawRainbow();
};

#endif  // christmasTree
