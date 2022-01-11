#include "motor_potentiometer.h"

MotorTurn m;


void setup() {
  Serial.begin(9600);

  /*m.direction(BRAKE);
  delay(500);*/


}

void loop() {

  m.revbutton();
  /*m.fwdleftbutton();*/


}
