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
int initializeWifiSettings(){
    Serial.println("Initializing wifi settings");

    int attempts = 0;
    Serial.begin(9600);
    Serial.println(ssid);
    Serial.println(pass);

    while((status != WL_CONNECTED) && (attempts < 10)){
        Serial.println("Attempting to connect to server");
        attempts++;
        status = WiFi.begin(ssid, pass);
    }

    attempts = 0;
    if (status == WL_CONNECTED) {
        status = WL_IDLE_STATUS;
        while((status != WL_CONNECTED) && (attempts < 10))
            Serial.println("Attempting to connect client to server");

            if(client.connect(server, 80)){
                Serial.println("Connected client to server");
                status = WL_CONNECTED;
            }
    } else {
        Serial.println("ERROR server not connected");
    }
    return status;
}

// sends a non null packet to the server set.
bool sendPacket(struct DataPacket* input){
    bool connected = client.connected();
    if((input != nullptr)){
        Serial.println((String) (input->value));
        Serial.println(input->time, 2);
        Serial.println((String) (input->type));
        if(connected){
            client.println((String) (input->value));
            client.println(input->time, 2);
            client.println((String) (input->type));
        }
    } else {
        Serial.println("DataPacket is NULL");
    }
    return connected;
}

// reads from serial buffer a char, integer and a string in that order. String is terminated with newline character.
struct DataPacket* readData(){
    int integerSent;
    char* valueSent;
    char* typeSent;
    if(Serial.available() >= 2){
        Serial.println("Data found in serial buffer for valueSent");
        if((Serial.peek() != -1) && (valueSent == NULL)){

            char c;
            valueSent = (char*)malloc(sizeof(c * 50)); //assumes the name of the type of data is less then 50 characters
            int i = 0;
            while(Serial.peek() != '\0'){
                *(valueSent + i) = Serial.read();
                i++;
            }
            *(valueSent + i) = '\0';
            while(i < 50){
                free(typeSent + i);
                i++;
            }
            Serial.println((String) *valueSent);
        }

        if((Serial.peek() != -1) && (integerSent == 0)){
                Serial.println("Data found in serial buffer for integer sent");
                integerSent = Serial.read(); // reads and removes 2 bytes, assumes smallest bits are sent first
                integerSent += 512 * Serial.read();
                Serial.println(integerSent);
        }

        if((Serial.peek() != -1) && (((String)typeSent).length() == 0)){
            Serial.println("Data found in serial buffer for type sent")
            char c;
            typeSent = (char*)malloc(sizeof(c * 50)); //assumes the contents of data is less then 50 characters
            int i = 0;
            while(Serial.peek() != '\0'){
                *(typeSent + i) = Serial.read();
                i++;
            }
            *(typeSent + i) = '\0';
            while(i < 50){
                free(typeSent + i);
                i++;
            }
            Serial.println((String) *typeSent);
        }

        if((valueSent != NULL) || (integerSent != 0) || (((String)typeSent).length() >= 1)){
            struct DataPacket* result = (struct DataPacket*)malloc(sizeof(struct DataPacket)); //must be destroyed when sent

            result->time = integerSent;
            result->value = valueSent;
            result->type = typeSent;
            return result;
        }
    }
    return NULL;
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