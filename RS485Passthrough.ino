/*Modified Arduino Example.
  the example does not call endTransmission(); making the 
  passthrough write only for a MAX485 type chips
  This code tested on the Arduion micro ATmega32u4
*/

#define RS485_TX            1  // PD3
#define RS485_RX            0  // PD2
#define RS485_DERE          18 // A0 PF7
#include <ArduinoRS485.h>

void setup() {

  RS485.setPins(RS485_TX, RS485_DERE, -1);
  Serial.begin(9600);
  RS485.begin(9600);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}
unsigned long time = 0;
void loop() {

  //If the LED is on, Keep it on for a time period
  if( digitalRead(13) ){

    //If the timer is not set, set it.
    if( time == 0){
      time = millis() + 300;
    }else{
      //if the timer is expired, turn off LED
      if(millis() > time){
        time = 0;
        digitalWrite(13,LOW);
      }
    }
  }

  if( Serial.available() ) {

    //Set the MAX485 into transmission mode
    RS485.beginTransmission();
    //relay data from serial->MAX485
    while( Serial.available() )
      RS485.write(Serial.read());
    //Set the MAX485 into reveive mode
    RS485.endTransmission();

    //Turn on the onboard LED
    digitalWrite(13, HIGH);
  }

  while(RS485.available()) {
    Serial.write(RS485.read());
    digitalWrite(13, HIGH);
  }
}
