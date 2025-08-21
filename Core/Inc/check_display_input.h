#ifndef CHECK_DISPLAY_INPUT_H
#define CHECK_DISPLAY_INPUT_H

#define PLAY_THE_SHOW_COMMAND 	"0x01"
#define CALIBRATE_COMMAND 		"0x02"
#define SETTINGS_COMMAND 		"0x03"

#include <stdbool.h>

void calibrateDisplay();
void displayInputCheck();
void waitUntilTapAnywhere();

bool isPlaying();
void setPlayingStatus();

void holdUntilDone();

enum PAGE_ROUTE{
	MENU_PAGE = 0,
	PLAYING_PAGE = 1,
	CALIBRATE_PAGE = 2,
	SETTINGS_PAGE = 3
};


#endif // CHECK_DISPLAY_INPUT_H
