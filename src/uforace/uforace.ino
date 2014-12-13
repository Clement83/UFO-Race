#include <SPI.h>
#include <Gamebuino.h>
Gamebuino gb;

#include <EEPROM.h>
#include <avr/pgmspace.h>
#include <Wire.h>

extern const byte font3x5[];
extern const byte font5x7[];

typedef struct {
  float x, y, v, vx, vy, angle;
  byte radius;
} Ufo;

Ufo player;
Ufo player2;

boolean paused = true;
boolean isMaster = false;
boolean disconnected = true;
boolean slave_updated = false;

//global variables
int camera_x, camera_y;


#define SLAVE_PAUSED 1
#define I_AM_MASTER 2
#define PLAYER_X 10
#define PLAYER_Y 21
#define PLAYER_A 22
#define SLAVE_DATA_BUFFER_LENGTH 6

void setup()
{
  gb.begin();
  gb.display.setFont(font5x7);
  initHighscore();
  drawTitleScreen();
  setupMaster();
  setupSlave();
}

void loop(){
  drawMenu();
}

void initGame(){
  gb.battery.show = false;
  initPlayer();
  initTime();
}

void play(){
  gb.display.setFont(font3x5);
  while(1){
    if(gb.update()){
      //pause the game if C is pressed
      if(gb.buttons.pressed(BTN_C)){
        gb.display.setFont(font5x7);
        return;
      }

      updatePlayer();
      if(isMaster)
      {
        updateMaster();
      }
      else 
      {
        updateSlave();
      }
      //updateTime();
      //envoi des donnee
      
      drawWorld();
      drawMap();
      drawTime();
      drawPlayer();
    }
  }
}


