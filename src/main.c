#include <string.h>
#include <stdlib.h>
#include "toolbox.h"
#include "data.h"
#include "objects.h"

typedef struct Vector2 {
    s32 x;
    s32 y;
} Vector2;

Vector2 cursorPos = (Vector2){14,10};
Vector2 screenPos = {0,0};
vu16 keyInput;
u8 cursorHold;
u8 cursorSpeed;
#define OBJECTMAP_WIDTH 128
#define OBJECTMAP_HEIGHT 128
EWRAM_DATA u8 objectMap[OBJECTMAP_WIDTH][OBJECTMAP_HEIGHT];
char displayMode;
char selectButtonPressed;

INLINE void updateCursorSprite() {
    obj_attr_mem[0].attr0 = (obj_attr_mem[0].attr0 & ~(ATTR0_Y_MASK)) | ATTR0_Y((8 + displayMode * 8) * cursorPos.y);
    obj_attr_mem[0].attr1 = (obj_attr_mem[0].attr1 & ~(ATTR1_X_MASK)) | ATTR1_X((8 + displayMode * 8) * cursorPos.x);
}

void verifyScreenPos() {
    if (screenPos.x < 0) {
        screenPos.x = 0;
    }
    if (screenPos.y < 0) {
        screenPos.y = 0;
    }
    if (displayMode == BITS_8) {
        if (screenPos.x > OBJECTMAP_WIDTH - 30) screenPos.x = OBJECTMAP_WIDTH - 30;
        if (screenPos.y > OBJECTMAP_HEIGHT - 20) screenPos.y = OBJECTMAP_HEIGHT - 20;
    }
    if (displayMode == BITS_16) {
        if (screenPos.x > OBJECTMAP_WIDTH - 15) screenPos.x = OBJECTMAP_WIDTH - 15;
        if (screenPos.y > OBJECTMAP_HEIGHT - 10) screenPos.y = OBJECTMAP_HEIGHT - 10;
    }
}
void displayModeSwitch()
{
    if (!(REG_KEYINPUT & KEY_SELECT)) {
        if (!(selectButtonPressed)) {
            if (displayMode == BITS_8) {
                displayMode = BITS_16;
                screenPos.x += cursorPos.x - 7;
                screenPos.y += cursorPos.y - 5;
                cursorPos = (Vector2){7,5};
                obj_attr_mem[0].attr2 = (obj_attr_mem[0].attr2 & ~0x003FF) | ATTR2_TILE(2);
                obj_attr_mem[0].attr1 = (obj_attr_mem[0].attr1 & ~0x0C000) | ATTR1_SIZE_2x2;
            } else if (displayMode == BITS_16) {
                displayMode = BITS_8;
                screenPos.x += cursorPos.x - 14;
                screenPos.y += cursorPos.y - 10;
                cursorPos = (Vector2){14,10};
                obj_attr_mem[0].attr2 = (obj_attr_mem[0].attr2 & ~0x003FF) | ATTR2_TILE(1);
                obj_attr_mem[0].attr1 = (obj_attr_mem[0].attr1 & ~0x0C000) | ATTR1_SIZE_1x1;

            }
        }
        selectButtonPressed = 1;
    } else {
        selectButtonPressed = 0;
    }
 }

void updateCursorPos() {
    keyInput = *((vu16*)(MEM_IO + 0x0130));
    if (((keyInput & 0x00F0)) != 0x00F0) {
        cursorHold++;
        if ((cursorHold > 15)) {
            if (!(keyInput & KEY_LEFT))  {
                if (cursorPos.x > 0) { 
                    cursorPos.x--;
                } else {
                    screenPos.x--;
                }
            }
            if (!(keyInput & KEY_RIGHT)) {
                if ((cursorPos.x < 29 && displayMode == BITS_8) || (cursorPos.x < 14 && displayMode == BITS_16)) { 
                    cursorPos.x++;
                } else {
                    screenPos.x++;
                }
            }
            if (!(keyInput & KEY_UP))  {
                if (cursorPos.y > 0) { 
                    cursorPos.y--;
                } else {
                    screenPos.y--;
                }
            }
            if (!(keyInput & KEY_DOWN))  {
                if ((cursorPos.y < 19 && displayMode == BITS_8) || (cursorPos.y < 9 && displayMode == BITS_16)) { 
                    cursorPos.y++;
                } else {
                    screenPos.y++;
                }
            }

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

void drawObjectTiles(int X, int Y) {
    switch (objectMap[X + screenPos.x][Y + screenPos.y]) {
        case OBJ_ID_BACKGROUND:
            drawBackgroundTile(X, Y);
            break;
        case OBJ_ID_PLACEHOLDER:
            drawPlaceholderTile(X, Y);                    
            break;
    }
}
void drawObjects() {
    if (displayMode == BITS_8) {
        for (int objX = 0; objX < 30; objX++) {
            for (int objY = 0; objY < 20; objY++) {
                drawObjectTiles(objX, objY);
            }
        }
    }
    if (displayMode == BITS_16) {
        for (int objX = 0; objX < 15; objX++) {
            for (int objY = 0; objY < 10; objY++) {
                drawObjectTiles(objX, objY);
            }
        }
    }
};


int main()
{
    objectMap[127][0] = 1;
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;
    REG_BG0CNT = BG_4BPP | BG_SIZE_32x32 | BG_CBB(0) | BG_SBB(8);

    bg_palette_mem[1] = numsPal;
    bg_palette_mem[0] = gamePal;
    obj_palette_mem[0] = gamePal;
    memcpy(&bg_tile4_mem[0][0], backgroundTiles, sizeof(backgroundTiles));
    memcpy(&bg_tile4_mem[0][4], numsTiles, sizeof(numsTiles));
    memcpy(&obj_tile4_mem[1], cursorTiles, sizeof(cursorTiles));
    obj_attr_mem[0].attr2 = ATTR2_TILE(1);
    obj_attr_mem[0].attr1 = ATTR1_SIZE_1x1;
    obj_attr_mem[0].attr0 = ATTR0_SQUARE;

    updateCursorSprite();
    
    while(1) {
        vid_vsync();
        if (!(REG_KEYINPUT & KEY_A)) {
            objectMap[cursorPos.x + screenPos.x][cursorPos.y + screenPos.y] = OBJ_ID_PLACEHOLDER;
        }
        if (!(REG_KEYINPUT & KEY_B)) {
            objectMap[cursorPos.x + screenPos.x][cursorPos.y + screenPos.y] = OBJ_ID_BACKGROUND;
        }
        updateCursorPos();
        displayModeSwitch();
        verifyScreenPos();
        updateCursorSprite();
        drawObjects();
    };
}