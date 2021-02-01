#include "buzzer.h"
#include "ledMatrix.h"

/* ===============================================
 * ================= MELODIES ====================
 * ===============================================
  */

note PeterGunn[48] = {
                     note(NOTE_F3, eightNote),note(NOTE_F3, eightNote), note(NOTE_G3, eightNote), note(NOTE_F3, eightNote),
                     note(NOTE_GS3, eightNote), note(NOTE_F3, eightNote), note(NOTE_AS3, eightNote), note(NOTE_GS3, eightNote),
                     
                     note(NOTE_DS4, halfNote), note(NOTE_C4, halfNote),
                     
                     note(NOTE_F3, eightNote),note(NOTE_F3, eightNote), note(NOTE_G3, eightNote), note(NOTE_F3, eightNote),
                     note(NOTE_GS3, eightNote), note(NOTE_F3, eightNote), note(NOTE_AS3, eightNote), note(NOTE_GS3, eightNote),
                     
                     note(NOTE_DS4, wholeNote),
                     
                     note(NOTE_C5, eightNote),note(NOTE_FS4, eightNote), note(NOTE_G3, eightNote), note(NOTE_F3, eightNote),
                     note(NOTE_GS3,eightNote), note(NOTE_F3, eightNote), note(NOTE_AS3, eightNote), note(NOTE_GS3, eightNote),

                     note(NOTE_F3, eightNote), note(NOTE_C4, eightNote), note(NOTE_DS4, eightNote), note(NOTE_F4, eightNote),
                     note(NOTE_FS4, quarterNote), note(NOTE_FS4, eightNote), note(NOTE_FS4, eightNote),

                     note(NOTE_FS4, quarterNote), note(NOTE_F4, eightNote), note(NOTE_DS4, eightNote),
                     note(NOTE_A3, quarterNote), note(NOTE_FS3, eightNote), note(NOTE_A3, eightNote),

                     note(NOTE_E3, eightNote),note(NOTE_F3, eightNote), note(NOTE_G3, eightNote), note(NOTE_F3, eightNote),
                     note(NOTE_GS3, eightNote), note(NOTE_F3, eightNote), note(NOTE_AS3, eightNote), note(NOTE_GS3, eightNote),
                     };                    
melody blues_brothers_PeterGunn(48, PeterGunn);

note kurki3[14] = {note(NOTE_D4, eightNote), note(NOTE_D4, eightNote), note(NOTE_A4, eightNote), note(NOTE_A4, eightNote),
                   note(NOTE_B4, eightNote), note(NOTE_B4, eightNote), note(NOTE_A4, quarterNote),
                   note(NOTE_G4, eightNote), note(NOTE_G4, eightNote), note(NOTE_FS4, eightNote), note(NOTE_FS4, eightNote),
                   note(NOTE_E4, eightNote), note(NOTE_E4, eightNote), note(NOTE_D4, quarterNote)};
melody kurki_trzy(14, kurki3);

note policeSirens[2] = {note(NOTE_GS4, eightNote), note(NOTE_E4, eightNote)};
melody police_sirens(2, policeSirens);


/* ===============================================
 * =============== ANIMATIONS ====================
 * ===============================================
  */
  
frame _happyFace[3] = {frame(1000, 0x0008640202640800), frame(2000, 0x0864020264080000), frame(1000, 0x0000086402026408)};
animation happyFace(3, _happyFace);

frame _bluesFace[5] = {frame(500, 0x0080800000808000), frame(500, 0xc02020c0c02020c0),frame(500, 0xe09090e0e09090e0),frame(500, 0x7048487070484870),frame(10000, 0x3824243838242438)};
animation bluesFace(5, _bluesFace);
