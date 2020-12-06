#define scd_debug 0

#define rot 4
#define gruen 3

int Fqz = 2;

#define SCD30WIRE Wire

#include "paulvha_SCD30.h"
#include <Arduino.h>
#include <Wire.h>

#define readinterval Fqz


SCD30 airSensor;

void setup()
{
  pinMode(gruen, OUTPUT);
  pinMode(rot, OUTPUT);

  SCD30WIRE.begin();

  Serial.begin(9600);
  Serial.println("SCD30 Example 1");

  airSensor.setDebug(scd_debug); 

  //This will cause readings to occur every two seconds
  if (airSensor.begin() == false)
  {
    Serial.println(F("The SCD30 did not respond. Please check wiring."));
    while (1);
  }



  airSensor.setMeasurementInterval(readinterval);
 // airSensor.setAutoSelfCalibration(0);

  DeviceInfo();
}

void loop()
{
  int co2 = airSensor.getCO2();
  int celsius = airSensor.getTemperature();

  Serial.print(co2);
  Serial.println(" ppm CO2");
  Serial.println();

  if (co2 > 1400) {
    digitalWrite(rot, HIGH);
    digitalWrite(gruen, LOW);
  } else if (co2 > 900) {
    digitalWrite(gruen, HIGH);
    digitalWrite(rot, HIGH);
  } else {
    digitalWrite(gruen, HIGH);
    digitalWrite(rot, LOW);
  }
  delay(1000);
}



void DeviceInfo()
{
  uint8_t val[2];
  char buf[(SCD30_SERIAL_NUM_WORDS * 2) + 1];

  if (airSensor.getSerialNumber(buf))
  {
    Serial.print(F("SCD30 serial number : "));
    Serial.println(buf);
  }

  if ( airSensor.getFirmwareLevel(val) ) {
    Serial.print("SCD30 Firmware level: Major: ");
    Serial.print(val[0]);

    Serial.print("\t, Minor: ");
    Serial.println(val[1]);
  }
  else {
    Serial.println("Could not obtain firmware level");
  }
}
