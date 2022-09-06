#define IDLE_PAUSE 5000

byte leds[] = { 2, 3, 4, 5, 8 };
unsigned long ellapsedTimeLed;
byte ledStatus = 0; // 0: idle; 1 - 5: leds correspondientes
byte idleStatusValue = 0;
byte j = 0;
byte temp;

void setLedStatus(byte status) {
  ledStatus = status;
}

void turnOn(byte number) {
  for(j = 0; j < 5; j++) {
    temp = 1 << j;
    if(number & temp) {
      digitalWrite(leds[j], HIGH);  
      Serial.print("1");
    } else {
      digitalWrite(leds[j], LOW);  
      Serial.print("0");
    }

    if(j == 4) {
      Serial.println("");  
    }
  }
}


void setupLed() {
  randomSeed(analogRead(A4));
  
  ellapsedTimeLed = millis();
  // configure pins as output
  for(j = 0; j < 5; j++) {
    pinMode(leds[j], OUTPUT);
  }
}


void loopLed() {
  if(ledStatus == 0) {
    if(millis() > ellapsedTimeLed + IDLE_PAUSE) {
      ellapsedTimeLed = millis();
      idleStatusValue = byte(random(1, 32));
      turnOn(idleStatusValue);
    }    
  } else {
    turnOn(1 << ledStatus - 1);  
  }
  

}
