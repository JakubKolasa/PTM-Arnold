  #define PWMA 11
#define AIN2 10
#define AIN1 9
#define STBY 8
#define BIN1 7
#define BIN2 6
#define PWMB 5

#define _motorChange 100

struct hbridge{
  int _A; // 0 - sleep, -1 backward, 1 foward 
  int _B;
  bool motorTurn = false; // false A, true B
  unsigned long _currentDuration;
  unsigned long _last_millis;
  
  void setup(){
  for(int i = 5; i<12; i++)
    {
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
    } 
    digitalWrite(STBY, HIGH);
    digitalWrite(PWMA, HIGH);
    digitalWrite(PWMB, HIGH);
  }

  //B - forward
  void BF(){ digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH);}

  //B - backward
  void BB(){  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);}

  //A - forward
  void AF(){ digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH);}

  //Left - backward
  void AB(){ digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);}

  void A_stop(){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);

  }

  void B_stop(){
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }

  void getTime(unsigned long milis){
    _currentDuration+= milis -_last_millis;
    _last_millis = milis;
    if( _currentDuration >= _motorChange){
      _currentDuration = 0;
      motorTurn = !motorTurn;
    }
    if(!motorTurn){
      if(_A) AF();
      else if(_A == -1) AB();
      else A_stop();
    }

    if(motorTurn){
      if(_B) BF();
      else if(_B == -1) BB();
      else B_stop();
    }    
  }
};
