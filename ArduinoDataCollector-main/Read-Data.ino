#include "Main.ino"
#include <SoftwareSerial.h>

void setup(){
    Serial.begin(9600);
}

struct DataPacket {
  char* value; //does this need to be a character array? Can this be a string or something?
  int time;
  String type;
};

// reads from serial buffer a char, integer and a string in that order. String is terminated with newline character.
DataPacket* readData(){
    int integerSent;
    char valueSent;
    String typeSent;
    if(serial.available() >= 2){
        if((serial.peek() != NULL) && (valueSent == NULL)){
            valueSent = Serial.read(); // reads and removes 1 byte, assumes one character currently, needs to be updated to handle a string
        }
        if((serial.peek() != NULL) && (integerSent == NULL)){
            integerSent = Serial.read(); // reads and removes 2 bytes
        }
        if((serial.peek() != NULL) && (typeSent.length() == 0)){
            typeSent = Serial.read(); // initialized string to the first character of the typesent data
            while(serial.peek() != '\0'){
                typeSent += Serial.read(); //reads until the string terminates
            }
        }

        if((valueSent == NULL) || (integerSent == NULL) || (typeSent.length >= 1)){
            DataPacket* result = malloc(sizeof(DataPacket)); //must be destroyed when sent
            
            result->time = integerSent;
            result->value = valueSent; //Uses C++ syntax, probably wrong
            result->type = typeSent;
            return result;
        }
    }
    return NULL;
}

