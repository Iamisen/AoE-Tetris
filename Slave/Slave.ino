#include <Wire.h>

int i2c_rcv[16][8];           // data received from I2C bus

void setup(){
  Wire.begin(0x70);
  Wire.onReceive(dataRcv);    // register an event handler for received data
}

void loop(){
  delay(100);
}

//received data handler function
void dataRcv(int numBytes){
	while(Wire.available()) {	// read all data received
		i2c_rcv = Wire.read();
    Serial.println(i2c_rcv);
	}
}