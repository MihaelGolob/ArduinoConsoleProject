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

// Joystick:
#define stickX A0
#define stickY A1
#define stickSW A2

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

  // joystick pins:
  pinMode(stickX, INPUT);
  pinMode(stickY, INPUT);
  pinMode(stickSW, INPUT);

  // counter for fps
  targetTime = millis() + 1000;

  // serial monitor
  Serial.begin(9200);

  // BME280:
  unsigned status = bme.begin(0x76);
  if (!status)
    Serial.println("Sensor not connected correctly");
}
void loop(){
  /*if(targetTime < millis()){
    targetTime = millis() + 1000;

    Serial.print("X value:");
    Serial.println(analogRead(stickX));
    Serial.print("Y value:");
    Serial.println(analogRead(stickY));
    Serial.print("SW value:");
    Serial.println(analogRead(stickSW));

    Serial.println();
    
    // clearDisp not needed because the fonts have 
    // a white background already
    //clearDisp(WHITE);
  }
  */
  
  

  clearDisp(BLUE);
  int sensorX = analogRead(stickX);
  int sensorY = analogRead(stickY);
  
  int x = map( sensorX, 0, 1023, 0, 159 );
  int y = map( sensorY, 0, 1023, 0, 127 );
  
  tft.setTextColor(WHITE);
  tft.setCursor(x,y);
  tft.setTextFont(2);
  tft.print("*");
}
