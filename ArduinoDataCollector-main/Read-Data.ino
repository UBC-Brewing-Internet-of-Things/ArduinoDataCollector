#include "Main.ino"
#include <SoftwareSerial.h>

void setup(){
    Serial.begin(9600);
}

struct DataPacket {
  char value;
  int time;
  String type;
};

// reads from serial buffer a char, integer and a string in that order. String is terminated with newline character.
DataPacket readData(){
    int integerSent;
    char valueSent;
    String typeSent;
    if(serial.available() >= 8){
        if((serial.peek() != NULL) && (valueSent == NULL)){
            valueSent = Serial.read();
        }
        if((serial.peek() != NULL) && (integerSent == NULL)){
            integerSent = Serial.read();
        }
        typeSent = Serial.read();
        while(serial.peek() != '\n'){
            typeSent += Serial.read();
        }

        typeSent += '\n';

        struct DataPacket returnData;
        returnData.time = integerSent;
        returnData.value = valueSent;
        returnData.type = typeSent;
        return returnData;
    }
    return NULL;
}

