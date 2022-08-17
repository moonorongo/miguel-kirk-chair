#define RED_PIN 10
#define GREEN_PIN 11
#define BLUE_PIN 9

//unsigned long rgbEllapsedTime;
//byte rgbStatus = 0;

void setColor(byte r, byte g, byte b) {
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}

void setupRgb() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  analogWrite(RED_PIN, 0);
  analogWrite(GREEN_PIN, 0);
  analogWrite(BLUE_PIN, 0);

//  rgbEllapsedTime = millis();
//  rgbStatus = 0;
}



void loopRgb() {
/*
  switch(rgbStatus) {
    case 0: 
      analogWrite(RED_PIN, 4);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 0);
      if (millis() > rgbEllapsedTime + 1000) {
        rgbEllapsedTime = millis();
        rgbStatus = 1;
      }
      break;
      
    case 1: 
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 0);
      if (millis() > rgbEllapsedTime + 1000) {
        rgbEllapsedTime = millis();
        rgbStatus = 2;  
      }
      break;
      
    case 2: 
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 255);
      if (millis() > rgbEllapsedTime + 1000) {
        rgbEllapsedTime = millis();
        rgbStatus = 0;  
      }
      break;
  }
*/  
}
