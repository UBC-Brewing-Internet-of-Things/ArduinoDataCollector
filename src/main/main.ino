#include <WiFi.h>
#include <SoftwareSerial.h>
#include "dataPacket.cpp"

void setup(){
    int initializeStatus = WL_IDLE_STATUS;
    while(initializeStatus != WL_CONNECTED){
        initializeStatus = initializeWifiSettings();
    }
    Serial.begin(9600);
}

//loops and repeatedly attempts to read the input bufferand send the input data to a remote server.
void loop(){
    struct DataPacket* packet;
    bool sent;
    int attempts;
    while(true){
        packet = readData();
    
        if(packet != NULL){
            if((packet->type != NULL) && (packet->value != NULL)){
                sent = false;
                attempts = 0;
                // sends packet
                while((attempts < 10) && (sent == false)){
                    sent = sendPacket(packet);
                    attempts++;
                }
            }
            //clears memory used for packet
            if(packet->type != NULL)
                deallocateString(packet->type);
            if(packet->value != NULL)
                deallocateString(packet->value);

            free(packet);
        }
    }
}
