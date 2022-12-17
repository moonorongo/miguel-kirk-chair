#define IDLE_PAUSE 5000

byte leds[] = { 22, 24, 26, 28, 30, 32, 34, 36, 38 };
unsigned long ellapsedTimeLed;
unsigned int ledStatus = 0; // 0: idle; 1 - 9: leds correspondientes
unsigned int idleStatusValue = 0;
byte j = 0;
unsigned int temp;

void setLedStatus(unsigned int status) {
  ledStatus = status;
}

void turnOn(unsigned int number) {
  for(j = 0; j < 9; j++) {
    temp = 1 << j;
    if(number & temp) {
      digitalWrite(leds[j], HIGH);  
//      Serial.print("1");
    } else {
      digitalWrite(leds[j], LOW);  
//      Serial.print("0");
    }

//    if(j == 8) {
//      Serial.println("");  
//    }
  }
}


void setupLed() {
  randomSeed(analogRead(A4));
  
  ellapsedTimeLed = millis();
  // configure pins as output
  for(j = 0; j < 9; j++) {
    pinMode(leds[j], OUTPUT);
  }
}


void loopLed() {
  
  if(ledStatus == 0) {
    if(millis() > ellapsedTimeLed + IDLE_PAUSE) {
      ellapsedTimeLed = millis();
      idleStatusValue = (unsigned int) random(0, 1024);
      turnOn(idleStatusValue);
    }
  } else {
    turnOn(1 << ledStatus - 1);  
  }
  

}
