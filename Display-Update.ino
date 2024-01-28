#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

void updateDisplay(int displayCode){
    switch(displaycode){
    case 0: errorDisplay();
    default: displaySensors(int displayCode);
    }
}


/** When called updates the LED display with the current status of the devices connectivity.
/*
/* Parameters: none
/* modified: Display screen, dispaying a smilely face or a sad face with debug lines as follows:
*/
void errorDisplay(){

int y = analogRead(VRY);
    int x = analogRead(VRX);

    while(x > 1020 && (517 < y && y < 523))
    {
        sadFace();

        y = analogRead(VRY);
        x = analogRead(VRX);
    }

    while((517 < x && x < 523) && y > 1020)
    {
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDR, LOW);
        y = analogRead(VRY);
        x = analogRead(VRX);
    }
    while(x < 5 && y > 1020)
    {
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDR, LOW);
        delay(1000);
        digitalWrite(LEDG, LOW);
        digitalWrite(LEDR, HIGH);
        delay(1000);
        y = analogRead(VRY);
        x = analogRead(VRX);
    }
    while((517 < x && x < 523) && y < 5)
    {
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDR, LOW);
        delay(500);
        digitalWrite(LEDG, LOW);
        digitalWrite(LEDR, HIGH);
        delay(500);
        y = analogRead(VRY);
        x = analogRead(VRX);
    }

    digitalWrite(LEDG, LOW);
    digitalWrite(LEDR, LOW);

}

void displaySensors(int )


