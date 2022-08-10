#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//SoftwareSerial mySoftwareSerial(7, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
byte leds[] = { 9, 10, 11, 12, 13 };

void playSoundPress(byte keyPressed) {
// myDFPlayer.play(keyPressed + 1);
// myDFPlayer.playFolder(15, 4);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  Serial.print("Keypressed: ");
  Serial.println(keyPressed);
}

void playSoundReleased(byte keyPressed) {
// myDFPlayer.play(keyPressed + 1);
// myDFPlayer.playFolder(15, 4);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  Serial.print("Key released: ");
  Serial.println(keyPressed);

}

void setup()
{
  Serial.begin(115200);
  setupSwitches();
  
  //mySoftwareSerial.begin(9600);
  //myDFPlayer.begin(mySoftwareSerial);
  
  //myDFPlayer.volume(30);  //Set volume value. From 0 to 30
}

void loop()
{
  loopSwitches();
  
}
