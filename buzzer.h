#include "notesFrequency.h"
#define BUZ A0

//default notes duration
int currentBPM = 75;
unsigned long quarterNote = 800; //ms
unsigned long wholeNote = quarterNote*4;
unsigned long halfNote = quarterNote*2;
unsigned long eightNote = quarterNote/2;
unsigned long distanceBetweenNotes = 10;

/*
 *  Change tempo of the melody
 *  int newBPM - new tempo in ,,beats per minute"
 */
void changeTempo(int newBPM){
  quarterNote = 60000/newBPM;  // T = 1/f  [min]      T * 60 * 100 [ms]   
  eightNote = quarterNote / 2;
  halfNote = quarterNote*2;
  wholeNote = quarterNote*4;
}

/*
 * Simple note
 */
struct note{
  int _frequency;
  unsigned long &_length;
  note(int frequency, unsigned long &length_ms): _length(length_ms), _frequency(frequency){}
};

/*
 * Vector of notes
 */
struct melody{
  int _notes_number;
  note* _notes;
  melody(int notes_number, note* notes): _notes_number(notes_number), _notes(notes){}
};

/*
 * Main buzzer struct
 */
struct buzzer{
  bool _isPlaying = false;
  bool _pausedBetweenNotes = false;
  unsigned long _currentDuration;
  int _currentNoteInd;
  unsigned long _last_millis;
  melody* _currentMelody;
  
  void pause(){ _isPlaying = false;}
  void play(melody* m){ _currentMelody = m ;_currentNoteInd = 0; _currentDuration = 0; _isPlaying = true;}
  void setup(){ pinMode(BUZ, OUTPUT);}
  
  /*
   * Main function of this struct
   * Get time from millis() arduino function in main()
   * Playing melody given in play() function
   */
  void getTime(unsigned long milis){
    if(_isPlaying){
      _currentDuration+= milis -_last_millis;
      _last_millis = milis;
      
      // Buzzer have to wait some time between notes
      // We have to distinguish between two notes from one
      if(_pausedBetweenNotes){ 
        noTone(BUZ);
        if(_currentDuration >= distanceBetweenNotes){
          _pausedBetweenNotes = false;
          _currentDuration = 0;
        }
      }
      else{
        // Change note if last one have ended.
        if( _currentDuration >= _currentMelody->_notes[_currentNoteInd]._length){
          _currentDuration = 0;
          _currentNoteInd++;
          if(_currentNoteInd == _currentMelody->_notes_number) _currentNoteInd = 0;
          _pausedBetweenNotes = true;
        }
        // Don't change note
        else tone(BUZ, _currentMelody->_notes[_currentNoteInd]._frequency);
      }
    }
    else noTone(BUZ);   
  }
};
