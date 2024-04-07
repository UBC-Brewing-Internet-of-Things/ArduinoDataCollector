#include <WiFi.h>
#include <SoftwareSerial.h>

char ssid[] = "myNetwork";          //  your network SSID (name)
char pass[] = "myPassword";   // your network password

int status = WL_IDLE_STATUS;
IPAddress server(74,125,115,105);  // Ip address for the server

struct DataPacket {
  char* value; // must be '\0' terminated
  int time;
  char* type; // must be '\0' terminated
};

WiFiClient client;


//Initialized the serial bus, Wifi client to the database server. Attempts to connect 10 times and returns the status of the connection.
//returns WL_CONNECTED if the connectiohn was sucsessful and WL_IDLE_STATUS if the connectin fails.
void setup(){
    int attempts = 0;
    Serial.begin(9600);
    Serial.println(ssid);
    Serial.println(pass);

    while((status != WL_CONNECTED) && (attempts < 10)){
        attempts++;
        status = WiFi.begin(ssid, pass);
    }

    attempts = 0;
    if (status == WL_CONNECTED) {
      status = WL_IDLE_STATUS;
      while((status != WL_CONNECTED) && (attempts < 10))
        if(client.connect(server, 80)){
            status = WL_CONNECTED;
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

// sends a non null packet to the server set.
bool sendPacket(struct DataPacket* input){
    bool connected = client.connected();
    if(connected && (input != nullptr)){ 
        Serial.println((String) (input->value));
        client.println((String) (input->value)); 
        Serial.println(input->time, 2);
        client.println(input->time, 2);
        Serial.println((String) (input->type));
        client.println((String) (input->type));
    }
    return connected;
}

// reads from serial buffer a char, integer and a string in that order. String is terminated with newline character.
struct DataPacket* readData(){
    int integerSent = 0;
    char* valueSent;
    char* typeSent;
    if(Serial.available() >= 2){      
            char c;
            valueSent = (char*)malloc(sizeof(c * 50)); //assumes the name of the type of data is less then 50 characters
            int i = 0;
            while(Serial.peek() != '\0'){
              if(Serial.peek() != -1){
                *(valueSent + i) = Serial.read();
                i++;
              }
            }
            *(valueSent + i) = '\0';
        
        while(true){
          if(Serial.available() >= 2){
            integerSent = Serial.read(); // reads and removes 2 bytes, assumes smallest bits are sent first
            integerSent += 512 * Serial.read();
            break;
          }
        }
        
        char c;
        typeSent = (char*)malloc(sizeof(c * 50)); //assumes the contents of data is less then 50 characters
        int i = 0;
        while(Serial.peek() != '\0'){
          *(typeSent + i) = Serial.read();
          i++;
        }
        *(typeSent + i) = '\0';

        if((((string)valueSent).length() >= 1) || (integerSent != 0) || (((String)typeSent).length() >= 1)){
            struct DataPacket* result = (struct DataPacket*)malloc(sizeof(struct DataPacket)); //must be destroyed when sent
            
            result->time = integerSent;
            result->value = valueSent; 
            result->type = typeSent;
            return result;
        }
    }
    return NULL;
}

//loops and repeatedly attempts to read the input bufferand send the input data to a remote server.
void loop(){
  struct DataPacket* packet;
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
