//#include "GM.h"
#include <Adafruit_NeoPixel.h> // подключаем библиотеку
#include <Arduino.h>
#include "main.h"
#include "ws2812.h"       
#include "buton.h"
#include <EEPROM.h>
#include "func.h"
void setup()
{
  // eeprom_write_byte(0,0x0);
  designcolor = EEPROM.read(0);
  FB_flag = EEPROM.read(2);
  Bright = EEPROM.read(4);
  strip.begin();            // инициализируем ленту
  strip.setBrightness(Bright); // указываем яркость светодиодов (максимум 255)
  //designcolor = 0;
  pinMode(FeedBack,OUTPUT);
  pinMode(Current,OUTPUT);
  pinMode(LED13,OUTPUT);
  //Serial.begin(9600);
  ledwrite(designcolor); // SHOW 
}

void loop()
{ 
  miglong();
  
    functions();
  
}
 
  
   
