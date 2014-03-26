
int beatCounter = 0;
const int NEXT_PUMP = 20/INTERVAL;
boolean waitFlag = false;

void pump() {
  
  int size = (beatCounter / NEXT_PUMP) / 4;
  if (size == 4) {
    size = 2; 
  }
  if (size == 5) {
    size = 1;
  }
  if (size == 6) {
    size = 0;
    waitFlag = true;
  }
  
  if (currentRow == 0) {
    digitalWrite(YPin[sizeofY-1], HIGH);
  }
  else {
    digitalWrite(YPin[currentRow-1], HIGH);
  }  

  for (int i=0; i<5; i++) {
  
    if (i>0) {
      digitalWrite(XPin[4+i], bitRead(pumpArray[size][currentRow], i));
      digitalWrite(XPin[4-i], bitRead(pumpArray[size][currentRow], i));
    }
    else {
      digitalWrite(XPin[4], bitRead(pumpArray[size][currentRow], 0));
    }
  
  }  
  
  digitalWrite(YPin[currentRow], LOW);
  
  currentRow++;
  if (currentRow == sizeofY) {
    currentRow = 0;    
  }
  
  if (waitFlag) {
    waitFlag = false;
    
    if (displayBPM == 93) {
      IBI = 645;
    }
    
    int waitTime = IBI-(beatCounter*INTERVAL);
    if (waitTime > 0) {
      delay(waitTime);    
    }
    beatCounter = 0; 
  }
  
  beatCounter++;
  
  //if (beatCounter == NEXT_PUMP*4) {
  //  beatCounter = 0;
   //delay(350); 
  //}
  
  
}
