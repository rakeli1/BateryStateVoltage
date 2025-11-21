#include <Arduino.h>


 const int BATPIN = A0;              // Определение пина А0 для входа от делителя батарейного напряжения 
 const float INREF = 1.1f;           // внутреннее опорное напряжение подключается функцией analogReference(INTERNAL);
 const float R1 = 3;                 // R1 - подключен м-у Vbat и пином A0 
 const float R2 = 1;                 // R2 - покдключен м-у GND
 const float RATIO = (R1 + R2) / R2; // коефицент увеличения напряжения выхода
 const float VMIN = 3.3f;            // значение напряжения батареи при котором считать уровень зарядки "0"
 const float VMAX = 4.2f;            // значение напряжения батареи при котором считать уровень заряда 100%
 const float K = R2 / (R1 + R2);     // коефицент затухания делителя
       float Va0 = 0;                // значение напряжения на пине А0; расчетное по значению от analogread(BATPIN)
       float Vbat = 0;               //  расчетное значение напряжения на батарее (подлежит калибровке)
          

void setup() 
{
  analogReference(INTERNAL); // подключение к внутреннему опорному напряжению 1,1В, на пин А0
                            // подключать напряжение не более 1,1В ВАЖНО!!!!!
  Serial.begin(9600);
}

void loop() 
{
  int adc = 0;                           //число формируемое АЦП 
  
  for(int sempl = 0; sempl < 20; ++sempl) // цикл для  усреднения значения АЦП
  {
     adc += analogRead(BATPIN);
      delayMicroseconds(50);
  }
  adc /= 20;                              // уреднение значения АЦП
  Va0 = adc * (INREF / 1024);             // вычисление напряжения на пине А0 
  Vbat = (adc * (INREF / 1024)) * RATIO;  // вычисление напряжения на батарее
  int percent = ((Vbat - VMIN) / (VMAX - VMIN)) * 100; // вычисление процента зарядки батареи
  if (percent > 100) percent = 100;
  if (percent < 0) percent = 0;

  Serial.print("Значение АЦП           ");
  Serial.println(adc);   //подключить конденсатор паралельно нижнему резистору 0.01-0.1мкФ

  // Напряжение на батарее
  Serial.print("Напряжение на батарее  ");
  Serial.println(Vbat);

  // Напряжение на пине А0
  Serial.print("Напряжение на пине A0  ");
  Serial.println(Va0);

  // Процент заряда батареи
  Serial.print("Процент заряда батареи ");
  Serial.println(percent);
  Serial.println();
  delay(5000);
}

