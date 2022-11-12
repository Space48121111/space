
#include "motor_potentiometer.h"
#include "Arduino.h"


MotorTurn::MotorTurn() {
}

void MotorTurn::revbutton() {

  const int revpin = 52;

  const int speedled = 50;
  const int alertled = 2;



  int revbuttonstate = 0;

  // define motorpwm potentiometer value
  // 0-255
  int value = analogRead(A0);
  // sensitivity
  int potentiometervalue = value / 4;

  // pwm pins
  pinMode(revpin, INPUT);
  pinMode(speedled, OUTPUT);
  pinMode(alertled, OUTPUT);


  // button as input, send the signal to revpin
  revbuttonstate = digitalRead(revpin);

  if (revbuttonstate == LOW) {
    direction(2, MOTOR2_B, FORWARD);
    // resistor to adjust the light and the motor speed
    analogWrite(speedled, potentiometervalue);
    // default forwarding, alert off
    digitalWrite(alertled, LOW);
  } else {
      direction(2, MOTOR2_A, REVERSE);
      digitalWrite(speedled, LOW);
      // alert on: reversing
      digitalWrite(alertled, HIGH);

    }

  // breadboard connection
  Serial.print("revbuttonstate is ");
  Serial.println(revbuttonstate);
  delay(2000);

  // print out the val
  Serial.print("Potentiometervalue is ");
  Serial.println(potentiometervalue);
  delay(2000);


}

/*void fwdleftbutton() {

  const int fwdleftpin = 53;

  int fwdleftbuttonstate = 0;

  pinMode(fwdleftpin, INPUT);

  fwdleftbuttonstate = digitalRead(fwdleftpin);

  if (fwdleftbuttonstate == HIGH) {
      steering(2, FWDLEFT);
  }


}*/



void MotorTurn::direction(int motornum, int motorpin, int directioncmd) {


  int motorA, motorB;
  int motorPWM;

  // global vars
  int value = analogRead(A0);
  int potentiometervalue = value / 4;



  switch(motornum)
  {
    case 1:
      motorA = MOTOR1_A;
      motorB = MOTOR1_B;
      break;
    case 2:
      motorA = MOTOR2_A;
      motorB = MOTOR2_B;
      break;
    case 3:
      motorA = MOTOR3_A;
      motorB = MOTOR3_B;
      break;
    case 4:
      motorA = MOTOR4_A;
      motorB = MOTOR4_B;
      break;
    default:
      break;

  }


  switch(motorpin)
  {
    case MOTOR1_A:
    case MOTOR1_B:
      motorPWM = MOTOR1_PWM;
      break;
    case MOTOR2_A:
    case MOTOR2_B:
      motorPWM = MOTOR2_PWM;
      break;
    case MOTOR3_A:
    case MOTOR3_B:
      motorPWM = MOTOR3_PWM;
      break;
    case MOTOR4_A:
    case MOTOR4_B:
      motorPWM = MOTOR4_PWM;
      break;
    default:
      break;


  }



  switch(directioncmd)
  {
    case FORWARD:
      //the direction of the shift register
      //high or low
      shiftWrite(motorA, LOW);
      shiftWrite(motorB, HIGH);
      analogWrite(motorPWM, potentiometervalue);
      break;
    case REVERSE:
      shiftWrite(motorA, HIGH);
      shiftWrite(motorB, LOW);
      analogWrite(motorPWM, potentiometervalue);
      break;
    case BRAKE:
      shiftWrite(motorA, LOW);
      shiftWrite(motorB, LOW);
      //no pwm
      break;
    default:
      break;


  }

}

/*void MotorTurn::steering(int motornum, int steeringcmd) {

  int motorAleft, motorAright, motorBleft, motorBright;

  switch(motornum)
  {
    case 1:
      motorAleft = MOTOR1_A;
      motorBleft = MOTOR1_B;
      break;
    case 2:
      motorAleft = MOTOR2_A;
      motorBleft = MOTOR2_B;
      break;
    case 3:
      motorAright = MOTOR3_A;
      motorBright = MOTOR3_B;
      break;
    case 4:
      motorAright = MOTOR4_A;
      motorBright = MOTOR4_B;
      break;
    default:
      break;


  }

    switch(steeringcmd)
    {

      case FWDLEFT:
        shiftWrite(motorAleft, HIGH);
        shiftWrite(motorBleft, LOW);
        shiftWrite(motorAright, LOW);
        shiftWrite(motorBright, HIGH);
        break;
      case FWDRIGHT:
        shiftWrite(motorAleft, LOW);
        shiftWrite(motorBleft, HIGH);
        shiftWrite(motorAright, HIGH;
        shiftWrite(motorBright, LOW);
        break;
      case REVLEFT:
        shiftWrite(motorAleft, LOW);
        shiftWrite(motorBleft, HIGH);
        shiftWrite(motorAright, HIGH);
        shiftWrite(motorBright, LOW);
      case REVRIGHT:
        shiftWrite(motorAleft, HIGH);
        shiftWrite(motorBleft, LOW);
        shiftWrite(motorAright, LOW);
        shiftWrite(motorBright, HIGH);
      default:
        break;
    }

}*/


// the motor shield/module controlled by arduino chip
void MotorTurn::shiftWrite(int motorpin, int state) {

  static int latch_copy;
  static int shift_register_initialized = false;

  if (!shift_register_initialized)
  {
    // L293D shield pins for shift register
    pinMode(MOTORENABLE, OUTPUT);
    pinMode(MOTORLATCH, OUTPUT);
    pinMode(MOTORCLK, OUTPUT);
    pinMode(MOTORDATA, OUTPUT);

    digitalWrite(MOTORENABLE, LOW);
    digitalWrite(MOTORLATCH, LOW);
    digitalWrite(MOTORCLK, LOW);
    digitalWrite(MOTORDATA, LOW);

    latch_copy = 0;

    // initialize
    shift_register_initialized = true;

  }

  //write variables
  bitWrite(latch_copy, motorpin, state);
  // shift register: serial in, parallel out
  // clock pulse: one bit at a time
  // MSB: the most significant bit first (leftmost) vs. least LSB
  shiftOut(MOTORDATA, MOTORCLK, MSBFIRST, latch_copy);
  delayMicroseconds(5);

  //latch pulse
  digitalWrite(MOTORLATCH, HIGH);
  delayMicroseconds(5);

  digitalWrite(MOTORLATCH, LOW);


}
