
/*
>> Pulse Sensor Amped 1.2 <<
This code is for Pulse Sensor Amped by Joel Murphy and Yury Gitman
    www.pulsesensor.com 
    >>> Pulse Sensor purple wire goes to Analog Pin 0 <<<
Pulse Sensor sample aquisition and processing happens in the background via Timer 2 interrupt. 2mS sample rate.
PWM on pins 3 and 11 will not work when using this code, because we are using Timer 2!
The following variables are automatically updated:
Signal :    int that holds the analog signal data straight from the sensor. updated every 2mS.
IBI  :      int that holds the time interval between beats. 2mS resolution.
BPM  :      int that holds the heart rate value, derived every beat, from averaging previous 10 IBI values.
QS  :       boolean that is made true whenever Pulse is found and BPM is updated. User must reset.
Pulse :     boolean that is true when a heartbeat is sensed then false in time with pin13 LED going out.

This code is designed with output serial data to Processing sketch "PulseSensorAmped_Processing-xx"
The Processing sketch is a simple data visualizer. 
All the work to find the heartbeat and determine the heartrate happens in the code below.
Pin 13 LED will blink with heartbeat.
If you want to use pin 13 for something else, adjust the interrupt handler
It will also fade an LED on pin fadePin with every beat. Put an LED and series resistor from fadePin to GND.
Check here for detailed code walkthrough:
http://pulsesensor.myshopify.com/pages/pulse-sensor-amped-arduino-v1dot1

Code Version 1.2 by Joel Murphy & Yury Gitman  Spring 2013
This update fixes the firstBeat and secondBeat flag usage so that realistic BPM is reported.

*/


const int XPin[] = { 0, 1, 2, 4, 5, 6, 7, 8, 9 };
//const int XPin[] = { 2, 4, 5, 6, 7, 8, 9 };
//const int XPin[] = { 8, 9 };
const int YPin[] = { 10, 12, 13, 15, 16, 17, 18, 19 };

const int sizeofX = 9;
//const int sizeofX = 7;
//const int sizeofX = 2;
const int sizeofY = 8;
const int INTERVAL = 5;
const long ANIMATION_CYCLE = 3000;
const long PATTERN_CYCLE = 15000;

//  VARIABLES
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int currentRow = 0;


// these variables are volatile because they are used during the interrupt service routine!
volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 700;             // holds the time between beats, must be seeded! 
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.
volatile boolean contact = false;
int displayBPM = 93;
//unsigned long displayTimerStart = 0;
//unsigned long lockInTime = 0;
//boolean lockDisplay = false;
boolean lastContact = false;

long animationTimerStart = 0;
long patternTimerStart = 0;
int animationState = 0;
int patternState = 0;

//long analogPinResetTime;
long signalCounterResetTime;


void setup(){
  for (int i=0; i<sizeofX; i++) {
    pinMode(XPin[i], OUTPUT);
  }
  for (int i=0; i<sizeofY; i++) {
    pinMode(YPin[i], OUTPUT);
  }  
  reset(); 
  
  //Serial.begin(115200);             // we agree to talk fast!
  
  patternTimerStart = millis();
  //analogPinResetTime = millis();
  signalCounterResetTime = millis();
  
  interruptSetup();
}

/*
void loop() {
  //avicciBannerLoop();
  pattern02();
  delay(INTERVAL); 
}

*/




void loop(){

  //sendDataToProcessing('S', Signal);     // send Processing the raw Pulse Sensor data
  if (QS == true){                       // Quantified Self flag is true when arduino finds a heartbeat
        //fadeRate = 255;                  // Set 'fadeRate' Variable to 255 to fade LED with pulse
        //sendDataToProcessing('B',BPM);   // send heart rate with a 'B' prefix
        //sendDataToProcessing('Q',IBI);   // send time between beats with a 'Q' prefix
        
        //if (BPM < 115 && BPM > 60) {
        //  contact = true; 
        //}
        
        QS = false;                      // reset the Quantified Self flag for next time    
     }
     
  //if (lastContact == false && contact == true) {
  //   animationTimerStart = millis();
  //}

  //ledFadeToBeat();


    if (BPM < 120 && BPM > 60) {
       displayBPM = BPM; 
     }
     
     //if (contact && (!lockDisplay)) {
     //  lockInTime = millis();
     //  lockDisplay = true;
     //}
     
     //if (lockDisplay) {
     // if ((millis() - lockInTime) > 1500) {
     //    lockDisplay = false;
     //  }
     //  handleDisplay();
     //}
  boolean hasContact = contact;
  handleDisplay(hasContact);

  delay(INTERVAL);                             //  take a break
  
  lastContact = hasContact;
  
  
  //tried to reset analog pin, didn't work
  
  //if (millis() - analogPinResetTime > 60000) {
  // analogPinResetTime =  millis();
  // pinMode(14, INPUT_PULLUP);
  // pinMode(14, OUTPUT);
  // pinMode(14, INPUT);
  //}

}



/********** count down

void loop() {
  
  int tmpDigit = 121;
  
  int tmpCounter = 1000;
  
  while (tmpDigit > 0) {
    
    if (tmpCounter-- < 0) {
      tmpCounter = 1000;
      tmpDigit--;
    }
    displayDigits(tmpDigit);
    delay(1);
  }
  
}

**************/



/*

void ledFadeToBeat(){
    fadeRate -= 15;                         //  set LED fade value
    fadeRate = constrain(fadeRate,0,255);   //  keep LED fade value from going into negative numbers!
    analogWrite(fadePin,fadeRate);          //  fade LED
  }
  



void sendDataToProcessing(char symbol, int data ){
    Serial.print(symbol);                // symbol prefix tells Processing what type of data is coming
    Serial.println(data);                // the data to send culminating in a carriage return
  }

*/





