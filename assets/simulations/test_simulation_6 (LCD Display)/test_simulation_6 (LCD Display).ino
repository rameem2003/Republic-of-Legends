/**
* Arduino Based ROBOT Car Project Firmware Version 2.0 Developer Preview (20/4 LCD Display)
* Developer & Contributors
* REPUBLIC OF LEGENDS
* Test 20/4 LCD Display
*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

string conn;
char sig;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    sig = Serial.read();

    
    conn = "*CONNECTED TO PHONE*";
    Display(conn);


  }else{
    Display("<<ME NOT CONNECTED>>");
  }

}


void Display(string conn){
  lcd.setCursor(0,0);
  lcd.print("REPUBLIC OF LEGENDS");

  lcd.setCursor(0, 1);
  lcd.print("   ROBOT CAR v1.0  ");

  lcd.setCursor(0, 2);
  lcd.print("   <BETA PREVIEW>  ");

  lcd.setCursor(0, 3);
  lcd.print(conn);
}
