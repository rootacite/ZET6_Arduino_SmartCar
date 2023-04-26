
#include "def.h"

int n_speed_wheel = 1200;

void set_left_motor(bool iof, bool dir = false)
{
    analogWriteResolution(8);
    analogWriteFrequency(n_speed_wheel);

    digitalWrite(LEFT_DIR, dir);

    analogWrite(LEFT_STP, iof ? 128 : 0);
}

void set_right_motor(bool iof, bool dir = false)
{
    analogWriteResolution(8);
    analogWriteFrequency(n_speed_wheel);

    digitalWrite(RIGHT_DIR, !dir);

    analogWrite(RIGHT_STP, iof ? 128 : 0);
}

void set_back_motor(bool iof, bool dir = false)
{
    analogWriteResolution(8);
    analogWriteFrequency(n_speed_wheel);

    digitalWrite(BACK_DIR, dir);

    analogWrite(BACK_STP, iof ? 128 : 0);
}

#define GO_STRAIGHT n_speed_wheel = 3000;\
                    set_left_motor(1);\
                    set_right_motor(1);\
                    set_back_motor(0);

#define GO_BACK n_speed_wheel = 3000;\
                set_left_motor(1, 1);\
                set_right_motor(1, 1);\
                set_back_motor(0);

#define TURN_LEFT n_speed_wheel = 800;\
                  set_left_motor(1, 1);\
                  set_right_motor(1);\
                  set_back_motor(1, 1);

#define TURN_RIGHT n_speed_wheel = 800;\
                   set_left_motor(1);\
                   set_right_motor(1, 1);\
                   set_back_motor(1);

#define STAY_STATIC  set_left_motor(0);\
                     set_right_motor(0);\
                     set_back_motor(0);