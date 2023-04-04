#include "Inc/tasks.h"
#include "Inc/screen.hpp"

#include <SPI.h>

#include <nRF24L01.h>
#include <RF24.h>

#include "Inc/def.h"

extern RF24 *RADIO1;

TxData RadioData;

void Task_Screen(void *param)
{
    while (1)
    {
        setColor(RGB(255, 0, 0));
        vTaskDelay(500 / portTICK_PERIOD_MS);
        setColor(RGB(0, 255, 0));
        vTaskDelay(500 / portTICK_PERIOD_MS);
        setColor(RGB(0, 0, 255));
        vTaskDelay(500 / portTICK_PERIOD_MS);
        setColor(RGB(255, 255, 0));
        vTaskDelay(500 / portTICK_PERIOD_MS);
        setColor(RGB(0, 255, 255));
        vTaskDelay(500 / portTICK_PERIOD_MS);
        setColor(RGB(255, 0, 255));
        vTaskDelay(500 / portTICK_PERIOD_MS);
        setColor(RGB(255, 255, 255));
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void Task_Radio(void *param)
{
    while (1)
    {
        if (RADIO1->available())
        {
            RADIO1->read(&RadioData, sizeof(RadioData));
        }
        vTaskDelay(5 / portTICK_PERIOD_MS);
        
    }
}