#include "ultrasonic.h"

static int trigPin;
static int echoPin;

void setupUltrasonic(int tPin, int ePin) {
  trigPin = tPin;
  echoPin = ePin;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int scanDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 10000);
  if (duration == 0) return 999;
  return duration * 0.034 / 2;
}
