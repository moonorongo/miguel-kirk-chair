#define DEBOUNCE_TIME 50
#define PRESSING_TIME 300

SoftwareSerial mySoftwareSerial(7, 6); // RX, TX

byte buttons[] = { 2, 3, 4, 5, 8 };

unsigned long ellapsedTime;
byte keyStatus = 0;
byte lastKeyPressed = 255;
byte i = 0;

void setupSwitches() {
  // configure pins as input
  for(i = 0; i < 5; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }

  ellapsedTime = millis();
  // 0: nothing press; 1: pressed; 2: released; 
  keyStatus = 0;
  
}

void loopSwitches() {
  switch(keyStatus) {
    case 0: // read initial status
      for(i = 0; i < 5; i++) {
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
