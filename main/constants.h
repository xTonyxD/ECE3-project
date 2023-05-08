#pragma once

#define SENSOR_READ_INT 50000
#define LED_UPDATE_INT 50000

#include <stdint.h>
#include <Arduino.h>

const uint16_t sensorMins = [666, 643, 643, 643, 574, 620, 666, 689];
const uint16_t sensorMaxes = [1834, 1857,  1857, 1857, 1846.6, 1880, 1834, 1811];
const uint16_t sensorWeights = [-15, -14, -12, -8, 8, 12, 14, 15];
