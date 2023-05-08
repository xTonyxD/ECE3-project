#include <ECE3.h>
#include <constants.h>
#define NUM_SENS 8

uint16_t sensorValues[NUM_SENS] = [0, 0, 0, 0, 0, 0, 0, 0];

uint16_t sensorValues[NUM_SENS];

void setup()
{
  ECE3_Init();
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(2000);
}

void normalizeSensorValues() {
  // find min and max element
  int i;
  uint16_t min = 0;
  uint16_t max = 0;
  for(i=0;i<NUM_SENS;i++) {
    if(sensorValues[i] <= min)
      min = sensorValues[i];
    if(sensorValues[i] >= max)
      max = sensorValues[i];
  }
  // normalize sensor values
  for(i=0;i<NUM_SENS;i++) 
    sensorValues[i] = (sensorValues[i] - min)/max * 1000;
}

void weightSensorValues() {
  // multiply array with weights
  int i;
  for(i=0;i<NUM_SENS;i++)
    sensorValues[i] = sensorValues[i] * sensorWeights[i];
}

void calculateMotorOutputs() {
  
}


void loop()
{
  // read raw sensor values
  ECE3_read_IR(sensorValues);
  normalizeSensorValues();
  weightSensorValues();
  calculateMotorOutputs();

  // PREVIOUS CODE START //
  // print the sensor values as numbers from 0 to 2500, where 0 means maximum reflectance and
  // 2500 means minimum reflectance
  /*
  for (unsigned char i = 0; i < NUM_SENS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println();

  delay(50);
  */
  // PREVIOUS CODE END //
}
