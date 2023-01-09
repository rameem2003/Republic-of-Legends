int led_1_pos = A3;
int led_1_neg = A2;

int led_2_pos = A1;
int led_2_neg = A0;



void setup() {
  // put your setup code here, to run once:
  pinMode(led_1_pos, OUTPUT);
  pinMode(led_1_neg, OUTPUT);

  pinMode(led_2_pos, OUTPUT);
  pinMode(led_2_neg, OUTPUT);


  analogWrite(led_1_neg, 0);
  analogWrite(led_2_neg, 0);

}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(led_1_pos, 255);
  delay(1000);
  analogWrite(led_1_pos, 0);
  delay(1000);

  analogWrite(led_2_pos, 255);
  delay(1000);
  analogWrite(led_2_pos, 0);
  delay(1000);

}


