#pragma once
#include <Adafruit_NeoPixel.h> // подключаем библиотеку
#define PIN 7 // 13 указываем пин для подключения ленты
#define NUMPIXELS 29 // указываем количество светодиодов в ленте
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void ledwrite(int color)
  {
    for (int i = 0; i < NUMPIXELS; i++)
    {
      strip.setPixelColor(i, strip.Color(MyArrayC[MyArray[color * NUMPIXELS+i] * 3], MyArrayC[MyArray[color * NUMPIXELS + i] * 3 + 1], MyArrayC[MyArray[color * NUMPIXELS + i] * 3 + 2])); // 
    }
      strip.show();
      //Serial.println(designcolor);
    }                         //
    
   
  
