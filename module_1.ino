#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(7, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
byte leds[] = { 9, 10, 11, 12, 13 };

// <folder>/<filename>.mp3
// folder: 01 .. 99
// filename: 001.mp3 (released action)
//           002.mp3 (press action)

void playSoundPress(byte keyPressed) {
  myDFPlayer.playFolder(keyPressed + 1, 2);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  Serial.print("Keypressed: ");
  Serial.println(keyPressed);
}

void playSoundReleased(byte keyPressed) {
  myDFPlayer.playFolder(keyPressed + 1, 1);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  Serial.print("Key released: ");
  Serial.println(keyPressed);

}

void setup()
{
  Serial.begin(115200);
  setupSwitches();
  
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial);

  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.setTimeOut(500);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
}

void loop()
{
  loopSwitches();
  
}
