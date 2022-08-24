#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#define integratingTime 15000  
#define oneMinute 60000  //1min
 
unsigned long counts = 0;     
unsigned long events = 0; 
unsigned long cpm = 0;      
unsigned int multiplier;  
unsigned long previousMillis;  
double avgCounts = 0;
double avgCPM = 0;
double avgUSV = 0;
double sumCPM = 0;
double sumUSV = 0;
double uSv = 0;
double dose = 0;
 
const int ledPin =  9;
 

 
 
void tube_impulse() 
{       
  counts++;
  events++;
}
 
 LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); //2004A = 0x3F
 
void setup() {

 
  counts = 0;
  cpm = 0;
  multiplier = oneMinute / integratingTime;      
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), tube_impulse, FALLING); //pin 2

Wire.begin();
lcd.init();
lcd.backlight(); 

}
 
 
void loop() 
{
  unsigned long currentMillis = millis();
                
                if(currentMillis - previousMillis > integratingTime){
                  
                  avgCounts++;
                  previousMillis = currentMillis;
                  cpm = counts * multiplier; //cpm * 60/15 = cpm * 4
 
                  uSv =( cpm  / 151.0);
               
                
                  sumCPM = (double)cpm + sumCPM;
                  sumUSV = uSv + sumUSV;
              
                  avgCPM = sumCPM / avgCounts;
                  avgUSV = sumUSV / avgCounts;                
                      
                Serial.print((currentMillis)/1000);
                Serial.print("\t");
                Serial.print(cpm);
                Serial.print("\t");
                Serial.print(avgCPM);
                Serial.print("\n");  
 
                 
                 lcd.setCursor(0, 0); 
                 lcd.print("CPM   uSv/hr"); 
                 lcd.setCursor(0, 1);
                 lcd.print(cpm);
                 lcd.print("    ");
                 lcd.print(uSv,4);
                 
                 lcd.setCursor(0, 2);
                 lcd.print("A ");
                 lcd.print(avgCPM,1);
                 lcd.print("  ");
                 lcd.print(avgUSV,4);
              
                                  
                 counts = 0;
              //-------------------------------------
               
              
                
                }

 
}
  
 
