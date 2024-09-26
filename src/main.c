#include <stdlib.h>
#include <string.h>
#include "toolbox.h"
#include "engine.h"
#include "graphics.h"
static u32 debugInts[2] = {1234567890,0};
int main() {
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
    debugInts[1] = 69;
    initGraphics();
    while(1) {
        vid_vsync();
        moveCursor();
        buttonsAB();
        drawCursor();


        //For debug
        if (~REG_KEYINPUT & KEY_L) {
            for (int objX = 0; objX < OBJECTMAP_WIDTH; objX++) {
                for (int objY = 0; objY < OBJECTMAP_HEIGHT; objY++) {
                    m3_plot((SCREEN_WIDTH - OBJECTMAP_WIDTH)/2 + objX, (SCREEN_HEIGHT - OBJECTMAP_HEIGHT)/2 + objY, RGB15(flowMap[objX][objY], 0, 0));
                }
            }
        }
        if (~REG_KEYINPUT & KEY_R) {
            initGraphics();
        }
    };
    return 0;
}