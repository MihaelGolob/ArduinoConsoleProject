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
  tft.setRotation(1);
  clearDisp(WHITE);

  // turn on display backlight:
  pinMode(5, OUTPUT);
  digitalWrite(5,HIGH);

  // counter for fps
  targetTime = millis() + 1000;

  // serial monitor
  Serial.begin(9200);

  // BME280:
  unsigned status = bme.begin();
  if (!status)
    Serial.println("Sensor not connected correctly");
}

void loop(){
  if(targetTime < millis()){
    targetTime = millis() + 1000;

    // clearDisp not needed because the fonts have 
    // a white background already
    //clearDisp(WHITE);
    
    printTemp();
    printHumid();
    printAlt();
    printPres();
  }
}

void printTemp(){
  // print to display
  tft.setTextColor(BLACK,WHITE);
  tft.setCursor(1, 5);
  tft.setTextFont(2);
  tft.print("Temp: ");
  tft.print(bme.readTemperature());
  tft.print(" stopinj C");
 
  // print to serial monitor
  Serial.print("Temp: ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");
}

void printHumid(){
  // print to display
  tft.setTextColor(BLACK,WHITE);
  tft.setCursor(1, 20);
  tft.setTextFont(2);
  tft.print("Vlaga: ");
  tft.print(bme.readHumidity());
  tft.print(" %");

  // print to serial monitor
  Serial.print("Vlaga: ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");
}

void printAlt(){
  // print to display
  tft.setTextColor(BLACK,WHITE);
  tft.setCursor(1, 35);
  tft.setTextFont(2);
  tft.print("Visina: ");
  tft.print(bme.readAltitude(SEA_LEVEL_PRE));
  tft.print(" m");

  // print to serial monitor
  Serial.print("Visina: ");
  Serial.print(bme.readAltitude(SEA_LEVEL_PRE));
  Serial.println(" m");
}

void printPres(){
  // print to display
  tft.setTextColor(BLACK,WHITE);
  tft.setCursor(1, 50);
  tft.setTextFont(2);
  tft.print("Tlak: ");
  tft.print(bme.readPressure()/100.0F);
  tft.print(" hPa");

  // print to serial monitor
  Serial.print("Tlak: ");
  Serial.print(bme.readPressure()/100.0F);
  Serial.println(" hPa");
}
