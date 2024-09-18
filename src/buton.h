// класс кнопки
#pragma once
#include <Arduino.h>
#define _BTN_DEB_TIME 100      // таймаут антидребезга
#define _BTN_DEB_LONGTIME 2000 // таймаут антидребезга

class Button
{
public:
    Button(int pin) : _pin(pin)
    {
        pinMode(_pin, INPUT);
    }

    byte brmig()
    {
        return mig;
    }

    int click()
    {
        bool btnState = digitalRead(_pin);

        if (!btnState && !_flag && millis() - _tmr >= _BTN_DEB_LONGTIME) // button off long press ok
        {
            mig = 1;
            _flag = true;
            _tmr = millis();
            return (2); // true;
        }

        if (btnState && !_flag && millis() - _tmr <= _BTN_DEB_LONGTIME + 500 && !_flag && millis() - _tmr >= _BTN_DEB_LONGTIME) // button off long press ok
        {
            mig = 0; // 0              bright -
        }
        if (btnState && !_flag && millis() - _tmr >= _BTN_DEB_LONGTIME + 500 && !_flag) // button off long press ok
        {
            mig = 1; // bright -
        }

        if (!btnState && !_flag && millis() - _tmr >= _BTN_DEB_TIME)
        {
            mig = 1;
            _flag = true;
            _tmr = millis();
            return (1);
        }
        if (btnState && _flag && millis() - _tmr >= _BTN_DEB_TIME)
        {
            _flag = false;
            _tmr = millis();
        }
        return (0);
    }

private:
    const byte _pin;
    uint32_t _tmr;
    bool _flag;
    byte mig;
};