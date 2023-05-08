#include <ECE3.h>
#include <constants.h>

uint16_t sensorValues[8] = [0, 0, 0, 0, 0, 0, 0, 0];

void setup()
{
  ECE3_Init();
  pinMode(41, OUTPUT)
  pinMode(
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(2000);
}

// Reads IR sensors. outputs 
uint_16 readIRsensors() {
  
}

void normalizeSensorValues() {

}

void weightSensorValues {

}

void calculateMotorOutputs{
  
}


void loop()
{
  // read raw sensor values
  ECE3_read_IR(sensorValues);

  // print the sensor values as numbers from 0 to 2500, where 0 means maximum reflectance and
  // 2500 means minimum reflectance
  for (unsigned char i = 0; i < 8; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println();

  delay(50);
}
