#include "Main.ino"
#include <SoftwareSerial.h>

void setup(){
    Serial.begin(9600);
}


DataPacket readData(){
    int incomingByte;
    if(Serial.avalible() > 0){
        incomingByte = Serial.Read();
        
    }
    
}

