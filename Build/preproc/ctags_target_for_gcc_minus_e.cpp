# 1 "E:\\DeskTopTools\\ZET6App\\ZET6App.ino"

# 3 "E:\\DeskTopTools\\ZET6App\\ZET6App.ino" 2
# 4 "E:\\DeskTopTools\\ZET6App\\ZET6App.ino" 2

TaskHandle_t x_tasks[2]={
# 5 "E:\\DeskTopTools\\ZET6App\\ZET6App.ino" 3 4
                        __null
# 5 "E:\\DeskTopTools\\ZET6App\\ZET6App.ino"
                            , 
# 5 "E:\\DeskTopTools\\ZET6App\\ZET6App.ino" 3 4
                              __null
# 5 "E:\\DeskTopTools\\ZET6App\\ZET6App.ino"
                                  };

void setup()
{
  SetupInit();

  xTaskCreate(
      Task_Screen,
      "TaskScreen",
      1024,
      
# 15 "E:\\DeskTopTools\\ZET6App\\ZET6App.ino" 3 4
     __null
# 15 "E:\\DeskTopTools\\ZET6App\\ZET6App.ino"
         ,
      1,
      &x_tasks[0]);


  xTaskCreate(
      Task_Radio,
      "TaskRadio",
      1024,
      
# 24 "E:\\DeskTopTools\\ZET6App\\ZET6App.ino" 3 4
     __null
# 24 "E:\\DeskTopTools\\ZET6App\\ZET6App.ino"
         ,
      1,
      &x_tasks[1]);

  vTaskStartScheduler();
}

void loop()
{
  delay(100);
}
