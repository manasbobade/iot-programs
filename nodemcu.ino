#include <DHT.h>  // Including library for dht
 
#include <ESP8266WiFi.h>
 
String apiKey = "8SAMNSL1TLWH97LY";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "OnePlus 8 Pro";     // replace with your wifi ssid and wpa2 key
const char *pass =  "12345678";
const char* server = "api.thingspeak.com";
int cnth=0;
int cntt=0;
//#define DHTPIN 2          //pin where the dht11 is connected, Here it is 2
 
//DHT dht(DHTPIN, DHT11);
 
WiFiClient client;
void setup()
{
       Serial.begin(9600);
       delay(10);
       dht.begin();
     Serial.print("Connecting to ");
    Serial.println(ssid);
        WiFi.begin(ssid, pass);  
          while (WiFi.status() != WL_CONNECTED)
     {
            delay(500);
            Serial.print(".");
     }
 Serial.println("");
      Serial.println("WiFi connected");
 
}
void loop()
{
 
   //   float h = dht.readHumidity();
     // float t = dht.readTemperature();
     float h=34;
     float t=60;
     cntt=cntt-3;
     cnth=cnth+3;
    /* if (isnan(h) || isnan(t))
      {
        Serial.println("Failed to read ");
         return;
    }*/
if (client.connect(server,80))   
//   "184.106.153.149" or api.thingspeak.com
                      {  
                           
                             String postStr = apiKey;
                             postStr +="&field1=";
                             t=cntt+t;
                             postStr += String(t);
                             postStr +="&field2=";
                             h=cnth+h;
                             postStr += String(h);
                             postStr += "\r\n\r\n";
client.print("POST /update HTTP/1.1\n");
  client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
 client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
           Serial.println("Waiting...");
 
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
