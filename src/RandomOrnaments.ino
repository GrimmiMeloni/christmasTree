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

#define BUTTON1 2 //first button
#define BUTTON2 8 //first button

long time_ref;  // Used as a time reference
int ornamentCycleIdx = 0;

// Creates a christmasTree instance with the DOUT pin as an argument
christmasTree ornament(PIN);

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);

    Serial.begin(9600);
    Serial.println("start");

    ornament.begin(3);  // Initializes the instance
    
    // Selects which ornaments to appear
    // Available choices: SNOW_BACK, SNOW_FRONT, TREE, GIFT, CHILD, HOUSE, SPACE_INVADER, RANDOM, CANDY
    ornament.setOrnaments(SNOW_BACK + TREE);  
    
    time_ref = millis();  // Gets the temporal baseline
}

void loop()
{
    if ( (unsigned long) (millis() - time_ref) > PERIOD )
    {
        // Picks an ornament at random.
        // It's a bit esoteric, but basically setting a bit in a byte enables a specific ornament
        uint8_t new_ornament = 0x02 << ( rand() % 8 );

        if (new_ornament == SPACE_INVADER) {
            ornament.setOrnaments(SNOW_FRONT + new_ornament);  // Sets the new ornament
        } else {
            ornament.setOrnaments(SNOW_BACK + new_ornament);  // Sets the new ornament
        }
        time_ref = millis();
    }
    
    // Refreshes the drawing on the matrix.
    // Any change basically involves scrolling the snowflakes down (if enabled)
    ornament.refresh();
    
    //digitalWrite(LED_BUILTIN, HIGH);
    int button1 = digitalRead(BUTTON1);
    int button2 = digitalRead(BUTTON2);

    if (button1 == LOW){
        Serial.print("Button1 pressed at ");
        Serial.println(millis());
        uint8_t new_ornament = 0x02 << ( ornamentCycleIdx % 8 );
        ornamentCycleIdx++;

        if (new_ornament == SPACE_INVADER) {
            ornament.setOrnaments(SNOW_FRONT + new_ornament);  // Sets the new ornament
        } else {
            ornament.setOrnaments(SNOW_BACK + new_ornament);  // Sets the new ornament
        }
        time_ref = millis();
    }


    if (button2 == LOW)
        Serial.println("Button2 pressed");

    delay(300);
    //digitalWrite(LED_BUILTIN, LOW);
    delay(300);
}
