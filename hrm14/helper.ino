void reset() {
  for (int i=0; i<sizeofX; i++) {
    digitalWrite(XPin[i], LOW);
  }
  for (int i=0; i<sizeofY; i++) {
    digitalWrite(YPin[i], HIGH);
  }
  
}

void prepareCurrentRow() {
  
  //turn off the last row
  if (currentRow == 0) {
    digitalWrite(YPin[sizeofY-1], HIGH);
  }
  else {
    digitalWrite(YPin[currentRow-1], HIGH);
  }
  
  for (int i=0; i<sizeofX; i++) {
    digitalWrite(XPin[i], LOW);
  }
  
}

void handleDisplay(boolean hasContact) {
 
     if (hasContact) {
       
       //if (millis() < 60000 && !lastContact) {
       if (!lastContact) {
         sensedTouch();
       }
       
        if ( (millis() - animationTimerStart) > ANIMATION_CYCLE ) {
          animationTimerStart = millis();
          animationState++;
        }
        
        if (animationState > 2) {
          animationState = 0; 
        }
       
        //( (millis() - displayTimerStart) % (ANIMATION_CYCLE*3)) / ANIMATION_CYCLE
       
         switch ( animationState ) {
         case 1:
            displayDigits( displayBPM );
            break;
            
         case 2:
            pump();
            break;
            
         default:
            pulseAnimation();
            
        }
     }
     else {
       
       //if (millis() < 60000 && lastContact) {
       if (lastContact) {
         lostTouch();
       }
       
      if ( (millis() - patternTimerStart) > PATTERN_CYCLE ) {
        patternTimerStart = millis();
        patternState++;
      }
      
      if (patternState > 3) {
        patternState = 0;
      }
       
      switch ( patternState ) {
       case 1:
          pattern01();
          break;
          
       case 2:
          pattern02();
          break;      
      
       case 3:
          pattern03();
          break;       
          
       default:
          avicciBannerLoop();
      }
      
      animationTimerStart = millis();
      animationState = 0;
       
     }
  
  
}

/********** ORIGINAL with for loop

const int pulseSeqX[] = { 0, 1, 2, 3, 3, 4, 4, 4, 4, 4, 5, 5, 6, 7, 8 };
const int pulseSeqY[] = { 2, 2, 2, 3, 4, 7, 6, 4, 2, 0, 1, 2, 2, 2, 2 };
const int sizeofSeq = 15;
const int pulseFrame = 24;

void pulseAnimation() {

  for (int i=0; i<sizeofSeq; i++) {
    
    reset();

    digitalWrite(XPin[pulseSeqX[i]], HIGH);
    digitalWrite(YPin[pulseSeqY[i]], LOW);

    if (i<(sizeofSeq-1)) {
      digitalWrite(XPin[pulseSeqX[i+1]], HIGH);
      digitalWrite(YPin[pulseSeqY[i+1]], LOW);      
    }
    
    if (!contact) {
      return;
    }

    delay(pulseFrame);

  }
  
  if (!contact) {
   return; 
  }
  
  
  if (displayBPM == 93) {
    IBI = 645;
  }
  
  reset();

  //15 frames x 24 ms/frame = 360ms
  delay(constrain(IBI-360, 0, 640));

}

*******************/

const int pulseSeqX[] = { 0, 1, 2, 3, 3, 4, 4, 4, 4, 4, 5, 5, 6, 7, 8 };
const int pulseSeqY[] = { 2, 2, 2, 3, 4, 7, 6, 4, 2, 0, 1, 2, 2, 2, 2 };
const int sizeofSeq = 15;
const int pulseFrame = 24;
int pulseSeqIndex = -1;
unsigned long pulseSeqTime = 0;


void pulseAnimation() {
  
  if (pulseSeqIndex == -1) {
    pulseSeqTime = millis(); 
  }
  
  int timeSincePulseStart = millis() - pulseSeqTime;
  
  int i = timeSincePulseStart / pulseFrame;
  
  //without the for loop and delay, it causes crazy cycle interference after about 2 mins
  //for (int i=0; i<sizeofSeq; i++) {
    
    if (i < sizeofSeq) {
    
        if (i > pulseSeqIndex) {
          reset();
          pulseSeqIndex = i;
        }
        
        digitalWrite(XPin[pulseSeqX[i]], HIGH);
        digitalWrite(YPin[pulseSeqY[i]], LOW);
    
        if (i<(sizeofSeq-1)) {
          digitalWrite(XPin[pulseSeqX[i+1]], HIGH);
          digitalWrite(YPin[pulseSeqY[i+1]], LOW);      
        }
    
    }
    //delay(pulseFrame);
  //}

  if ( (timeSincePulseStart >= 360)  ) { //15x24
      reset();
      
      if (displayBPM == 93) {
        IBI = 645;
      }      
      
      int delayValue = constrain(IBI-360, 0, 640);
      
      if (timeSincePulseStart <= (360+delayValue)) {
        return;
      }
      else {
        pulseSeqIndex = -1;
      }
  }
  
}



