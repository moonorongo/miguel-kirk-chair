#define DEBOUNCE_TIME 50
#define PRESSING_TIME 500

byte buttons[] = { A0, A1, A2, A3, A5 };

unsigned long ellapsedTime;
byte keyStatus = 0;
byte lastKeyPressed = 255;
byte i = 0;

void setupSwitches() {
  
  ellapsedTime = millis();
  keyStatus = 0;
 
}

void loopSwitches() {
//  Serial.print("A0: ");
//  Serial.print(analogRead(A0));
//
//  Serial.print(", A1: ");
//  Serial.print(analogRead(A1));
//
//  Serial.print(", A2: ");
//  Serial.print(analogRead(A2));
//
//  Serial.print(", A3: ");
//  Serial.print(analogRead(A3));
//
//  Serial.print(", A5: ");
//  Serial.println(analogRead(A5));
  
  switch(keyStatus) {
    case 0: // read initial status
      for(i = 0; i < 5; i++) {
        if(analogRead(buttons[i]) < 512) {
          ellapsedTime = millis();
          keyStatus = 1;
          lastKeyPressed = i;
          break;
        }
      } // end for
      break;

    case 1: // key press (debounce)
      if(analogRead(buttons[lastKeyPressed]) > 512) { // if released key
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
      if(analogRead(buttons[lastKeyPressed]) > 512) { // if released key (after pressing time)
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
