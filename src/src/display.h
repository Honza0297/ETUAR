#ifndef _DISPLAY16X2_H
#define _DISPLAY16X2_H  1

#define DISPLAY_ENABLE true

/* Adresa displeje muze byt ruzna TODO */
#define DISPLAY_ADDRESS_PRIMARY 0x3F
#define DISPLAY_ADDRESS_FALLBACK 0x20 //nebo cokoli 0x20 az 0x27
#define DISPLAY_ADDRESS  DISPLAY_ADDRESS_PRIMARY

void display_init();
void display_print(const char *text);
void display_print(const int num);
void display_print(const long num);
void display_print(const double num);

#endif