#define PAUSEMENULENGTH 4
const char strPlay[] PROGMEM = "Play";
const char strHighScores[] PROGMEM = "High scores";
const char strSystemInfo[] PROGMEM = "System Info";
const char strMainMenu[] PROGMEM = "Main Menu";


const char* const pauseMenu[PAUSEMENULENGTH] PROGMEM = {
  strPlay,
  strHighScores,
  strSystemInfo,
  strMainMenu
};


const char strMaster[] PROGMEM = "Host (master)";
const char strSlave[] PROGMEM = "Join (slave)";
const char* const menu[2] PROGMEM = {
  strMaster,
  strSlave
};

void drawMenu(){
  /*switch(gb.menu(pauseMenu, PAUSEMENULENGTH)){
  case 0: //play
    initGame();
    play();
    break;
  case 1: //high scores
    drawHighScores();
    break;
  case 2: //System info
    while (1) {
      if (gb.update()) {
        if (gb.buttons.pressed(BTN_C)) {
          gb.sound.playCancel();
          break;
        }
        //gb.display.setCursor(0, 0);
        gb.display.print(F("Bat:"));
        gb.display.print(gb.battery.voltage);
        gb.display.println(F("mV"));

        gb.display.print(F("Bat lvl:"));
        gb.display.print(gb.battery.level);
        gb.display.println(F("/4"));

        gb.display.print(F("Light:"));
        gb.display.println(gb.backlight.ambientLight);

        gb.display.print(F("Backlight:"));
        gb.display.println(gb.backlight.backlightValue);

        gb.display.print(F("Volume:"));
        gb.display.print(gb.sound.getVolume());
        gb.display.print(F("/"));
        gb.display.println(gb.sound.volumeMax);
      }
    }
    break;
  default: //title screen
    drawTitleScreen();
    break;
  }*/
  
        paused = true;
    
      switch(gb.menu(menu, 2)){
      case 0: //Host
        paused = false;
        disconnected = false;
        isMaster = true;
        break;
      case 1: //Join
        paused = false;
        disconnected = false;
        isMaster = false;
        break;
      default:
        gb.titleScreen(F("Duel")); //shows the main menu
        break;
      }
      
    initGame();
    play();
}



