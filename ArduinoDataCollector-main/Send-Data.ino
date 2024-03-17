#include <WiFi.h>
#include "Main.ino"

char ssid[] = "myNetwork";          //  your network SSID (name)
char pass[] = "myPassword";   // your network password

int status = WL_IDLE_STATUS;
IPAddress server(74,125,115,105);  // Google


int initializeWifiSettings(){

    int attempts = 0;
    Serial.begin(9600);
    Serial.println(ssid);

    while((status = WL_IDLE_STATUS) && (attempts < 10)){
        attempts++;
        status = WiFi.begin(ssid, pass);
    }

    if (status == WL_CONNECTED) {
        client.connect(server, 80);
    }
    return status;
}   



bool sendPacket(DataPacket* input){
    bool connected = client.connected();
    if(connected && (DataPacket != nullptr)){ 
        client.write((string)input->value); 
        client.write(input->time);
        client.write(input->type);
    }
    return connected;
}
