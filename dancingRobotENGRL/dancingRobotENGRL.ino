/*
 * Ben Tan, Guillermo Teran, and Daniel Walsh
 * 
 * All songs are done by Robson Couto at https://dragaosemchama.com/en/2019/02/songs-for-arduino/
 * 
 */

#include <Servo.h>

//initialize all servos
Servo rF; //rightFoot
Servo rT; //rightThigh
Servo lF; //leftFoot
Servo lT; //leftThigh

//create globals for our components
int buzzer = 8;
int led1 = 6;
int led2 = 4;
int button1 = 2;
int button2 = 12;
int button3 = 13;

//button trackers for each button
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

//global variables to keep track of place in songs
int tempo = 0;
int notes = 0;
int wholenote = 0;
int divider = 0;
int noteDuration = 0;


//all notes done by Robson Cuoto at https://dragaosemchama.com/en/2019/02/songs-for-arduino/
#define NOTE_B0  31 
#define NOTE_C1  33 
#define NOTE_CS1 35 
#define NOTE_D1  37 
#define NOTE_DS1 39 
#define NOTE_E1  41 
#define NOTE_F1  44
#define NOTE_FS1 46 
#define NOTE_G1  49 
#define NOTE_GS1 52 
#define NOTE_A1  55 
#define NOTE_AS1 58 
#define NOTE_B1  62 
#define NOTE_C2  65
#define NOTE_CS2 69 
#define NOTE_D2  73 
#define NOTE_DS2 78 
#define NOTE_E2  82 
#define NOTE_F2  87 
#define NOTE_FS2 93 
#define NOTE_G2  98
#define NOTE_GS2 104 
#define NOTE_A2  110 
#define NOTE_AS2 117 
#define NOTE_B2  123 
#define NOTE_C3  131 
#define NOTE_CS3 139 
#define NOTE_D3  147
#define NOTE_DS3 156 
#define NOTE_E3  165 
#define NOTE_F3  175 
#define NOTE_FS3 185 
#define NOTE_G3  196 
#define NOTE_GS3 208 
#define NOTE_A3  220 
#define NOTE_AS3 233 
#define NOTE_B3  247 
#define NOTE_C4  262 
#define NOTE_CS4 277 
#define NOTE_D4  294 
#define NOTE_DS4 311 
#define NOTE_E4  330
#define NOTE_F4  349 
#define NOTE_FS4 370 
#define NOTE_G4  392 
#define NOTE_GS4 415 
#define NOTE_A4  440 
#define NOTE_AS4 466 
#define NOTE_B4  494
#define NOTE_C5  523 
#define NOTE_CS5 554 
#define NOTE_D5  587 
#define NOTE_DS5 622 
#define NOTE_E5  659 
#define NOTE_F5  698 
#define NOTE_FS5 740 
#define NOTE_G5  784 
#define NOTE_GS5 831 
#define NOTE_A5  880 
#define NOTE_AS5 932 
#define NOTE_B5  988 
#define NOTE_C6  1047 
#define NOTE_CS6 1109
#define NOTE_D6  1175 
#define NOTE_DS6 1245 
#define NOTE_E6  1319 
#define NOTE_F6  1397 
#define NOTE_FS6 1480 
#define NOTE_G6  1568 
#define NOTE_GS6 1661
#define NOTE_A6  1760 
#define NOTE_AS6 1865 
#define NOTE_B6  1976 
#define NOTE_C7  2093 
#define NOTE_CS7 2217 
#define NOTE_D7  2349 
#define NOTE_DS7 2489
#define NOTE_E7  2637 
#define NOTE_F7  2794 
#define NOTE_FS7 2960 
#define NOTE_G7  3136 
#define NOTE_GS7 3322 
#define NOTE_A7  3520
#define NOTE_AS7 3729   
#define NOTE_B7  3951 
#define NOTE_C8  4186 
#define NOTE_CS8 4435 
#define NOTE_D8  4699 
#define NOTE_DS8 4978 
#define REST      0

//gloabal varibles for servo location
int pos = 0;
int pos1 = 0;




void setup() {

  //initalize all servos
  rF.attach(9);
  rT.attach(5);
  lF.attach(3);
  lT.attach(11);

  //move servos to default locations
  lF.write(10);
  lT.write(90);
  rT.write(105);
  rF.write(180);

  //initailze all components
  pinMode(buzzer, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);

  
}

