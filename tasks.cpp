#include "Inc/tasks.h"
#include "Inc/screen.hpp"

#include "Inc/motor.hpp"

#include <SPI.h>
#include <Wire.h>

#include <nRF24L01.h>
#include <RF24.h>

#include "trac.hpp"

///////////////////
/// Internal Objects
///////////////////

extern RF24 *RADIO1;
extern TwoWire iic1;

///////////////////
/// Flags
///////////////////

bool _on_ends_show = false;
bool _en_clear_flag = false;
bool flag_en_21 = false;

///////////////////
/// Buffers
///////////////////

//uint8_t Data_Dits[8] = {0, 0, 0, 0, 0, 0, 0, 0};
char Screen_Console_Text[11][64];

//////////////////
/// Params
//////////////////

int cc = 0;
TxData RadioData;

//////////////////
/// Methods
//////////////////

void Task_IICLight(void *param)
{

    // ref 10~14 Front

    while (1)
    {
        iic1.requestFrom(0x20, 10);
        for (int i = 0; i < 10;)
        {
            if (iic1.available())
            {
                ad_refs_current[i] = iic1.read();
                i++;
            }
        }

        iic1.requestFrom(0x21, 10);
        for (int i = 0; i < 10;)
        {
            if (iic1.available())
            {
                ad_refs_current[i + 10] = iic1.read();
                i++;
            }
        }

        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

void Task_Main(void *param)
{
    set_left_motor(0);
    set_right_motor(0);
    set_back_motor(0);

    while (1)
    {
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

void Task_Screen(void *param)
{
    setColor(RGB(0, 0, 0));
    bool ixcv = false;
    while (1)
    {

        int cc_ll = 0;
        if (_en_clear_flag)
        {
            setColor(RGB(0, 0, 0));
            _en_clear_flag = false;
        }
        for (auto i : Screen_Console_Text)
        {
            char ll_f[64];
            strcpy(ll_f, ">>");
            strcat(ll_f, i);

            drawText(4, 4 + cc_ll * 21, ll_f);
            cc_ll++;
        }
        // Speed:%d
        ixcv = !ixcv;
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

void Task_Radio(void *param)
{
    while (1)
    {
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
}

void Task_Wheel(void *param)
{
    while (1)
    {
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
}