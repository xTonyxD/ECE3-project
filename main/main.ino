#include <ECE3.h>
#include "constants.h"

uint16_t rawInput[] = {0, 0, 0, 0, 0, 0, 0, 0};
int16_t sensorValues[] = {0, 0, 0, 0, 0, 0, 0, 0};
int leftSpd = 0;
int rightSpd = 0;

// Encoder Variables
long enc_bin_cnt;


// Serial Communication
char new_duty_cycle[4];

const unsigned long enc_bin_len = 50; // 50 ms bins
    // Encoder Speed Calculation Explanation:
    // We wait for a set amount of time (enc_bin_len), and find how many
    // times the encoder has incremented in that period. We call 
    // this period a bin when refering to the encoder. The number 
    // encoder counts per bin is a proportional to speed.

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
    sensorValues[i] = sensorValues[i] * sensorWeights[i];
}

void calculateMotorOutputs() {
  int fusedSensorOutput = fuseSensors();
  if (fusedSensorOutput < 0) {
    leftSpd = getSpd(50);
    rightSpd = getSpd(0);
  } else if (fusedSensorOutput > 0) {
    leftSpd = getSpd(0);
    rightSpd = getSpd(50);
  } else if (fusedSensorOutput == 0) {
    //donut
  }
  analogWrite(PWML_PIN, leftSpd);
    analogWrite(PWMR_PIN, rightSpd);
  delay(10);
}

int getSpd(int prev_spd) {

  int bytes_avail = Serial.available();
  if(bytes_avail == 0) // no new serial inputs
    return prev_spd;
    
  else if (bytes_avail > 4) { // invalid serial input
    
    do { // eat invalid buffered input
      delay(100);
      Serial.read();
    } while(Serial.available() > 0);  
    Serial.println("INVALID"); 
    //Serial.println(bytes_avail);  
    return prev_spd;
  }
  
  else {
    for (int i = 0; i < bytes_avail; i++) // read out buffer
      new_duty_cycle[i] = Serial.read();
    int sum = 0;
    for (int i = 0; i < bytes_avail; i++) { // calculate new speed
      
      int num = new_duty_cycle[i] - '0';
      if (num == -38)
        break;
      else if (num > 9 || num < 0) { // invalid character
        Serial.println("INVALID"); 
        return prev_spd;
      }
      sum += pow(10, bytes_avail - 2 - i) * num;
    }

    if (sum >= 255)
      return 255;
    else
      return sum;
  }
}

int fuseSensors() {
  int fusedSensorOutput = 0;
  for (int i = 0; i < NUM_SENS; i++) {
     fusedSensorOutput += sensorValues[i];
  }
  return fusedSensorOutput;
}


void loop()
{
  // read raw sensor values
  ECE3_read_IR(rawInput);
  for(int i = 0 ; i < NUM_SENS; i++) {
    sensorValues[i] = (int16_t)rawInput[i];
  }
  normalizeSensorValues();
  weightSensorValues();
  calculateMotorOutputs();
  for (unsigned char i = 0; i < 8; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println(fuseSensors());

  delay(50);
}
