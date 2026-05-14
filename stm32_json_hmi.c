#include "stm32_json_hmi.h"
#include <stdio.h>
#include <string.h>

// ===== INIT =====
void HMI_Init(HMI_HandleTypeDef *hmi, UART_HandleTypeDef *huart)
{
    hmi->huart = huart;
}

// ===== LOW LEVEL SEND =====
void HMI_SendRaw(HMI_HandleTypeDef *hmi, const char *json)
{
    int len = snprintf(hmi->tx_buffer, JSON_TX_BUFFER_SIZE,
                       "ST<%s>ET", json);

    HAL_UART_Transmit(hmi->huart,
                      (uint8_t*)hmi->tx_buffer,
                      len,
                      100);
}

// ===== GENERIC BUILDER =====
static void HMI_BuildAndSend(HMI_HandleTypeDef *hmi,
                             const char *cmd,
                             const char *type,
                             const char *widget,
                             const char *params)
{
    char json[JSON_TX_BUFFER_SIZE];

    if (params != NULL)
    {
        snprintf(json, sizeof(json),
                 "{\"cmd_code\":\"%s\",\"type\":\"%s\",\"widget\":\"%s\",%s}",
                 cmd, type, widget, params);
    }
    else
    {
        snprintf(json, sizeof(json),
                 "{\"cmd_code\":\"%s\",\"type\":\"%s\",\"widget\":\"%s\"}",
                 cmd, type, widget);
    }

    HMI_SendRaw(hmi, json);
}

// ===== BASIC =====
void HMI_SetText(HMI_HandleTypeDef *hmi, const char *widget, const char *text)
{
    char params[128];
    snprintf(params, sizeof(params), "\"text\":\"%s\"", text);

    HMI_BuildAndSend(hmi, "set_text", "label", widget, params);
}

void HMI_SetValue(HMI_HandleTypeDef *hmi,
                  const char *type,
                  const char *widget,
                  int value)
{
    char params[64];
    snprintf(params, sizeof(params), "\"value\":%d", value);

    HMI_BuildAndSend(hmi, "set_value", type, widget, params);
}

void HMI_SetValueFloat(HMI_HandleTypeDef *hmi,
                        const char *type,
                        const char *widget,
                        float value)
{
    char params[64];
    snprintf(params, sizeof(params), "\"value\":%.2f", value);

    HMI_BuildAndSend(hmi, "set_value", type, widget, params);
}

// ===== SYSTEM =====
void HMI_SetBrightness(HMI_HandleTypeDef *hmi, uint8_t brightness)
{
    char params[32];
    snprintf(params, sizeof(params), "\"brightness\":%d", brightness);

    HMI_BuildAndSend(hmi, "set_brightness", "system", "sys", params);
}

void HMI_Buzzer(HMI_HandleTypeDef *hmi, uint16_t time_ms)
{
    char params[32];
    snprintf(params, sizeof(params), "\"time\":%d", time_ms);

    HMI_BuildAndSend(hmi, "set_buzzer", "system", "sys", params);
}

// ===== CONTROL =====
void HMI_SetVisible(HMI_HandleTypeDef *hmi,
                    const char *widget,
                    uint8_t visible)
{
    char params[32];
    snprintf(params, sizeof(params),
             "\"visible\":%s", visible ? "true" : "false");

    HMI_BuildAndSend(hmi, "set_visible", "widget", widget, params);
}

void HMI_SetEnable(HMI_HandleTypeDef *hmi,
                   const char *widget,
                   uint8_t enable)
{
    char params[32];
    snprintf(params, sizeof(params),
             "\"enable\":%s", enable ? "true" : "false");

    HMI_BuildAndSend(hmi, "set_enable", "widget", widget, params);
}

void HMI_SetXY(HMI_HandleTypeDef *hmi,
               const char *widget,
               int x, int y)
{
    char params[64];
    snprintf(params, sizeof(params), "\"x\":%d,\"y\":%d", x, y);

    HMI_BuildAndSend(hmi, "set_xy", "widget", widget, params);
}

// ===== COLOR =====
void HMI_SetColor(HMI_HandleTypeDef *hmi,
                  const char *widget,
                  const char *color_object,
                  uint32_t color)
{
    char params[128];
    snprintf(params, sizeof(params),
             "\"color_object\":\"%s\",\"color\":%lu",
             color_object, color);

    HMI_BuildAndSend(hmi, "set_color", "widget", widget, params);
}

// ===== SLIDER =====
void HMI_SetSlider(HMI_HandleTypeDef *hmi,
                   const char *widget,
                   int value)
{
    HMI_SetValue(hmi, "slider", widget, value);
}

// ===== WINDOW =====
void HMI_OpenWindow(HMI_HandleTypeDef *hmi,
                    const char *window)
{
    HMI_BuildAndSend(hmi, "open_win", "window", window, NULL);
}

// ===== CUSTOM =====
void HMI_Custom(HMI_HandleTypeDef *hmi,
                const char *cmd,
                const char *type,
                const char *widget,
                const char *params)
{
    HMI_BuildAndSend(hmi, cmd, type, widget, params);
}
