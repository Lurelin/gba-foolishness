#include <stdio.h>
#include "toolbox.hpp"

int main()
{// or CLR_BLUE

    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

    m3_plot( 120, 80, 0b111110000000000 );
    m3_plot( 136, 80, 0b000001111100000 );
    m3_plot( 120, 96, 0b000000000011111 );    
    while(1);

    return 0;
}