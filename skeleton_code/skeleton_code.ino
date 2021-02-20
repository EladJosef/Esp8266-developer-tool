#include <ESP8266WiFi.h>                               //|Include the Wi-Fi library
                                                       //|
                                                       //|
const char* SSID     = "None";                //|The SSID (name) of the Wi-Fi network you want to connect to
const char* PASSWORD = "None";                    //|The password of the Wi-Fi network
const int   PORT     = 8500;                           //|
WiFiServer wifiServer(PORT);                           //|Set listen port to 8500

void connect_msg(IPAddress ip, int port){
  // print all connecting info
  Serial.println("");
  Serial.print("Connected to WiFi on IP : ");
  Serial.println(ip);
  Serial.print("Listen on port : ");
  Serial.println(PORT);
}

char* commend_msg(String msg)
{
  // The program API
  Serial.println("accept from user :""+msg+""");
  	if(msg.equals("A"))
	{
		return "option a";
	}
	if(msg.equals("B"))
	{
		return "option b";
	}
	if(msg.equals("C"))
	{
		return "option c";
	}
	if(msg.equals("D"))
	{
		return "option d";
	}
	if(msg.equals("E"))
	{
		return "option e";
	}
	if(msg.equals("on?"))
	{
		return "yes";
	}

  return "error-v1-unknown-command";
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD); // Connecting wifi
  Serial.print("Connecting..");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  
  connect_msg(WiFi.localIP(),PORT); // Print connect data
  wifiServer.begin();
}

void loop() {
  WiFiClient client = wifiServer.available();
  String buff = ""; // creating buffer for messages
  if (client)
  {
    while(client.connected()>0)
    {
      while(client.available()>0)
      {
        buff = buff + char(client.read()); // Read msg
      }
      if(buff != "")
      {
        client.print(commend_msg(buff)); // Send API result to client
        client.stop(); // End connection
        buff = "";
      }
    }
  }
}