#ifndef __STM32_JSON_HMI_H
#define __STM32_JSON_HMI_H

#include "stm32f1xx_hal.h"
#include <stdint.h>

// ===== CONFIG =====
#define JSON_TX_BUFFER_SIZE   256

// ===== PUBLIC STRUCT =====
typedef struct
{
    UART_HandleTypeDef *huart;
    char tx_buffer[JSON_TX_BUFFER_SIZE];
} HMI_HandleTypeDef;

// ===== INIT =====
void HMI_Init(HMI_HandleTypeDef *hmi, UART_HandleTypeDef *huart);

// ===== CORE SEND =====
void HMI_SendRaw(HMI_HandleTypeDef *hmi, const char *json);

// ===== BASIC COMMANDS =====
void HMI_SetText(HMI_HandleTypeDef *hmi, const char *widget, const char *text);
void HMI_SetValue(HMI_HandleTypeDef *hmi, const char *type, const char *widget, int value);
void HMI_SetValueFloat(HMI_HandleTypeDef *hmi, const char *type, const char *widget, float value);

// ===== SYSTEM =====
void HMI_SetBrightness(HMI_HandleTypeDef *hmi, uint8_t brightness);
void HMI_Buzzer(HMI_HandleTypeDef *hmi, uint16_t time_ms);

// ===== WIDGET CONTROL =====
void HMI_SetVisible(HMI_HandleTypeDef *hmi, const char *widget, uint8_t visible);
void HMI_SetEnable(HMI_HandleTypeDef *hmi, const char *widget, uint8_t enable);
void HMI_SetXY(HMI_HandleTypeDef *hmi, const char *widget, int x, int y);

// ===== COLOR =====
void HMI_SetColor(HMI_HandleTypeDef *hmi, const char *widget, const char *color_object, uint32_t color);

// ===== SLIDER =====
void HMI_SetSlider(HMI_HandleTypeDef *hmi, const char *widget, int value);

// ===== SCREEN =====
void HMI_OpenWindow(HMI_HandleTypeDef *hmi, const char *window);

// ===== ADVANCED (CUSTOM JSON) =====
void HMI_Custom(HMI_HandleTypeDef *hmi,
                const char *cmd,
                const char *type,
                const char *widget,
                const char *params);

#endif
