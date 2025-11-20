#include <Arduino.h>


int bateryPin = A0;
int voltageinBatery = 0;
int ratio = 2;          // коефицент делителя напряжения

void setup() 
{
  analogReference(INTERNAL);
  Serial.begin(9600);
}

void loop() 
{
  int adc = 0;
  
  for(int sempl = 0; sempl < 20; ++sempl)
  {
     adc += analogRead(bateryPin);
      delayMicroseconds(200);
  }
  adc /= 20;  
  Serial.println(adc);   //подключить конденсатор паралельно нижнему резистору 0.01-0.1мкФ
  delay(1000);
}

