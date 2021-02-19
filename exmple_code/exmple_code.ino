#include <ESP8266WiFi.h>                               //| Include the Wi-Fi library
                                                      // |
                                                     //  |
const char* SSID     = "Julius Caesar";             //   |The SSID (name) of the Wi-Fi network you want to connect to
const char* PASSWORD = "12345678e";                //    |The password of the Wi-Fi network
const int   PORT     = 8500;                      //     |
bool blinked = true;                             //      |
WiFiServer wifiServer(PORT);                    //       |Set listen port to 8500

void wait_msg(int time){
  delay(1000);
  Serial.print(".");
}

void blink_led(){
  if(blinked){
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    digitalWrite(LED_BUILTIN, LOW); 
  }
  blinked = !blinked;
}

void connect_msg(IPAddress ip, int port){
  Serial.print("\n");
  Serial.print("Connected to WiFi on IP : ");
  Serial.println(ip);
  Serial.print("Listen on port : ");
  Serial.print(PORT);
}

char* commend_msg(String msg)
{
  Serial.println("accept from user :\""+msg+"\"");
  blink_led(); 
  if(msg.equals("on?"))
  {
    return "yes";
  }
  if(msg.equals("A"))
  {
    return "Option a";
  }
  if(msg.equals("B"))
  {
    return "Option b";
  }
  if(msg.equals("C"))
  {
    return "Option c";
  }
  if(msg.equals("D"))
  {
    return "Option d";
  }
  return "error-v1-unknown-command";
}

void setup() {
 
  Serial.begin(115200); 
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting..");
  pinMode(LED_BUILTIN, OUTPUT);
  
  while (WiFi.status() != WL_CONNECTED) {
    wait_msg(1000);
  }
  
  connect_msg(WiFi.localIP(),PORT);
  wifiServer.begin();
}
 
void loop() {
  WiFiClient client = wifiServer.available();
  String buff = "";
  if (client) 
  {
    while(client.connected()>0)
    {
      while(client.available()>0)
      {
        buff = buff + char(client.read());
      }
      if(buff != "")
      {
        client.print(commend_msg(buff));
        client.stop();
        buff = "";
      }
    }
  }
}
