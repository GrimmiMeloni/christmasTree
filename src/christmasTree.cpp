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

    for (uint8_t i = 0; i < 8; ++i) snowPixels[i] = 0;
    _ornaments = RANDOM;

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

// Selects the ornaments to be drawn on the matrix
void christmasTree::setOrnaments(uint16_t ornaments)
{
    _ornaments = ornaments;
}

// Refreshes the drawn ornament
void christmasTree::refresh()
{
    matrix->fillScreen(0);

    uint16_t ornament = 0x01;
    boolean on = _ornaments & ornament;
    for (uint8_t i = 0; i < 10; ++i)
    {
        switch (ornament)
        {
            case 0x01:
                if ( on ) dropSnow();
                break;
            case 0x02:
                if ( on ) drawTree();
                break;
            case 0x04:  
                if ( on ) drawGift();
                break;
            case 0x08:  
                if ( on ) drawChild();
                break;
            case 0x10:
                if ( on ) drawHouse();
                break;
            case 0x20:
                if ( on ) drawIceCrystal();
                break;
            case 0x40:
                if ( on ) drawRandom();
                break;
            case 0x80:
                if ( on ) drawCandy();
                break;
            case 0x100:
                if ( on ) dropSnow();
                break;
                /* never reachable due to only 10 bitshifts - see for loop above
                raise this to 11 to also include this one

            case 0x200:
                if ( on ) drawRainbow();
                break;
                */
        }

        ornament <<= 1;
        on = _ornaments & ornament;
    }

    matrix->show();
}

// Updates the ornament and refreshes the drawing
void christmasTree::refresh(uint16_t ornaments)
{
    _ornaments = ornaments;
    refresh();
}

// Scrolls the snowflakes down, and
// creates snow on the top row with a probability
void christmasTree::dropSnow()
{
    for (uint8_t x = 7; x > 0; --x)
        snowPixels[x] = snowPixels[x-1];

    snowPixels[0] = 0;
    uint16_t white = matrix->Color(255, 255, 255);

    for (uint8_t y = 0; y < 8; ++y)
        if ( (double)rand() / RAND_MAX < 0.1 )
                snowPixels[0] = snowPixels[0] | (0x01 << y);

    for (int x = 0; x < 8; ++x)
        for (int y = 0; y < 8; ++y)
            if ( (snowPixels[x] >> y) & 0x01 )
                matrix->drawPixel(x, y, white);
}

// Draws a fir on the matrix
void christmasTree::drawTree()
{
    uint16_t red = matrix->Color(255, 0, 0),
             green = matrix->Color(0, 255, 0),
             brownish = matrix->Color(210, 180, 40);

    matrix->drawFastVLine(0, 3, 2, red);  // Star
    matrix->drawFastVLine(1, 3, 2, green);  // Branches
    matrix->drawRect(2, 2, 2, 4, green);
    matrix->drawRect(4, 1, 2, 6, green);
    matrix->drawRect(6, 3, 2, 2, brownish);  // Stem
}

// Draws a gift on the matrix
void christmasTree::drawGift()
{
    uint16_t red = matrix->Color(255, 0, 0),
             green = matrix->Color(0, 255, 0);

    matrix->drawPixel(0, 1, red);  // Bow
    matrix->drawPixel(1, 2, red);
    matrix->drawPixel(2, 3, red);
    matrix->drawPixel(2, 4, red);
    matrix->drawPixel(1, 5, red);
    matrix->drawPixel(1, 6, red);
    matrix->fillRect(3, 1, 4, 6, green);  // Box
}

// Draws a child on the matrix
void christmasTree::drawChild()
{
    uint16_t blue = matrix->Color(0, 0, 255);

    matrix->drawRect(0, 3, 2, 2, blue);  // Head
    matrix->drawPixel(2, 1, blue);  // Hands
    matrix->drawPixel(2, 6, blue);
    matrix->drawFastVLine(3, 2, 4, blue);
    matrix->drawRect(4, 3, 2, 2, blue);  // Torso
    matrix->drawFastHLine(6, 2, 2, blue);  // Legs
    matrix->drawFastHLine(6, 5, 2, blue);
}

// Draws a house on the matrix
void christmasTree::drawHouse()
{
    uint16_t red = matrix->Color(255, 0, 0),
             yellow = matrix->Color(255, 255, 0);

    matrix->drawFastVLine(0, 3, 2, red);  // Housetop
    matrix->drawFastVLine(1, 2, 4, red);
    matrix->drawFastVLine(2, 1, 6, red);
    matrix->drawFastVLine(3, 0, 8, red);
    matrix->fillRect(4, 1, 4, 6, yellow);  // Walls
}

