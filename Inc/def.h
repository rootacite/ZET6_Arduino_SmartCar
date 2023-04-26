
#ifndef _H_DEF
#define _H_DEF

typedef bool(*BOOL_CONDITION)();

struct TxData
{
    uint8_t sz;
    uint8_t dt[31];
};

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

#define LEFT_EN PB8
#define LEFT_STP PA1
#define LEFT_DIR PF13

#define RIGHT_EN PD13
#define RIGHT_STP PA3
#define RIGHT_DIR PF15

#define BACK_EN PD12
#define BACK_STP PA2
#define BACK_DIR PF14

#define HAND PA6
#define ARM_UPDOWM PB0
#define ARM_ROUND PA7
#define ARM_FB PB1

#define PLANT PB6

#define PULSE_MAX 8192
#define PULSE_MIN 1637
#define PULSE_MID 4915

#endif