#include <LiquidCrystal.h>


const int rs = 12, en = 11, d4 = 9, d5 = 10, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int sensorTA12 = A4; // Analog input pin that sensor is attached to
float error_factor = 0.08;
float nVPP;   // Voltage measured across resistor
float currnt,power;     // Actual RMS current in Wire
float zeroFactor=0;
void setup() 
 {
   Serial.begin(9600); 
  lcd.begin(16, 2);
 }
 
 
 void loop() 
 {
  nVPP = getVPP();//-zeroFactor;
  nVPP = (nVPP / 2) * 0.707 * 1000.0;
  currnt= ((nVPP) / 54.5);
  if(currnt<0.1)
  {
    currnt=0.0;
  }
  else{
    currnt+=error_factor;
  }
 
   Serial.print("Volts Peak : ");
   Serial.println(nVPP,3);
   
   
   Serial.print("Current Through Resistor (Peak) : ");
   Serial.print(currnt,3);
   Serial.println(" A Peak to Peak");
   
   power=currnt*245;
   Serial.print("Wattage : ");
   Serial.print(power,3);
   Serial.println(" W");
   
   
   Serial.println();
   delay(500);
}



float getVPP()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  long int avgVal = 0;
  uint32_t start_time = millis();
  int i = 0;
  while ((millis() - start_time) < 100){
      readValue = analogRead(A4);
      avgVal = avgVal + readValue;
      if (readValue > maxValue){
        maxValue = readValue;
      }
      i++;

  }
  maxValue = (maxValue - (avgVal / i));
  result = ((maxValue * 5.0) / 1024.0);
  return result;

}
