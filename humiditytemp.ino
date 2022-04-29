#include <DHT.h>
int sensorPin=2;
#define DHTTYPE DHT11
DHT dht(sensorPin,DHTTYPE);

void setup(){
  Serial.begin(9600);
 }
 
void loop(){
    delay(2000);
  float t=dht.readTemperature();
    Serial.print("temperature is");
    Serial.println(t);
    float h=dht.readHumidity();
    Serial.print("Humidity is");
    Serial.println(h);
    }