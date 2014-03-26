
boolean skipRow3 = false;
boolean skipRow6 = false;

void displayDigits(int rate) {
  
  prepareCurrentRow();
  //reset();

  int firstDigit = rate % 10;
  int secondDigit = rate / 10;
  
  
  /*
  if (currentRow==3) {
    if (skipRow3 == false) {
     skipRow3 = true; 
    }
    else {
     skipRow3 = false; 
    }
  }
  
  if (currentRow==6) {

    if (skipRow6 == false) {
     skipRow6 = true; 
    }
    else {
     skipRow6 = false; 
    }
  
  }
  
  */
  
  if (rate <= 99) {

    setDigit(firstDigit, 5, currentRow, false);
    setDigit(secondDigit, 0, currentRow, false);

  } else { //100 and above
  
    secondDigit = secondDigit % 10;
    
    digitalWrite(XPin[0], HIGH);
    setDigit(firstDigit, 5, currentRow, false);
    setDigit(secondDigit, 1, currentRow, true);    

  }

  digitalWrite(YPin[currentRow], LOW);

  currentRow++;
  
  if (currentRow == sizeofY) {
    currentRow = 0;    
  }

}




void setDigit(int digit, int startX, int row, boolean shift) {
  


  for (int i=0; i<4; i++) {
    if (shift && i==3) {
        if (row > 0) {
          digitalWrite(XPin[startX+i], bitRead(digitArray[digit][row-1], i));
        }
    } else {
      
      //if (skipRow6 && currentRow==6 && ((startX+i)==0 || (startX+i)==2 || (startX+i)==3 || (startX+i)==5 || (startX+i)==6|| (startX+i)==8) ) {
      //  digitalWrite(XPin[startX+i], LOW);
      //} else if (skipRow3 && currentRow==3 && ( (startX+i)<3 || (startX+i)>5 ) ) {
      //  digitalWrite(XPin[startX+i], LOW);
      //} else {
        digitalWrite(XPin[startX+i], bitRead(digitArray[digit][row], i));
      //}
      
      
    }
  }
  
  
}



