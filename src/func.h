#pragma once
#include <Arduino.h>
#include "main.h"
#include "ws2812.h"
#include <EEPROM.h>

void miglong(){
    if ((btn1.brmig() && btn2.brmig()) == 0)
    {
        strip.setBrightness(8); // MIG for long press
        ledwrite(designcolor);
    }
    if ((btn1.brmig() && btn2.brmig()) == 1)
    {
        strip.setBrightness(Bright); //
        ledwrite(designcolor);
    }
}
void functions(){
    if (!TuneCurrent_flag && !Bright_flag)
    {
        switch (btn1.click())       // 1/left knob short press!!!!!!!!!!!!!!!
        {
        case 1:     //short press
            tempcolor = designcolor; // Save color to Temp
            if (!FB_flag)
            {
                designcolor = 18; // color for FeedBack
            }
            else
            {
                designcolor = 19; // color for NO FeedBack
            }
            ledwrite(designcolor); // SHOW Color
            delay(1000);
            designcolor = tempcolor;
            ledwrite(designcolor);
            break;
            //-------------------YES / NO FEED BACK--------------------------------

        case 2:                      // FeedBack route        (1/right LONG press)!!!!!!!!!!!!!!!!!!!!!
            tempcolor = designcolor; // Save color to Temp
            if (!FB_flag)
            {
                designcolor = 18; // color for FeedBack
            }
            else
            {
                designcolor = 19; // color for NO FeedBack
            }
            ledwrite(designcolor); // SHOW Color
            delay(2000);
            FB_flag = !FB_flag;              // invert status FB
            digitalWrite(FeedBack, FB_flag); // output FB to port
            if (!FB_flag)
            {
                designcolor = 18; // color for FeedBack
            }
            else
            {
                designcolor = 19; // color for NO FeedBack
            }
            ledwrite(designcolor); // SHOW Color
            delay(1000);
            designcolor = tempcolor;
            ledwrite(designcolor); // SHOW Color
            break;
        }
        switch (btn2.click())
        {

            //---------------------TUNE CURRENT / > LONG PRESS > TUNR COLOR-------------------------------
        case 2:
            tempcolor = designcolor;     // Save color to Temp
            TuneCurrent_flag = true;     // State status_flag tuneCurrent
            designcolor = 21;            // color for FeedBack
            digitalWrite(Current, HIGH); // Reley Klatc to ON
            ledwrite(designcolor);       // SHOW Color
            break;
        }
    }
    if (TuneCurrent_flag && !TuneColor_flag)
    { // Mode Tune Current

        switch (btn2.click())
        {
        case 1:
            designcolor = tempcolor; // Restore State color
            ledwrite(designcolor);
            digitalWrite(Current, LOW); // Reley Klatc to ON
            TuneCurrent_flag = false;
            break;
        case 2:                         //------------------------------------------Vector TUNE C O L O R !!!
            designcolor = tempcolor;    // Restore State color
            TuneColor_flag = true;      // Tuning Color ON
            digitalWrite(Current, LOW); // Reley Klatc to ON
            ledwrite(designcolor);      // SHOW Color
            break;
        }
        switch (btn1.click())
        {
        case 1:                      /* constant-expression */
            designcolor = tempcolor; // Restore State color
            TuneColor_flag = false;  // Tuning Color ON
            TuneCurrent_flag = false;
            digitalWrite(Current, LOW); // Reley Klatc to ON
            ledwrite(designcolor);      // SHOW Color
            break;

        case 2:                      /* constant-expression */
            designcolor = tempcolor; // Restore State color
            TuneColor_flag = false;  // Tuning Color ON
            TuneCurrent_flag = false;
            digitalWrite(Current, LOW); // Reley Klatc to ON
            ledwrite(designcolor);      // SHOW Color
            break;
        }
    }

    if (TuneCurrent_flag && TuneColor_flag && !Bright_flag) //--------------- Curr -Y Color - Y BrigT U N E      C O L O R -----------------
    {
        switch (btn2.click()) // Route keys----------------btn2 (+1) ---------------------
        {
        case 1:
            designcolor = designcolor + 1; // Palette COLOR
            if (designcolor > 20)
            {
                designcolor = 0;
            }
            ledwrite(designcolor);
            //sprint_rgb();
            break;

        case 2: //--------VECTOR--BRIGHT------+++++++++++++++++++++++++++++++++
            Bright_flag = true;
            TuneColor_flag = false;
            TuneCurrent_flag = false;
            break;
        }

        switch (btn1.click()) //----------------btn1 (-1) ---------------------
        {
        case 1:
            designcolor = designcolor - 1; // Palette
            if (designcolor <= 0)
            {
                designcolor = 20;
            }
            ledwrite(designcolor);
            //sprint_rgb();
            break;
        }
    }
    //----------------------B R I G H T----------------------
    if (Bright_flag == true)

    {

        switch (btn2.click()) // Route keys----------------btn2 (+1) ---------------------
        {
        case 1:
            Bright = Bright + 10; // Palette
            if (Bright > 244)
            {
                Bright = 244;
            }
            strip.setBrightness(Bright); // указываем яркость светодиодов (максимум 255)
            ledwrite(designcolor);
            //sprint_rgb();
            break;
        //--------Exit and save to eeprom--------
        case 2:
            Bright_flag = false;
            EEPROM.write(0, designcolor);
            delay(100);
            EEPROM.write(2, FB_flag);
            delay(100);
            EEPROM.write(4, Bright);
            delay(100);
            // Serial.println("EEPROM SAVE");
            //sprint_rgb();
            break;
        }
        //----------------btn1 (-1) ---------------------
        switch (btn1.click())
        {
        case 1:
            Bright = Bright - 10; // Palette
            if (Bright < 30)
            {
                Bright = 30;
            }
            strip.setBrightness(Bright); // указываем яркость светодиодов (максимум 255)
            ledwrite(designcolor);
            //sprint_rgb();
            break;
        }
    }
}