/**
* Arduino Based ROBOT Car Project Firmware Version 3.0 LTS
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
* Added display function to show the car activities
* Separate display function into dynamic and static
* Voice control not available on this version of firmware
* Implement dynamic speed control feature
* Changed the access name and password of HC-06 bluetooth module
* Implement sound & led notification
* All members are contributing on our robot firmware (Major contribution Fahmida Yeasmin & Mahmood Hassan Rameem)
* Increase stability
*/

/**

                   oooo    .oooooo.    .oooooo..o 
                   `888   d8P'  `Y8b  d8P'    `Y8 
oooo d8b  .ooooo.   888  888      888 Y88bo.      
`888""8P d88' `88b  888  888      888  `"Y8888o.  
 888     888   888  888  888      888      `"Y88b 
 888     888   888  888  `88b    d88' oo     .d8P 
d888b    `Y8bod8P' o888o  `Y8bood8P'  8""88888P'  
                                                  
                                                  
                                                  

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

int notificationPin = 11; // Initialize buzzer for notification sound

// int led = 12; //led line comes from pin 12 

int camera = 8; // camera positive

// backside led's
int back_led_1_pos = A3;
int back_led_1_neg = A2;

int back_led_2_pos = A1;
int back_led_2_neg = A0;

// frotside led's
int front_led_1_pos = 2;
int front_led_1_neg = 3;
int front_led_2_pos = 12;
int front_led_2_neg = 13;

/*
*
* Declaring varialbles for sound & led notification animation
* Use millis() function replace delay() function
*
*/
bool state = 1; // for high/low state
unsigned long currTime = 0; // current time
unsigned long prevTime = 0; // previous time

unsigned long onTime = 500; // sound & light on duration
unsigned long offTime = 2000; // sound & light off duration



int speed = 150; // Set car default speed
char sig; // variable for get the signal
String status; // variable for store the messages



