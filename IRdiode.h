#include <IRremote.h>

#define SIG A1
#define VCC 13
#define signalDelay 100

IRrecv irrecv(SIG);
decode_results results;;
char actionNumber = 0x16; // default action, 0 on pilot

struct IRdiode{
  unsigned long _currentDuration;
  unsigned long _last_millis;

  void setup(){
    Serial.begin(9600);
    irrecv.enableIRIn();
     pinMode(VCC, OUTPUT);
     digitalWrite(VCC, HIGH);
    }
    
  void getTime(unsigned long milis){
    _currentDuration+= milis -_last_millis;
    _last_millis = milis;
    if(_currentDuration >= signalDelay){
      if(irrecv.decode()) {
          Serial.print("Signal detected");
          actionNumber =  results.value;
          _currentDuration = 0;
          irrecv.resume();
      }
    }         
  }
};
