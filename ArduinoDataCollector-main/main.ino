#include <WiFi.h>
#include <SoftwareSerial.h>

char ssid[] = "myNetwork";          //  your network SSID (name)
char pass[] = "myPassword";   // your network password

int status = WL_IDLE_STATUS;
IPAddress server(74,125,115,105);  // Google

int initializeWifiSettings(){

    int attempts = 0;
    Serial.begin(9600);
    Serial.println(ssid);

    while((status != WL_CONNECTED) && (attempts < 10)){
        attempts++;
        status = WiFi.begin(ssid, pass);
    }

    if (status == WL_CONNECTED) {
        client.connect(server, 80);
    }
    return status;
}   

void setup(){
  int initializeStatus = WL_IDLE_STATUS;
  while(initializeStatus != WL_CONNECTED){
    initializeStatus = initializeWifiSettings();
  }
  Serial.begin(9600);
}

struct DataPacket {
  char* value; // must be '\0' terminated
  int time;
  char* type; // must be '\0' terminated
};

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

// sends a non null packet to the server set.
bool sendPacket(DataPacket* input){
    bool connected = client.connected();
    if(connected && (DataPacket != nullptr)){ 
        client.write(string (input->value)); 
        client.write(input->time, 2);
        client.write(string (input->type));
    }
    return connected;
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

//loops and repeatedly attempts to read the input bufferand send the input data to a remote server.
void loop(){
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
