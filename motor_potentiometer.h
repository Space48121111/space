
#include "Arduino.h"

#ifndef motor_potentiometer_h
#define motor_potentiometer_h

// PWM L293D shield pins
#define MOTORENABLE 7
#define MOTORLATCH 12
#define MOTORCLK 4
#define MOTORDATA 8

// Arduino PWM pin
#define MOTOR1_PWM 11
#define MOTOR2_PWM 3
#define MOTOR3_PWM 6
#define MOTOR4_PWM 5

// motor module/shield transistors/H bridges
// 74HC595 pins for 8-bit bus (shift register)
// use high low to set direction of the half H bridges
#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4
#define MOTOR3_A 5
#define MOTOR3_B 7
#define MOTOR4_A 0
#define MOTOR4_B 6

#define FORWARD 1
#define REVERSE 2
#define BRAKE 3
//or release

// two buttons: fwd+left
#define FWDLEFT 1
#define FWDRIGHT 2
#define REVLEFT 3
#define REVRIGHT 4




class MotorTurn
{
  public:
    // construct the class
    MotorTurn();
    // function
    void revbutton();
    /*void fwdleftbutton();*/

    ~MotorTurn();

  private:
    void direction(int motornum, int motorpin, int directioncmd);
    /*void steering(int motornum, int steeringcmd);*/
    //state = high 1 or low 0
    void shiftWrite(int motorpin, int state);



};




#endif
