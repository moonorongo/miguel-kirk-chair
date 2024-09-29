#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

/* 
  Modulo 2: Intercom y reproductor de musica (ARDUINO MEGA con 2 reproductores MP3)
  Intercom
  --------
    1.- al pulsar el boton del intercom suena un pitido, al soltar reproduce un audio (respuesta) al azar
    2. Organizacion de la SD: carpeta 001 tiene el pitido, a partir de alli vamos a poner n respuestas fijas (que van de 003 a 013) 
       que son las que se reproduciran al azar

  Reproductor de musica
  ---------------------
    1. Al insertar una tarjeta se acciona un pulsador
    2. primero reproduce un pitido (diferente al intercom, 002)
    3. al finalizar la reproduccion del pitido comienza a reproducir la musica
       (se diferencia del anterior en que en el anterior reproduce al soltar, aqui al terminar)  
 
    4. Al retirar la tarjeta (soltar el switch) frena la reproduccion y emite un pitido (diferente al anterior 003) 
    4. Organizacion de la SD: 001 y 002 : pitidos, 023 a 033 en adelante: archivos de musica
*/
DFRobotDFPlayerMini intercomPlayer;
DFRobotDFPlayerMini musicPlayer;

byte isPlayingIntercomPlayer = 0; // (1) en el circuito, 24 arduino
byte isPlayingMusicPlayer = 0;    // (2) en el circuito, 25 arduino

// <folder>/<filename>.mp3
// folder: 01 .. 99
// filename: 001.mp3 (released action)
//           002.mp3 (press action)


void playSoundPress(byte lastKeyPressed) {
  if(lastKeyPressed == 0) {
    // intercom
    playIntercomPress();
  } else {
    // Music Player - logica invertida
    playMusicReleased();
//    playMusicPress();
  }  
}


void playSoundReleased(byte lastKeyPressed) {
  if(lastKeyPressed == 0) {
    // Intercom
    playIntercomReleased();
  } else {
    // Music Player - logica invertida
    playMusicPress();
//    playMusicReleased();
  }    
}

// Intercom
void playIntercomPress() {
  // pitido inicial
  intercomPlayer.playFolder(1, 1);
  isPlayingIntercomPlayer = 1;
}


void playIntercomReleased() {
  if(isPlayingIntercomPlayer != 0) {
    intercomPlayer.stop();
    isPlayingIntercomPlayer = 0;
  } else {
    intercomPlayer.playFolder(random(4, 15), 1);
    isPlayingIntercomPlayer = 1;
  }
}

// Music Player
void playMusicPress() {
  musicPlayer.playFolder(2, 1);
  isPlayingMusicPlayer = 1;
}

void playMusicReleased() {
  if(isPlayingMusicPlayer != 0) {
    isPlayingMusicPlayer = 3; // pasa a estado "toca pitido salida"
    musicPlayer.playFolder(3, 1);
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
      if(isPlayingMusicPlayer == 1) { // si estaba tocando el pitido de entrada
        isPlayingMusicPlayer = 2; // pasa a estado "toca musica"
        // random folder 004 - 014 -> pasar a 015 - 025
        musicPlayer.playFolder(random(4, 14), 1);
      } else if(isPlayingMusicPlayer == 2) { // si estaba tocando musica
        isPlayingMusicPlayer = 3; // pasa a estado "toca pitido salida"
        musicPlayer.playFolder(3, 1);
//        musicPlayer.playFolder(random(15, 26), 1);
      } else {
        isPlayingMusicPlayer = 0;
      }
    }
  }

  loopSwitches();
}
