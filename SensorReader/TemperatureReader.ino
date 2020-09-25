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

void setup(){
  // basic display settings:
  tft.init();
  tft.setRotation(3);
  clearDisp(WHITE);

  // turn on display backlight:
  pinMode(5, OUTPUT);
  digitalWrite(5,HIGH);

  // counter for fps
  targetTime = millis() + 1000;

  // serial monitor
  Serial.begin(9200);

  // BME280:
  unsigned status = bme.begin(0x76);
  if (!status)
    Serial.println("Sensor not connected correctly");
}

int currSens = 0;
int currSel = 0;
bool reset = false;

void loop(){
  if(targetTime < millis()){
    targetTime = millis() + 400;

    // clearDisp not needed because the fonts have 
    // a white background already
    //clearDisp(WHITE);
    
    float temp = printTemp(currSel);
    float hum = printHumid(currSel);
    float pres = printPres(currSel);
  
    switch (currSens) {
      case 1:
        bigPrint(temp, "st. C   ");
        break;
      case 2:
        bigPrint(hum, "%         ");
        break;
      case 3:
        bigPrint(pres, "hPa");
        break;      
    }
  }
  
  if (analogRead(A1) > 509 && !reset) {
    currSel++;
    if (currSel >= 2) currSel = 2;
    reset = true;
  } else if (analogRead(A1) < 509 && !reset) {
    currSel--;
    if (currSel <= 0) currSel = 0;
    reset = true;
  } else if (analogRead(A1) == 509 && reset){
    reset = false;
  }

  if (analogRead(A2) == 0 && analogRead(A1) == 509) {
     switch (currSel) {
        case 0:
          currSens = 1;
          break;
        case 1:
          currSens = 2;
          break;
        case 2:
          currSens = 3;
     }
  }
}

float printTemp(int sel){
  float value = bme.readTemperature();
  // print to display
  tft.setTextColor(BLACK,WHITE);
  tft.setCursor(1, 5);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.print("Temp: ");
  tft.print(value);
  tft.print(" st. C");

  tft.setTextColor(RED,WHITE);
  if (sel == 0) {
    tft.print(" <-");
  } else {
    tft.print("     ");
  }

  return value;
}

float printHumid(int sel){
  float value = bme.readHumidity();
  // print to display
  tft.setTextColor(BLACK,WHITE);
  tft.setCursor(1, 20);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.print("Vlaga: ");
  tft.print(value);
  tft.print(" %");

  tft.setTextColor(RED,WHITE);
  if (sel == 1) {
    tft.print(" <-");
  } else {
    tft.print("     ");
  }

  return value;
}

float printPres(int sel){
  float value = bme.readPressure()/100.0F;
  // print to display
  tft.setTextColor(BLACK,WHITE);
  tft.setCursor(1, 35);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.print("Tlak: ");
  tft.print(value);
  tft.print(" hPa");

  tft.setTextColor(RED,WHITE);
  if (sel == 2) {
    tft.print(" <-");
  } else {
    tft.print("     ");
  }

  return value;
}

void bigPrint(float value, String unit) {
  tft.setTextColor(RED,WHITE);
  tft.setTextSize(1);
  tft.setCursor(1, 60);
  tft.setTextFont(6);
  tft.print(value);
  tft.setCursor(20, 100);
  tft.setTextFont(2);
  tft.setTextSize(2);
  tft.print(unit);
}
