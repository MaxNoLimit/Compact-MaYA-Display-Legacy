#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "uart_message.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

/*
void sendDebugMessage(char * msg){
	uint8_t *data;
	memcpy(&data, msg, sizeof(uint8_t));
	HAL_UART_Transmit(&huart2, data, 16, 500);
	UART_
}
*/

void sendDebugMessage(const char * msg, ...){
	char buff[256];
	va_list args;
	va_start(args, msg);
	vsnprintf(buff, sizeof(buff), msg, args);
	HAL_UART_Transmit(&huart2, (uint8_t*)buff, strlen(buff), HAL_MAX_DELAY);
//	HAL_UART_Transmit(&huart2, (uint8_t*)'\n', 1, HAL_MAX_DELAY);
	va_end(args);
}

void sendSpecifiedMessage(uint8_t msg){
//	HAL_UART_Transmit(&huart2, msg, 12, 1000);
}

uint8_t * receivedMessage(){
	uint8_t msg_buffer[6];
	while(HAL_UART_Receive(&huart2, (uint8_t*)msg_buffer, 6, HAL_MAX_DELAY) != HAL_OK){
		// do nothing
	}
//	HAL_UART_Receive(&huart2, msg_buffer, 6, HAL_MAX_DELAY);
	uint8_t *t_msg_buffer = (uint8_t*)malloc(sizeof(uint8_t) * 6);
	memcpy(t_msg_buffer, msg_buffer, (sizeof(uint8_t) * 6));
	HAL_UART_Transmit(&huart2, t_msg_buffer, 6, HAL_MAX_DELAY);
	return t_msg_buffer;

}

void flushUART(){
	HAL_UART_Transmit(&huart2, (uint8_t*)'\n', 1, HAL_MAX_DELAY);
}

char* receivedMessageBuffer(){
	uint8_t rxChar;
	char recv_str[7];
	int i = 0;

	// empty buffer
	memset(recv_str, 0, 7);

	// do while loop for reading each byte one by one
	do {
		// Receive one byte with a timeout
		if (HAL_UART_Receive(&huart2, &rxChar, 1, 100) == HAL_OK) {
			recv_str[i++] = rxChar;
			if (i > 5) {
				break;
			}
		} else{
			// do nothing
			break;
		}
	} while (rxChar != '\n' && rxChar != '\r');

	recv_str[i] = '\0';

	// Allocate first
	char* t_return = (char *)malloc(7);

	// Copy the string
	strcpy(t_return, recv_str);


	return t_return;
}


