#ifndef _DISPLAY16X2_H
#define _DISPLAY16X2_H  1

#define DISPLAY_ENABLE true
#define DISPLAY_ADDRESS 0x3F

void display_init();
void display_print(const char *text);
void display_print(const int num);
void display_print(const long num);
void display_print(const float num);
#endif