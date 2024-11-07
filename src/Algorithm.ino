#include "TFT9341Touch.h"

tft9341touch LcdTouch(10, 9, 7, 2);

#define BLACK 0x0000
#define WHITE 0xFFFF
#define GREEN 0x00BF63
#define BLUE 0x001F
#define RED 0xF800

#define ldrPin A3
#define hygrometerPin A2
#define pumpPin 3

uint16_t x, y;
int ButtonNum;
int cursor = 0;
char string[20];
int indexString = 0;

int hygrometer;
int watering_time;

void setup() {
  Serial.begin(9600);

  LcdTouch.begin();
  LcdTouch.clearButton();
  LcdTouch.set(3780, 372, 489, 3811);
  LcdTouch.fillScreen(WHITE);

  pinMode(hygrometerPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(pumpPin, OUTPUT);

  digitalWrite(pumpPin, LOW);

  screenMain();
}

void loop() {
  ButtonNum = 0;
  int humidity = analogRead(hygrometerPin);
  int ldr = analogRead(ldrPin);
  char state[9] = " ";

  Serial.print("in loop function: ");
  Serial.print("hygrometer: ");
  Serial.println(humidity);
  Serial.print("LDR: ");
  Serial.println(ldr);

  LcdTouch.clearButton();
  LcdTouch.print(30, 20, "State:", 3, BLACK);
  LcdTouch.print(30, 50, "hygrometer: ", 3, BLACK);
  LcdTouch.print(humidity);
  LcdTouch.drawButton(999, 150, 200, 30, 30, 2, WHITE, RED, "EXIT", 5);

  if (humidity < hygrometer) { 
    if ((ldr < 20 && watering_time == 1) || (ldr > 50 && watering_time == 0)) {
      Serial.println("the pump get on");
      playWatering();
      strcpy(state, "Watering");
    }
  } else {
    strcpy(state, "Idle");
  }

  LcdTouch.print(60, 20, state, 3, BLACK);


  LcdTouch.readTouch();
  x = LcdTouch.xTouch;
  y = LcdTouch.yTouch;
  ButtonNum = LcdTouch.ButtonTouch(x, y);
  ButtonNum = LcdTouch.ButtonTouch(x, y);
  if (ButtonNum == 999) {
    screenMain();
  }

  delay(5000);
  InitDisplay();
}


void screenMain() {
  LcdTouch.print(35, 20, "Hi, I'm your", 3, BLACK);
  LcdTouch.print(35, 50, "Waterman", 3, BLUE);
  LcdTouch.print(35, 80, "Before we begin,", 3, BLACK);
  LcdTouch.print(35, 110, "I have two", 3, BLACK);
  LcdTouch.print(35, 140, "questions.", 3, BLACK);
  while (!LcdTouch.touched());
  screenInitHygrometer();
}

void screenInitHygrometer() {
  LcdTouch.fillScreen(BLACK);
  LcdTouch.print(10, 20, "What the degree", 3, WHITE);
  LcdTouch.print(10, 45, "of humidity?", 3, WHITE);
  LcdTouch.clearButton();
  LcdTouch.drawButton(1, 5, 75, 30, 30, 2, GREEN, WHITE, "1", 4);
  LcdTouch.drawButton(2, 45, 75, 30, 30, 2, GREEN, WHITE, "2", 4);
  LcdTouch.drawButton(3, 85, 75, 30, 30, 2, GREEN, WHITE, "3", 4);
  LcdTouch.drawButton(4, 125, 75, 30, 30, 2, GREEN, WHITE, "4", 4);
  LcdTouch.drawButton(5, 165, 75, 30, 30, 2, GREEN, WHITE, "5", 4);
  LcdTouch.drawButton(6, 205, 75, 30, 30, 2, GREEN, WHITE, "6", 4);
  LcdTouch.drawButton(7, 245, 75, 30, 30, 2, GREEN, WHITE, "7", 4);
  LcdTouch.drawButton(8, 285, 75, 30, 30, 2, GREEN, WHITE, "8", 4);
  LcdTouch.drawButton(9, 5, 120, 30, 30, 2, GREEN, WHITE, "9", 4);
  LcdTouch.drawButton(10, 45, 120, 30, 30, 2, GREEN, WHITE, "0", 4);
  LcdTouch.drawButton(11, 85, 120, 30, 30, 2, GREEN, WHITE, ".", 4);
  LcdTouch.drawButton(0, 10, 210, 30, 30, 2, 0x7F82BB, WHITE, "ok", 2);
  LcdTouch.setTextColor(WHITE, BLACK);

  int i = 0;
  cursor = 10;
  ButtonNum = 999;

  while (ButtonNum != 0) {
    if (LcdTouch.touched()) {
      LcdTouch.readTouch();
      x = LcdTouch.xTouch;
      y = LcdTouch.yTouch;
      ButtonNum = LcdTouch.ButtonTouch(x, y);
      keyboard(ButtonNum);
      while (string[i] != NULL) {
        LcdTouch.print(String(string[i++]));
        LcdTouch.setCursor(cursor, 170);
      }
    }
  }
  LcdTouch.setTextColor(WHITE, RED);
  LcdTouch.setCursor(cursor, 170);
  Serial.println("hygrometer to watering setup");
  hygrometer = atoi(string);
  InitWateringTime();
}

void keyboard(int ButtonNum) {
  switch (ButtonNum) {
    case 1:
      LcdTouch.setCursor(cursor += 15, 170);
      string[indexString++] = '1';
      delay(500);
      break;
    case 2:
      LcdTouch.setCursor(cursor += 15, 170);
      string[indexString++] = '2';
      delay(500);
      break;
    case 3:
      LcdTouch.setCursor(cursor += 15, 170);
      string[indexString++] = '3';
      delay(500);
      break;
    case 4:
      LcdTouch.setCursor(cursor += 15, 170);
      string[indexString++] = '4';
      delay(500);
      break;
    case 5:
      LcdTouch.setCursor(cursor += 15, 170);
      string[indexString++] = '5';
      delay(500);
      break;
    case 6:
      LcdTouch.setCursor(cursor += 15, 170);
      string[indexString++] = '6';
      delay(500);
      break;
    case 7:
      LcdTouch.setCursor(cursor += 15, 170);
      string[indexString++] = '7';
      delay(500);
      break;
    case 8:
      LcdTouch.setCursor(cursor += 15, 170);
      string[indexString++] = '8';
      delay(500);
      break;
    case 9:
      LcdTouch.setCursor(cursor += 15, 170);
      string[indexString++] = '9';
      delay(500);
      break;
    case 10:
      LcdTouch.setCursor(cursor += 15, 170);
      string[indexString++] = '0';
      delay(500);
      break;
    case 11:
      LcdTouch.setCursor(cursor += 15, 170);
      string[indexString++] = '.';
      delay(500);
      break;
  }
  while (!LcdTouch.touched());
}

void InitWateringTime() {
  LcdTouch.fillScreen(BLACK);
  LcdTouch.print(40, 20, "What is the", 3, WHITE);
  LcdTouch.print(40, 70, "Watering time?", 3, WHITE);
  LcdTouch.clearButton();
  LcdTouch.drawButton(1, 45, 120, 60, 30, 2, WHITE, YELLOW, "DAY", 4);
  LcdTouch.drawButton(2, 200, 120, 80, 30, 2, WHITE, BLACK, "NIGHT", 4);

  ButtonNum = 999;

  while (!LcdTouch.touched());  

  LcdTouch.readTouch();
  x = LcdTouch.xTouch;
  y = LcdTouch.yTouch;
  ButtonNum = LcdTouch.ButtonTouch(x, y);
  
  if (ButtonNum == 1) {
    watering_time = 1;
    Serial.println("Watering time set to DAY");
    screenOK();
  }
  if (ButtonNum == 2) {
    watering_time = 0;
    Serial.println("Watering time set to NIGHT");
    screenOK();
  }
}

void screenOK() {
  Serial.println("The client setups");
  Serial.print("Watering time: ");
  Serial.println(watering_time);
  Serial.print("Hygrometer: ");
  Serial.println(hygrometer);

  LcdTouch.fillScreen(WHITE);
  LcdTouch.print(120, 70, "OK", 10, GREEN);
  while (!LcdTouch.touched());
  InitDisplay();
}

void InitDisplay() {
  LcdTouch.begin();
  LcdTouch.fillScreen(WHITE);
  loop();
}

void playWatering() {
  digitalWrite(pumpPin, HIGH);
  delay(5000);
  digitalWrite(pumpPin, LOW);
  delay(5000);
  loop();
}


