#include <ECE3.h>
#include "constants.h"

uint16_t rawInput[] = {0, 0, 0, 0, 0, 0, 0, 0};
float sensorValues[] = {0, 0, 0, 0, 0, 0, 0, 0};
float motorSpeeds[] = {0, 0};
int16_t lastSensorOut = 0;
int leftSpd = 0;
int rightSpd = 0;
bool debug = true;

//maybe if possible add pid for theo duty cycle vs real duty cycle

void setup()
{
  //init IR sensros
  ECE3_Init();

  //init all pins
  pinMode(FRONT_RIGHT_LED_PIN, OUTPUT);
  pinMode(FRONT_LEFT_LED_PIN, OUTPUT);

  pinMode(LEFT_NSLP_PIN,OUTPUT);
  pinMode(RIGHT_NSLP_PIN,OUTPUT);
  pinMode(DIR_L_PIN, OUTPUT);
  pinMode(DIR_R_PIN, OUTPUT);
  pinMode(PWML_PIN, OUTPUT);
  pinMode(PWMR_PIN, OUTPUT);

  digitalWrite(DIR_L_PIN,LOW);
  digitalWrite(LEFT_NSLP_PIN,HIGH);
  digitalWrite(DIR_R_PIN,LOW);
  digitalWrite(RIGHT_NSLP_PIN,HIGH);

  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(2000);
}


void normalizeSensorValues() {
  // find min and max element
  int i;
  int16_t min = 0;
  int16_t max = 0;
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
    sensorValues[i] = sensorValues[i] * sensorWeights[i] / 1000;

  
}

void calcPID(int16_t currSensorOut) {
  if (currSensorOut == 0) {
    if (debug) {
      Serial.println("***********ALL BLACK*************");
    } else {
      analogWrite(PWML_PIN, -255);
      analogWrite(PWMR_PIN, 255);
    
      delay(100);//delay so it goes past the black bar and senses white again
      //now should be able to PID back onto the path again
  
      //reset sensor outputs for PID calcs (get new readings)
      lastSensorOut = fuseSensors();
      delay(10);
      currSensorOut = fuseSensors();
    }
  }

  motorSpeeds[0] = 255 * (LKp * currSensorOut + LKd * (currSensorOut - lastSensorOut) + LKi * 0.5 * (currSensorOut + lastSensorOut)) / 1000;
  motorSpeeds[1] = 255 * (RKp * currSensorOut + RKd * (currSensorOut - lastSensorOut) + RKi * 0.5 * (currSensorOut + lastSensorOut)) / 1000;

  
}

void writeMotors() {
  calcPID(fuseSensors());
  if (debug) {
    Serial.print("L-" + String(motorSpeeds[0]) + ", R-" + String(motorSpeeds[1])); 
    Serial.print('\t');
    Serial.print('\t');
  } else {
    analogWrite(PWML_PIN, motorSpeeds[0]);
    analogWrite(PWMR_PIN, motorSpeeds[1]);
  }
  delay(10);
}


int fuseSensors() {
  int fusedSensorOutput = 0;
  for (int i = 0; i < NUM_SENS; i++) {
     fusedSensorOutput += sensorValues[i];
  }
  return fusedSensorOutput;
}

void readIR (float * sensorValuesInput) {
  ECE3_read_IR(rawInput);
  for(int i = 0 ; i < NUM_SENS; i++) {
    sensorValues[i] = (float)rawInput[i];
  } //should be fine because sensor inputs wont ever exceed int16_t max
}

//generic wrapper method to normalize and weight the sensor values
void processSensors() {
  normalizeSensorValues();
  weightSensorValues();
}

void loop()
{
  // read raw sensor values, spits t out to global array sensorValues
  readIR(sensorValues);
  processSensors();
  writeMotors();
  if (debug) {
    for (unsigned char i = 0; i < 8; i++)
    {
      Serial.print(sensorValues[i]);
      Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
    }
    Serial.println(fuseSensors());
  }

  delay(50);
}
