#include <SoftwareSerial.h>
 
const int rxPin = 7;
const int txPin = 8;
SoftwareSerial bluetooth(rxPin, txPin);

float temperature;  
int reading;
int lm35Pin = A1; 
int ledPin = 13;
int piezo = 4;


void setup()  
{

  Serial.begin(9600);
  bluetooth.begin(9600);  
  
  analogReference(INTERNAL); 
  pinMode(piezo, OUTPUT);
}

void loop(){
  
  reading = analogRead(lm35Pin);
  temperature = reading / 9.31;
  
  Serial.println(temperature);
  bluetooth.println(temperature);


  if(temperature > 28)   { 
    digitalWrite (ledPin, HIGH);
    analogWrite(piezo, 256);           // PWM 100% 적용
    delay(500);
    analogWrite(piezo, 0);           // PWM 100% 적용
    delay(500);
      
  } else {
    digitalWrite (ledPin, LOW);
  }
    
 
  delay(500);
}
