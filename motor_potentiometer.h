
#include "Arduino.h"

#ifndef motor_potentiometer_h
#define motor_potentiometer_h

#define MOTORENABLE 7
//PWM L293D shield pins
#define MOTORLATCH 12
#define MOTORCLK 4
#define MOTORDATA 8

#define MOTOR1_PWM 11
//Arduino PWM pin
#define MOTOR2_PWM 3
#define MOTOR3_PWM 6
#define MOTOR4_PWM 5


#define MOTOR1_A 2
//74HC595 pins for 8-bit bus (shift register)
//use high low to set direction of the half H bridges
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

#define FWDLEFT 1
#define FWDRIGHT 2
#define REVLEFT 3
#define REVRIGHT 4




class MotorTurn
{

  public:
    MotorTurn();
    void revbutton();
    /*void fwdleftbutton();*/

  private:
    void direction(int motornum, int motorpin, int directioncmd);
    /*void steering(int motornum, int steeringcmd);*/
    void shiftWrite(int motorpin, int state);
    //state = high 1 or low 0


};




#endif
