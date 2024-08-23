#include <stdio.h>
#include <stdbool.h>
#include "toolbox.hpp"

int main()
{
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
    int y = 0;
    while (true) {
        vid_vsync();
        if (y < SCREEN_HEIGHT) {
            m3_plot(12, y, 0b111110000000000);
            if (y - 1 != -1) {
                m3_plot(12, y - 1, 0);
            } else {
                m3_plot(12, 159, 0);
            }
            y++;
        } else {
            y = 0;
        }
    }    
    return 0;
}