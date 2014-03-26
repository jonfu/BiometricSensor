
void pattern01() {

  for (int i=0; i<sizeofY; i++) {
    if (i==0) {
      digitalWrite(YPin[sizeofY-1], LOW);
    } 
    else {
      digitalWrite(YPin[i-1], LOW);
    }
    digitalWrite(YPin[i], HIGH);
    for (int j=0; j<sizeofX; j++) {
      fadeInAndOut(XPin[j]);
		if (contact) {
                    reset();
	            return;
		}
    }  
	if (contact) {
          reset();
          return;
	}
  }
  
  reset();
  
  for (int i=sizeof(YPin)/2-1; i>0; i--) {
    /*
    if (i==0) {
      digitalWrite(YPin[sizeof(YPin)/2-1], LOW);
    } 
    else {
      digitalWrite(YPin[i-1], LOW);
    }
    */
    digitalWrite(YPin[i], LOW);
    for (int j=0; j<sizeofX; j++) {
      fadeInAndOut(XPin[j]);
		if (contact) {
  reset();
			return;
		}
    }  
	if (contact) {
  reset();
		return;
	}
  }
  
  reset();
  
}

void pattern02() {
  prepareCurrentRow();
  
  for (int i=0; i<sizeofX; i++) {
    
    //light up LEDs 35% of the time randomly
    if ( random(0, 100) < 35 ) {
      digitalWrite(XPin[i], HIGH);
    }
    
  }
  
  digitalWrite(YPin[currentRow], LOW);
  
  currentRow++;
  
  if (currentRow == sizeofY) {
    currentRow = 0;    
  }
  
  long myTime = (20000 - millis() % 20000) / 100;
  
  myTime -= 50;

  if (myTime > 0) {
    delay(myTime); 
  }
  
}

const int BANNER_INTERVAL = 270;
unsigned long lastKnownBannerRef = 0;
int bannerStep = -1;
const int bannerSeq[] = { 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4,    8, 9, 10, 11, 8, 9, 10, 11, 8, 9, 10, 11, 8, 9, 10, 11 }; //size 28+16

void pattern03() {
  
  prepareCurrentRow();
  
  if ( (millis() - lastKnownBannerRef) > BANNER_INTERVAL) {
    lastKnownBannerRef = millis();
    bannerStep++;
  }
  
  if ( (millis() - lastKnownBannerRef) > (BANNER_INTERVAL/2)) {
    return;
  }
  
  if (bannerStep == 44) {
    bannerStep = 0;
  }
  
  for (int i=0; i<9; i++) {
    int bannerPat = bannerSeq[bannerStep];
    digitalWrite(XPin[i], bitRead(avicciBannerArray[bannerPat][currentRow], i));
  }
  
    digitalWrite(YPin[currentRow], LOW);

  currentRow++;
  
  if (currentRow == sizeofY) {
    currentRow = 0;    
  }

}

void avicciBannerLoop() {
  
    prepareCurrentRow();
  
  if ( (millis() - lastKnownBannerRef) > (BANNER_INTERVAL/3)) {
    lastKnownBannerRef = millis();
    bannerStep++;
  }

  if (bannerStep == 44) {
    bannerStep = 0;
  }
  
  for (int i=0; i<9; i++) {
    int bannerPat = bannerSeq[bannerStep];
    digitalWrite(XPin[i], bitRead(avicciBannerArray2[bannerPat][currentRow], i));
  }
  
    digitalWrite(YPin[currentRow], LOW);

  currentRow++;
  
  if (currentRow == sizeofY) {
    currentRow = 0;    
  }
  
  
}


void fadeInAndOut(int pin) {
  int brightness = 255;
  int increment = -5;
  while (true) {
    brightness += increment;
    if (brightness == 255) {
      analogWrite(pin, brightness);
      break;
    }
    if (brightness == 0) {
      increment = 5;
    }
    analogWrite(pin, brightness);

	if (contact) {
		return;
	}
    delayMicroseconds(750);
  }
}
