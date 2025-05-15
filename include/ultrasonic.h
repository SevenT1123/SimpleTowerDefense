#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

void setupUltrasonic(int trigPin, int echoPin);
int scanDistance();

#endif
