#pragma once

#define SENSOR_READ_INT 50000
#define LED_UPDATE_INT 50000

#define DONUT_DELAY 350

#include <stdint.h>
#include <Arduino.h>

//pins
#define FRONT_RIGHT_LED_PIN 41
#define FRONT_LEFT_LED_PIN 51
#define LEFT_NSLP_PIN 31
#define RIGHT_NSLP_PIN 11
#define DIR_L_PIN 29
#define DIR_R_PIN 30
#define PWML_PIN 40
#define PWMR_PIN 39

//number of sensros
#define NUM_SENS 8

//PID constants
#define Kp 14
#define Ki 0
#define Kd 2


const uint16_t sensorMins[] = {666, 643, 643, 643, 574, 620, 666, 689};
const uint16_t sensorMaxes[] = {1834, 1857,  1857, 1857, 1847, 1880, 1834, 1811};
const int16_t sensorWeights[] = {-15, -14, -12, -8, 8, 12, 14, 15};

/*changelog
 * 
 * speed 45, p = 10; worked, was a little faster
 * speed 50, p = 11.5; worked, got a little faster, oscillated a lot
 * speed 55, p = 14, d = 2; worked, got a little faster, still oscillates
 * speed 60, p = 17, d = 5; DID NOT WORK. oscillated too much
 * speed 60, p = 17, d = -2; worked. oscillated less
 * speed 65, p = 19, d = -7; DID NOT WORK............. 
 * speed 65, p = 19, d = -5; did not work
 * speed 65, p = 21, d = -5; did not work, osc too much
 * speed 65, p = 21; almost works, car breaks after track break
 * peed 65, p = 21, d = 1; same as last
 * speed 65, p = 21, d = -.5
 * 
 */ 
