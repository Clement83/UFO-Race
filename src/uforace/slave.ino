///////////////////////////////////// SETUP SLAVE
void setupSlave(){
  Wire.begin(2);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

///////////////////////////////////// UPDATE SLAVE
void updateSlave(){
  byte timout = 0;
  paused = false;
  while(slave_updated == false){
    //wait for the master's interrupt
    delay(1);
    timout++;
    if(timout >= 20){
      gb.popup(F("No master"),2);
      disconnected = true;
      paused = true;
      slave_updated = false;
      break;
    }
  }
  slave_updated = false;
}

///////////////////////////////////// SLAVE SEND
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
char output[SLAVE_DATA_BUFFER_LENGTH];
void requestEvent()
{

  //the slave can only answer with one "write" so you have to put all the variables in an string
  output[0] = PLAYER_X; //identifier
  output[1] = (char)player.x; //variable
  output[2] = PLAYER_Y; //identifier
  output[3] = (char)player.y; //variable
  output[4] = PLAYER_A;
  output[5] = (char)player.angle;

  if(paused){
    output[0] = SLAVE_PAUSED;
    output[1] = SLAVE_PAUSED;
    output[2] = SLAVE_PAUSED;
    output[3] = SLAVE_PAUSED;
    output[4] = SLAVE_PAUSED;
    output[5] = SLAVE_PAUSED;
  }

  if(isMaster){
    output[0] = I_AM_MASTER;
    output[1] = I_AM_MASTER;
    output[2] = SLAVE_PAUSED;
    output[3] = SLAVE_PAUSED;
    output[4] = SLAVE_PAUSED;
    output[5] = SLAVE_PAUSED;
  }

  Wire.write(output);
}

///////////////////////////////////// SLAVE RECEIVE
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(Wire.available())    // slave may send less than requested
  {
    char data_in = Wire.read(); // receive byte per byte
    switch(data_in){
    case PLAYER_X:
      player2.x = (float)Wire.read();
      break;
    case PLAYER_Y:
      player2.y = (float)Wire.read();
      break;
    case PLAYER_A :
      player2.angle = (float)Wire.read();
      break;
    default:
      break;
    }
  }
  slave_updated = true;
  disconnected = false;
}







