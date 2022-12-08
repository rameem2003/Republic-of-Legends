/**
* Arduino Based ROBOT Car Project Firmware Version 2.4 Beta Preview
* Developer & Contributors
* REPUBLIC OF LEGENDS
* With Bluetooth Connectivity
* ROBOT forward, backward, left, right and stop function added 
* Added 20/4 LCD display with I2C
* Added display function for simplify the firmware
* Separate display function into dynamic and static display
* Increase stability
* Voice control not added
*/

// Declare all dependencies
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
int ENB_A = 10; // power connection for right side motors
int ENB_B = 9; // power connection for left side motors

int motor_A_in_1 = 4; // right front
int motor_A_in_2 = 5; // right back
int motor_B_in_1 = 6; // left front
int motor_B_in_2 = 7; // left back

char sig;
String status;


void setup() {
  // Initialize all motor, blutooth and display


  Serial.begin(9600); // setup bluetooth connection to arduino
  lcd.begin(); // lcd display start

  /**
   * activate all motors
   * power up all motors
  */
 
  pinMode(ENB_A, OUTPUT);
  pinMode(ENB_B, OUTPUT);

  pinMode(motor_A_in_1, OUTPUT); 
  pinMode(motor_A_in_2, OUTPUT);
  pinMode(motor_B_in_1, OUTPUT);
  pinMode(motor_B_in_2, OUTPUT);
  staticDisplay();
}

void loop() {
  /**
   * Robot main activity functions
  */

  // Set the robot speed limit
  int speed = 50;
  analogWrite(ENB_A, speed);
  analogWrite(ENB_B, speed);

  // if robot connected to our phone
  if(Serial.available() != 0){
    

    sig = Serial.read(); // if robot connected to phone then get the signal

    Serial.println(sig);

    if(sig == 'S'){
      robotStop(); // if robot get S signal then robot stop
      status = "*CONNECTED TO PHONE*";
      dynamicDisplay(status); // if robot get signal from phone then print the msg
    }

    if(sig == 'F'){
      goForward(); // if robot get F signal then go forward
      dynamicDisplay("GO FORWARD      ");
    }

    if(sig == 'B'){
      goBackward(); // if robot get B signal then go backward
      dynamicDisplay("GO BACKWARD");
    }

    if(sig == 'L'){
      goLeft(); // if robot get L signal then go left
      dynamicDisplay("GO LEFT");
    }

    if(sig == 'R'){
      goRight(); // if robot get R signal then go right
      dynamicDisplay("GO RIGHT");
    }
  }

  else if (Serial.available() == 0) {
    status = "<<ME NOT CONNECTED>>";
    dynamicDisplay(status);
  }

}


/**
 * All basic functions for robot
 * Forward
 * Backward
 * Left
 * Right
 * Stop
*/

void goForward(){
  digitalWrite(motor_A_in_1, HIGH); 
  digitalWrite(motor_A_in_2, LOW);


  digitalWrite(motor_B_in_1, HIGH);
  digitalWrite(motor_B_in_2, LOW);
}

void goBackward(){
  digitalWrite(motor_A_in_1, LOW); 
  digitalWrite(motor_A_in_2, HIGH);


  digitalWrite(motor_B_in_1, LOW);
  digitalWrite(motor_B_in_2, HIGH);
}

void goLeft(){
  digitalWrite(motor_A_in_1, HIGH); 
  digitalWrite(motor_A_in_2, LOW);


  digitalWrite(motor_B_in_1, LOW);
  digitalWrite(motor_B_in_2, HIGH);
}


void goRight(){
  digitalWrite(motor_A_in_1, LOW); 
  digitalWrite(motor_A_in_2, HIGH);


  digitalWrite(motor_B_in_1, HIGH);
  digitalWrite(motor_B_in_2, LOW);
}

void robotStop(){
  digitalWrite(motor_A_in_1, LOW); 
  digitalWrite(motor_A_in_2, LOW);


  digitalWrite(motor_B_in_1, LOW);
  digitalWrite(motor_B_in_2, LOW);
}


/**
 * Create Display Function
 * To show robot's all activities, status
*/

void staticDisplay(){
  lcd.setCursor(0,0);
  lcd.print("REPUBLIC OF LEGENDS");

  lcd.setCursor(0, 1);
  lcd.print("   ROBOT CAR v1.0  ");

  lcd.setCursor(0, 2);
  lcd.print("   <BETA PREVIEW>  ");
}


void dynamicDisplay(String status){
  lcd.setCursor(0, 3);
  lcd.print(status);
}