#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

/* 
  Modulo 3: Switches con sonidos de fondo, y panel de 9 leds, con secuencia aleatoria (ARDUINO MEGA con 1 reproductor MP3)
  Switches
  --------
    1.- al cambiar el estado del switch a ON comienza a reproducir el archivo (on keypress)
    2.- al detectar on keyup frena la reproduccion

  Leds
  ----
    1. secuencia aleatoria
*/

DFRobotDFPlayerMini myDFPlayer;

byte isPlaying = 0;    // (2) en el circuito, 25 arduino

// <folder>/<filename>.mp3
// folder: 01 .. 99
// filename: 001.mp3 (released action)
//           002.mp3 (press action)


void playSoundPress(byte keyPressed) {
  myDFPlayer.playFolder(keyPressed + 1, 2);
   
  isPlaying = keyPressed + 1;  
}


void playSoundReleased(byte keyPressed) {
    myDFPlayer.stop();
}


void setup()
{
  setupSwitches();

  Serial.begin(9600);
  Serial1.begin(9600);

  myDFPlayer.begin(Serial1);
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
      isPlaying = 0;
    }
  }
 
  loopSwitches();
  loopLed();
}
