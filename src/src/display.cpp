#include "display.h"
#include "additional/LiquidCrystal_I2C.h"

Display::Display()
{
    display = new LiquidCrystal_I2C(DISPLAY_ADDRESS, 16, 2);
    display->init();
    display->backlight();
    display->setCursor(0,0);
    display->print("Hello world!");
}

template <typename T> void Display::print_first_line(T to_print)
{
    //display->clear();
    display->print(to_print);
}

template <typename T> void Display::print_second_line(T to_print)
{
    display->setCursor(0,1);
    //display->clear();
    display->print(to_print);
}

void Display::clear()
{
    display->clear();
}