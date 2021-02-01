#define R A2
#define G A3
#define B A4

enum rgb_state{off, police, error,green };

struct rgb{
  unsigned long _currentDuration;
  unsigned long _last_millis;
  unsigned long _colorChange = 300; // [ms]
  rgb_state mystate = off;
  bool _light;

  void changeState(rgb_state newState){ mystate = newState;}
  void setup(){ pinMode(R,OUTPUT); pinMode(G,OUTPUT); pinMode(B,OUTPUT);}
  void getTime(unsigned long milis){
    _currentDuration+= milis -_last_millis;
    _last_millis = milis;
    if( _currentDuration >= _colorChange){
      _currentDuration = 0;
      _light = !_light;
    }
    switch (mystate){
      case off:
        digitalWrite(R,0);
        digitalWrite(G,0);
        digitalWrite(B,0);
        break;
      case police:  
        digitalWrite(R, _light);
        digitalWrite(G,0);
        digitalWrite(B, !_light);
        break;
      case error:
        digitalWrite(R, _light);
        digitalWrite(G,0);
        digitalWrite(B,0);
        break;
      case green:
        digitalWrite(R, 0);
        digitalWrite(G,_light);
        digitalWrite(B,0);
      }
    }
};
