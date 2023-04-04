
#include "Inc/Init.hpp"
#include "Inc/tasks.h"

TaskHandle_t x_tasks[2]={NULL, NULL};

void setup()
{
  SetupInit();

  xTaskCreate(
      Task_Screen,     
      "TaskScreen",   
      1024,    
      NULL,         
      1,
      &x_tasks[0]); 

      
  xTaskCreate(
      Task_Radio,     
      "TaskRadio",   
      1024,    
      NULL,         
      1,
      &x_tasks[1]); 

  vTaskStartScheduler();
}

void loop()
{
  delay(100);
}
