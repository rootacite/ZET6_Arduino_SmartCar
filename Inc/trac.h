#include "Arduino.h"

#include "Wire.h"

#define MIN0(x) ((x) < 0 ? 0 : (x))
#define MAX1(x) ((x) > 1 ? 1 : (x))
/* float TRAC_FRONT(int x)
{
    float current_offset = MIN0(ad_refs_current[10 + x] - ad_refs_black[10 + x]);
    float max_range = ad_refs_white[10 + x] - ad_refs_black[10 + x];

    return MAX1(current_offset / max_range);
}
 */
#define TRAC_FRONT(x) MAX1(MIN0(ad_refs_current[10 + x] - ad_refs_black[10 + x]) / (float)(ad_refs_white[10 + x] - ad_refs_black[10 + x]))
#define TRAC_RIGHT(x) MAX1(MIN0(ad_refs_current[x] - ad_refs_black[x]) / (float)(ad_refs_white[x] - ad_refs_black[x]))
#define TRAC_BACK(x) MAX1(MIN0(ad_refs_current[5 + x] - ad_refs_black[5 + x]) / (float)(ad_refs_white[5 + x] - ad_refs_black[5 + x]))
#define TRAC_LEFT(x) MAX1(MIN0(ad_refs_current[15 + x] - ad_refs_black[15 + x]) / (float)(ad_refs_white[15 + x] - ad_refs_black[15 + x]))

void get_value_with_index(int index, float &l2, float &l1, float &m, float &r1, float &r2);

float get_line_pos_with_trac(int index);

float get_line_width(int index);

bool get_crash_raw(int index);

bool get_whether_in_cross();
