
#include "Inc/Init.hpp"
#include "Inc/tasks.h"

#include "Wire.h"
#include "EEPROM.h"

TaskHandle_t x_tasks[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
extern bool _on_ends_show;

extern uint8_t ad_refs_black[];
extern uint8_t ad_refs_white[];
extern uint8_t ad_refs_current[];

extern bool flag_en_21;

void setup()
{
  Wire.begin();
  Wire.setClock(400000);

  

  SetupInit();

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
      2,
      &x_tasks[3]);

  xTaskCreate(
      Task_IICLight,
      "TaskIIC",
      1024,
      nullptr,
      1,
      &x_tasks[4]);

  
    xTaskCreate(
        Task_Radio,
        "TaskRadio",
        4096,
        nullptr,
        1,
        &x_tasks[1]);
  
 xTaskCreate(
        Task_Wheel,
        "TaskArm",
        1024,
        nullptr,
        1,
        &x_tasks[2]);
  vTaskStartScheduler();
}

void loop()
{
  delay(350);
}