void loop() {
  // put your main code here, to run repeatedly:

  //checking which button is pressed
  buttonState1 = digitalRead(button1);
  buttonState2 = digitalRead(button2);
  buttonState3 = digitalRead(button3);

  
  //if button one is pressed, plays take on me then resets
  if(buttonState1 == 1){
    buttonState2 = 0;
    buttonState3 = 0;
    takeOnMe();
    defaultPos();
    exit(0);

  //if button two is pressed, plays cantina band
  }else if(buttonState2 == 1){
    buttonState1 = 0;
    buttonState3 = 0;
    cantinaBand();
    defaultPos();
    exit(0);

  //if button three is pressed, it plays the mii theme song
  }else if(buttonState3 == 1){
    buttonState2 = 0;
    buttonState1 = 0;
    miiTheme();
    defaultPos();
    exit(0);
  }
  
}

//sets the legs back to defualt position and turns off the lights
void defaultPos(){
 
  lF.write(10);
  lT.write(90);
  rT.write(105);
  rF.write(180);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  
  delay(1000);
}

//moves the given servo to the given position from read position
void posMove(Servo sr, int pos, int pos1){

  int difference = pos - pos1;
  int i;

  //moves forward if positive difference
  if(difference > 0){
    for(i = 0; i < difference; i++, pos--){
      sr.write(pos);
    }

  //moves backward if negative difference
  }else{
    for(i = 0; i < difference; i++, pos++){
      sr.write(pos);
    }
  }
}


//take on me array by Robson Couto at https://dragaosemchama.com/en/2019/02/songs-for-arduino/
int aHaMelody[] = {

  // Take on me, by A-ha

  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  
};

//cantina band array by Robson Couto at https://dragaosemchama.com/en/2019/02/songs-for-arduino/
int cantinaMelody[] = {
  
  NOTE_B4,-4, NOTE_E5,-4, NOTE_B4,-4, NOTE_E5,-4, 
  NOTE_B4,8,  NOTE_E5,-4, NOTE_B4,8, REST,8,  NOTE_AS4,8, NOTE_B4,8, 
  NOTE_B4,8,  NOTE_AS4,8, NOTE_B4,8, NOTE_A4,8, REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_G4,8,
  NOTE_G4,4,  NOTE_E4,-2, 
  NOTE_B4,-4, NOTE_E5,-4, NOTE_B4,-4, NOTE_E5,-4, 
  NOTE_B4,8,  NOTE_E5,-4, NOTE_B4,8, REST,8,  NOTE_AS4,8, NOTE_B4,8,

  NOTE_A4,-4, NOTE_A4,-4, NOTE_GS4,8, NOTE_A4,-4,
  NOTE_D5,8,  NOTE_C5,-4, NOTE_B4,-4, NOTE_A4,-4,
  NOTE_B4,-4, NOTE_E5,-4, NOTE_B4,-4, NOTE_E5,-4, 
  NOTE_B4,8,  NOTE_E5,-4, NOTE_B4,8, REST,8,  NOTE_AS4,8, NOTE_B4,8,
  NOTE_D5,4, NOTE_D5,-4, NOTE_B4,8, NOTE_A4,-4,
  NOTE_G4,-4, NOTE_E4,-2,
  NOTE_E4, 2, NOTE_G4,2,
  NOTE_B4, 2, NOTE_D5,2,

  NOTE_F5, -4, NOTE_E5,-4, NOTE_AS4,8, NOTE_AS4,8, NOTE_B4,4, NOTE_G4,4, 
  
};


