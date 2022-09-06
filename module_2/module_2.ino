#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

/* 
  Modulo 2: Intercom y reproductor de musica (ARDUINO MEGA con 2 reproductores MP3)
  Intercom
  --------
    1.- al pulsar el boton del intercom suena un pitido, al soltar reproduce un audio (respuesta) al azar
    2. Organizacion de la SD: carpeta 001 tiene el pitido, a partir de alli vamos a poner n respuestas fijas (que van de 002 a 0nn) 
       que son las que se reproduciran al azar

  Reproductor de musica
  ---------------------
    1. Al insertar una tarjeta se acciona un pulsador
    2. primero reproduce un pitido (el mismo que el del intercom)
    3. al finalizar la reproduccion del pitido comienza a reproducir la musica
       (se diferencia del anterior en que en el anterior reproduce al soltar, aqui al terminar)  
 
    4. Al retirar la tarjeta (soltar el switch) frena la reproduccion y emite un pitido (diferente al anterior) 
    4. Organizacion de la SD: 001 y 002 : pitidos, 003 en adelante: archivos de musica
*/

DFRobotDFPlayerMini intercomPlayer;
DFRobotDFPlayerMini musicPlayer;

byte isPlayingIntercomPlayer = 0;
byte isPlayingMusicPlayer = 0;

// <folder>/<filename>.mp3
// folder: 01 .. 99
// filename: 001.mp3 (released action)
//           002.mp3 (press action)

void playSoundPress(byte keyPressed) {
  //myDFPlayer.playFolder(keyPressed + 1, 2);
  isPlaying = keyPressed + 1;  
}

void playSoundReleased(byte keyPressed) {
  if(isPlaying != 0) {
    //myDFPlayer.stop();
    isPlaying = 0;
  } else {
    //myDFPlayer.playFolder(keyPressed + 1, 1);
    isPlaying = keyPressed + 1;
  }
}

void setup()
{
  setupSwitches();

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);  

  intercomPlayer.begin(Serial1);
  intercomPlayer.EQ(DFPLAYER_EQ_NORMAL);
  intercomPlayer.setTimeOut(500);
  intercomPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  intercomPlayer.volume(20);  //Set volume value. From 0 to 30

  musicPlayer.begin(Serial2);
  musicPlayer.EQ(DFPLAYER_EQ_NORMAL);
  musicPlayer.setTimeOut(500);
  musicPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  musicPlayer.volume(20);  //Set volume value. From 0 to 30
}

void loop()
{
  if(intercomPlayer.available()) {
    // triggered on finish play
    if(intercomPlayer.readType() == 5) {
      isPlayingIntercomPlayer = 0;
    }
  }

  if(musicPlayer.available()) {
    // triggered on finish play
    if(musicPlayer.readType() == 5) {
      isPlayingMusicPlayer = 0;
    }
  }
  
  loopSwitches();
}