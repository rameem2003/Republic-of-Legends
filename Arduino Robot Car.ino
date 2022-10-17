/**
* Arduino Based Robot Car Project Firmware Version 0.1 Developer Preview
* Developer & Contributors
* Republic of Legends
*/

// Initialize LCD Display
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// initializze 2 led's to check bluetooth communication
int led1 = 7;
int led2 = 8;

// massage for robot
char msg;

void setup() {
  // initialize serial communication for robot
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    msg = Serial.read();
    Serial.print(msg);
  }


  if(msg == 'F'){
    goForward();
  }

  if(msg == 'B'){
    goBackward();
  }

  if(msg == 'S'){
    nowStop();
  }


  if(msg == 'L'){
    goLeft();
  }

}


void goForward(){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
}


void goBackward(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
}

void goLeft(){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
}


void nowStop(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}





