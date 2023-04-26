
#include "Inc/trac.h"

// Defines the Current Trac Value
uint8_t ad_refs_current[20] = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0};

// Defines the Trac Value in Black Line
uint8_t ad_refs_black[20] = {
    // ch1
    20, 20, 15, 20, 30,
    35, 30, 30, 30, 35,
    // ch2
    40, 35, 20, 30, 35,
    35, 25, 25, 20, 15};

// Defines the Trac Value in White Area
uint8_t ad_refs_white[20] = {
    // ch1
    105, 135, 110, 95, 125,
    135, 120, 100, 115, 105,
    // ch2
    95, 95, 85, 90, 130,
    90, 85, 95, 75, 65};

void get_value_with_index(int index, float &l2, float &l1, float &m, float &r1, float &r2)
{
    Wire.requestFrom(0x20, 10);
    for (int i = 0; i < 10;)
    {
        if (Wire.available())
        {
            ad_refs_current[i] = Wire.read();
            i++;
        }
    }

    Wire.requestFrom(0x21, 10);
    for (int i = 0; i < 10;)
    {
        if (Wire.available())
        {
            ad_refs_current[i + 10] = Wire.read();
            i++;
        }
    }
    // index 0 ~ 3 F L R B
    switch (index)
    {
    case 0:
        l2 = 1 - TRAC_FRONT(0);
        l1 = 1 - TRAC_FRONT(1);
        m = 1 - TRAC_FRONT(2);
        r1 = 1 - TRAC_FRONT(3);
        r2 = 1 - TRAC_FRONT(4);
        break;
    case 1:
        l2 = 1 - TRAC_LEFT(0);
        l1 = 1 - TRAC_LEFT(1);
        m = 1 - TRAC_LEFT(2);
        r1 = 1 - TRAC_LEFT(3);
        r2 = 1 - TRAC_LEFT(4);
        break;
    case 2:
        l2 = 1 - TRAC_RIGHT(0);
        l1 = 1 - TRAC_RIGHT(1);
        m = 1 - TRAC_RIGHT(2);
        r1 = 1 - TRAC_RIGHT(3);
        r2 = 1 - TRAC_RIGHT(4);
        break;
    case 3:
        l2 = 1 - TRAC_BACK(0);
        l1 = 1 - TRAC_BACK(1);
        m = 1 - TRAC_BACK(2);
        r1 = 1 - TRAC_BACK(3);
        r2 = 1 - TRAC_BACK(4);
    default:
        break;
    }
}

float get_line_pos_with_trac(int index)
{
    float l2, l1, m, r1, r2;
    get_value_with_index(index, l2, l1, m, r1, r2);

    float marginalization = ((l2 * 2 + l1) - (r1 + r2 * 2)) / 2;
    // marginalization *= 1 - m;

    return marginalization;
}

float get_line_width(int index)
{
    float l2, l1, m, r1, r2;
    get_value_with_index(index, l2, l1, m, r1, r2);

    return l2 + l1 + m + r1 + r2;
}

bool get_crash_raw(int index)
{
    float l2, l1, m, r1, r2;
    get_value_with_index(index, l2, l1, m, r1, r2);
    float pos = get_line_pos_with_trac(index);

    if (abs(pos) < 0.2 && get_line_width(index) > 3.5)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool get_whether_in_cross()
{
    float f, l, r, b;

    f = TRAC_FRONT(2);
    l = TRAC_LEFT(2);
    r = TRAC_RIGHT(2);
    b = TRAC_BACK(2);

    if (f > 0.5 && l > 0.5 && r > 0.5 && b > 0.5)
    {
        return true;
    }
    return false;
}
