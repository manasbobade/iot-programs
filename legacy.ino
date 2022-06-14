#include <dht.h>
#define dht_pin A0
#include <Servo.h>
#define ledPin 8
dht DHT;
Servo myservo;
Servo myservo3; 
Servo myservo2; 
int trigPin = 11;    
int echoPin = 12;  
int trigPin2 = 5;    
int echoPin2 = 4;   
long duration,inches;
long duration2,inches2=90;
int pos = 0; 
int data = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  myservo.attach(9);
  myservo2.attach(6);
  myservo3.attach(7);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  delay(1000);
 }
void loop() {
  DHT.read11(dht_pin);
  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature); 
  Serial.println("C  ");
  if(Serial.available() > 0){ 
    data = Serial.read(); 
          if (data =='0'){
            digitalWrite(ledPin, LOW); 
            Serial.println("LED: OFF"); 
            }
              else if (data =='1') {
                digitalWrite(ledPin, HIGH);
                Serial.println("LED: ON");
               
              } 
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);    
  inches = (duration/2) / 74;   
  delay(500);
  
  if(inches<5)
    {
      digitalWrite(ledPin, HIGH);
      for (pos = 0; pos <= 90; pos += 1) { 
        myservo.write(pos);              
        delay(60);                      
        }
      delay(4000);
      for (pos = 90; pos >= 0; pos -= 1) { 
        myservo.write(pos);             
        delay(60);                     
        }
    }
  delay(500);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);    
  inches2 = (duration2/2) / 74;
  Serial.println(inches2);
    if(inches2<5)
  {
    for (pos = 0; pos <= 90; pos += 1) {   
      myservo2.write(pos);  
      myservo3.write(90-pos);            
      delay(60);   
      }
      delay(4000); 
    for (pos = 90; pos >= 0; pos -= 1) { 
      myservo2.write(pos); 
      myservo3.write(90-pos);           
      delay(60);                      
      }
  }
}
