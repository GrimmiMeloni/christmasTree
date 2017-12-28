#include "Rocket.h"

Rocket::Rocket(Adafruit_NeoMatrix* _matrix) 
    : rising(true), column(0), height(8), matrix(_matrix) {
    init();
}

void Rocket::init() {
    column = (rand() % 6) + 1;
    flareCycle = 0;
    
    int r = rand() % 64;
    int g = rand() % 64;
    int b = rand() % 64;
    color = matrix->Color(r,g,b);
    Serial.print("init'ed rocket with r,g,b : ");
    Serial.print(r);
    Serial.print(",");
    Serial.print(g);
    Serial.print(",");
    Serial.println(b);
}

void Rocket::update() {
    if (height > 2) {
        height--;
        uint8_t r = 244;
        uint8_t g = 167;
        uint8_t b = 66;

        uint8_t r2 = 127;
        uint8_t g2 = 100;
        uint8_t b2 = 67;

        uint8_t scale = 6;

        matrix->drawPixel(height, column, matrix->Color(r/scale,g/scale,b/scale));
        matrix->drawPixel(height+1, column, matrix->Color(r/scale/2,g/scale/2,b/scale/2));
        //matrix->setPassThruColor(Adafruit_NeoPixel::Color(r2,g2,b2));
        //matrix->drawPixel(height+1, column, matrix->Color(r2,g2,b2));
        //matrix->setPassThruColor();
        matrix->drawPixel(height+2, column, matrix->Color(r/scale/3,g/scale/3,b/scale/3));
        Serial.println("rocket still rising");
        return;
    }

    if (flareCycle < 4) {
        flareCycle++;

        matrix->drawPixel(height, column - flareCycle, color);
        matrix->drawPixel(height, column + flareCycle, color);
        matrix->drawPixel(height - flareCycle, column, color);
        matrix->drawPixel(height + flareCycle, column, color);
        
        Serial.println("updating flare");
        return;
    } 
    Serial.print("noop land... :(");  
}

bool Rocket::hasFaded() {
    return flareCycle >= 4;
}