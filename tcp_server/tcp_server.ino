#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#define DEBUG

const char* ssid = "ssid";
const char* password = "pass";

uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;

WiFiServer server(80);

void setup() {
   Serial.begin(9600);

   #ifdef DEBUG
   Serial.printf("Connecting to %s ", ssid);
   #endif
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED)
   {
    #ifdef DEBUG
    delay(500);
    Serial.print(".");
    #endif
   }

#ifdef DEBUG
   Serial.println(" connected");
#endif
   server.begin();
   #ifdef DEBUG
   Serial.printf("TCP server started, address: %s \n", WiFi.localIP().toString().c_str());
   #endif
}

void setColor(uint8_t red, uint8_t green, uint8_t blue)
{
  Serial.write(14);

  while (Serial.available() == 0)
  {
    
  }

  if (Serial.read() == 15)
  {
    Serial.write(red);
    Serial.write(green);
    Serial.write(blue);  
  } 
}

void loop() {  
  WiFiClient client = server.available();

  if (client) {
    while (client.connected()){    
      
        // Read the incoming TCP command
        String command = client.readStringUntil('\r');
        
        // Debugging display command
        command.trim();

        if (command == "on")
        {
          setColor(255, 255, 255);
        }

        else if (command == "off")
        {
          setColor(0, 0, 0);
        }

        else if (command.indexOf("red") > -1)
        {
          red = command.substring(command.indexOf(":") + 1, command.length() - 1).toInt();
          setColor(red, green, blue);
        }
        else if (command.indexOf("green") > -1)
        {
          green = command.substring(command.indexOf(":") + 1, command.length() - 1).toInt();
          setColor(red, green, blue);
        }
        else if (command.indexOf("blue") > -1)
        {
          blue = command.substring(command.indexOf(":") + 1, command.length() - 1).toInt();
          setColor(red, green, blue);
        }
        
        Serial.println(command.c_str());
        // Phrase the command        
    } // while
  }
}
