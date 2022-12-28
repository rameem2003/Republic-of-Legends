int sound = 9;
int led = 13;

unsigned long curr = 0;
unsigned long prev = 0;

unsigned long onTime = 500;
unsigned long offTime = 2000;

bool state = 1;

void setup(){
  pinMode(sound, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop(){
  notification();
}

void notification(){
  curr = millis();

  if(state == 1){
    if(curr - prev >= onTime){
      state = 0;
      prev = curr;
    }
  }

  else{
    if(curr - prev >= offTime){
      state = 0;
      prev = curr;
    }
  }


  digitalWrite(led, state);
}