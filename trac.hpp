
// Defines the Current Trac Value
uint8_t ad_refs_current[20] = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0};

// Defines the Trac Value in Black Line
const uint8_t ad_refs_black[20] = {
    // ch1
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    // ch2
    26, 27, 24, 25, 36,
    0, 0, 0, 0, 0};

// Defines the Trac Value in White Area
const uint8_t ad_refs_white[20] = {
    // ch1
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    // ch2
    54, 57, 50, 52, 86,
    0, 0, 0, 0, 0};

#define MIN0(x) ((x) < 0 ? 0 : (x))

#define TRAC_FRONT(x) (MIN0(ad_refs_current[10 + x] - ad_refs_black[10 + x]) / (float)(ad_refs_white[10 + x] - ad_refs_black[10 + x]))
#define TRAC_BACK(x) (MIN0(ad_refs_current[x] - ad_refs_black[x]) / (float)(ad_refs_white[x] - ad_refs_black[x]))
#define TRAC_LEFT(x) (MIN0(ad_refs_current[5 + x] - ad_refs_black[5 + x]) / (float)(ad_refs_white[5 + x] - ad_refs_black[5 + x]))
#define TRAC_RIGHT(x) (MIN0(ad_refs_current[15 + x] - ad_refs_black[15 + x]) / (float)(ad_refs_white[15 + x] - ad_refs_black[15 + x]))

void get_value_with_index(int index, float &l2, float &l1, float &m, float &r1, float &r2)
{
    // index 0 ~ 3 F L R B
    switch (index)
    {
    case 0:
        l2 = 1 - TRAC_FRONT(0);
        l1 = 1 - TRAC_FRONT(1);
        m = 1 - TRAC_FRONT(2);
        r1 = 1 - TRAC_FRONT(3);
        r2 = 1 - TRAC_FRONT(4);

    case 1:
        l2 = 1 - TRAC_LEFT(0);
        l1 = 1 - TRAC_LEFT(1);
        m = 1 - TRAC_LEFT(2);
        r1 = 1 - TRAC_LEFT(3);
        r2 = 1 - TRAC_LEFT(4);

    case 2:
        l2 = 1 - TRAC_RIGHT(0);
        l1 = 1 - TRAC_RIGHT(1);
        m = 1 - TRAC_RIGHT(2);
        r1 = 1 - TRAC_RIGHT(3);
        r2 = 1 - TRAC_RIGHT(4);

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

    float marginalization = ((l2 + l1 * 0.5) - (r1 * 0.5 + r2)) / 2;
    marginalization *= 1 - m;

    return marginalization;
}

float get_line_width(int index)
{
    float l2, l1, m, r1, r2;
    get_value_with_index(index, l2, l1, m, r1, r2);

    return l2 + l1 + m + r1 + r2;
}

bool get_catch_raw(int index)
{
    float l2, l1, m, r1, r2;
    get_value_with_index(index, l2, l1, m, r1, r2);
    float pos = get_line_pos_with_trac(index);

    if (abs(pos) < 0.2 && get_line_width(index) > 2.5)
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

    f = get_line_pos_with_trac(0);
    l = get_line_pos_with_trac(1);
    r = get_line_pos_with_trac(2);
    b = get_line_pos_with_trac(3);

    if(f < 0.2 && l < 0.2 && r < 0.2 && b < 0.2)
    {
        return true;
    }
    return false;
}