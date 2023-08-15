/**
* Arduino Based rolOS Core Firmware Version 3.0 LTS
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
*/

/**

                   oooo    .oooooo.    .oooooo..o        .oooooo.                                
                   `888   d8P'  `Y8b  d8P'    `Y8       d8P'  `Y8b                               
oooo d8b  .ooooo.   888  888      888 Y88bo.           888           .ooooo.  oooo d8b  .ooooo.  
`888""8P d88' `88b  888  888      888  `"Y8888o.       888          d88' `88b `888""8P d88' `88b 
 888     888   888  888  888      888      `"Y88b      888          888   888  888     888ooo888 
 888     888   888  888  `88b    d88' oo     .d8P      `88b    ooo  888   888  888     888    .o 
d888b    `Y8bod8P' o888o  `Y8bood8P'  8""88888P'        `Y8bood8P'  `Y8bod8P' d888b    `Y8bod8P' 
                                                                                                 
                                                                                                 
                                                                                                 
By Mahmood Hassan Rameem                                                

*/

// Declare all dependencies
int ENB_A = 10; // power signal for right side motors
int ENB_B = 9; // power signal for left side motors

int motor_A_in_1 = 4; // right positive
int motor_A_in_2 = 5; // right negetive

int motor_B_in_1 = 6; // left positive
int motor_B_in_2 = 7; // left negetive

int notificationPin = 11; // Initialize buzzer for notification sound



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



int speed = 150; // Set car default speed
char sig; // variable for get the signal
String status; // variable for store the messages



void setup() {
  // Initialize all motor, blutooth, buzzer and display
  Serial.begin(9600); // setup bluetooth connection to arduino (Yellow, Orange, Coffee, Red)

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
      notificationOff(); // notification sound off
    }

    if(sig == 'F'){
      goForward(); // if robot get F signal then go forward
      notificationOff(); // notification sound off
      backLight_off();
    }

    if(sig == 'B'){
      goBackward(); // if robot get B signal then go backward
      notificationOff(); // notification sound off
    }

    if(sig == 'L'){
      goLeft(); // if robot get L signal then go left
      notificationOff(); // notification sound off
    }

    if(sig == 'R'){
      goRight(); // if robot get R signal then go right
      notificationOff(); // notification sound off
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
 * Create sound & led function for notification
*/

void notificationOn(){
  analogWrite(notificationPin, 2);
}

void notificationOff(){
  digitalWrite(notificationPin, LOW);
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