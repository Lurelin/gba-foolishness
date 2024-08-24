#include <stdio.h>
#include <stdbool.h>
#include "toolbox.h"
#include "data.h"

int main()
{
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
    m3_plot(8, 8, 0b111110000011010);
    m3_plot(8, 16, colour(26,0,31));
    m3_plot(16, 8, 0b111110000000000);
    m3_plot(16, 16, colour(0,0,31));

    while(1);
}