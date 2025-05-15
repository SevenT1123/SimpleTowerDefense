#include <Arduino.h>
#include <Servo.h>
#include "ultrasonic.h"

// Pins
const int EchoPin = 5;
const int TrigPin = 6;
Servo scanner;

// Using millis() since we want servo and ultrasonic to work at the same time
const int scanDelay = 10;
const int checkDelay = 100;
const int detectionThreshold = 25;

// Variables used for pausing servo if an object is detected
bool paused = false;
int currentAngle = 0;
int step = 1;
unsigned long lastMoveTime = 0;
unsigned long pauseStartTime = 0;

void setup() {
  Serial.begin(9600);
  setupUltrasonic(TrigPin, EchoPin);
  scanner.attach(9);
  scanner.write(currentAngle);
}

void loop() {
  // Using millis() since we want servo and ultrasonic to run at a same time
  unsigned long currentTime = millis();

  if (!paused && currentTime - lastMoveTime >= scanDelay) {
    lastMoveTime = currentTime;

    int distance = scanDistance();
    
    // Return servo and ultrasonic position is an object is detected. Angles in degree. Distance in centimeters
    if (distance < detectionThreshold) {
      paused = true;
      pauseStartTime = currentTime;
      Serial.println("Object detected: ");
      Serial.print("Angle: ");
      Serial.print(currentAngle);
      Serial.print(" Distance: ");
      Serial.println(distance);
      Serial.print("\n");
      return;
    }

    // Update angle
    currentAngle += step;
    if (currentAngle >= 180 || currentAngle <= 0) {
      step = -step;
      currentAngle = constrain(currentAngle, 0, 180);
    }

    scanner.write(currentAngle);
  }

  // Update distance and check condition
  if (paused && currentTime - pauseStartTime >= checkDelay) {
    pauseStartTime = currentTime;
    int distance = scanDistance();
    if (distance >= detectionThreshold) {
      paused = false;
    }
  }
}
