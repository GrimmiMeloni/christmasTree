/**
 * An example demonstrating the christmasTree library
 * The example exposes some of the library's interface
 * Specifically, the example shows how to create an instance
 * of the christmasTree library, initialize the instance,
 * set the ornaments, and refresh the matrix
 *
 * The library is based on the NeoMatrix modules from Adafruit
 * You can use the NeoMatrix modules as ornaments on your christmas tree
 *
 * ** Happy Holidays **
 */

// Includes the necessary libraries
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include "christmasTree.h"

#define PIN 6  // Pin to which the input of the matrix is connected
#define PERIOD 10000  // Refreshes the ornament every 10 sec

// Creates a christmasTree instance with the DOUT pin as an argument
christmasTree ornament(PIN);

void setup()
{
    Serial.begin(9600);
    Serial.println("start");

    ornament.begin(255);  // Initializes the instance   
}

void loop()
{
    // Refreshes the drawing on the matrix.
    // Any change basically involves scrolling the snowflakes down (if enabled)
    ornament.refresh();
    delay(300);
}
