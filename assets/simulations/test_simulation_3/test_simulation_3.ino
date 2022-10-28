/**
* Arduino Based ROBOT Car Project Firmware Version 1.0 Developer Preview
* Developer & Contributors
* REPUBLIC OF LEGENDS
* No Bluetooth Connectivity
* ROBOT going forward, backward and stop
* Added 20/4 LCD display replace 16/2 LCD dispslay
*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
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
  lcd.print("REPUBLIC OF LEGENDS");
  lcd.setCursor(0, 1);
  lcd.print("   ROBOT CAR v1.0   ");
  lcd.setCursor(0, 2);
  lcd.print("<DEVELOPER  PREVIEW>");
  lcd.setCursor(0, 3);
  lcd.print(" ROBOT FORWARD ");
  digitalWrite(motor_A_in_1, HIGH);
  digitalWrite(motor_A_in_2, LOW);

  digitalWrite(motor_B_in_1, HIGH);
  digitalWrite(motor_B_in_2, LOW);
}

void goBackword(){
  lcd.setCursor(0,0);
  lcd.print("REPUBLIC OF LEGENDS");
  lcd.setCursor(0, 1);
  lcd.print("   ROBOT CAR v1.0   ");
  lcd.setCursor(0, 2);
  lcd.print("<DEVELOPER  PREVIEW>");
  lcd.setCursor(0, 3);
  lcd.print(" ROBOT BACKWARD ");
  digitalWrite(motor_A_in_1, LOW);
  digitalWrite(motor_A_in_2, HIGH);

  digitalWrite(motor_B_in_1, LOW);
  digitalWrite(motor_B_in_2, HIGH);
}

void nowStop(){
  lcd.setCursor(0,0);
  lcd.print("REPUBLIC OF LEGENDS");
  lcd.setCursor(0, 1);
  lcd.print("   ROBOT CAR v1.0   ");
  lcd.setCursor(0, 2);
  lcd.print("<DEVELOPER  PREVIEW>");
  lcd.setCursor(0, 3);
  lcd.print(" ROBOT STOP    ");
  digitalWrite(motor_A_in_1, LOW);
  digitalWrite(motor_A_in_2, LOW);

  digitalWrite(motor_B_in_1, LOW);
  digitalWrite(motor_B_in_2, LOW);
}
