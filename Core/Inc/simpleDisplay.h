#ifndef SIMPLEDISPLAY_H
#define SIMPLEDISPAY_H


#include "ili9341_gfx.h"
#include "ili9341_stm32_driver.h"
#include "stdio.h"

void pageSetup(void);

void firstPage(void);
void menuPage(void);
void playingPage(void);
void calibratePage(void);
void settingsPage(void);

void message(char* msg);
void messageDetail(char *msg);
void clearMessage();

#endif // SIMPLEDISPLAY_H
