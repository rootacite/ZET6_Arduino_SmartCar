#line 1 "E:\\DeskTopTools\\ZET6App\\Inc\\Init.hpp"

#include <Arduino.h>

#include <SPI.h>

#include <nRF24L01.h>
#include <RF24.h>

#include "Inc/fsmc.hpp"
#include "Inc/bsp_ili9341_lcd.h"

#include "def.h"

#define Emm42_En_Pin PC6  // the number of the Emm42_En_pin
#define Emm42_Stp_Pin PB9 // the number of the Emm42_Stp_pin
#define Emm42_Dir_Pin PG0 // the number of the Emm42_Dir_pin

SPIClass HSPI2(PB15, PB14, PB13);
RF24* RADIO1=NULL;

const byte address[5] = {0xFF, 0xDD, 0xEE, 0xAA, 0x22};

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
    pinMode(FRONT_EN, OUTPUT);
    digitalWrite(FRONT_EN, LOW);
    pinMode(FRONT_STP, OUTPUT);
    digitalWrite(FRONT_STP, LOW);
    pinMode(FRONT_DIR, OUTPUT);
    digitalWrite(FRONT_DIR, LOW);

    /////////////////////////////////////////
    /// Init 2.4G Communication
    /////////////////////////////////////////

    RADIO1 = new RF24(PG15, PG8);

    bool r = RADIO1->begin(&HSPI2);

    while (!r)
        delay(1);

    RADIO1->setDataRate(RF24_1MBPS);
    RADIO1->setPALevel(RF24_PA_MIN);
    RADIO1->setChannel(37);
    RADIO1->setCRCLength(RF24_CRC_16);
    RADIO1->openReadingPipe(0, address);
    RADIO1->startListening();
}