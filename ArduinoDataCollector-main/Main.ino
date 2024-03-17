#include "Display-Update.ino"
#include "Read-Data.ino"
#include "Sent-Data.ino"
#include <WiFi.h>


struct DataPacket {
  char* value;
  int time;
  char* type;
};

void readingLoop(){
  DataPacket* packet;
  bool sent;
  int attempts;
  while(true){
    
    packet = NULL;
    packet = readData();
    
    if(packet != NULL){
      sent = false;
      attempts = 0;
      // sends packet
      while((attempts < 10) && (sent == false)){
        sent = sendPacket(packet);
        attempts++;
      }
      
      //clears memory used for packet
      deallocateString(packet->type);
      deallocateString(packet->value);
      free(packet);
    }
  }
}

//clobbers pointer
void deallocateString(char* ptr){
    while(*ptr != '\0'){
      free(ptr);
      ptr++;
    }
    free(ptr);
    return;
}

void loop{
  int initializeStatus = WL_IDLE_STATUS;
  while(initializeStatus != WL_CONNECTED){
    initializeStatus = initializeWifiSettings();
  }
  readingLoop();
}
