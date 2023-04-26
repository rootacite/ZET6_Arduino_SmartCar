
#include <Arduino.h>

#include <SPI.h>

#include <nRF24L01.h>
#include <RF24.h>

#include "Inc/fsmc.hpp"
#include "Inc/bsp_ili9341_lcd.h"

#include "def.h"
#include "Inc/mpu.h"

SPIClass HSPI2(PB15, PB14, PB13);
RF24 *RADIO1 = nullptr;

const byte address[5] = {0xFF, 0xDD, 0xEE, 0xAA, 0x22};
HardwareSerial Serial_3(PD9, PD8);

void SetupInit()
{

    /////////////////////////////////////////
    /// Make Sure that All Pin Clock is Enable
    /////////////////////////////////////////
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /////////////////////////
    /// Pull up BK and RST Pin
    /////////////////////////

    Serial2.setRx(PA10);
    Serial2.setTx(PA9);
    Serial2.begin(115200);

    //Serial_3.begin(115200);

    /////////////////////////
    /// Pull up BK and RST Pin
    /////////////////////////
    pinMode(PG6, OUTPUT);
    pinMode(PG11, OUTPUT);
    digitalWrite(PG6, LOW);
    digitalWrite(PG11, LOW);

    /////////////////////
    /// Init FSMC and LCD
    /////////////////////
    MX_FSMC_Init();
    ILI9341_Init();
    ILI9341_GramScan(3);

    /////////////////////////////////////////
    /// Init Stepper Motor Pins
    /////////////////////////////////////////

    // Left Motor

    pinMode(LEFT_EN, OUTPUT);
    digitalWrite(LEFT_EN, LOW);
    pinMode(LEFT_STP, OUTPUT);
    digitalWrite(LEFT_STP, LOW);
    pinMode(LEFT_DIR, OUTPUT);
    digitalWrite(LEFT_DIR, LOW);

    // Right Motor

    pinMode(RIGHT_EN, OUTPUT);
    digitalWrite(RIGHT_EN, LOW);
    pinMode(RIGHT_STP, OUTPUT);
    digitalWrite(RIGHT_STP, LOW);
    pinMode(RIGHT_DIR, OUTPUT);
    digitalWrite(RIGHT_DIR, LOW);

    // Back Motor

    pinMode(BACK_EN, OUTPUT);
    digitalWrite(BACK_EN, LOW);
    pinMode(BACK_STP, OUTPUT);
    digitalWrite(BACK_STP, LOW);
    pinMode(BACK_DIR, OUTPUT);
    digitalWrite(BACK_DIR, LOW);

    //////////////
    /// Init Hand
    //////////////

    pinMode(HAND, OUTPUT);
    pinMode(ARM_UPDOWM, OUTPUT);
    pinMode(ARM_ROUND, OUTPUT);
    pinMode(ARM_FB, OUTPUT);
    pinMode(PLANT, OUTPUT);


    /////////////////////////////////////////
    /// Init 2.4G Communication
    /////////////////////////////////////////

   /*  RADIO1 = new RF24(PG15, PG8);

    bool r = RADIO1->begin(&HSPI2);

    while (!r)
        return;

    RADIO1->setDataRate(RF24_1MBPS);
    RADIO1->setPALevel(RF24_PA_MIN);
    RADIO1->setChannel(37);
    RADIO1->setCRCLength(RF24_CRC_16);
    RADIO1->openReadingPipe(0, address);
    RADIO1->startListening(); */

    /////////////////
    /// Init MPU6050
    /////////////////
    

}