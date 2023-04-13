#include <Tetris.h>

int i = 0;
void setup() {
  // put your setup code here, to run once:
  //Tetris tetris();
  Serial.begin(9600);
  Serial.println("Testing the code...");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (i<=10){
    Serial.println(i);
    delay(100);
    i++;
  }
}
