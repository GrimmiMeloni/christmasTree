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
#include "Rocket.h"

// Class for the creation of ornaments
class christmasTree
{
public:
    christmasTree(uint8_t pin);
    void begin(uint8_t brightness = 5);
    void setBrightness(uint8_t brightness);
    void refresh();

private:
    Adafruit_NeoMatrix *matrix;
    Rocket* rocket;
    Rocket* rocket2;
};

#endif  // christmasTree
