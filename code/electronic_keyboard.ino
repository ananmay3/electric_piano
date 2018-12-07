#include "pitches.h"
int sensorPin = 0;
int ultraPin = 1;
int TonePin = 8;
int ultraButton = 3;
int recordButton = 4;
int playbackButton = 5;
int halfStepUpButton = 7;
int halfStepDownButton = 13;
int furEliseButton = 9;
int ledPin = 6;
// int note_values[] = {262, 294, 330, 349, 392, 440, 494}; // C, D, E, F, G, A, B
// int sharp_note_values[] = {277, 311, 349, 370, 415, 466, 523}; // C#, D#, F, F#, G#, A#, C
const int trigPin = 11;
const int echoPin = 12;
const int shift = 25;
boolean ultraOn = false;
boolean record = false;
boolean playback = false;
boolean halfStepUp = false;
boolean halfStepDown = false;
int shiftconst = 0;
boolean constShiftMode = false;

struct node {
  float value;
  node* next;
};

class arr {
public:
  node* head;
  node* tail;
  arr() {
    head = NULL;
    tail = NULL;
  }

  void add(float val) {

    node* newNode = new node;
    newNode->value = val;

    if (head == NULL) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      tail = tail->next;
    }
  }
  int playBack() {
    node* temp = new node;
    for (temp = head; temp != NULL; temp = temp->next) {
      if (temp->value == 0) {
        noTone(8);
      } else {
       tone(8, temp->value);
      }
      delay(50);
    }
    delay(50);
    return 0;
  }
};

arr newarr;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ultraButton, INPUT);
  pinMode(recordButton, INPUT);
  pinMode(playbackButton, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(halfStepUpButton, INPUT);
  pinMode(halfStepDownButton, INPUT);
  pinMode(furEliseButton, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

   int sensorValue;
   float ultraValue;
   float shiftVal = 0;
   
   if (digitalRead(furEliseButton)) {
    if (!record and !ultraOn) {
      furElise();
    }
   }

   if (digitalRead(recordButton)) {
    record = !record;
    
    if (record == true) {
      
      if (newarr.head != NULL) {
        newarr.head = NULL;
        newarr.tail = NULL;
      }
      
      playback = false;
      digitalWrite(ledPin, HIGH);
      
    }
    if (record == false) {
      
      playback = true;
      digitalWrite(ledPin, LOW);
      
    }
    
    delay(500);
    
   }
   
   if (playback == true) {
    
    if (digitalRead(playbackButton)) {
      
      digitalWrite(ledPin, HIGH);
      int x = newarr.playBack();
      digitalWrite(ledPin, LOW);
      
    }
   }
   
//   Serial.print();
//   Serial.println();
   
   if (digitalRead(ultraButton)) {
    
    ultraOn = !ultraOn;
    if (ultraOn == false) {
      constShiftMode = false;
      shiftconst = 0;
    }
    delay(500);
    
   }

   if (ultraOn) {
    if (digitalRead(furEliseButton) and constShiftMode == false) {
      constShiftMode = true;
      shiftconst = getShift();
    }
    
    shiftVal = getShift();

    if (constShiftMode) {
      shiftVal = shiftconst;
    }
    
   }
         
   sensorValue = analogRead(sensorPin);
   delay(10);
   int sensorValueTest = analogRead(sensorPin);

   Serial.print(sensorValue);
   Serial.println();
   
   /*Serial.print(digitalRead(playbackButton));
   Serial.println(); */

   halfStepUp = digitalRead(halfStepUpButton);
   halfStepDown = digitalRead(halfStepDownButton);

   float note = 0.0;

   if (sensorValue >= 350 and sensorValue <= 384) {

//    if (halfStepUp) {
//      note = NOTE_CS4; //C#
//    } else {
//      note = NOTE_C4; // C
//    }

    if (halfStepUp) {
      note = NOTE_C5; // C
    } else if (halfStepDown) {
      note = NOTE_A4;
    } else {
      note = NOTE_B4; // B
    }
    
   } else if (sensorValue > 384 and sensorValue <= 396 and sensorValueTest <= 396) {
    
//    if (halfStepUp) {
//      note = NOTE_DS4; // D#
//    } else {
//      note = NOTE_D4; // D
//    }
    if (halfStepUp) {
      note = NOTE_AS4; // A#
    } else if (halfStepDown) {
      note = NOTE_GS4;
    } else {
      note = NOTE_A4; // A
    }
    
   } else if (sensorValue > 396 and sensorValue < 409) {
    
//    if (halfStep) {
//      note = NOTE_F4; // F
//    } else {
//      note = NOTE_E4; // E
//    }
    if (halfStepUp) {
      note = NOTE_GS4; // G#
    } else if (halfStepDown) {
      note = NOTE_FS4;
    } else {
      note = NOTE_G4; // G
    }
    
   } else if (sensorValue >= 409 and sensorValue <= 422) {
    
    if (halfStepUp) {
      note = NOTE_FS4; // F#
    } else if (halfStepDown) {
      note = NOTE_E4;
    } else {
      note = NOTE_F4; // F
    }
    
   } else if (sensorValue > 422 and sensorValue <= 450) {
    
//    if (halfStep) {
//      note = NOTE_GS4; // G#
//    } else {
//      note = NOTE_G4; // G
//    }
    if (halfStepUp) {
      note = NOTE_F4; // F
    } else if (halfStepDown) {
      note = NOTE_DS4;
    } else {
      note = NOTE_E4; // E
    }
    
   } else if (sensorValue > 450 and sensorValue <= 520) {
    
//    if (halfStep) {
//      note = NOTE_AS4; // A#
//    } else {
//      note = NOTE_A4; // A
//    }
    if (halfStepUp) {
      note = NOTE_DS4; // D#
    } else if (halfStepDown) {
      note = NOTE_CS4;
    } else {
      note = NOTE_D4; // D
    }
    
   } else if (sensorValue > 520 and sensorValue <= 570) {
    
//    if (halfStep) {
//      note = NOTE_C5 // C
//    } else {
//      note = NOTE_B4; // B
//    }
    if (halfStepUp) {
      note = NOTE_CS4; //C#
    } else if (halfStepDown) {
      note = NOTE_B3;
    } else {
      note = NOTE_C4; // C
    }
    
   }
   
   if (note == 0) {
    
    noTone(8);
    
    if (record == true) {
      newarr.add(note);
    }
    
   } else {
    
    tone(8, note + shiftVal);
    
    if (record == true) {
      newarr.add(note + shiftVal);
    }
    
   }
   
   delay(50);
   
}

float getShift() {

  float echoTime;
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);

  return echoTime / shift;
}

