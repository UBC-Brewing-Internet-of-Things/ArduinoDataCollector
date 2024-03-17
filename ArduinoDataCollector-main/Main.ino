#include "Display-Update.ino"
#include "Read-Data.ino"
#include "Sent-Data.ino"
#include <WiFi.h>


struct DataPacket {
  char* value; // must be '\0' terminated
  int time;
  char* type; // must be '\0' terminated
};

//loops and repeatedly attempts to read the input bufferand send the input data to a remote server.
void readingLoop(){
  DataPacket* packet;
  bool sent;
  int attempts;
  while(true){
    
    packet = NULL;
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
}

/**
* deallocateString takes as input a pointer to a NULL terminated string in the heap and will deallocate it returning nothing.
* @params: ptr: a '\0' terminated string in the heap that is to be deallocated
* @effects: free's memory used by the input string
*/
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