//mii theme song array by Robson Couto at https://dragaosemchama.com/en/2019/02/songs-for-arduino/
int miiMelody[] = {
   
  NOTE_FS4,8, REST,8, NOTE_A4,8, NOTE_CS5,8, REST,8,NOTE_A4,8, REST,8, NOTE_FS4,8, //1
  NOTE_D4,8, NOTE_D4,8, NOTE_D4,8, REST,8, REST,4, REST,8, NOTE_CS4,8,
  NOTE_D4,8, NOTE_FS4,8, NOTE_A4,8, NOTE_CS5,8, REST,8, NOTE_A4,8, REST,8, NOTE_F4,8,
  NOTE_E5,-4, NOTE_DS5,8, NOTE_D5,8, REST,8, REST,4,
  
  NOTE_GS4,8, REST,8, NOTE_CS5,8, NOTE_FS4,8, REST,8,NOTE_CS5,8, REST,8, NOTE_GS4,8, //5
  REST,8, NOTE_CS5,8, NOTE_G4,8, NOTE_FS4,8, REST,8, NOTE_E4,8, REST,8,
  NOTE_E4,8, NOTE_E4,8, NOTE_E4,8, REST,8, REST,4, NOTE_E4,8, NOTE_E4,8,
  NOTE_E4,8, REST,8, REST,4, NOTE_DS4,8, NOTE_D4,8, 

  NOTE_CS4,8, REST,8, NOTE_A4,8, NOTE_CS5,8, REST,8,NOTE_A4,8, REST,8, NOTE_FS4,8, //9
  NOTE_D4,8, NOTE_D4,8, NOTE_D4,8, REST,8, NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, REST,8,
  REST,8, NOTE_FS4,8, NOTE_A4,8, NOTE_CS5,8, REST,8, NOTE_A4,8, REST,8, NOTE_F4,8,
  NOTE_E5,2, NOTE_D5,8, REST,8, REST,4,

  NOTE_B4,8, NOTE_G4,8, NOTE_D4,8, NOTE_CS4,4, NOTE_B4,8, NOTE_G4,8, NOTE_CS4,8, //13
  NOTE_A4,8, NOTE_FS4,8, NOTE_C4,8, NOTE_B3,4, NOTE_F4,8, NOTE_D4,8, NOTE_B3,8,
  NOTE_E4,8, NOTE_E4,8, NOTE_E4,8, REST,4, REST,4, NOTE_AS4,4,
  NOTE_CS5,8, NOTE_D5,8, NOTE_FS5,8, NOTE_A5,8, REST,8, REST,4, 

  REST,2, NOTE_A3,4, NOTE_AS3,4, //17 
  NOTE_A3,-4, NOTE_A3,8, NOTE_A3,2,
  REST,4, NOTE_A3,8, NOTE_AS3,8, NOTE_A3,8, NOTE_F4,4, NOTE_C4,8,
  NOTE_A3,-4, NOTE_A3,8, NOTE_A3,2,

  REST,2, NOTE_B3,4, NOTE_C4,4, //21
  NOTE_CS4,-4, NOTE_C4,8, NOTE_CS4,2,
  REST,4, NOTE_CS4,8, NOTE_C4,8, NOTE_CS4,8, NOTE_GS4,4, NOTE_DS4,8,
  NOTE_CS4,-4, NOTE_DS4,8, NOTE_B3,1,
  
  NOTE_E4,4, NOTE_E4,4, NOTE_E4,4, REST,8,//25
   
};

//global to keep track of what beat the song is on
int curMove = 0;

//array of what degree to move servo to
int dance[] = {
  
  135, 90, 150, 105,
  45, 90, 60, 105,
};


//array of which servo to move
Servo moves[]{

  lT, lT, rT, rT,
  lT, lT, rT, rT,
};



void takeOnMe(){

  tempo = 140;


  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  notes = sizeof(aHaMelody) / sizeof(aHaMelody[0]) / 2;

  // this calculates the duration of a whole note in ms
  wholenote = (60000 * 4) / tempo;

  divider = 0;
  noteDuration = 0;

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2, curMove++) {

    // calculates the duration of each note
    divider = aHaMelody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, aHaMelody[thisNote], noteDuration * 0.9);

    //moves servo to desired position from current
    posMove(moves[curMove % 8], moves[curMove].read(), dance[curMove % 8]);

    //changes the leds
    if(curMove % 2 == 0){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
    }else{
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
    }

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
  
    
}


void cantinaBand(){

  tempo = 140;
  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int notes = sizeof(cantinaMelody) / sizeof(cantinaMelody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;
  
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2, curMove++) {

    // calculates the duration of each note
    divider = cantinaMelody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, cantinaMelody[thisNote], noteDuration * 0.9);

    //moves servo to desired position from current
    posMove(moves[curMove % 8], moves[curMove].read(), dance[curMove % 8]);

    //changes the leds
    if(curMove % 2 == 0){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
    }else{
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
    }

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
  
    
}

void miiTheme(){

  tempo = 114;

  int notes = sizeof(miiMelody) / sizeof(miiMelody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;
  
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2, curMove++) {

    // calculates the duration of each note
    divider = miiMelody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, miiMelody[thisNote], noteDuration * 0.9);

    //moves servo to desired position from current
    posMove(moves[curMove % 8], moves[curMove].read(), dance[curMove % 8]);

    //changes the leds
    if(curMove % 2 == 0){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
    }else{
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
    }

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
  
    
}
