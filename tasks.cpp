#include "Inc/tasks.h"
#include "Inc/screen.hpp"

#include "Inc/controller.hpp"

#include <SPI.h>

#include <nRF24L01.h>
#include <RF24.h>

#include "EEPROM.h"

#include "Inc/data.h"
#include <Wire.h>

#include "Inc/mpu.h"
#include "Inc/armhand.hpp"

extern uint8_t ad_refs_black[];
extern uint8_t ad_refs_white[];
extern uint8_t ad_refs_current[];

///////////////////
/// Internal Objects
///////////////////

extern RF24 *RADIO1;

///////////////////
/// Flags
///////////////////

bool _on_ends_show = false;
bool _en_clear_flag = false;
bool flag_en_21 = false;

///////////////////
/// Buffers
///////////////////

// uint8_t Data_Dits[8] = {0, 0, 0, 0, 0, 0, 0, 0};
char Screen_Console_Text[11][64];

//////////////////
/// Params
//////////////////

int cc = 0;
TxData RadioData;
bool on_start_flag = false;

int arm_ctrl_params[4] = {0, 0, 0, 0};

extern TaskHandle_t x_tasks[];

//////////////////
/// Methods
//////////////////

void Task_IICLight(void *param)
{

    // ref 10~14 Front

    while (1)
    {
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void Task_Main(void *param)
{

    STAY_STATIC;

    while (1)
    {
        if (on_start_flag)
        {
            on_start_flag = false;
            break;
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    move_micro_step();
    Serial.println("Start Go");
    GO_STRAIGHT;
    while (!get_crash_raw(0))
    {
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
    Serial.println("Crash Init Line");
    vTaskDelay(450 / portTICK_PERIOD_MS);
    STAY_STATIC;

    oc_celi_target = 270;
    celi_to_target();

    for (int i = 0; i < 5; i++)
    {
        move_micro_step();
        GO_STRAIGHT;
        while (!get_crash_raw(0))
        {
            vTaskDelay(1 / portTICK_PERIOD_MS);
        }
        Serial.println("Crash Init Line");
        STAY_STATIC;
    }
    celi_to_target();
    Serial.println("celi_to_target");

    GO_STRAIGHT;
    delay(1200);
    STAY_STATIC;

    oc_celi_target = 0;
    celi_to_target();

    GO_STRAIGHT;
    while (!get_crash_raw(0))
    {
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
    STAY_STATIC;
    Serial.println("prepair to handle items");
    vTaskDelay(450 / portTICK_PERIOD_MS);

    while (1)
    {
        // celi_to_target();
        // Serial.println("Normal");
        vTaskDelay(25 / portTICK_PERIOD_MS);
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
    get_data_from_eeprom();

    float fl2 = 1, fl1 = 1, fm = 1, fr1 = 1, fr2 = 1;
    float ll2 = 1, ll1 = 1, lm = 1, lr1 = 1, lr2 = 1;
    float rl2 = 1, rl1 = 1, rm = 1, rr1 = 1, rr2 = 1;
    float bl2 = 1, bl1 = 1, bm = 1, br1 = 1, br2 = 1;

    while (1)
    {
        if (Serial.available())
        {
            vTaskDelay(10 / portTICK_PERIOD_MS);
            String ls = Serial.readStringUntil('\n');

            if (ls == "stb")
            {
                for (int i = 0; i < 20; i++)
                {
                    ad_refs_black[i] = ad_refs_current[i];
                }

                save_data_to_eeprom();
                continue;
            }
            else if (ls == "stw")
            {
                for (int i = 0; i < 20; i++)
                {
                    ad_refs_white[i] = ad_refs_current[i];
                }

                save_data_to_eeprom();
                continue;
            }
            else if (ls == "infof")
            {
                Serial.printf("FRONT 1:%d,%d,%d\n", ad_refs_current[10], ad_refs_black[10], ad_refs_white[10]); // ad_refs_current
                Serial.printf("FRONT 2:%d,%d,%d\n", ad_refs_current[11], ad_refs_black[11], ad_refs_white[11]);
                Serial.printf("FRONT 3:%d,%d,%d\n", ad_refs_current[12], ad_refs_black[12], ad_refs_white[12]);
                Serial.printf("FRONT 4:%d,%d,%d\n", ad_refs_current[13], ad_refs_black[13], ad_refs_white[13]);
                Serial.printf("FRONT 5:%d,%d,%d\n", ad_refs_current[14], ad_refs_black[14], ad_refs_white[14]);
                Serial.println();

                continue;
            }

            else if (ls == "infor")
            {
                Serial.printf("RIGHT 1:%d,%d,%d\n", ad_refs_current[0], ad_refs_black[0], ad_refs_white[0]); // ad_refs_current
                Serial.printf("RIGHT 2:%d,%d,%d\n", ad_refs_current[1], ad_refs_black[1], ad_refs_white[1]);
                Serial.printf("RIGHT 3:%d,%d,%d\n", ad_refs_current[2], ad_refs_black[2], ad_refs_white[2]);
                Serial.printf("RIGHT 4:%d,%d,%d\n", ad_refs_current[3], ad_refs_black[3], ad_refs_white[3]);
                Serial.printf("RIGHT 5:%d,%d,%d\n", ad_refs_current[4], ad_refs_black[4], ad_refs_white[4]);
                Serial.println();

                continue;
            }

            else if (ls == "infob")
            {
                Serial.printf("BACK 1:%d,%d,%d\n", ad_refs_current[5], ad_refs_black[5], ad_refs_white[5]); // ad_refs_current
                Serial.printf("BACK 2:%d,%d,%d\n", ad_refs_current[6], ad_refs_black[6], ad_refs_white[6]);
                Serial.printf("BACK 3:%d,%d,%d\n", ad_refs_current[7], ad_refs_black[7], ad_refs_white[7]);
                Serial.printf("BACK 4:%d,%d,%d\n", ad_refs_current[8], ad_refs_black[8], ad_refs_white[8]);
                Serial.printf("BACK 5:%d,%d,%d\n", ad_refs_current[9], ad_refs_black[9], ad_refs_white[9]);
                Serial.println();

                continue;
            }

            else if (ls == "infol")
            {
                Serial.printf("LEFT 1:%d,%d,%d\n", ad_refs_current[15], ad_refs_black[15], ad_refs_white[15]); // ad_refs_current
                Serial.printf("LEFT 2:%d,%d,%d\n", ad_refs_current[16], ad_refs_black[16], ad_refs_white[16]);
                Serial.printf("LEFT 3:%d,%d,%d\n", ad_refs_current[17], ad_refs_black[17], ad_refs_white[17]);
                Serial.printf("LEFT 4:%d,%d,%d\n", ad_refs_current[18], ad_refs_black[18], ad_refs_white[18]);
                Serial.printf("LEFT 5:%d,%d,%d\n", ad_refs_current[19], ad_refs_black[19], ad_refs_white[19]);
                Serial.println();

                continue;
            }

            else if (ls == "all")
            {
                get_value_with_index(0, fl2, fl1, fm, fr1, fr2);
                get_value_with_index(1, ll2, ll1, lm, lr1, lr2);
                get_value_with_index(2, rl2, rl1, rm, rr1, rr2);
                get_value_with_index(3, bl2, bl1, bm, br1, br2);

                Serial.print("FRONT : ");
                Serial.print(fl2);
                Serial.print(", ");
                Serial.print(fl1);
                Serial.print(", ");
                Serial.print(fm);
                Serial.print(", ");
                Serial.print(fr1);
                Serial.print(", ");
                Serial.print(fr2);
                Serial.print(", ");
                Serial.println();

                Serial.print("LEFT : ");
                Serial.print(ll2);
                Serial.print(", ");
                Serial.print(ll1);
                Serial.print(", ");
                Serial.print(lm);
                Serial.print(", ");
                Serial.print(lr1);
                Serial.print(", ");
                Serial.print(lr2);
                Serial.print(", ");
                Serial.println();

                Serial.print("BACK : ");
                Serial.print(bl2);
                Serial.print(", ");
                Serial.print(bl1);
                Serial.print(", ");
                Serial.print(bm);
                Serial.print(", ");
                Serial.print(br1);
                Serial.print(", ");
                Serial.print(br2);
                Serial.print(", ");
                Serial.println();

                Serial.print("RIGHT : ");
                Serial.print(rl2);
                Serial.print(", ");
                Serial.print(rl1);
                Serial.print(", ");
                Serial.print(rm);
                Serial.print(", ");
                Serial.print(rr1);
                Serial.print(", ");
                Serial.print(rr2);
                Serial.print(", ");
                Serial.println();
            }

            else if (ls == "pos")
            {
                Serial.println("F, L, R, B");
                Serial.print(get_line_pos_with_trac(0));
                Serial.print(", ");
                Serial.print(get_line_pos_with_trac(1));
                Serial.print(", ");
                Serial.print(get_line_pos_with_trac(2));
                Serial.print(", ");
                Serial.print(get_line_pos_with_trac(3));
                Serial.println();
            }

            else if (ls == "width")
            {
                Serial.println("F, L, R, B");
                Serial.print(get_line_width(0));
                Serial.print(", ");
                Serial.print(get_line_width(1));
                Serial.print(", ");
                Serial.print(get_line_width(2));
                Serial.print(", ");
                Serial.print(get_line_width(3));
                Serial.println();
            }

            else if (ls == "cas")
            {
                Serial.println("F, L, R, B");
                Serial.print(get_crash_raw(0));
                Serial.print(", ");
                Serial.print(get_crash_raw(1));
                Serial.print(", ");
                Serial.print(get_crash_raw(2));
                Serial.print(", ");
                Serial.print(get_crash_raw(3));
                Serial.println();
            }

            else if (ls == "inc")
            {
                if (get_whether_in_cross())
                    Serial.println("True");
                else
                    Serial.println("False");
            }

            else if (ls == "start")
            {
                on_start_flag = true;
            }

            else if (ls == "w1")
            {
                arm_ctrl_params[1] = 1;
            }
            else if (ls == "w2")
            {
                arm_ctrl_params[1] = 0;
            }

            else if (ls == "s1")
            {
                arm_ctrl_params[1] = -1;
            }
            else if (ls == "s2")
            {
                arm_ctrl_params[1] = 0;
            }

            else if (ls == "a1")
            {
                arm_ctrl_params[3] = 1;
            }
            else if (ls == "a2")
            {
                arm_ctrl_params[3] = 0;
            }

            else if (ls == "d1")
            {
                arm_ctrl_params[3] = -1;
            }
            else if (ls == "d2")
            {
                arm_ctrl_params[3] = 0;
            }

            else if (ls == "i1")
            {
                arm_ctrl_params[2] = 1;
            }
            else if (ls == "i2")
            {
                arm_ctrl_params[2] = 0;
            }

            else if (ls == "k1")
            {
                arm_ctrl_params[2] = -1;
            }
            else if (ls == "k2")
            {
                arm_ctrl_params[2] = 0;
            }

            else if (ls == "j1")
            {
                arm_ctrl_params[0] = 1;
            }
            else if (ls == "j2")
            {
                arm_ctrl_params[0] = 0;
            }

            else if (ls == "l1")
            {
                arm_ctrl_params[0] = -1;
            }
            else if (ls == "l2")
            {
                arm_ctrl_params[0] = 0;
            }

            else if (ls == "p1")
            {
                on_start_flag = true;
            }
        
            else if (ls == "f")
            {
                GO_STRAIGHT;
            }else if (ls == "r")
            {
                TURN_RIGHT;
            }else if (ls == "l")
            {
                TURN_LEFT;
            }else if (ls == "b")
            {
                GO_BACK;
            }else if (ls == "s")
            {
                STAY_STATIC;
            }
        
            else if (ls == "eney_stop")
            {
                vTaskSuspend(x_tasks[3]);
                STAY_STATIC;
            }
            else
            {
                sprintf(Screen_Console_Text[1]," [%s] ",ls.c_str());
            }
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void Task_Wheel(void *param)
{
    while (1)
    {
        for (int i = 0; i < 4; i++)
        {
            if (arm_ctrl_params[i] == 1)
            {
                if(Data_Arms[i] + 4 < PULSE_MAX)
                    Data_Arms[i] += 4;
            }
            if (arm_ctrl_params[i] == -1)
            {
                if(Data_Arms[i] - 4 > PULSE_MIN)
                    Data_Arms[i] -= 4;
            }
        }
        arm_flush();

        sprintf(Screen_Console_Text[0]," [No Debugger] ");
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
}