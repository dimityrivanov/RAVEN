#include <Arduino.h>

int iRedLUT[] = {
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 79,
  76, 73, 71, 69, 67, 65, 63, 62, 60, 58, 57, 52, 50, 49, 48, 47,
  49, 48, 47, 46, 45, 44, 43, 43, 42, 41, 40, 40, 39, 38, 37, 37,
  36, 36, 35, 35, 34, 33, 33, 32, 32, 31, 31, 31, 30, 30, 29, 29,
  29, 28, 28, 27, 27, 27, 26, 26, 26, 25, 25, 25, 25, 24, 24, 24,
  23, 23, 23, 23, 22, 22, 22, 22, 22, 21, 21, 21, 21, 20, 20, 20,
  20, 20, 20, 19, 19, 19, 19, 19, 18, 18, 18, 18, 18, 18, 18, 17,
  17, 17, 17, 17, 17, 17, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  15, 15, 15, 15, 15, 15, 15, 14, 14, 14, 14, 14, 14, 14, 14, 14,
  13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11, 11, 11, 11, 11,
  11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, 10,
  10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
class ultrasonic
{
  public:
    double leftDistance();
    double centerDistance();
    double rightDistance();
    void leftSensorAttach(int inPin, int outPin);
    void centerSensorAttach(int inPin, int outPin);
    void rightSensorAttach(int inPin, int outPin);
  private:
    int c_inPin;
    int c_outPin;
    int l_inPin;
    int l_outPin;
    int r_inPin;
    int r_outPin;
};

class leftMotors
{
  public:
    void setSpeed(int speed, int direction);
    int directionSetup(int _FLMDirPin, int _RLMDirPin, int _dirFLM, int _dirRLM);
    int pinMap(int _FLMPin, int _RLMPin);
  private:
    int FLMDirPin; int RLMDirPin; int dirFLM; int dirRLM; int FLMPin; int RLMPin;
};

class rightMotors
{
  public:
    void setSpeed(int speed, int direction);
    int directionSetup(int _FRMDirPin, int _RRMDirPin, int _dirFRM, int _dirRRM);
    int pinMap(int _FRMPin, int _RRMPin);
  private:
    int FRMDirPin; int RRMDirPin; int dirFRM; int dirRRM; int FRMPin; int RRMPin;
};

class iRay
{
  public:
    void attachFR(int pin);
    void attachRR(int pin);
    void attachFL(int pin);
    void attachRL(int pin);
    double distanceFR();
    double distanceRR();
    double distanceFL();
    double distanceRL();
  private:
    int fr_pin;
    int rr_pin;
    int fl_pin;
    int rl_pin;
};
