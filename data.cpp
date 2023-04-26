
#include "Inc/data.h"

extern uint8_t ad_refs_black[];
extern uint8_t ad_refs_white[];
extern uint8_t ad_refs_current[];

void get_data_from_eeprom()
{
    for(int i=0;i<20;i++)
    {
        ad_refs_black[i] = EEPROM.read(i);
    }

    for(int i=20;i<40;i++)
    {
        ad_refs_white[i - 20] = EEPROM.read(i);
    }
}

//EEPROM.write(i, Ipm_Data[i]);
void save_data_to_eeprom()
{
    for(int i=0;i<20;i++)
    {
        EEPROM.write(i, ad_refs_black[i]);
    }

    for(int i=20;i<40;i++)
    {
         EEPROM.write(i, ad_refs_white[i - 20]);
    }
}