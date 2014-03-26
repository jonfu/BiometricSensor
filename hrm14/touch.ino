void sensedTouch() {
  
  if (useTouchAnimation) {
  
    reset();
    
    for (int i=0; i<sizeofY; i++) {
      digitalWrite(YPin[i], LOW);
      for (int j=0; j<sizeofX; j++) {
        digitalWrite(XPin[j], HIGH);
        delayMicroseconds(1500);
      }  
    }
    
    for (int i=0; i<sizeofY; i++) {
      digitalWrite(YPin[i], HIGH);
      delay(pulseFrame);
    }  
  
    delay(200);
    
    for (int j=0; j<sizeofX; j++) {
      digitalWrite(XPin[j], LOW);
    }
  
  }

}


void lostTouch() {
  
  if (useTouchAnimation) {
    
    reset();
    
    for (int i=sizeofY; i>0; i--) {
      digitalWrite(YPin[i], LOW);
      for (int j=0; j<sizeofX; j++) {
        digitalWrite(XPin[j], HIGH);
      }
      delay(pulseFrame);
      reset(); 
    }
    
    delay(200);
  }

}
