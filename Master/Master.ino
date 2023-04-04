#include "Wire.h"
#include "TetrisMatrices.h"

int mypins[4] = {9,10,11,12}; //UP, DOWN, RIGHT, LEFT
int myreadings[4] = {0,0,0,0};
char mode;//options: menu, game

void setup(){
  for (i=0,i<4,i++){
    pinmode(mypins[i], INPUT);
  }
  mode = "menu"
  Serial.begin(9600);
  Wire.begin();
}

void loop(){
  for (i=0,i<4,i++){
    myreadings[i] = digitalRead(mypins[i]);
  }

  Wire.beginTransmission(4);
  ProcessState();
  Wire.endTransmission(4);
}

void ProcessState(){
  if (mode == "menu"){
    Serial.println("Press the top button to start");
    if (myreadings[0] == 1){
      mode = "game";
      Serial.println("Game Starting...")
    }
  }
  if (mode == "game"){

  }
}