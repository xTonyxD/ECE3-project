#pragma once

#define SENSOR_READ_INT 50000
#define LED_UPDATE_INT 50000

#define DONUT_DELAY 300

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
#define Kp 21
#define Ki 0
#define Kd -2


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
 * speed 65, p = 21, d = 1; same as last
 * speed 65, p = 21, d = -.5
 * speed 70, p = 21, d = -2; wobbly but worked
 * speed 85, p = 35, d = -5; wobbly, did not recognize first black bar
 * speed 85, p = 35, d = -7; it completed the first half of the track, it was just too wobbly at the first black bar
 * speed 85, p = 35, d = 7; did not work
 * speed 87, p = 35, d = -7; did not work
 * speed 85, p = 35, d = -12; did not work
 * speed 85, p = 35, d = -20; did not work
 * speed 85, p = 40, d = -7; did not pass vertical black bars
 * speed 85, p = 50, d = -10; did not work
 * speed 85, p = 35, d = -7.5; worked first half
 * speed 85, p = 35, d = -7.75; worked first falf
 * speed 85, p = 35, d = -7.25; did not work
 * speed 85, p = 35, d = -8; did not work 
 * speed 85, p = 30, d = -7.75; did not work
 * speed 85, p = 21, d = -7; did not work
 * speed 85, p = 25, d = -7; did not work
 * speed 85, p = 27.5, d = -7; worked first half
 * speed 85, p = 27.5, d = -7.25; did not work
 * speed 85, p = 28, d = 7; did not work
 * speed 85, p = 28, d = 0; did not work
 * speed 85, p = 27.5, d = -7; did not work
 * speed 75, p = 21, d = -2; worked ******************** new fastest working version
 * speed 80, p = 21, d = -2; did not work
 * speed 80, p = 24, d = -3; did not work
 * speed 80, p = 25, d = -3; worked?
 * speed 100, p = 50, d = 0; did not work
 * speed 100, p = 60, d = 0; did not work
 * speed 100, p = 25, d = 3;
 * DONE
 */ 
