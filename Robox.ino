/*
  Arduino Mario Bros Tunes
  With Piezo Buzzer and PWM

  Connect the positive side of the Buzzer to pin 3,
  then the negative side to a 1k ohm resistor. Connect
  the other side of the 1 k ohm resistor to
  ground(GND) pin on the Arduino.

  by: Dipto Pratyaksa
  last updated: 31/3/13
*/

/*************************************************
 * Buzzers & Notes definitions
 *************************************************/

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

#define melodyPin 8

//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};

//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

/*************************************************
 * 4x4 LED Matrix definitions
 *************************************************/

//initialize the port numbers. You can easily change them here if you connected your LEDs in another way than I suggested
int led0 = 0;
int led1 = 1;
int led2 = 2;
int led3 = 3;
int led4 = 4;
int led5 = 5;
int led6 = 6;
int led7 = 7;

//the time we will wait after lighting one LED (in ms)
int time = 100;

/*************************************************
 * IR Comands definitions
 *************************************************/

#include <IRremote.h>

//aqui é declarado o dispositivo ligado a cada pino

int IR_Sensor = 11;
int L_Cooler = 12;
int R_Cooler = 13;

IRrecv irrecv(IR_Sensor);
decode_results frequencia;  

/*************************************************
 * Status and avaliability LEDs definitions
 *************************************************/

int ledStatus = 9;
int ledIdle = 10;
                   
/*************************************************
 * Proximity sensors definitions
                  

int TriggerPin = A0;
int R_PresenceEcho = A1;
int L_PresenceEcho = A3;

long duration;
long distance;

*************************************************/                                 
                   
                   
                   /**************START PROGRAM******************/

void setup(void)
{
  //Buzzers
  pinMode(8, OUTPUT);
  
  //Matrix' LEDs
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  
  //Ensures all the Matrix LEDs are off
  //off();
  
  //Enabling IR sensor
  irrecv.enableIRIn();

  //IR sensor
  pinMode(IR_Sensor, INPUT);

  //Status and avaliability LEDs
  pinMode(ledStatus, OUTPUT);
  pinMode(ledIdle, OUTPUT);

  //Coolers
  pinMode(L_Cooler, OUTPUT);
  pinMode(R_Cooler, OUTPUT);

  /*//Proximity sensors
  
  pinMode(L_PresenceEcho, INPUT);
  pinMode(R_PresenceEcho, INPUT);
  pinMode(TriggerPin, OUTPUT);

  Serial.begin(9600);

  */
  
  //Ensures all the coolers are off
  digitalWrite(L_Cooler, HIGH);
  digitalWrite(R_Cooler, HIGH);



}
void loop(){
  
  //Box is On
  digitalWrite(ledStatus, HIGH);
      
  //Sweeping for IR info
  if (irrecv.decode(&frequencia)) {
          
      if (frequencia.value == 2011249326){
        //CENTER WAS PRESSED
        digitalWrite(ledIdle, LOW);
        sing(1);
      }
      
      else if (frequencia.value == 2011259054){
        //LEFT WAS PRESSED        
        digitalWrite(ledIdle, LOW);
        Beep();
        digitalWrite(R_Cooler, LOW);
        L2R();
        L2R();
        L2R();
        //off();
        digitalWrite(R_Cooler, HIGH);
      }
      
      else if (frequencia.value == 2011271342){
        //RIGHT WAS PRESSED
        digitalWrite(ledIdle, LOW);
        Beep();
        digitalWrite(L_Cooler, LOW);
        R2L();
        R2L();
        R2L();
        //off();
        digitalWrite(L_Cooler, HIGH);
      }
      
      
      else if (frequencia.value == 2011254958){
        //UP WAS PRESSED
        digitalWrite(ledIdle, LOW);
        Beep();
        D2U();
        D2U();
        D2U();
        //off();
      }
      
      else if (frequencia.value == 2011246766){
        //DOWN WAS PRESSED
        digitalWrite(ledIdle, LOW);
        Beep();
        U2D();
        U2D();
        U2D();
        //off();
      }
      
      else if (frequencia.value == 2011298478){
        //PLAY WAS PRESSED
        digitalWrite(ledIdle, LOW);
        digitalWrite(L_Cooler, LOW);
        digitalWrite(R_Cooler, LOW);
        splash2();
        digitalWrite(L_Cooler, HIGH);
        digitalWrite(R_Cooler, HIGH);
                                      
  }
  
  // O próximo valor é lido 
  irrecv.resume(); 
  
  //Holds 0,1s to refresh
  delay(100);
  
  //Turn on avaliability LED
  digitalWrite(ledIdle, HIGH);

   splash1(); 
  }

}

