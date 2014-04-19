// Simply inovation out of nowhere

#include <Wire.h>
#include <LSM303.h>
#include "rover.h"
#include <math.h>
LSM303 compass;
ultrasonic ultrasonic;
iRay iRay;
rightMotors rightMotors;
leftMotors leftMotors;
long interruptsLeft = 0;
long interruptsRight = 0;
long allDistanceLeft = 0;
long allDistanceRight = 0;
long tempDistanceLeft = 0;
long tempDistanceRight = 0;
int heading = 0;
int targetHeading = 0;
int targetDistance = 0;
int lastHeading = 0;



void setup()
{
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();
  lastHeading = heading;
  compass.m_min = (LSM303::vector<int16_t>) {
    -32767, -32767, -32767
  };
  compass.m_max = (LSM303::vector<int16_t>) {
    +32767, +32767, +32767
  };
  attachInterrupt(50, rightEncoder, RISING);
  attachInterrupt(52, leftEncoder, RISING);
  ultrasonic.leftSensorAttach(39, 38);
  ultrasonic.centerSensorAttach(40, 41);
  ultrasonic.rightSensorAttach(42, 43);
  iRay.attachFR(A4);
  iRay.attachRR(A5);
  iRay.attachFL(A3);
  iRay.attachRL(A2);
  leftMotors.directionSetup(10,8,1,1);
  rightMotors.directionSetup(4,6,1,1);
  leftMotors.pinMap(11,9);
  rightMotors.pinMap(5,7);
}




void loop()
{
  compass.read();
  heading = compass.heading();
  double x = (double)-compass.a.x/16320;
  double y = (double)-compass.a.y/16320;
  double z = (double)-compass.a.z/16320;

  if (iRay.distanceFR() < 25 || iRay.distanceFL() < 25 || ultrasonic.centerDistance() < 30)
  {
    while (ultrasonic.centerDistance() < 30 && iRay.distanceFR() < 25 && iRay.distanceFL() < 25)
    {
      refreshSensorValues();
      if (iRay.distanceFR() > iRay.distanceFL())
      {
        rightMotors.setSpeed(100, 0);
        leftMotors.setSpeed(100, 1);
      }
      else
      {
        rightMotors.setSpeed(100, 1);
        leftMotors.setSpeed(100, 0);
      };
    }
  }

  else if (ultrasonic.rightDistance() < 20 || ultrasonic.leftDistance() < 20)
  {
    if (ultrasonic.rightDistance() < 20 && ultrasonic.leftDistance() < 20 && ultrasonic.centerDistance() < 20)
    {
      while (ultrasonic.rightDistance() < 30 && ultrasonic.leftDistance() < 30 && ultrasonic.centerDistance() < 30)
      {
        leftMotors.setSpeed(ultrasonic.leftDistance() * 3, 0);
        rightMotors.setSpeed(ultrasonic.rightDistance() * 3, 0);
      }
      leftMotors.setSpeed(100, 1);
      rightMotors.setSpeed(100, 0); \
      delay(500);
    }

    if (ultrasonic.rightDistance () < 20)
    {
      leftMotors.setSpeed(100, 1);
      rightMotors.setSpeed(100 - (5 * (20 - ultrasonic.rightDistance())),1);
    }
    if (ultrasonic.rightDistance () < 20)
    {
      rightMotors.setSpeed(100, 1);
      leftMotors.setSpeed(100 - (5 * (20 - ultrasonic.leftDistance())),1);
    }
  }

  else
  {
    rightMotors.setSpeed(100, 0);
    leftMotors.setSpeed(100, 0);
  }
  if(heading - lastHeading < - 5 || heading - lastHeading > 5)
  {
    Serial.print("l:");
    Serial.print((allDistanceRight + allDistanceLeft)/2);
    Serial.print(",");
    Serial.print(heading);
    Serial.println(";");
    lastHeading = heading;
    allDistanceLeft = 0;
    allDistanceRight = 0;
  }


}

void refreshSensorValues()
{
}

void rightEncoder()
{
  interruptsRight ++;
  if (interruptsRight == 10)
  {
    allDistanceRight++;
    interruptsRight = 0;
  }
}

