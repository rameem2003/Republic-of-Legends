/**
* Arduino Based ROBOT Car Project Firmware Version 2.7 Beta Preview
* Developer & Contributors
* REPUBLIC OF LEGENDS
*
* #################################### *
* #                                  # *
* #           CHANGE LOG             # *
* #                                  # *
* #################################### *
*
* With Bluetooth Connectivity
* ROBOT forward, backward, left, right and stop function added 
* Added 20/4 LCD display with I2C
* Added display function for simplify the firmware
* Separate display function into dynamic and static
* Voice control not available on this version of firmware
* Increase stability
* Control robot speed using controller
* All members are contributing on our robot firmware
*/

// Declare all dependencies
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
int ENB_A = 10; // power signal for right side motors
int ENB_B = 9; // power signal for left side motors

int motor_A_in_1 = 4; // right positive
int motor_A_in_2 = 5; // right negetive

int motor_B_in_1 = 6; // left positive
int motor_B_in_2 = 7; // left negetive

int notification = 12; // Initialize buzzer for notification sound

int speed = 150;
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
      dynamicDisplay("     GO FORWARD     "); // Display message
    }

    if(sig == 'B'){
      goBackward(); // if robot get B signal then go backward
      dynamicDisplay("     GO BACKWARD    "); // Display message
    }

    if(sig == 'L'){
      goLeft(); // if robot get L signal then go left
      dynamicDisplay("      GO LEFT       "); // Display message
    }

    if(sig == 'R'){
      goRight(); // if robot get R signal then go right
      dynamicDisplay("      GO RIGHT      "); // Display message
    }

    if(sig == 'D'){
      // status = "<<ME NOT CONNECTED>>";
      dynamicDisplay("<<ME NOT CONNECTED>>");
    }

    if(sig == 'K'){
      // status = "<<ME NOT CONNECTED>>";
      dynamicDisplay("<<ME NOT CONNECTED>>");
    }

    if(sig == '+'){
      // status = "<<ME NOT CONNECTED>>";
      dynamicDisplay("<<ME NOT CONNECTED>>");
    }


    // control speed of robot
    /**
    *
    * Signal range from controller 1 to 9
    * 
    */


    if(sig == '0'){
      speed = 0;
    }

    if(sig == '1'){
      speed = 30;
    }

    if(sig == '2'){
      speed = 60;
    }

    if(sig == '3'){
      speed = 90;
    }

    if(sig == '4'){
      speed = 120;
    }

    if(sig == '5'){
      speed = 150;
    }

    if(sig == '6'){
      speed = 180;
    }

    if(sig == '7'){
      speed = 210;
    }

    if(sig == '8'){
      speed = 240;
    }

    if(sig == '9'){
      speed = 255;
    }
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
  lcd.setCursor(0, 0);
  lcd.print("REPUBLIC OF LEGENDS");

  lcd.setCursor(0, 1);
  lcd.print("   ROBOT CAR v1.0  ");

  lcd.setCursor(0, 2);
  lcd.print("   <BETA PREVIEW>  ");
  // lcd.print("  <STABLE RELEASE>  ");

  lcd.setCursor(0, 3);
  lcd.print("<<ME NOT CONNECTED>>");
}


void dynamicDisplay(String status){
  lcd.setCursor(0, 3);
  lcd.print(status);
}