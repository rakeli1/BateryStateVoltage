#include <Arduino.h>


 const int BATPIN = A0;
 const float INTERNREF = 1.1f;
 const float R1 = 0;
 const float R2 = 0;
 const float RATIO = (R1 + R2) / R2;
 const float VMIN = 3.3f;
 const float VMAX = 4.2f;
 const float K = R2 / (R1 + R2);

          

void setup() 
{
  analogReference(INTERNAL); // подключение к внутреннему опорному напряжению 1,1В, на пин А0
                            // подключать напряжение не более 1,1В ВАЖНО!!!!!
  Serial.begin(9600);
}

void loop() 
{
  int adc = 0;
  
  for(int sempl = 0; sempl < 20; ++sempl)
  {
     adc += analogRead(BATPIN);
      delayMicroseconds(200);
  }
  adc /= 20;  
  Serial.println(adc);   //подключить конденсатор паралельно нижнему резистору 0.01-0.1мкФ
  delay(1000);
}

