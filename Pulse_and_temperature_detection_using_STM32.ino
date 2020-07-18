#include <Wire.h>
#include "MAX30100_PulseOximeter.h" 
#define REPORTING_PERIOD_MS     2000
PulseOximeter pox;
uint32_t tsLastReport = 0;
const int sensor=PA0; // Assigning analog pin A0 to variable 'sensor'
float tempc; //variable to store temperature in degree Celsius
float tempf; //variable to store temperature in Fahreinheit
float vout; //temporary variable to hold sensor reading

void onBeatDetected()
{
    Serial.println("Beat!");
    pinMode(sensor,INPUT);
}
 
void setup()
{
    Serial.begin(115200);
    Serial.print("Initializing pulse oximeter..");
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);
}
void loop()
{
  vout=analogRead(sensor); //Reading the value from sensor
  vout=(vout*330)/4096;
  tempc=vout; // Storing value in Degree Celsius
  tempf=(vout*1.8)+32; // Converting to Fahrenheit
  Serial.print("in DegreeC=");
  Serial.print("\t");
  Serial.print(tempc);
  Serial.print(" ");
  Serial.print("in Fahrenheit=");
  Serial.print("\t");
  Serial.print(tempf);
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");
         tsLastReport = millis();
    }
}


  