void furElise() {
  int notesLine1[] = {NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_B3, NOTE_D4, NOTE_C4, NOTE_A3};
  int notesLine2[] = {NOTE_C4, NOTE_E4, NOTE_A4, NOTE_B4};
  int notesLine3[] = {NOTE_E4, NOTE_A4, NOTE_B4, NOTE_C5};
  int notesLine4[] = {NOTE_E4, NOTE_C5, NOTE_B4, NOTE_A4};
  int notesLine5[] = {NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5};
  int notesLine6[] = {NOTE_G4, NOTE_F5, NOTE_E5, NOTE_D5};
  int notesLine7[] = {NOTE_F4, NOTE_E5, NOTE_D5, NOTE_C5};
  int notesLine8[] = {NOTE_E4, NOTE_D5, NOTE_C5, NOTE_B4};

  int i = 0;
  int inval = 250;
  int outval = 500;

  for (i = 0; i < sizeof(notesLine1) / sizeof(int); i++) {
    tone(8, notesLine1[i]);
    delay(inval);
  }
  
  delay(outval);

  for (i = 0; i < sizeof(notesLine2) / sizeof(int); i++) {
    tone(8, notesLine2[i]); 
    delay(inval);
  }
  delay(outval);

  for (i = 0; i < sizeof(notesLine3) / sizeof(int); i++) {
    tone(8, notesLine3[i]); 
    delay(inval);
  }
  delay(outval);

  for (i = 0; i < sizeof(notesLine1) / sizeof(int); i++) {
    tone(8, notesLine1[i]); 
    delay(inval);
  }
  delay(outval);

  for (i = 0; i < sizeof(notesLine2) / sizeof(int); i++) {
    tone(8, notesLine2[i]); 
    delay(inval);
  }
  delay(outval);

  for (i = 0; i < sizeof(notesLine4) / sizeof(int); i++) {
    tone(8, notesLine4[i]);
    delay(inval);
  }
  delay(outval);

  for (i = 0; i < 4; i++) {
    tone(8, notesLine5[i]); 
    delay(inval);
  }
  delay(outval);

  for (i = 0; i < 4; i++) {
    tone(8, notesLine6[i]); 
    delay(inval);
  }
  delay(outval);

  for (i = 0; i < 4; i++) {
    tone(8, notesLine7[i]); 
    delay(inval);
  }
  delay(outval);

  for (i = 0; i < 4; i++) {
    tone(8, notesLine8[i]); 
    delay(inval);
  }
  delay(2*outval);

  for (i = 0; i < sizeof(notesLine1) / sizeof(int); i++) {
    tone(8, notesLine1[i]); 
    delay(inval);
  }
  delay(outval);

  for (i = 0; i < sizeof(notesLine2) / sizeof(int); i++) {
    tone(8, notesLine2[i]); 
    delay(inval);
  }
  delay(outval);

  for (i = 0; i < sizeof(notesLine3) / sizeof(int); i++) {
    tone(8, notesLine3[i]); 
    delay(inval);
  }
  delay(outval);

  for (i = 0; i < sizeof(notesLine1) / sizeof(int); i++) {
    tone(8, notesLine1[i]); 
    delay(inval);
  }
  delay(outval);

  for (i = 0; i < sizeof(notesLine2) / sizeof(int); i++) {
    tone(8, notesLine2[i]); 
    delay(inval);
  }
  delay(outval);

  for (i = 0; i < sizeof(notesLine4) / sizeof(int); i++) {
    tone(8, notesLine4[i]); 
    delay(inval);
  }
  delay(outval);
  
}
