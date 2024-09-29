#define DEBOUNCE_TIME 50
#define PRESSING_TIME 300


// 24: intercom
// 25: music player
byte buttons[] = { 24, 25 };

unsigned long ellapsedTime;
unsigned long ellapsedTimeIntercom;
byte keyStatus = 0;
byte keyStatusIntercom = 0;
byte lastKeyPressed = 255;
byte lastKeyPressedIntercom = 255;
byte i = 0;

void setupSwitches() {
  pinMode(buttons[0], INPUT_PULLUP); 
  pinMode(buttons[1], INPUT); 
  
  ellapsedTime = millis();
  keyStatus = 0;
}

void loopSwitches() {
  // MUSIC PLAYER read sensor
  switch(keyStatus) {
    case 0: // read initial status
      if(!digitalRead(buttons[1])) {
        ellapsedTime = millis();
        keyStatus = 1;
        lastKeyPressed = 1;
      }
      break;

    case 1: // key press (debounce)
      if(digitalRead(buttons[lastKeyPressed])) { // if released key
        if(millis() < ellapsedTime + DEBOUNCE_TIME) {
          keyStatus = 0;
          lastKeyPressed = 255;  
        } else {
          keyStatus = 4;
        }
      } else { // key still pressing
        if(millis() > ellapsedTime + PRESSING_TIME) {
          keyStatus = 3;
          playSoundPress(lastKeyPressed); // si queremos un sonido al pulsar, y otro al soltar  
        }          
      }
      break;

    case 3: // key still pressing
      if(digitalRead(buttons[lastKeyPressed])) { // if released key (after pressing time)
        keyStatus = 4;
      }
      break;

    case 4: // key released
      playSoundReleased(lastKeyPressed);
      keyStatus = 0;
      lastKeyPressed = 255;
      break;
  }
  // END SWITCH MUSIC PLAYER


  // START INTERCOM
  switch(keyStatusIntercom) {
    case 0: // key released
      if(!digitalRead(buttons[0])) {
        ellapsedTimeIntercom = millis();
        keyStatusIntercom = 1;
        lastKeyPressedIntercom = 0;
//        Serial.println("presionado Intercom 1st time");
      }
      break;
    case 1: // key press (debounce)
      if(digitalRead(buttons[0])) { // if released key
        if(millis() < ellapsedTimeIntercom + DEBOUNCE_TIME) {
          keyStatusIntercom = 0;
          lastKeyPressedIntercom = 255; // 255 es none  
        } else {
          keyStatusIntercom= 4;
        }
      } else { // key still pressing
        if(millis() > ellapsedTimeIntercom + PRESSING_TIME) {
          keyStatusIntercom = 3;
          playSoundPress(lastKeyPressedIntercom); // si queremos un sonido al pulsar, y otro al soltar  
        }          
      }
      break;

    case 3: // key still pressing
//      Serial.println("Intercom still press");
      if(digitalRead(buttons[0])) { // if released key (after pressing time)
        keyStatusIntercom = 4;
      }
      break;

    case 4: // key released
//      Serial.println("Intercom released");
      playSoundReleased(lastKeyPressedIntercom);
      keyStatusIntercom = 0;
      lastKeyPressedIntercom = 255;
      break;
  }
}
