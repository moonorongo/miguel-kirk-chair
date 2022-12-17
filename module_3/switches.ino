#define DEBOUNCE_TIME 50
#define PRESSING_TIME 300

byte buttons[] = { 40, 42, 44, 46, 48, 50, 52, 53 };

unsigned long ellapsedTime;
byte keyStatus = 0;
byte lastKeyPressed = 255;
byte i = 0;

void setupSwitches() {
  for(i = 0; i < 8; i++) {
    pinMode(buttons[i], INPUT_PULLUP); 
  }
  
  ellapsedTime = millis();
  keyStatus = 0;
}

void loopSwitches() {
  
  switch(keyStatus) {
    case 0: // read initial status
      for(i = 0; i < 8; i++) {
        if(!digitalRead(buttons[i])) {
          ellapsedTime = millis();
          keyStatus = 1;
          lastKeyPressed = i;
          break;
        }
      } // end for
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
}
