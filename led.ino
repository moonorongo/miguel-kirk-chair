/*
  pending: 
    loop leeds (cuando esta iddle)

    encender led correspondiente (cuando se pulsa un boton)
*/

byte leds[] = { 2, 3, 4, 5, 8 };
unsigned long ellapsedTimeLed;
byte ledStatus = 0;
byte j = 0;

void allLeds(byte status) {
  // configure pins as output
  for(j = 0; j < 5; j++) {
    if(status == 1) {
      digitalWrite(leds[j], HIGH);
    } else {
      digitalWrite(leds[j], LOW);
    }
  }
}


void setupLed() {
  ellapsedTimeLed = millis();
  // configure pins as output
  for(j = 0; j < 5; j++) {
    pinMode(leds[j], OUTPUT);
  }
}


void loopLed() {
    if(millis() > ellapsedTimeLed + 500) {
        ellapsedTimeLed = millis();
        if(ledStatus == 0) {
          ledStatus = 1;  
        } else {
          ledStatus = 0;  
        }

        allLeds(ledStatus);
    }
}
