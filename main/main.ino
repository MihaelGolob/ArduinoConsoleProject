#include <SPI.h>
#include <TFT_ILI9163.h>
#include <User_Setup.h>

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

TFT_ILI9163 tft = TFT_ILI9163();

unsigned long targetTime = 0;

void clearDisp(int color){
  for(int i = 0; i < 160; i++){
     tft.drawFastVLine(i, 0, tft.height(), color);
  }
}

void setup(){
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(GRAY);
  clearDisp(WHITE);

  //turn on backlight
  pinMode(5, OUTPUT);
  digitalWrite(5,HIGH);

  //counter for fps
  targetTime = millis() + 1000;
}

void loop(){
  if(targetTime < millis()){
    targetTime = millis() + 1000;

    tft.setTextColor(RED, RED);
    tft.setCursor(1,5);
    tft.setTextFont(2);
    tft.print("HELLOO!! TUKAJ MIHAEL!");

    tft.setTextColor(BLACK, BLACK);
    tft.setCursor(1,30);
    tft.setTextFont(1);
    tft.print("zivijo tilen! kako si kaj?");
  }
}
