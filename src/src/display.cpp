#include "display.h"
#include "additional/LiquidCrystal_I2C.h"

LiquidCrystal_I2C *display;

void display_init()
{
    display = new LiquidCrystal_I2C(DISPLAY_ADDRESS, 16, 2);;
    display->init();
    display->backlight();
    display->setCursor(0,0);
}

void display_print(const char *text)
{
    display->clear();
    display->print(text);
}

void display_print(const int num)
{
    display->clear();
    display->print(num, 10);
}

void display_print(const double num)
{
    display->clear();
    display->print(num, 5);
}