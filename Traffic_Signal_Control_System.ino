#define s1_r 2 // Green  Led Pin Out
#define s1_y 3 // Yellow Led Pin Out
#define s1_g 4 // Red    Led Pin Out

#define s2_r 5 // Green  Led Pin Out
#define s2_y 6 // Yellow Led Pin Out
#define s2_g 7 // Red    Led Pin Out

#define s3_r 8 // Green  Led Pin Out
#define s3_y 9 // Yellow Led Pin Out
#define s3_g 10// Red    Led Pin Out

#define s4_r 11// Green  Led Pin Out
#define s4_y 12// Yellow Led Pin Out
#define s4_g 13// Red    Led Pin Out

int G1_time = 4;  //Set singl 1 open time
int G2_time = 6;  //Set singl 2 open time
int G3_time = 8;  //Set singl 3 open time
int G4_time = 10; //Set singl 4 open time

int Y_time = 1; //Set All singl Wait time

int Mode=0;
int Second=0;
word MilliSecond=0;

void setup(){ // put your setup code here, to run once

pinMode(s1_r, OUTPUT);
pinMode(s1_y, OUTPUT);
pinMode(s1_g, OUTPUT);

pinMode(s2_r, OUTPUT);
pinMode(s2_y, OUTPUT);
pinMode(s2_g, OUTPUT);

pinMode(s3_r, OUTPUT);
pinMode(s3_y, OUTPUT);
pinMode(s3_g, OUTPUT);

pinMode(s4_r, OUTPUT);
pinMode(s4_y, OUTPUT);
pinMode(s4_g, OUTPUT);

noInterrupts();         // disable all interrupts
TCCR1A = 0;             // set entire TCCR1A register to 0  //set timer1 interrupt at 1kHz  // 1 ms
TCCR1B = 0;             // same for TCCR1B
TCNT1  = 0;             // set timer count for 1khz increments
OCR1A = 1999;           // = (16*10^6) / (1000*8) - 1
//had to use 16 bit timer1 for this bc 1999>255, but could switch to timers 0 or 2 with larger prescaler
// turn on CTC mode
TCCR1B |= (1 << WGM12); // Set CS11 bit for 8 prescaler
TCCR1B |= (1 << CS11);  // enable timer compare interrupt
TIMSK1 |= (1 << OCIE1A);
interrupts();           // enable

Second = Y_time;
yellow(Mode);
delay(100); // Waiting for a while
}

void loop(){ 

if(Mode==0 && Second==0){Second=G1_time; Mode=1; Open(Mode);}
if(Mode==1 && Second==0){Second=Y_time;  Mode=2; yellow(Mode);}

if(Mode==2 && Second==0){Second=G2_time; Mode=3; Open(Mode);}
if(Mode==3 && Second==0){Second=Y_time;  Mode=4; yellow(Mode);}

if(Mode==4 && Second==0){Second=G3_time; Mode=5; Open(Mode);}
if(Mode==5 && Second==0){Second=Y_time;  Mode=6; yellow(Mode);}

if(Mode==6 && Second==0){Second=G4_time; Mode=7; Open(Mode);}
if(Mode==7 && Second==0){Second=Y_time;  Mode=0; yellow(Mode);}

delay(10); 
}

void yellow(int y){
digitalWrite(s1_r, 1);  
if(y==0){digitalWrite(s1_y, 1);}
       else{digitalWrite(s1_y, 0);}
digitalWrite(s1_g, 0);

digitalWrite(s2_r, 1);  
if(y==2){digitalWrite(s2_y, 1);}
       else{digitalWrite(s2_y, 0);}
digitalWrite(s2_g, 0);

digitalWrite(s3_r, 1);  
if(y==4){digitalWrite(s3_y, 1);}
       else{digitalWrite(s3_y, 0);}
digitalWrite(s3_g, 0);

digitalWrite(s4_r, 1);  
if(y==6){digitalWrite(s4_y, 1);}
       else{digitalWrite(s4_y, 0);}
digitalWrite(s4_g, 0);
}

void Open(int Set){
 
digitalWrite(s1_y, 0);
if(Set==1){digitalWrite(s1_g, 1); digitalWrite(s1_r, 0);}
       else{digitalWrite(s1_g, 0); digitalWrite(s1_r, 1);}

digitalWrite(s2_y, 0);
if(Set==3){digitalWrite(s2_g, 1); digitalWrite(s2_r, 0);}
       else{digitalWrite(s2_g, 0); digitalWrite(s2_r, 1);}
 
digitalWrite(s3_y, 0);
if(Set==5){digitalWrite(s3_g, 1); digitalWrite(s3_r, 0);}
       else{digitalWrite(s3_g, 0); digitalWrite(s3_r, 1);}

digitalWrite(s4_y, 0);
if(Set==7){digitalWrite(s4_g, 1); digitalWrite(s4_r, 0);}
       else{digitalWrite(s4_g, 0); digitalWrite(s4_r, 1);}

}

ISR(TIMER1_COMPA_vect){   
MilliSecond++;
if(MilliSecond >= 1000){MilliSecond = 0;
       Second = Second-1;
 }
}

