#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "toolbox.h"
#include "data.h"

Vector2 cursorPos = {0,0};
Vector2 screenPos = {0,0};
vu16 keyInput;

void cursorUpdate() {
    obj_attr_mem[0].attr0 = ATTR0_Y(8 * cursorPos.x);
    obj_attr_mem[0].attr1 = ATTR1_X(8 * cursorPos.y);
}

int main()
{
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ;
    REG_BG0CNT = BG_4BPP | BG_SIZE_32x32 | BG_CBB(0) | BG_SBB(8);
    obj_palette_mem[0] = gamePalette;
    
    //obj_tile4_mem[1] = cursorTile;
    //obj_attr_mem[0].attr2 = ATTR2_TILE(1);
    while(1) {
        vid_vsync();
        keyInput = *((vu16*)(MEM_IO + 0x0130));
        if (keyInput & KEY_UP) {

        }
    };
}