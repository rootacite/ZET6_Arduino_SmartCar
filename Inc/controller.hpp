#include "Arduino.h"

#include "Inc/motor.hpp"
#include "Inc/trac.h"

#include "Inc/mpu.h"

float oc_celi_target = 180.00;

void move_micro_step(bool fb = true)
{
    if (fb)
    {
        GO_STRAIGHT;
    }
    else
    {
        GO_BACK;
    }

    vTaskDelay(450 / portTICK_PERIOD_MS);
    STAY_STATIC;
}

void move_acro_trac_until(BOOL_CONDITION Condition)
{
    while (Condition)
    {
        float fv = get_line_pos_with_trac(0);

        if (fv > 0.25) // turn left
        {
            TURN_RIGHT;
        }
        else if (fv < -0.25) // turn right
        {
            TURN_LEFT;
        }
        else
        {
            GO_STRAIGHT;
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    STAY_STATIC;
}

void move_until_crash_raw()
{
    GO_STRAIGHT;
    while (!get_crash_raw(0))
    {
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
    STAY_STATIC;
}

#define MIN(x, y) ((x) < (y) ? (x) : (y))

static float get_angle_diff(float a, float b)
{
    float lr = abs(a - b);
    if (lr > 180.0)
    {
        return 360.0 - lr;
    }
    //Serial.println(lr);
    return lr;
}

void celi_to_target()
{
    float yyu = Get();

    if (get_angle_diff(yyu, oc_celi_target) < 0.5)
        return;

    bool _turn_flag = true;

    if(yyu < oc_celi_target)
    {
        if(oc_celi_target - yyu > 180)
            _turn_flag = false;
        else
            _turn_flag = true;
    }
    else
    {
        if(yyu - oc_celi_target > 180)
            _turn_flag = true;
        else
            _turn_flag = false;
    }

    if(_turn_flag)
    {
        do
        {
            TURN_RIGHT;
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }while(get_angle_diff(Get(), oc_celi_target) > 0.5);

        STAY_STATIC;
    }
    else
    {
        do
        {
            TURN_LEFT;
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }while(get_angle_diff(Get(), oc_celi_target) > 0.5);

        STAY_STATIC;
    }
}