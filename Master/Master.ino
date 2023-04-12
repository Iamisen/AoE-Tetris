#include "Wire.h"
#include "Tetris.h"

int mypins[4] = {9,10,11,12}; //UP, DOWN, RIGHT, LEFT
byte myreadings[4];
String mode;//options: MENU, GAME
String actions[4] = {"UP", "DOWN", "RIGHT", "LEFT"};
String action; //UP, DOWN, RIGHT, LEFT, NONE
int block = 0; //number of blocks dropped so far

void setup(){
  for (int i=0;i<4;i++){
    pinMode(mypins[i], INPUT);
  }
  mode = "MENU";
  Serial.begin(9600);
  Wire.begin();

  Tetris tetris();
  bool playing = false;
  int screen[16][8];
}

void loop(){
  for (int i=0; i<4; i++){
    myreadings[i] = digitalRead(mypins[i]);

    action = "NONE";

    if (myreadings[i] == LOW){//it is a pull up button
      action = actions[i];
    }
    Serial.println(action);
  }
  
  Wire.beginTransmission(4);
  ProcessState();
  Wire.endTransmission(4);
}

void ProcessState(){
  //process states
  if (mode == "MENU"){
    if (action != "NONE"){
        mode = "GAME";
        playing = true;
      }
  }
  
  if (mode == "GAME"){
    if (!tetris.block_falling){
      screen = tetris.SpawnShape();
      if (block == false){
        playing = false;
      }
    }

    if (tetris.block_falling){
      screen = tetris.Action(action);
    }
  }
}