// Draws a space invader alien on the matrix
void christmasTree::drawSpaceInvader()
{
    uint16_t blue = matrix->Color(0, 0, 255);

    matrix->drawPixel(0, 1, blue);  // Antennas
    matrix->drawPixel(0, 6, blue);
    matrix->drawFastVLine(1, 2, 4, blue);  // Forehead
    matrix->drawFastVLine(2, 1, 6, blue);
    matrix->drawFastVLine(3, 0, 2, blue);  // Eyes Level
    matrix->drawFastVLine(3, 3, 2, blue);
    matrix->drawFastVLine(3, 6, 2, blue);
    matrix->drawFastVLine(4, 1, 6, blue);  // Nose Level
    matrix->drawPixel(5, 1, blue);  // Mouth
    matrix->drawPixel(6, 2, blue);
    matrix->drawPixel(5, 6, blue);
    matrix->drawPixel(6, 5, blue);
}

// Draws random pixels on the matrix
void christmasTree::drawRandom()
{
    uint16_t color;

    for (int x = 0; x < 8; ++x)
        for (int y = 0; y < 8; ++y)
            if ( (double)rand() / RAND_MAX < 0.5 )
            {
                color = matrix->Color(rand() % 256, rand() % 256, rand() % 256);
                matrix->drawPixel(x, y, color);
            }  
}

// Draws a gift on the matrix
void christmasTree::drawCandy()
{
    uint16_t red = matrix->Color(255, 0, 0),
             white = matrix->Color(255, 255, 255);

    matrix->drawLine(7, 1, 7, 2, red);
    matrix->drawLine(6, 1, 6, 2, white);
    matrix->drawLine(5, 1, 5, 2, red);
    matrix->drawLine(4, 1, 4, 2, white);
    matrix->drawLine(3, 1, 3, 2, red);
    matrix->drawLine(2, 1, 2, 2, white);
    //bottom bow
    matrix->drawLine(1, 2, 1, 3, red);
    matrix->drawLine(0, 3, 0, 5, white);
    //back up
    matrix->drawLine(1, 5, 1, 6, red);
    matrix->drawLine(2, 5, 2, 6, white);
    matrix->drawLine(3, 5, 3, 6, red);
}

void christmasTree::drawRainbow() {

            // Diangonal Rainbow Scroll
        for (int j=0; j<6; j++) {

        for(int i=-1;i<=8;i++){
            for(int n=-18; n<=6; n+=6){
                matrix->drawLine(n+i,0,n+i+7,7, matrix->Color(255,0,0));
                matrix->drawLine(n+i+1,0,n+i+8,7, matrix->Color(255,255,0));
                matrix->drawLine(n+i+2,0,n+i+9,7, matrix->Color(0,255,0));
                matrix->drawLine(n+i+3,0,n+i+10,7, matrix->Color(0,255,255));
                matrix->drawLine(n+i+4,0,n+i+11,7, matrix->Color(0,0,255));
                matrix->drawLine(n+i+5,0,n+i+12,7, matrix->Color(255,0,255));
            }
            matrix->show();
            delay(200);
        }
        }
}

void christmasTree::drawIceCrystal() {
uint32_t ledarray[] = {
                       0x00000000, 0x0000FFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000FFFF, 0x00000000, 
                       0x0000FFFF, 0x0000FFFF, 0x00000000, 0x0080FFFF, 0x0080FFFF, 0x00000000, 0x0000FFFF, 0x0000FFFF, 
                       0x00000000, 0x00000000, 0x0000FFFF, 0x00000000, 0x00000000, 0x0000FFFF, 0x00000000, 0x00000000, 
                       0x00000000, 0x0080FFFF, 0x00000000, 0x0000FFFF, 0x0000FFFF, 0x00000000, 0x0080FFFF, 0x00000000, 
                       0x00000000, 0x0080FFFF, 0x00000000, 0x0000FFFF, 0x0000FFFF, 0x00000000, 0x0080FFFF, 0x00000000, 
                       0x00000000, 0x00000000, 0x0000FFFF, 0x00000000, 0x00000000, 0x0000FFFF, 0x00000000, 0x00000000, 
                       0x0000FFFF, 0x0000FFFF, 0x00000000, 0x0080FFFF, 0x0080FFFF, 0x00000000, 0x0000FFFF, 0x0000FFFF, 
                       0x00000000, 0x0000FFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000FFFF, 0x00000000, 
                       };

  for (int t = 0; t < 64; t++)
  {
    if (ledarray[t] == 0) continue;
    //matrix->drawPixel(t/8, t%8, matrix->Color(ledarray[t] & 0x00FF0000, ledarray[t] & 0x0000FF00, ledarray[t] & 0x000000FF)); 
    matrix->setPixelColor(t, ledarray[t]);
  }
}

