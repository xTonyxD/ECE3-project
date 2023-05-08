#include <ECE3.h>
#include <constants.h>

uint16_t sensorValues[8] = [0, 0, 0, 0, 0, 0, 0, 0];

void setup()
{
  //init IR sensros
  ECE3_Init();

  //init all pins
  pinMode(FRONT_RIGHT_LED_PIN, OUTPUT)
  pinMode(FRONT_LEFT_LED_PIN, OUTPUT)
  pinMode(DIR_L_PIN, OUTPUT)
  pinMode(DIR_R_PIN, OUTPUT)
  pinMode(PWML_PIN, OUTPUT)
  pinMode(PWMR_PIN, OUTPUT)

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
