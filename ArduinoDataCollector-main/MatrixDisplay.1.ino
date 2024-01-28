#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

/**
Face functions
Parameters: none
Purpose: When each function is called it displays the corresponding face feature/face. i.e left eye displays left eye, 
sadFace displays a sad face.
*/

void leftEye(){
  //Left eye
  frame[1][6] = 1;
  frame[1][7] = 1;
  frame[2][6] = 1;
  frame[2][7] = 1;
}
void wink(){
  //Wink with the left eye
  frame[1][3] = 0;
  frame[1][4] = 0;
  frame[2][3] = 1;
  frame[2][4] = 1;
}
void rightEye(){
  //Right eye
  frame[1][9] = 1;
  frame[1][10] = 1;
  frame[2][9] = 1;
  frame[2][10] = 1;
}
void sadMouth(){
  //Mouth
  frame[6][6] = 1;
  frame[6][10] = 1;
  frame[5][6] = 1;
  frame[5][7] = 1;
  frame[5][8] = 1;
  frame[5][9] = 1;
  frame[5][10] = 1;
}
void happyMouth(){
  //Mouth
  frame[6][6] = 1;
  frame[6][10] = 1;
  frame[5][6] = 1;
  frame[6][7] = 1;
  frame[6][8] = 1;
  frame[6][9] = 1;
  frame[5][10] = 1;
}
void sadFace(){
    leftEye();
    rightEye();
    sadMouth();
}
void happyFace(){
    leftEye();
    rightEye();
    happyMouth();
}


/**
Error Functions
Parameters: none
Purpose: When called displays corresponding error
*/
void errorOne()
void errorTwo()
void errorThree()


void displayError(){
    int y = analogRead(VRY);
    int x = analogRead(VRX);

    while(x > 1020 && (517 < y && y < 523))
    {
        digitalWrite(LEDG, LOW);
        digitalWrite(LEDR, HIGH);
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

void setup() 
{
  Serial.begin(115200);
  matrix.begin();
}
uint8_t frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};
}

void loop() 
{
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
