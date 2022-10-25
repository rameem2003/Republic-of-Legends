#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int ENA_A = 4;
int ENA_B = 3;
int motor_A_in_1 = 8;
int motor_A_in_2 = 7;
int motor_B_in_1 = 5;
int motor_B_in_2 = 6;

void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  pinMode(ENA_A, OUTPUT);
  pinMode(ENA_B, OUTPUT);
  pinMode(motor_A_in_1, OUTPUT);
  pinMode(motor_A_in_2, OUTPUT);
  pinMode(motor_B_in_1, OUTPUT);
  pinMode(motor_B_in_2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ENA_A, HIGH);
  digitalWrite(ENA_B, HIGH);

  goForward();
  delay(5000);

  goBackword();
  delay(5000);

  nowStop();
  delay(2000);

}

void goForward(){
  lcd.setCursor(0,0);
  lcd.print("Robot Forward");
  digitalWrite(motor_A_in_1, HIGH);
  digitalWrite(motor_A_in_2, LOW);

  digitalWrite(motor_B_in_1, HIGH);
  digitalWrite(motor_B_in_2, LOW);
}

void goBackword(){
  lcd.setCursor(0,0);
  lcd.print("Robot Backward");
  digitalWrite(motor_A_in_1, LOW);
  digitalWrite(motor_A_in_2, HIGH);

  digitalWrite(motor_B_in_1, LOW);
  digitalWrite(motor_B_in_2, HIGH);
}

void nowStop(){
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Robot Stoped");
  digitalWrite(motor_A_in_1, LOW);
  digitalWrite(motor_A_in_2, LOW);

  digitalWrite(motor_B_in_1, LOW);
  digitalWrite(motor_B_in_2, LOW);
}
