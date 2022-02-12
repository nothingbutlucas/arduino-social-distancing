#include "LedControl.h"
// For ultrasonic sensor

int TRIG = 6;
int ECHO = 9;
int DURACION;
int DISTANCIA;

// For matriz control

int DIN = 11;
int CLK = 13;
int CS = 10;
int DISPOSITIVO = 1;

LedControl lc=LedControl(DIN,CLK,CS,DISPOSITIVO);

byte smile[8] = {
  B00000000,
  B00000000,
  B00100100,
  B00000000,
  B00000000,
  B01000010,
  B00111100,
  B00000000
};

byte sad[8] = {
  B00000000,
  B00000000,
  B00100100,
  B00000000,
  B00000000,
  B00111100,
  B01000010,
  B00000000
};

byte died[8] = {
  B00000000,
  B01000010,
  B00100100,
  B00000000,
  B00000000,
  B00111100,
  B01000010,
  B00000000
};

byte full[8] = {
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111
};

const byte metros[][8] = {
{
  B01111000,
  B11001100,
  B00001100,
  B00111000,
  B01100000,
  B11001100,
  B11111100,
  B00000000
},{
  B11000110,
  B11101110,
  B11111110,
  B11111110,
  B11010110,
  B11000110,
  B11000110,
  B00000000
},{
  B11111110,
  B01100010,
  B01101000,
  B01111000,
  B01101000,
  B01100010,
  B11111110,
  B00000000
},{
  B11111100,
  B10110100,
  B00110000,
  B00110000,
  B00110000,
  B00110000,
  B01111000,
  B00000000
},{
  B11111100,
  B01100110,
  B01100110,
  B01111100,
  B01101100,
  B01100110,
  B11100110,
  B00000000
},{
  B00111000,
  B01101100,
  B11000110,
  B11000110,
  B11000110,
  B01101100,
  B00111000,
  B00000000
},{
  B01111000,
  B11001100,
  B11100000,
  B01110000,
  B00011100,
  B11001100,
  B01111000,
  B00000000
}};
const int metros_len = sizeof(metros)/8;

void setup()
{
  lc.shutdown(0,false);
  lc.setIntensity(0,1);
  lc.clearDisplay(0);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}


void show_smile(){
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,smile[i]);
}
}

void show_sad(){
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,sad[i]);
}
}

void show_angry(){
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,died[i]);
}
}

void show_full(){
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,full[i]);
}
}

void show_image(const byte* image){
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      lc.setLed(0, i, j, bitRead(image[i], 7 - j));
    }
  }
}

int i = 0;

void loop()
{
  
  digitalWrite(TRIG, HIGH);
  delay(1);
  digitalWrite(TRIG, LOW);
  
  DURACION = pulseIn(ECHO, HIGH);
  DISTANCIA = DURACION / 58.2;
  delay(200);
  int i = 0;
  if (DISTANCIA > 200){
    lc.setIntensity(0,2);
    show_smile(); 
    delay(500);
  }
  if (DISTANCIA < 200 && DISTANCIA >= 100){
    lc.setIntensity(0,4);
    show_sad();
    delay(500);
  }
  if (DISTANCIA < 100 && DISTANCIA >= 50) {
    lc.setIntensity(0,6);
    show_angry();
    delay(500);
    }
  if (DISTANCIA < 50)
  {
    lc.setIntensity(0,10);
    for (int i=0; i < 5; i++)
    {
      show_angry();
      delay(DISTANCIA * 10);
      show_full();
      delay(DISTANCIA * 10);
      lc.clearDisplay(0);
    }
    for (int x=0; x < 7; x++)
    {
      show_image(metros[i]);
      if (++i >= metros_len ) {
        i = 0;
      }
      delay(200);
    }
    }
}
