#include "userinterface.h"
Vector2 cursorPos = (Vector2){0,0};
int cursorTimer = 0;
#define CURSOR_SPEED 3
int ABbuttonTimer = 0;
#define AB_BUTTON_PADDING 3

char selectedObject = OBJECTS_PIPE_HORIZONTAL;

void doPlaceRemoveButtons() {
    if (~REG_KEYINPUT & KEY_A) {
        createObject(cursorPos, selectedObject);
        ABbuttonTimer = 0;
    }
    if (~REG_KEYINPUT & KEY_B) {
        removeObject(cursorPos);
        ABbuttonTimer = 0;
    }
}

void buttonsAB() {
    if (ABbuttonTimer > AB_BUTTON_PADDING) {
        doPlaceRemoveButtons();
    } else {
        ABbuttonTimer++;
    }
}

void moveCursor() {
    if (cursorTimer > CURSOR_SPEED) {
        if (~REG_KEYINPUT & KEY_RIGHT && cursorPos.x < 127) {
            cursorPos.x++;
            cursorTimer = 0;
        }
        if (~REG_KEYINPUT & KEY_LEFT && cursorPos.x > 0) {
            cursorPos.x--;
            cursorTimer = 0;
        }
        if (~REG_KEYINPUT & KEY_DOWN && cursorPos.y < 127) {
            cursorPos.y++;
            cursorTimer = 0;
        }
        if (~REG_KEYINPUT & KEY_UP && cursorPos.y > 0) {
            cursorPos.y--;
            cursorTimer = 0;
        }
        if (~REG_KEYINPUT & (KEY_RIGHT | KEY_LEFT | KEY_DOWN | KEY_UP)) {
            doPlaceRemoveButtons();
        }
    } else {
        cursorTimer++;
    }
}
