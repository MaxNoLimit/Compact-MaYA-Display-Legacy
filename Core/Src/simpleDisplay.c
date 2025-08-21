#include "simpleDisplay.h"
#include "ili9341_gfx.h"
#include "ili9341_stm32_driver.h"
#include <stdbool.h>
#include "check_display_input.h"

char * volumeInSettings = "20";
char * versionString = "v7.2.7	wysi Firmware w/ STM32Cube";

void pageSetup(void){
	ILI9341_Init();
}
void firstPage(void){
	char * str1 = "Automated Leather";
	char * str2 = "Wayang Player 2025";

	ILI9341_FillScreen(WHITE);
	ILI9341_SetRotation(SCREEN_VERTICAL_2);

	ILI9341_DrawText(str1, FONT4, 10, 149, BLACK, WHITE);
	ILI9341_DrawText(str2, FONT4, 10, 169, BLACK, WHITE);

	HAL_Delay(1000);

	// progress bar
	ILI9341_DrawHollowRectangleCoord(8, 200, 231, 219, BLACK);
	HAL_Delay(500);
	for (int var = 0; var < 201; var++) {
		ILI9341_DrawRectangle(10, 202, 1.1*var, 16, BLUE);
		HAL_Delay(10);
	}
	HAL_Delay(100);

	// remove the progress bar
	ILI9341_DrawFilledRectangleCoord(8, 200, 232, 220, WHITE);

	message("Opening...");
	HAL_Delay(2000);
	message("Tap anywhere");

}

void menuPage(void){
	char * menuString[4] = {
			"Menu",
			"Play the show",
			"Calibrate",
			"Settings",
	};

	ILI9341_FillScreen(WHITE);
	ILI9341_SetRotation(SCREEN_VERTICAL_2);
	// Blue Bar like flutter
	ILI9341_DrawRectangle(0, 0, 240, 35, BLUE);
	ILI9341_DrawText(menuString[0], FONT4, 10, 10, WHITE, BLUE);
	for (int var = 0; var < 3; ++var) {
		int y_position = 30*(var + 1) + 20*var + 50;
		ILI9341_DrawRectangle(10, y_position , 220, 40, BLUE);
		ILI9341_DrawText(menuString[var + 1], FONT4, 30, y_position + 10, WHITE, BLUE);
	};

	// version
	ILI9341_DrawText(versionString, FONT2, 5, 305, BLUE, WHITE);
}

void message(char *msg){
	ILI9341_DrawText(msg, FONT2, 60, 269, WHITE, BLACK);
}

void messageDetail(char * msg){
	ILI9341_DrawText(msg, FONT2, 60, 284, WHITE, BLACK);
}

void clearMessage(){
	ILI9341_DrawText("                                                 ", FONT4, 10, 269, WHITE, WHITE);
	ILI9341_DrawText("                                                 ", FONT4, 10, 284, WHITE, WHITE);
}

void playingPage(){
	ILI9341_FillScreen(WHITE);
	ILI9341_SetRotation(SCREEN_VERTICAL_2);
	// Blue Bar like flutter
	ILI9341_DrawRectangle(0, 0, 240, 35, BLUE);
	ILI9341_DrawText("< Back", FONT4, 10, 10, WHITE, BLUE);

//	ILI9341_DrawText("Play the show page!", FONT4, 10, 159 + 10, BLUE, WHITE);

	ILI9341_DrawRectangle(10, 80 , 220, 40, BLUE);
	ILI9341_DrawText("Abort", FONT4, 30, 80 + 10, WHITE, BLUE);

	ILI9341_DrawText("Currently playing the show...", FONT2, 10, 269, WHITE, BLACK);

	// version
	ILI9341_DrawText(versionString, FONT2, 5, 305, BLUE, WHITE);

}

void calibratePage(){
	const char * calibrateString[2] = {
			"V-Slot Linear",
			"Wayang's Hand"
	};
	ILI9341_FillScreen(WHITE);
	ILI9341_SetRotation(SCREEN_VERTICAL_2);
	// Flutter like blue bar
	ILI9341_DrawRectangle(0, 0, 240, 35, BLUE);
	ILI9341_DrawText("< Back", FONT4, 10, 10, WHITE, BLUE);

//	ILI9341_DrawText("Calibrating page!", FONT4, 10, 159 + 10, BLUE, WHITE);
	for (int var = 0; var < 2; ++var) {
		int y_position = 30*(var + 1) + 20*var + 50;
		ILI9341_DrawRectangle(10, y_position , 220, 40, BLUE);
		ILI9341_DrawText(calibrateString[var], FONT4, 30, y_position + 10, WHITE, BLUE);
	};

	// version
	ILI9341_DrawText(versionString, FONT2, 5, 305, BLUE, WHITE);
}

void settingsPage(){
	char * settingString[2] = {
			"Volume",
			"Voice Language"
	};
	ILI9341_FillScreen(WHITE);
	ILI9341_SetRotation(SCREEN_VERTICAL_2);
	// Blue Bar like flutter
	ILI9341_DrawRectangle(0, 0, 240, 35, BLUE);
	ILI9341_DrawText("< Back", FONT4, 10, 10, WHITE, BLUE);

	for (int var = 0; var < 2; ++var) {
		int y_position = 30*(var + 1) + 20*var + 50;
		ILI9341_DrawRectangle(10, y_position , 220, 40, BLUE);
		ILI9341_DrawText(settingString[var], FONT4, 20, y_position + 10, WHITE, BLUE);
		if (var == 0) {
			ILI9341_DrawText(volumeInSettings, FONT4, 192, y_position + 10, WHITE, BLUE);
		} else {
			ILI9341_DrawText("EN", FONT4, 192, y_position + 10, WHITE, BLUE);
		}
	};

	// version
	ILI9341_DrawText(versionString, FONT2, 5, 305, BLUE, WHITE);

}