void setup() {
  // Initialize all motor, blutooth, buzzer and display
  Serial.begin(9600); // setup bluetooth connection to arduino (Yellow, Orange, Coffee, Red)
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
  pinMode(notificationPin, OUTPUT);
  // pinMode(led, OUTPUT);

  /**
   * activate all led's
   * power up all led's
  */


  pinMode(back_led_1_pos, OUTPUT);
  pinMode(back_led_1_neg, OUTPUT);
  pinMode(back_led_2_pos, OUTPUT);
  pinMode(back_led_2_neg, OUTPUT);

  pinMode(front_led_1_pos, OUTPUT);
  pinMode(front_led_1_neg, OUTPUT);
  pinMode(front_led_2_pos, OUTPUT);
  pinMode(front_led_2_neg, OUTPUT);

  analogWrite(back_led_1_neg, 0);
  analogWrite(back_led_2_neg, 0);
  digitalWrite(front_led_1_neg, LOW);
  digitalWrite(front_led_2_neg, LOW);

  pinMode(camera, OUTPUT);
  digitalWrite(camera, HIGH);


  staticDisplay(); // Display initial message
  notificationOn(); // Play initial disconnect sound
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

    if(sig == 'U'){
      backLight_on();
    }

    if(sig == 'u'){
      backLight_off();
    }

    if(sig == 'W'){
      led_on(); // if robot get signal from phone then head light will be turn on
    }

    if(sig == 'w'){
      led_off(); // // if robot get signal from phone then head light will be turn off
    }

    if(sig == 'S'){
      robotStop(); // if robot get S signal then robot stop
      status = "*CONNECTED TO PHONE*";
      dynamicDisplay(status); // if robot get signal from phone then print the msg
      notificationOff(); // notification sound off
    }

    if(sig == 'F'){
      goForward(); // if robot get F signal then go forward
      dynamicDisplay("     GO FORWARD     "); // Display message
      notificationOff(); // notification sound off
      backLight_off();
    }

    if(sig == 'B'){
      goBackward(); // if robot get B signal then go backward
      dynamicDisplay("     GO BACKWARD    "); // Display message
      notificationOff(); // notification sound off
    }

    if(sig == 'L'){
      goLeft(); // if robot get L signal then go left
      dynamicDisplay("      GO LEFT       "); // Display message
      notificationOff(); // notification sound off
    }

    if(sig == 'R'){
      goRight(); // if robot get R signal then go right
      dynamicDisplay("      GO RIGHT      "); // Display message
      notificationOff(); // notification sound off
    }

    if(sig == 'D'){
      dynamicDisplay("<<ME NOT CONNECTED>>");
      // notificationOn();
    }

    if(sig == 'K'){
      dynamicDisplay("<<ME NOT CONNECTED>>");
      notificationOn();
      led_off();
      backLight_off();
      // beeper();
    }

    if(sig == '+'){
      dynamicDisplay("<<ME NOT CONNECTED>>");
      // notificationOn();
    }

    if(sig == 'I'){
      dynamicDisplay("<<ASSALA-MUALAIKUM>>"); // Display message
      salam(); // greetings activity
    }

    if(sig == 'H'){
      dynamicDisplay("<<ASSALA-MUALAIKUM>>"); // Display message
      salam(); // greetings activity
    }

  
    /**
    *
    * Control speed of robot
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

  analogWrite(back_led_1_pos, 0);
  analogWrite(back_led_2_pos, 0);
}

void goBackward(){
  digitalWrite(motor_A_in_1, LOW); 
  digitalWrite(motor_A_in_2, HIGH);


  digitalWrite(motor_B_in_1, LOW);
  digitalWrite(motor_B_in_2, HIGH);

  analogWrite(back_led_1_pos, 255);
  analogWrite(back_led_2_pos, 255);
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
  //lcd.print("   <BETA PREVIEW>  ");
  // lcd.print("FIRMWARE v3.0 STABLE");
  // lcd.print(" FIRMWARE  v3.0 LTS ");
  lcd.print("   rolOS v3.0 LTS   ");

  lcd.setCursor(0, 3);
  lcd.print("<<ME NOT CONNECTED>>");
}


void dynamicDisplay(String status){
  lcd.setCursor(0, 3);
  lcd.print(status);
}

/**
 * Create sound & led function for notification
*/

void notificationOn(){
  analogWrite(notificationPin, 2);
}

void notificationOff(){
  digitalWrite(notificationPin, LOW);
}

void beeper(){
  currTime = millis();
  // if(currTime - prevTime => 500){
  //   digitalWrite(notificationPin, state);
  //   state = !state;
  //   prevTime = currTime;
  // }

  if(state == 1){
    if(currTime - prevTime >= onTime){
      state = 0;
      prevTime = currTime;
    }
  }

  else{
    if(currTime - prevTime >= offTime){
      state = 1;
      prevTime = currTime;
    }
  }


  digitalWrite(notificationPin, state);
}

/**
 * Led notification function 
 * Function maker Fahmida Yeasmin
 * Code added 
*/

void led_on(){
  // digitalWrite(led, HIGH);
  digitalWrite(front_led_1_pos, HIGH);
  digitalWrite(front_led_2_pos, HIGH);
}
void led_off(){
  // digitalWrite(led, LOW);
  digitalWrite(front_led_1_pos, LOW);
  digitalWrite(front_led_2_pos, LOW);
}


/**
 * Back light function
 * Function maker Mahmood Hassan Rameem
*/

void backLight_on(){
  analogWrite(back_led_1_pos, 255);
  analogWrite(back_led_2_pos, 255);
}

void backLight_off(){
  analogWrite(back_led_1_pos, 0);
  analogWrite(back_led_2_pos, 0);
}




/**
 * Greetings function for robot
 * Function name salam()
*/

void salam(){
  digitalWrite(notificationPin, HIGH);
  // digitalWrite(led, HIGH);
  digitalWrite(front_led_1_pos, HIGH);
  digitalWrite(front_led_2_pos, HIGH);
}