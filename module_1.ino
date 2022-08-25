#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

/* 
MODIFICAR:
  TECLAS: QUE LAS LEA DE LOS ANALOG INPUT (EN VEZ DE LOS DIGITAL INPUT)

  LOS ACTUALES KEY INPUT QUE LOS UTILICE PARA MANEJAR LOS 5 LEDS DEL MODULO
*/

SoftwareSerial mySoftwareSerial(7, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

struct RGB {
  byte r;
  byte g;
  byte b;
};

RGB rgbValues[] = { {255, 255, 0}, {0, 255, 255}, {255, 0, 255}, {255, 255, 255}, { 0, 0, 0} };

// <folder>/<filename>.mp3
// folder: 01 .. 99
// filename: 001.mp3 (released action)
//           002.mp3 (press action)

void playSoundPress(byte keyPressed) {
//  myDFPlayer.playFolder(keyPressed + 1, 2);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
//  Serial.print("Keypressed: ");
//  Serial.println(keyPressed);
}

void playSoundReleased(byte keyPressed) {
  //myDFPlayer.playFolder(keyPressed + 1, 1);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
//  Serial.print("Key released: ");
//  Serial.println(keyPressed);

  setColor(rgbValues[keyPressed].r, rgbValues[keyPressed].g, rgbValues[keyPressed].b);
}

void setup()
{
  setupLed();
  setupSwitches();
  setupRgb();
//Serial.begin(115200);  
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
  loopLed();
//  loopRgb();
}
