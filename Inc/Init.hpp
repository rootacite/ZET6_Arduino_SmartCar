
#include <Arduino.h>

#include <SPI.h>

#include <nRF24L01.h>
#include <RF24.h>

#include "Inc/fsmc.hpp"
#include "Inc/bsp_ili9341_lcd.h"

#include "def.h"

SPIClass HSPI2(PB15, PB14, PB13);
RF24* RADIO1=NULL;

const byte address[5] = {0xFF, 0xDD, 0xEE, 0xAA, 0x22};

/////////////////////////////
///Defintion of Tracking Pins
/////////////////////////////

#define TRACKING_FRONT_1 PF0
#define TRACKING_FRONT_2 PF1
#define TRACKING_FRONT_3 PF2
#define TRACKING_FRONT_4 PF3
#define TRACKING_FRONT_5 PF4

#define TRACKING_LEFT_1 PE1
#define TRACKING_LEFT_2 PE3
#define TRACKING_LEFT_3 PE4
#define TRACKING_LEFT_4 PE5
#define TRACKING_LEFT_5 PE6

#define TRACKING_RIGHT_1 PF6
#define TRACKING_RIGHT_2 PF7
#define TRACKING_RIGHT_3 PF8
#define TRACKING_RIGHT_4 PF9
#define TRACKING_RIGHT_5 PF10

#define TRACKING_BACK_1 PG2
#define TRACKING_BACK_2 PG3
#define TRACKING_BACK_3 PG4
#define TRACKING_BACK_4 PG5
#define TRACKING_BACK_5 PG7

/////////////////////////////
///Defintion of Motor Pins
/////////////////////////////

#define FRONT_EN PC6
#define FRONT_STP PB9
#define FRONT_DIR PG0

#define LEFT_EN PD13
#define LEFT_STP PA3
#define LEFT_DIR PF15

#define RIGHT_EN PD12
#define RIGHT_STP PA2
#define RIGHT_DIR PF14

#define BACK_EN PB8
#define BACK_STP PA1
#define BACK_DIR PF13

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

    // Front Motor
    pinMode(FRONT_EN, OUTPUT);
    digitalWrite(FRONT_EN, LOW);
    pinMode(FRONT_STP, OUTPUT);
    digitalWrite(FRONT_STP, LOW);
    pinMode(FRONT_DIR, OUTPUT);
    digitalWrite(FRONT_DIR, LOW);

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