 // Display:
#include <SPI.h>
#include <TFT_ILI9163.h>
#include <User_Setup.h>

// BME280 Sensors
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

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

void setup(){
  // basic display settings:
  tft.init();
  tft.setRotation(3);
  clearDisp(WHITE);

  // turn on display backlight:
  pinMode(5, OUTPUT);
  digitalWrite(5,HIGH);

  Serial.begin(9600);

  // BME280:
  unsigned status = bme.begin(0x76);
  if (!status)
    Serial.println("Sensor not connected correctly");
}

int cursorY = 2;
char text[100] = "";
int index = 0;

void loop(){
  if (Serial.available() > 0) {
    char input = Serial.read();

    if (input != '\n') {
      text[index] = input;
      index++; 
    } else {
      if (text[0] == 'T') {
        printTemp(1, cursorY);
      } else {
        tft.setTextColor(BLACK,WHITE);
        tft.setCursor(1, cursorY);
        tft.setTextFont(2);
        tft.print(text); 
      }
      cursorY += 15; 

      if (cursorY > 120){
        cursorY = 2;
        clearDisp(WHITE);
      }

      index = 0;
      for (int i = 0; i < 100; i++)
        text[i] = '\0';
    }
  }
}


void printTemp(int x, int y){
  // print to display
  tft.setTextColor(BLACK,WHITE);
  tft.setCursor(1, cursorY);
  tft.setTextFont(2);
  tft.print("Temp: ");
  tft.print(bme.readTemperature());
  tft.print(" stopinj C");
}
