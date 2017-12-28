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
 * File description: Implementation of methods for the christmasTree library
 */

#include "christmasTree.h"
#include <stdlib.h>

#ifndef PSTR
#define PSTR // For Arduino Due
#endif

// Creates an instance, and initializes the instance variables
christmasTree::christmasTree(uint8_t pin)
{
    matrix = new Adafruit_NeoMatrix(8, 8, pin,
                                    NEO_MATRIX_BOTTOM  + NEO_MATRIX_RIGHT +
                                    NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                                    NEO_GRB            + NEO_KHZ800);

    /*
    for (uint8_t i = 0; i < 8; ++i) snowPixels[i] = 0;
    _ornaments = RANDOM;
        */

    rocket = new Rocket(matrix);
    rocket2 = nullptr;
}

// Gets the instance set up and ready for use
void christmasTree::begin(uint8_t brightness)
{
    matrix->begin();
    matrix->setBrightness(brightness);
    matrix->fillScreen(0);  // Clears the matrix
    matrix->show();
}

// Sets the brightness of the NeoPixels. Range: [0,255]
void christmasTree::setBrightness(uint8_t brightness)
{
    matrix->setBrightness(brightness);
}

// Refreshes the drawn ornament
void christmasTree::refresh()
{
    matrix->fillScreen(0);

    if (rocket->hasFaded()){
        delete rocket;
        rocket = new Rocket(matrix);
    }
    rocket->update();


    
    if (millis() > 1000) {
        if (rocket2 == nullptr)
            rocket2 = new Rocket(matrix);

        if (rocket2->hasFaded()){
            delete rocket2;
            rocket2 = new Rocket(matrix);
        }
        rocket2->update();
    }
    

    matrix->show();

    

}
