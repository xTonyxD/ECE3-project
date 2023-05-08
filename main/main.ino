#include <ECE3.h>

uint16_t sensorValues[8];
uint16_t sensorMins = [666, 643, 643, 643, 574, 620, 666, 689];
uint16_t sensorMaxes = [1834, 1857,  1857, 1857, 1846.6, 1880, 1834, 1811]
uint16_t sensorWeights = [-15, -14, -12, -8, 8, 12, 14, 15]

void setup()
{
  ECE3_Init();
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(2000);
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