void leftEncoder()
{
  interruptsLeft ++;
  if (interruptsLeft == 10)
  {
    allDistanceLeft++;
    interruptsLeft = 0;
  }
}


void ultrasonic::centerSensorAttach(int inPin, int outPin)
{
  c_inPin = inPin;
  c_outPin = outPin;
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
}
void ultrasonic::leftSensorAttach(int inPin, int outPin)
{
  l_inPin = inPin;
  l_outPin = outPin;
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
}
void ultrasonic::rightSensorAttach(int inPin, int outPin)
{
  r_inPin = inPin;
  r_outPin = outPin;
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
}


double ultrasonic::leftDistance()
{
  digitalWrite(l_outPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(l_outPin, LOW);
  return (pulseIn(l_inPin, HIGH, 30000) / 2) / 29.1;
}

double ultrasonic::centerDistance()
{
  digitalWrite(c_outPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(c_outPin, LOW);
  return (pulseIn(c_inPin, HIGH, 30000) / 2) / 29.1;
}

double ultrasonic::rightDistance()
{
  digitalWrite(r_outPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(r_outPin, LOW);
  return (pulseIn(r_inPin, HIGH, 30000) / 2) / 29.1;
}



void iRay::attachFR(int pin)
{
  fr_pin = pin;
  pinMode(pin, INPUT);
}
void iRay::attachRR(int pin)
{
  rr_pin = pin;
  pinMode(pin, INPUT);
}
void iRay::attachFL(int pin)
{
  fl_pin = pin;
  pinMode(pin, INPUT);
}
void iRay::attachRL(int pin)
{
  rl_pin = pin;
  pinMode(pin, INPUT);
}

double iRay::distanceFR()
{
  return (iRedLUT[analogRead(fr_pin) / 4]);
}

double iRay::distanceFL()
{
  return (iRedLUT[analogRead(fl_pin) / 4]);
}

double iRay::distanceRL()
{
  return (iRedLUT[analogRead(rl_pin) / 4]);
}
double iRay::distanceRR()
{
  return (iRedLUT[analogRead(rr_pin) / 4]);
}

int leftMotors::directionSetup(int _FLMDirPin, int _RLMDirPin, int _dirFLM, int _dirRLM)
{
  FLMDirPin = _FLMDirPin;
  pinMode(FLMDirPin, OUTPUT);
  RLMDirPin = _RLMDirPin;
  pinMode(FLMDirPin, OUTPUT);
  dirFLM = _dirFLM;
  dirRLM = _dirFLM;
}

int leftMotors::pinMap(int _FLMPin, int _RLMPin) {
  FLMPin = _FLMPin;
  RLMPin = _RLMPin;
  pinMode(FLMPin, OUTPUT);
  pinMode(RLMPin, OUTPUT);
}

int rightMotors::directionSetup(int _FRMDirPin, int _RRMDirPin, int _dirFRM, int _dirRRM)
{
  FRMDirPin = _FRMDirPin;
  pinMode(FRMDirPin, OUTPUT);
  RRMDirPin = _RRMDirPin;
  pinMode(FRMDirPin, OUTPUT);
  dirFRM = _dirFRM;
  dirRRM = _dirFRM;
}

int rightMotors::pinMap(int _FRMPin, int _RRMPin) {
  FRMPin = _FRMPin;
  RRMPin = _RRMPin;
  pinMode(FRMPin, OUTPUT);
  pinMode(RRMPin, OUTPUT);
}

void leftMotors::setSpeed(int speed, int direction)
{
  if (speed > 100) speed = 100;
  if (speed <= 0) speed = 0;
  digitalWrite(FLMDirPin, direction);
  digitalWrite(RLMDirPin, direction);
  analogWrite(FLMPin, speed * 2);
  analogWrite(RLMPin, speed * 2);
}

void rightMotors::setSpeed(int speed, int direction)
{
  if (speed > 100) speed = 100;
  if (speed <= 0) speed = 0;
  digitalWrite(FRMDirPin, !direction);
  digitalWrite(RRMDirPin, !direction);
  analogWrite(FRMPin, speed * 2);
  analogWrite(RRMPin, speed * 2);
}







