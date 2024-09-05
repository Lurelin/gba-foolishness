#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "toolbox.h"
#include "data.h"

Vector2 cursorPos = {0,10};
Vector2 screenPos = {0,0};
vu16 keyInput;
u8 cursorHold;
u8 cursorSpeed;


INLINE void updateCursorSprite() {
    obj_attr_mem[0].attr0 = ATTR0_Y(8 * cursorPos.y);
    obj_attr_mem[0].attr1 = ATTR1_X(8 * cursorPos.x);
}

void updateCursorPos() {
    keyInput = *((vu16*)(MEM_IO + 0x0130));
    if (((keyInput & 0x00F0)) != 0x00F0) {
        cursorHold++;
        if ((cursorHold > 15)) {
            if (!(keyInput & KEY_LEFT)  && cursorPos.x > 0)  {cursorPos.x--;}
            if (!(keyInput & KEY_RIGHT) && cursorPos.x < 29) {cursorPos.x++;}
            if (!(keyInput & KEY_UP)    && cursorPos.y > 0)  {cursorPos.y--;}
            if (!(keyInput & KEY_DOWN)  && cursorPos.y < 19) {cursorPos.y++;}
            if (cursorSpeed < 3) {
                cursorHold = 0;
                cursorSpeed++;
            } else {
                cursorHold = 10;
            }
        }
    } else {
        cursorHold = 15;
        cursorSpeed = 0;
    }
}

int main()
{
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ;
    REG_BG0CNT = BG_4BPP | BG_SIZE_32x32 | BG_CBB(0) | BG_SBB(8);
    obj_palette_mem[0] = gamePalette;
    
    obj_tile4_mem[1] = cursorTile;
    obj_attr_mem[0].attr2 = ATTR2_TILE(1);

    updateCursorSprite();
    
    while(1) {
        vid_vsync();
        updateCursorPos();
        updateCursorSprite();
    };
}