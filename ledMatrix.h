#define CLK 2 // clock
#define CS 3  // load pulse
#define DIN 4  // data in


/* 
 *  Simple frame
 *  frames generator https://xantorohara.github.io/led-matrix-editor/
 */
struct frame{
  unsigned long _length; // ms
  int64_t _image;
  frame(unsigned long length,  int64_t image): _length(length), _image(image){}
};

/*
 * Vector of frames
 */
struct animation{
  frame* _frames;  
  unsigned int _framesNumber;
  animation(unsigned int framesNumber, frame* frames): _framesNumber(framesNumber), _frames(frames){}
};

/*
 * Main led matrix struct
 */
struct ledMatrix{
  unsigned char imageTable[8];  // char == 1 byte
  int64_t img = 0x815a241818245a81; // int64_t == 8 * char =  8 bytes
  unsigned long _currentDuration;
  unsigned long _last_millis;
  animation* _currentAnimation;
  int _currentFrameInd = 0;

 /*
  * Transform 8bytes hex into 8 1 byte hex 
 */
  void changeImageTable(int64_t hex){ for(int i = 0; i < 8; i++){ imageTable[i] = (hex >> (8*i)) & 0xff;}}
  
  void send_byte(unsigned char data){
    digitalWrite(CS,LOW);
    for(int i=8;i>0;i--){
      digitalWrite(CLK,LOW);  
      if((data&0x80)==0x80) digitalWrite(DIN,HIGH); 
      else  digitalWrite(DIN,LOW);
      data = data<<1;
      digitalWrite(CLK,HIGH); 
    } 
  }
  
  void send_data(unsigned char address,unsigned char dat) {
    digitalWrite(CS,LOW);
    send_byte(address); 
    send_byte(dat);
    digitalWrite(CS,HIGH);
  }

  void display(){for(int i=1;i<9;i++) send_data(i,imageTable[i-1]);}


  // https://tinusaur.org/tag/max7219/
  void init_MAX7219() {
    send_data(0x09, 0x00); // Decode-Mode Register, 00 = No decode
    send_data(0x0a, 0x03); // Intensity Register, 0x00 .. 0x0f
    send_data(0x0b, 0x07); // Scan-Limit Register, 0x07 to show all lines
    send_data(0x0c, 0x01); // Shutdown Register, 0x01 = Normal Operation
    send_data(0x0f, 0x00); // Display-Test Register, 0x00 = Normal 
  }
  
  
  
  void setup(){
    pinMode(CLK,OUTPUT);
    pinMode(CS,OUTPUT);
    pinMode(DIN,OUTPUT);
    delay(50); 
    changeImageTable(img);
    init_MAX7219();
  }

    void play(animation* a){ _currentAnimation = a ;_currentFrameInd = 0; _currentDuration = 0;}
    
    /*
   * Main function of this struct
   * Get time from millis() arduino function in main()
   * Playing animation given in play() function
   */
   void getTime(unsigned long milis){
    _currentDuration+= milis -_last_millis;
    _last_millis = milis;
    if( _currentDuration >= _currentAnimation->_frames[_currentFrameInd]._length){
      _currentDuration = 0;
      _currentFrameInd++;
      if(_currentFrameInd == _currentAnimation->_framesNumber) _currentFrameInd = 0;
      changeImageTable(_currentAnimation->_frames[_currentFrameInd]._image);
    }
    else display();
   }
};
