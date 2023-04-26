
#include "def.h"

// h 
uint16_t Data_Arms[5] = {4270, 5245, 5000, 4915, PULSE_MIN + 950};

void arm_flush()
{
    analogWriteResolution(16);
    analogWriteFrequency(50);

    analogWrite(HAND, Data_Arms[0]);
    analogWrite(ARM_ROUND, Data_Arms[1]);
    analogWrite(ARM_UPDOWM, Data_Arms[2]);
    analogWrite(ARM_FB, Data_Arms[3]);
    analogWrite(PLANT, Data_Arms[4]);
}
