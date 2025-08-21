#include "check_display_input.h"
#include "ili9341_stm32_driver.h"
#include "ili9341_touch.h"
#include "simpleDisplay.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "uart_message.h"
#include "simpleDisplay.h"

uint16_t x, y;
int pageRoute = 0;
bool showState = false;
bool holdState = true;
uint8_t msg_buffer_for_IT[7] = { 0 };

void calibrateDisplay() {
	int npoints = 0;
	while (npoints < 10000) {
		uint16_t x, y;
		if (ILI9341_TouchGetCoordinates(&x, &y)) {
			message("Pressed!");
			x = 240 - x;
//			ILI9341_DrawPixel(x, 320-y, WHITE);
			sendDebugMessage("x: %d, y: %d\r\n", x, y);
			npoints++;
			HAL_Delay(500);
		}
		clearMessage();
	}
}

void displayInputCheck() {
	if (ILI9341_TouchGetCoordinates(&x, &y)) {
		x = 240 - x; // optional honestly, just to swap the pixel position
//		debug function
//		sendDebugMessage("x: %d, y: %d\r\n", x, y);
		switch (pageRoute) {
		case MENU_PAGE:
			if (x > 10 && x < 230 && y > 80 - 1 && y < 120 + 1) {
				pageRoute = PLAYING_PAGE;
				playingPage();
				sendDebugMessage("PlayTheShow");
			} else if (x > 10 && x < 230 && y > 150 - 1 && y < 170 + 1) {
				pageRoute = CALIBRATE_PAGE;
				calibratePage();
			} else if (x > 10 && x < 230 && y > 180 - 1 && y < 220 + 1) {
				pageRoute = SETTINGS_PAGE;
				settingsPage();
			}
			break;
		case PLAYING_PAGE:
			if (x > 0 && x < 46 && y > 0 && y < 36) {
				// Go back widget, will pause the show
				pageRoute = MENU_PAGE;
				menuPage();
				sendDebugMessage("PauseTheShow");
				message("Show paused!");
				HAL_Delay(1000);
			} else if (x > 10 && x < 230 && y > 80 - 1 && y < 120 + 1) {
				clearMessage();
				message("Aborting...");
				sendDebugMessage("AbortTheShow");
				HAL_Delay(2000);
//					while(strcmp((const char *)receivedMessage(), "AbortShowDone") != 0 || strcmp((const char *)receivedMessage(), "Ignore") != 0){
//						// do nothing
//					}
				clearMessage();
				message("Aborted!");
				HAL_Delay(1000);
				clearMessage();
				pageRoute = MENU_PAGE;
				menuPage();
			}
			break;
		case CALIBRATE_PAGE:
			if (x > 0 && x < 46 && y > 0 && y < 36) {
				pageRoute = MENU_PAGE;
				menuPage();
			} else if (x > 10 && x < 230 && y > 80 - 1 && y < 120 + 1) {
				clearMessage();
				message("Please wait");
				messageDetail("V-Slot Linear");
				sendDebugMessage("VSlotCalibration");
				flushUART();

				HAL_UART_Transmit(&huart2, (uint8_t*) '\n', 1, HAL_MAX_DELAY);
				// Input check
				while(1){
					const char* recv_buff = receivedMessageBuffer();
					if (strcmp(recv_buff, "VSDone") == 0) {
						char feedback_buffer[100];
						sprintf(feedback_buffer, "Message accepted: %s\n",
								recv_buff);
						HAL_UART_Transmit(&huart2, (uint8_t*) feedback_buffer,
								strlen((const char*) feedback_buffer),
								HAL_MAX_DELAY);
						break;
					}
					else {
						// do nothing, wait until correct
//						sendDebugMessage("Unknown Message!");
					}
					HAL_UART_Transmit(&huart2, (uint8_t*) '\0', 1,
					HAL_MAX_DELAY);
				}

				clearMessage();
				message("Okay!");
				HAL_Delay(1000);
				clearMessage();

			} else if (x > 10 && x < 230 && y > 130 - 1 && y < 170 + 1) {
				message("Please wait");
				messageDetail("Wayang's Hand");
				sendDebugMessage("WayangServo");
				flushUART();

				HAL_UART_Transmit(&huart2, (uint8_t*) '\n', 1, HAL_MAX_DELAY);
				// Input check
				while(1){
					const char* recv_buff = receivedMessageBuffer();
					if (strcmp(recv_buff, "WSDone") == 0) {
						char feedback_buffer[100];
						sprintf(feedback_buffer, "Message accepted: %s\n",
								recv_buff);
						HAL_UART_Transmit(&huart2, (uint8_t*) feedback_buffer,
								strlen((const char*) feedback_buffer),
								HAL_MAX_DELAY);
						break;
					}
					else {
						// do nothing, wait until correct
//						sendDebugMessage("Unknown Message!");
					}
					HAL_UART_Transmit(&huart2, (uint8_t*) '\0', 1,
					HAL_MAX_DELAY);
				}

				clearMessage();
				message("Okay!");
				HAL_Delay(1000);
				clearMessage();
			}
			break;
		case SETTINGS_PAGE:
			if (x > 0 && x < 46 && y > 0 && y < 36) {
				pageRoute = MENU_PAGE;
				menuPage();

			}
			break;
		default:
			break;
		}

	}
}

void waitUntilTapAnywhere() {
	while (!ILI9341_TouchGetCoordinates(&x, &y)) {
		// do nothing, press the screen to break the while loop
	}
}

bool isPlaying() {
	bool result;
	if (!showState)
		result = true;
	if (showState)
		result = false;
	return result;
}

void setPlayingStatus() {
	showState = !showState;
	HAL_Delay(1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

//	if (holdState) {
//		HAL_UART_Receive_IT(&huart2, (uint8_t*)msg_buffer_for_IT, 6);
//		if (strncmp((const char*) msg_buffer_for_IT, "WSDone", 6) == 0
//				|| strncmp((const char*) msg_buffer_for_IT, "VSDone", 6) == 0) {
//			char callback_buffer[100];
//			sprintf((char*)callback_buffer,"Accepted! with the message of: %s\n", (const char*)msg_buffer_for_IT);
//			HAL_UART_Transmit(&huart2, (uint8_t*)callback_buffer,
//					strlen((const char*) callback_buffer), HAL_MAX_DELAY);
//			HAL_Delay(100);
//			holdState = false;
////				flushUART();
//		} else {
//			// do nothing
//
//		}
//	} else {
//		memset(msg_buffer_for_IT, 0, sizeof(msg_buffer_for_IT));
//	}

}

void holdUntilDone() {

}
