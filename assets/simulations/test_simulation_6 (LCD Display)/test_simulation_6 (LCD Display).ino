/**
* Arduino Based ROBOT Car Project Firmware Version 2.0 Developer Preview (20/4 LCD Display)
* Developer & Contributors
* REPUBLIC OF LEGENDS
* No Bluetooth Connectivity
* ROBOT going forward, backward and stop
* Added 20/4 LCD display replace 16/2 LCD dispslay
*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

String conn;
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

    if(sig == 'S'){
      conn = "Connected to phone";
    }
    else {
      conn = "Me Not Connected    ";
    }
  }

  Display(conn);
  
  
  
  

}


void Display(String conn){
  lcd.setCursor(0,0);
  lcd.print("Republic of Legends");

  lcd.setCursor(0, 1);
  lcd.print("   Robot Car v1.0  ");

  lcd.setCursor(0, 2);
  lcd.print("   <BETA PREVIEW>  ");

  lcd.setCursor(0, 3);
  lcd.print(conn);
}
