#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(7, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

struct RGB {
  byte r;
  byte g;
  byte b;
};

RGB rgbValues[] = { {255, 255, 0}, {0, 255, 255}, {255, 0, 255}, {255, 255, 255}, { 0, 0, 0} };

byte isPlaying = 0;

// <folder>/<filename>.mp3
// folder: 01 .. 99
// filename: 001.mp3 (released action)
//           002.mp3 (press action)


void playSoundPress(byte keyPressed) {
  myDFPlayer.playFolder(keyPressed + 1, 2);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  isPlaying = keyPressed + 1;  
}

void playSoundReleased(byte keyPressed) {
  if(isPlaying != 0) {
    myDFPlayer.stop();
    setColor(0,0,0);
    isPlaying = 0;
    setLedStatus(0);
  } else {
    myDFPlayer.playFolder(keyPressed + 1, 1);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
    isPlaying = keyPressed + 1;
    setLedStatus(isPlaying);  
    setColor(rgbValues[keyPressed].r, rgbValues[keyPressed].g, rgbValues[keyPressed].b);
  }
}


void setup()
{
  setupLed();
  setupSwitches();
  setupRgb();

  Serial.begin(9600);  
  
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial);

  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.setTimeOut(500);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  
  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
}

void loop()
{
  if(myDFPlayer.available()) {
    // triggered on finish play
    if(myDFPlayer.readType() == 5) {
      setColor(0,0,0);
      isPlaying = 0;
      setLedStatus(0);
    }
  }
 
  loopSwitches();
  loopLed();
//  loopRgb();
}
