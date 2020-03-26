// Display:
#include <SPI.h>
#include <TFT_ILI9163.h>
#include <User_Setup.h>

// BME280 sensor:
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEA_LEVEL_PRE (1013.25)

// define colors:
#define BLACK 0x0000
#define WHITE 0xFFFF
#define GRAY 0xBDF7
#define RED 0x1F
#define YELLOW 0x7FF
#define ORANGE 0xFBE0 
#define BROWN 0x79E0 
#define GREEN 0x7E0  
#define CYAN 0xFFE0
#define BLUE 0xF800
#define PINK 0xF81F

// Initialize display library:
TFT_ILI9163 tft = TFT_ILI9163(160,128);
// Initialize BME280:
Adafruit_BME280 bme;

unsigned long targetTime = 0;

void clearDisp(int color){
  for(int i = 0; i < 160; i++){
    tft.drawFastVLine(i,0, tft.height(), color);
  }
}

int a[5];
int b[5];

int c[5] = {0,0,0,0,0};

int cursorPos = 0;

// joystick
int joyY = analogRead(A1);
int button = analogRead(A2);
bool coolDown = false;
int pravilni = 0;
bool konec = false;

void setup(){
  // basic display settings:
  tft.init();
  tft.setRotation(3);
  clearDisp(BLACK);

  // turn on display backlight:
  pinMode(5, OUTPUT);
  digitalWrite(5,HIGH);

  // set joystick pins:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  // random:
  randomSeed(analogRead(A7));
  for (int i = 0; i < 5; i++)
    a[i] = random(0,100);
  for (int i = 0; i < 5; i++)
    b[i] = random(0,100);

  // print the starting numbers:
  int x = 5;
  int y = 5;
  for (int i = 0; i < 5; i++) {
    drawCalculation(i, x, y);
    y += 20;
  }

  // counter for fps
  targetTime = millis() + 1000;

  // serial monitor
  Serial.begin(9200);
}

int num = 0;
void loop(){
  if (!konec){
    joyY = analogRead(A1);
    if (joyY == 1023)
      num -= 2;
    else if (joyY > 510)
      num -= 1;
  
    if (joyY == 0)
      num += 2;
    else if (joyY < 500)
      num += 1;
  
    if (num > 200)
      num = 200;
    else if (num < 0)
      num = 0;
    
    drawCalculation(cursorPos, 5, 5 + cursorPos*20);
    String tmp = String(num);
    while(tmp.length() < 3)
      tmp = "0" + tmp;
    tft.print(tmp);  
  }

  if (!konec && analogRead(A2) == 0 && !coolDown && cursorPos <= 4){
    if (num == a[cursorPos] + b[cursorPos]){
      drawCalculation(cursorPos, 5, 5 + cursorPos*20);
      String tmp = String(num);
      while(tmp.length() < 3)
        tmp = "0" + tmp;
      tft.print(tmp); 
      tft.setTextColor(GREEN, BLACK);
      tft.print(" pravilno");
      pravilni++;
    } else {
      drawCalculation(cursorPos, 5, 5 + cursorPos*20);
      String tmp = String(num);
      while(tmp.length() < 3)
        tmp = "0" + tmp;
      tft.print(tmp); 
      tft.setTextColor(RED, BLACK);
      tft.print(" narobe");
    }

    cursorPos++;
    num = 0;
    coolDown = true;
    targetTime = millis() + 500;
  }

  if (targetTime < millis()){
    coolDown = false;
  }

  if (cursorPos == 5 && !konec){
    tft.setCursor(5, 5 + cursorPos*20);
    tft.setTextColor(CYAN, BLACK);
    tft.print("pravilnih: ");
    tft.print(pravilni);
    tft.print("/5");
    konec = true;
    Serial.println("narisan rezultat");
  }

  delay(70);
  
}

void drawCalculation(int line, int x, int y){
  tft.setTextColor(WHITE,BLACK);
  tft.setCursor(x, y);
  tft.setTextFont(2.2);
  tft.print(a[line]);
  tft.print(" + ");
  tft.print(b[line]);
  tft.print(" = ");
}
