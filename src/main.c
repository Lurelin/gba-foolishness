#include <string.h>
#include <stdlib.h>
#include "toolbox.h"
#include "data.h"
#include "objects.h"

//Vector2 struct, usually used to represent 2d position
typedef struct Vector2 {
    s32 x;
    s32 y;
} Vector2;

#define OBJECTMAP_WIDTH 128
#define OBJECTMAP_HEIGHT 128
EWRAM_DATA u8 objectMap[OBJECTMAP_WIDTH][OBJECTMAP_HEIGHT]; //Map of object IDs

Vector2 screenPos = {OBJECTMAP_WIDTH / 2 - 14,OBJECTMAP_HEIGHT / 2 - 10}; //Camera position on the object map
Vector2 cursorPos = (Vector2){14,10}; //Position of cursor on the screen in 8/16 px intervals, takes effect when updatecursorsprite() is run
char displayMode = DISPMODE_8PX; //Displaymode decides whether 16px tiles, 8px tiles, or pixels are displayed
u8 cursorHold; //tracker for length dpad keys have been held(in frames)
u8 cursorSequenceLength;

void initDisp() { //initialize program
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D; //put the gba in mode0(tiles mode), enable bg0 & object layer
    REG_BG0CNT = BG_4BPP | BG_SIZE_32x32 | BG_CBB(0) | BG_SBB(8); //init background 0
    bg_palette_mem[0] = gamePal; //set bgmem0 to main palette
    obj_palette_mem[0] = gamePal; //set objmem0 to main palette
    memcpy(&bg_tile4_mem[0][0], backgroundTiles, sizeof(backgroundTiles)); //copy background tiles to vram
    memcpy(&bg_tile4_mem[0][4], pipesTiles, sizeof(pipesTiles)); //copy pipes tiles to vram
    memcpy(&obj_tile4_mem[1], cursorTiles, sizeof(cursorTiles)); //copy cursor tiles to vram
    obj_attr_mem[0].attr2 = ATTR2_TILE(1);
    obj_attr_mem[0].attr1 = ATTR1_SIZE_1x1;
    obj_attr_mem[0].attr0 = ATTR0_SQUARE;
}

void updateCursorSprite() { //Changes cursor position in vram to match cursorPos
    if (displayMode == DISPMODE_16PX) {
        obj_attr_mem[0].attr0 = (obj_attr_mem[0].attr0 & ~(ATTR0_Y_MASK)) | ATTR0_Y((16) * cursorPos.y);
        obj_attr_mem[0].attr1 = (obj_attr_mem[0].attr1 & ~(ATTR1_X_MASK)) | ATTR1_X((16) * cursorPos.x);
    }
    if (displayMode == DISPMODE_8PX) {
        obj_attr_mem[0].attr0 = (obj_attr_mem[0].attr0 & ~(ATTR0_Y_MASK)) | ATTR0_Y((8) * cursorPos.y);
        obj_attr_mem[0].attr1 = (obj_attr_mem[0].attr1 & ~(ATTR1_X_MASK)) | ATTR1_X((8) * cursorPos.x);
    }
}

void drawObjectTiles() {
    if (displayMode == DISPMODE_8PX) {
        for (int objX = 0; objX < 30; objX++) {
            for (int objY = 0; objY < 20; objY++) {
                drawTile(objectMap[objX + screenPos.x][objY + screenPos.y], objX, objY);
            }
        }
    }
    if (displayMode == DISPMODE_16PX) {
        for (int objX = 0; objX < 15; objX++) {
            for (int objY = 0; objY < 10; objY++) {
                drawTile(objectMap[objX + screenPos.x][objY + screenPos.y], objX, objY);
            }
        }
    }
};
void drawObjectPixels() {
    for (int objX = 0; objX < OBJECTMAP_WIDTH; objX++) {
        for (int objY = 0; objY < OBJECTMAP_HEIGHT; objY++) {
            m3_plot((SCREEN_WIDTH - OBJECTMAP_WIDTH)/2 + objX, (SCREEN_HEIGHT - OBJECTMAP_HEIGHT)/2 + objY, objectColours[objectMap[objX][objY]]);
        }
    }
}

