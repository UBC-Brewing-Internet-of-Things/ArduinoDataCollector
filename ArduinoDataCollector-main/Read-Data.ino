#include "Main.ino"
#include <SoftwareSerial.h>

void initializeWifiSettings(){
    Serial.begin(9600);
}

// reads from serial buffer a char, integer and a string in that order. String is terminated with newline character.
DataPacket* readData(){
    int integerSent;
    char* valueSent;
    char* typeSent;
    if(serial.available() >= 2){
        if((serial.peek() != -1) && (valueSent == NULL)){
            
            char c;
            valueSent = malloc(sizeof(c * 50)); //assumes the name of the type of data is less then 50 characters
            int i = 0;
            while(serial.peek() != '\0'){
                *(valueSent + i) = serial.read();
                i++;
            }
            *(valueSent + i) = '\0';
            
        }
        
        if((serial.peek() != -1) && (integerSent == NULL)){
                integerSent = Serial.read(); // reads and removes 2 bytes, assumes smallest bits are sent first
                integerSent += 512 * Serial.read();
        }
        
        if((serial.peek() != NULL) && (typeSent.length() == 0)){
            char c;
            typeSent = malloc(sizeof(c * 50)); //assumes the contents of data is less then 50 characters
            int i = 0;
            while(serial.peek() != '\0'){
                *(typeSent + i) = serial.read();
                i++;
            }
            *(typeSent + i) = '\0';
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

