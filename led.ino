/*
  pending: 
    loop leeds (cuando esta iddle)

    encender led correspondiente (cuando se pulsa un boton)
*/

byte leds[] = { 2, 3, 4, 5, 8 };
unsigned long ellapsedTimeLed;
byte ledStatus = 0; // 0: idle; 1 - 31: leds correspondientes
byte j = 0;
byte temp;

void logStatus() {
    
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
  ellapsedTimeLed = millis();
  // configure pins as output
  for(j = 0; j < 5; j++) {
    pinMode(leds[j], OUTPUT);
  }
}


void loopLed() {
    if(millis() > ellapsedTimeLed + 500) {
        ellapsedTimeLed = millis();

        turnOn(ledStatus);
        ledStatus++;
        if(ledStatus == 32) {
          ledStatus == 0;  
        }
      
    }


}