void updateCursorPos() { //Update cursor & screen position
    u16 keyInput = *((vu16*)(MEM_IO + 0x0130)); //set keyinput variable
    if (((keyInput & 0x00F0)) != 0x00F0) { //if dpad keys pressed
        cursorHold++; //increase tracker for length dpad keys have been held
        if ((cursorHold > 15)) { //if the dpad keys have been held for 15 frames, move the cursor
            //if by moving the cursor, you'd put it outside of the screen, move the background instead.
            if (!(keyInput & KEY_LEFT))  {
                if (cursorPos.x > 0) { 
                    cursorPos.x--;
                } else {
                    screenPos.x--;
                }
            }
            if (!(keyInput & KEY_RIGHT)) {
                if ((cursorPos.x < 29 && displayMode == DISPMODE_8PX) || (cursorPos.x < 14 && displayMode == DISPMODE_16PX)) { 
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
                if ((cursorPos.y < 19 && displayMode == DISPMODE_8PX) || (cursorPos.y < 9 && displayMode == DISPMODE_16PX)) { 
                    cursorPos.y++;
                } else {
                    screenPos.y++;
                }
            }

            if (cursorSequenceLength < 3) { 
                cursorHold = 0;
                cursorSequenceLength++;
            } else { //if the cursor has been moved 3 times in a row 
                cursorHold = 10; //Set cursorHold to 10 so only 5 frames need to pass to move the cursor again
            }
        }
    } else { //if dpad keys are released
        cursorHold = 15; //Set cursorhold to 15 so that when pressed the cursor moves responsively
        cursorSequenceLength = 0;
    }
}
void verifyScreenPos() { //Verify the screen position, fix it if it is attempting to display out of objmap
    if (screenPos.x < 0) {
        screenPos.x = 0;
    }
    if (screenPos.y < 0) {
        screenPos.y = 0;
    }
    if (displayMode == DISPMODE_8PX) {
        if (screenPos.x > OBJECTMAP_WIDTH - 30) screenPos.x = OBJECTMAP_WIDTH - 30;
        if (screenPos.y > OBJECTMAP_HEIGHT - 20) screenPos.y = OBJECTMAP_HEIGHT - 20;
    }
    if (displayMode == DISPMODE_16PX) {
        if (screenPos.x > OBJECTMAP_WIDTH - 15) screenPos.x = OBJECTMAP_WIDTH - 15;
        if (screenPos.y > OBJECTMAP_HEIGHT - 10) screenPos.y = OBJECTMAP_HEIGHT - 10;
    }
}

void displayModeSwitch(int mode)
{   switch (mode) {
        case DISPMODE_1PX:
            displayMode = DISPMODE_1PX;
            REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
            obj_attr_mem[0].attr2 = 0; //change cursor tile to 0(no tile)
            memset(vid_mem, 0, 0x17FFF); //fill vram with 0s 
            drawObjectPixels(); //only need to do this when entering 1px mode
        break;
        case DISPMODE_8PX:
            displayMode = DISPMODE_8PX;
            screenPos.x += cursorPos.x - 14; //center screen around cursor
            screenPos.y += cursorPos.y - 10;
            cursorPos = (Vector2){14,10};
            obj_attr_mem[0].attr2 = (obj_attr_mem[0].attr2 & ~0x003FF) | ATTR2_TILE(1); 
            obj_attr_mem[0].attr1 = (obj_attr_mem[0].attr1 & ~0x0C000) | ATTR1_SIZE_1x1;
        break;
        case DISPMODE_16PX:
            displayMode = DISPMODE_16PX;
            screenPos.x += cursorPos.x - 7; //center screen around cursor
            screenPos.y += cursorPos.y - 5;
            cursorPos = (Vector2){7,5};
            obj_attr_mem[0].attr2 = (obj_attr_mem[0].attr2 & ~0x003FF) | ATTR2_TILE(2);
            obj_attr_mem[0].attr1 = (obj_attr_mem[0].attr1 & ~0x0C000) | ATTR1_SIZE_2x2;
        break;
    }
}
void doKeys() {
    if (!(REG_KEYINPUT & KEY_R) && !(REG_KEYINPUT & KEY_RIGHT)) { //zoom in
        if (displayMode != DISPMODE_16PX) {
            displayModeSwitch(DISPMODE_16PX);
        }
    }
    if (!(REG_KEYINPUT & KEY_R) && !(REG_KEYINPUT & KEY_LEFT)) { //zoom out
        if (displayMode != DISPMODE_8PX) {
            displayModeSwitch(DISPMODE_8PX);
        }
    }
            
    if (!(REG_KEYINPUT & KEY_R) && !(REG_KEYINPUT & KEY_A)) { //zoom out
        displayModeSwitch(DISPMODE_1PX);
    }
    if (!(REG_KEYINPUT & KEY_A)) {
        objectMap[cursorPos.x + screenPos.x][cursorPos.y + screenPos.y] = OBJ_ID_HORIZONTALPIPE;
    }
    if (!(REG_KEYINPUT & KEY_B)) {
        objectMap[cursorPos.x + screenPos.x][cursorPos.y + screenPos.y] = OBJ_ID_BACKGROUNDTILE;
    }
}

int main()
{
    objectMap[64][64] = OBJ_ID_HORIZONTALPIPE;

    initDisp();

    updateCursorSprite();
    
    while(1) {
        vid_vsync();
        if (displayMode != 0) {
            updateCursorPos();
            verifyScreenPos();
            updateCursorSprite();
            doKeys();
            drawObjectTiles();
        } else {
            if (!(REG_KEYINPUT & KEY_A) && (REG_KEYINPUT & KEY_R)) {
                memset(vid_mem, 0, 0x17FFF); //fill vram with 0 to clear pixels set 
                displayModeSwitch(DISPMODE_8PX);
                initDisp();
            }
        }
    };
}