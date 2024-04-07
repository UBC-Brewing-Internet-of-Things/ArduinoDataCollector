#include <WiFi.h>
#include <SoftwareSerial.h>

char ssid[] = "myNetwork";          //  your network SSID (name)
char pass[] = "myPassword";   // your network password

int status = WL_IDLE_STATUS;
IPAddress server(74,125,115,105);  // Ip address for the server

struct DataPacket {
  String* value; 
  int time;
  String* type; // must be '\0' terminated
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


// sends a non null packet to the server set.
bool sendPacket(struct DataPacket* input){
    bool connected = client.connected();
    if(connected && (input != nullptr)){ 
        Serial.println((*input->value));
        client.println((*input->value)); 
        Serial.println(input->time, 2);
        client.println(input->time, 2);
        Serial.println((*input->type));
        client.println((*input->type));
    }
    return connected;
}

// reads from serial buffer a char, integer and a string in that order. String is terminated with newline character.
struct DataPacket* readData(){
    int integerSent = 0;
    char* valueSent;
    char* typeSent;
    if(Serial.available() >= 2){      
            char valueTemp[50];
            //valueSent = (char*)malloc(sizeof(c * 50)); //assumes the name of the type of data is less then 50 characters
            int i = 0;
            while(Serial.peek() != '\0'){
              if(Serial.peek() != -1){
                valueTemp[i]= Serial.read();
                i++;
              }
            }
            valueTemp[i] = '\0';
            String valueSent(valueTemp);
        
        while(true){
          if(Serial.available() >= 2){
            integerSent = Serial.read(); // reads and removes 2 bytes, assumes smallest bits are sent first
            integerSent += 512 * Serial.read();
            break;
          }
        }
        
        char typeTemp[50];
        //typeSent = (char*)malloc(sizeof(c * 50)); //assumes the contents of data is less then 50 characters
        i = 0;
        while(Serial.peek() != '\0'){
          typeTemp[i] = Serial.read();
          i++;
        }
        typeTemp[i] = '\0';
        String typeSent (typeTemp);

        if((valueSent.length() >= 1) && (integerSent != 0) && ((typeSent.length() >= 1))){
            struct DataPacket* result = (struct DataPacket*)malloc(sizeof(struct DataPacket)); //must be destroyed when sent
            result->time = integerSent;
            result->value = malloc(sizeof(valueSent)); 
            *result->value = valueSent;
            result->type = malloc(sizeof(typeSent));
            *result->type = typeSent;
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
        free(packet->type);
      if(packet->value != NULL)
        free(packet->value);
      
      free(packet);
      }
    }
  }
