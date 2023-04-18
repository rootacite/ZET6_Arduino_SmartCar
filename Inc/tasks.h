
#include <Arduino.h>
#include <STM32FreeRTOS.h>

void Task_Screen(void *param);
void Task_Radio(void *param);
void Task_Wheel(void *param);
void Task_Main(void *param);
void Task_IICLight(void *param);

/*if (radio.available())
    {
        radio.read(&buffer, sizeof(buffer));

        *(char *)(&buffer[0] + 1 + buffer[0]) = 0;

        for (int position = 0; position < 8; position++)
        {
            digitalWrite(Pins[position], buffer[1 + position]);
        }
    }*/