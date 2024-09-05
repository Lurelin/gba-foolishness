#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "toolbox.h"
#include "data.h"

Vector2 cursorPos = {0,8};
Vector2 screenPos = {0,0};
vu16 keyInput;
u8 cursorHold;
u8 cursorSpeed;

INLINE void updateCursorSprite() {
    obj_attr_mem[0].attr0 = (obj_attr_mem[0].attr0 & ~(ATTR0_Y_MASK)) | ATTR0_Y(16 * cursorPos.y);
    obj_attr_mem[0].attr1 = (obj_attr_mem[0].attr1 & ~(ATTR1_X_MASK)) | ATTR1_X(16 * cursorPos.x);
}

void updateCursorPos() {
    keyInput = *((vu16*)(MEM_IO + 0x0130));
    if (((keyInput & 0x00F0)) != 0x00F0) {
        cursorHold++;
        if ((cursorHold > 15)) {
            if (!(keyInput & KEY_LEFT)  && cursorPos.x > 0)  {cursorPos.x--;}
            if (!(keyInput & KEY_RIGHT) && cursorPos.x < 14) {cursorPos.x++;}
            if (!(keyInput & KEY_UP)    && cursorPos.y > 0)  {cursorPos.y--;}
            if (!(keyInput & KEY_DOWN)  && cursorPos.y < 9) {cursorPos.y++;}
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
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;
    REG_BG0CNT = BG_4BPP | BG_SIZE_32x32 | BG_CBB(0) | BG_SBB(8);
    obj_palette_mem[0] = gamePalette;
    
    memcpy(&obj_tile4_mem[1], cursorTiles, sizeof(cursorTiles));
    obj_attr_mem[0].attr2 = ATTR2_TILE(1);
    obj_attr_mem[0].attr1 = ATTR1_SIZE_2x2;
    obj_attr_mem[0].attr0 = ATTR0_SQUARE;

    updateCursorSprite();
    
    while(1) {
        vid_vsync();
        updateCursorPos();
        updateCursorSprite();
    };
}