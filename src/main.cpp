#include <Arduino.h>


 const int BATPIN = A0;
 const float INREF = 1.1f;
 const float R1 = 0;
 const float R2 = 0;
 const float RATIO = (R1 + R2) / R2;
 const float VMIN = 3.3f;
 const float VMAX = 4.2f;
 const float K = R2 / (R1 + R2);
       float Va0 = 0;
       float Vbat = 0;
          

void setup() 
{
  analogReference(INTERNAL); // подключение к внутреннему опорному напряжению 1,1В, на пин А0
                            // подключать напряжение не более 1,1В ВАЖНО!!!!!
  Serial.begin(9600);
}

void loop() 
{
  int adc = 0;                           //число формируемое АЦП 
  
  for(int sempl = 0; sempl < 20; ++sempl)
  {
     adc += analogRead(BATPIN);
      delayMicroseconds(50);
  }
  adc /= 20;
  Va0 = adc * (INREF / 1023);
  Vbat = (adc * (INREF / 1023)) * RATIO;
  int percent = ((Vbat - VMIN) / (VMAX - VMIN)) * 100;

  Serial.println(adc);   //подключить конденсатор паралельно нижнему резистору 0.01-0.1мкФ

  // Напряжение на батарее
  Serial.print("Напряжение на батарее ");
  Serial.println(Vbat);

  // Напряжение на пине А0
  Serial.print("Напряжение на пине A0 ");
  Serial.println(Va0);

  // Процент заряда батареи
  Serial.print("Процент заряда батареи ");
  Serial.println(percent);
  delay(1000);
}

