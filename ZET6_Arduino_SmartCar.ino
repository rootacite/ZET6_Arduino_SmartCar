
#include "Inc/Init.hpp"
#include "Inc/tasks.h"

#include "Wire.h"

TaskHandle_t x_tasks[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
extern bool _on_ends_show;

extern bool flag_en_21;

TwoWire iic1(PB11, PB10);

void setup()
{
  SetupInit();

  iic1.begin();
  iic1.setClock(400000);

  xTaskCreate(
       Task_Screen,
       "TaskScreen",
       1024,
       nullptr,
       1,
       &x_tasks[0]);

   xTaskCreate(
       Task_Main,
       "TaskMain",
       1024,
       nullptr,
       1,
       &x_tasks[3]);

   xTaskCreate(
       Task_IICLight,
       "TaskIIC",
       1024,
       nullptr,
       1,
       &x_tasks[4]);
 
  /*
    xTaskCreate(
        Task_Radio,
        "TaskRadio",
        1024,
        nullptr,
        1,
        &x_tasks[1]);
  */
  

   vTaskStartScheduler();
}

void loop()
{
  delay(350);
}