/*************************************************
 * Proximidy sensors' functions


void readPresence(){

  float duration_L, distance_L, duration_R, distance_R;
  
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TriggerPin, LOW);

  duration_L = pulseIn(L_PresenceEcho, HIGH);
  duration_R = pulseIn(R_PresenceEcho, HIGH);
  
  distance_L = duration_L/2/29.1;
  distance_R = duration_R/58.2;

  Serial.print("Distance left: ");
  Serial.println(distance_L);
  Serial.print("Distance right: ");
  Serial.println(distance_R);
  }
 *************************************************/
 
/*************************************************
 * 4x4 LED Matrix functions
 *************************************************/

void U2D(){
  R1();
  delay(1);
  R2();
  delay(1);
  R3();
  delay(1);
  R4();
  delay(1);
  R1();
  delay(1);
  R2();
  delay(1);
  R3();
  delay(1);
  R4();
  delay(1);
}

void D2U(){
  R4();
  delay(1);
  R3();
  delay(1);
  R2();
  delay(1);
  R1();
  delay(1);
  R4();
  delay(1);
  R3();
  delay(1);
  R2();
  delay(1);
  R1();
  delay(1); 
}

void R2L(){
  C4();
  delay(1);
  C3();
  delay(1);
  C2();
  delay(1);
  C1();
  delay(1);
  C4();
  delay(1);
  C3();
  delay(1);
  C2();
  delay(1);
  C1();
  delay(1);
}

void L2R(){
  C1();
  delay(1);
  C2();
  delay(1);
  C3();
  delay(1);
  C4();
  delay(1);
    C1();
  delay(1);
  C2();
  delay(1);
  C3();
  delay(1);
  C4();
  delay(1); 
}


void splash2(){
  all();  //puts on all the LEDs for one second
  Beep();
  Beep();
  a();  //puts on the first LED
  b();  //puts on the second LED (turns first one off)
  c();  //...
  d();
  e();
  f();
  g();
  h();
  i();
  j();
  k();
  l();
  m();
  n();
  o();
  p();
  off();  //turns all LEDs off
}

void splash1(){
  all();  //puts on all the LEDs for one second
  a();  //puts on the first LED
  b();  //puts on the second LED (turns first one off)
  c();  //...
  d();
  e();
  f();
  g();
  h();
  i();
  j();
  k();
  l();
  m();
  n();
  o();
  p();
  off();  //turns all LEDs off
}

void all(){
  digitalWrite(led0, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, HIGH);
}

void off(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  //delay (time);
}

void R1(){
  digitalWrite(led0, LOW);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, HIGH);
  delay (time);
  }

void R2(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, HIGH);
  delay (time);
  }  

void R3(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, HIGH);
  delay (time);
  }

void R4(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);

  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, HIGH);
  delay (time);
  }  

void C1(){
  digitalWrite(led0, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  digitalWrite(led4, HIGH);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  delay (time);
  }

  void C2(){
  digitalWrite(led0, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  digitalWrite(led4, LOW);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  delay (time);
  }

  void C3(){
  digitalWrite(led0, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, LOW);
  delay (time);
  }

  void C4(){
  digitalWrite(led0, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, HIGH);
  delay (time);
  }
  
void a(){
  digitalWrite(led0, LOW);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, HIGH);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  delay (time);
}

void b(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, HIGH);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  delay (time);
}

void c(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, HIGH);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  delay (time);
}

void d(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);

  digitalWrite(led4, HIGH);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  delay (time);
}

void e(){
  digitalWrite(led0, LOW);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, LOW);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  delay (time);
}

void f(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, LOW);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  delay (time);
}

void g(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, LOW);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  delay (time);
}

void h(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);

  digitalWrite(led4, LOW);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  delay (time);
}

void i(){
  digitalWrite(led0, LOW);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, LOW);
  delay (time);
}

void j(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, LOW);
  delay (time);
}

void k(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, LOW);
  delay (time);
}

void l(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);

  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, LOW);
  delay (time);
}

void m(){
  digitalWrite(led0, LOW);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, HIGH);
  delay (time);
}

void n(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, HIGH);
  delay (time);
}

void o(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);

  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, HIGH);
  delay (time);
}

void p(){
  digitalWrite(led0, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);

  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, HIGH);
  delay (time);
}

/*************************************************
 * Buzzer & Notes functions
 *************************************************/

int song = 0;

void sing(int s) {
  // iterate over the notes of the melody:
  song = s;
  Serial.println(" 'Mario Theme'");
  int size = sizeof(melody) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {

    int noteDuration = 1000 / tempo[thisNote];

    buzz(melodyPin, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // stop the tone playing:
    buzz(melodyPin, 0, noteDuration);

    }
  }

void buzz(int targetPin, long frequency, long length) {
  all();

  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
   
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  off();

}

/*************************************************
 * IR Comands functions
 *************************************************/

int Beep(){
  digitalWrite(8, HIGH);
  delay(200);
  digitalWrite(8, LOW);
  }
