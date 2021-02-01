#include "IRdiode.h"
#include "hbridge.h"
#include "songs_and_melodies.h"
#include "rgb.h"

buzzer _buzzer;
rgb _rgb;
ledMatrix _ledMatrix;
IRdiode _IR;
hbridge _hbridge;

#define default_state 0x16 // 0 on pilot
#define policeChase_state 0x0C // 1 on pilot
#define bluesBrothers_state 0x18 // 2 on pilot
#define szly_kurki_state 0x5E // 3 on pilot
#define totoro_state 0x08 // 4 on pilot
#define buzzerSpeedUp_state 0x15 // vol+ on pilot
#define buzzerSpeedDown_state 0x07 // vol - on pilot

struct states{
  char _currentState;
  
  void setup(){
    _rgb.setup();
    _buzzer.setup();
    _ledMatrix.setup();
    _IR.setup();
    _hbridge.setup();
    this->changeState(default_state);
    }
    
  void getTime(){
    _buzzer.getTime(millis());
    _rgb.getTime(millis());
    _ledMatrix.getTime(millis());
    _IR.getTime(millis());  
    _hbridge.getTime(millis()); 
  }
  
  void changeState(char _actionNumber){
    if(_actionNumber == _currentState) return void();
    _currentState = _actionNumber;
    
    switch(_actionNumber){
      case default_state:
        _buzzer.pause();
        _rgb.changeState(error);
        _ledMatrix.play(&happyFace);
        _hbridge._A = 0; _hbridge._B = 0;
        break; 
      case policeChase_state:
        _buzzer.play(&police_sirens);
        _rgb.changeState(police);
        _ledMatrix.play(&bluesFace);
        _hbridge._A = 1; _hbridge._B = 1;
        break;
      case buzzerSpeedUp_state:
        if(currentBPM < 150) currentBPM +=15;
        changeTempo(currentBPM);
        break;
      case buzzerSpeedDown_state:
        if(currentBPM > 50) currentBPM -=15;
        changeTempo(currentBPM);
        break;
      case bluesBrothers_state:
        _buzzer.play(&blues_brothers_PeterGunn);
        _rgb.changeState(police);
        _ledMatrix.play(&bluesFace);
        _hbridge._A = 1; _hbridge._B = -1;
        break;
      case szly_kurki_state:
        _buzzer.play(&kurki_trzy);
        _rgb.changeState(green);
        _ledMatrix.play(&happyFace);
        _hbridge._A = -1; _hbridge._B = 1;
        break;
      case totoro_state:
        break;
    } 
  }

};
