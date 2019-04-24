#include <Arduino.h>

int motorControlPin = 9; //Set pin 9 as motor control pin
int analogPin = 0; // potentiometer wiper (middle terminal) connected to analog pin 3
int val = 0; // variable to store the value read
int motorSpeed = 0;
float signal;
float gain = 0.08;
float averageArray[200];
int calibration = true;
int calibrationCount = 0;

void setup() {
  pinMode(motorControlPin, OUTPUT); //Set MotorControlPin as output Pin
  signal = analogRead(analogPin); // read the input pin
  Serial.begin(9600); //Let user know range of values to enter
}

int average(float value) {
  if(calibrationCount <= 200) {
    averageArray[calibrationCount] = value;
    calibrationCount++;
//    Serial.print(calibrationCount);
//    Serial.print(' ');
//    Serial.print(averageArray[calibrationCount]);
//    Serial.println();
//    Serial.println(calibrationCount + ' ' + averageArray[calibrationCount]);
  } else {
    calibration = false;
  }
}

void loop() 
{
  analogWrite(motorControlPin, 255);//Write the 'speed' value to motorControlPin
  if(calibration) {
    average(signal);
  }
  motorSpeed = 0;
  signal += (analogRead(analogPin)*gain - signal);  // IIR filter
  if (signal > 60){
    motorSpeed = 255;
    delay(1000);
  } else {
    motorSpeed = 0;
  }
  analogWrite(motorControlPin, motorSpeed);//Write the 'speed' value to motorControlPin
  Serial.println(signal);
}


