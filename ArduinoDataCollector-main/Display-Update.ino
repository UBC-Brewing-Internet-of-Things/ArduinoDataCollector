#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

void updateDisplay(int displayCode){
    switch(displaycode){
    case -1: errorDisplay();
    default: displaySensors(int displayCode);
    }
}


/** When called updates the LED display with the current status of the devices connectivity.
*
* @arameters: none
* @modifies: Display screen, dispaying a smilely face or a sad face with debug lines as follows:
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

/** Displays interpreted sensor data based on the type signiture of the data 
 * 
 *  @paramaters: the pin number of the digital sensor to be read as input data
 *  @modifies: Display screen, presenting the data from the selected digital sensor
 * 
*/
void displaySensors(int sensorID){


}

// double must not be null 
void displayDisolvedOx(double ppm){

}

// double must not be null
void displaypH(double pH){

}

//double must not be null
void displayTempature(double temperature){

}


