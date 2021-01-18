#include <ESP8266WiFi.h>                               // Include the Wi-Fi library
#include <farmAPI.h>                                  // Include the farm functions
                                                     // 
const char* SSID     = "Julius Caesar WiFi";        // The SSID (name) of the Wi-Fi network you want to connect to
const char* PASSWORD = "12345678e";                // The password of the Wi-Fi network
const int   PORT     = 8500;                      //
                                                 //
WiFiServer wifiServer(PORT);                    // Set listen port to 8500

void wait(int time){
  delay(1000);
  Serial.print(".");
}

void connect_msg(char* ip, int port){
  Serial.print("\n");
  Serial.print("Connected to WiFi. IP:");
  Serial.println(WiFi.localIP());
}
 
void setup() {
 
  Serial.begin(115200);
  delay(1000);
 
  WiFi.begin(SSID, PASSWORD);
  Serial.println("Connecting..");
  while (WiFi.status() != WL_CONNECTED) {
    wait(1000);
  }
 
  wifiServer.begin();
}
 
void loop() {
 
  WiFiClient client = wifiServer.available();
 
  if (client) {
    while (client.available()>0) {
      char c = client.read();
      Serial.write(c);
    }
      client.print("OK");
      delay(10);
      client.stop();
    Serial.println("Client disconnected");
  }
}
