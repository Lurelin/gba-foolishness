#include "graphics.h"

void drawObjectTile(int X, int Y) {
    m3_plot((SCREEN_WIDTH - OBJECTMAP_WIDTH)/2 + X, (SCREEN_HEIGHT - OBJECTMAP_HEIGHT)/2 + Y, objectColours[objectMap[X][Y]]);
}

void initGraphics() {
    for (int objX = 0; objX < OBJECTMAP_WIDTH; objX++) {
        for (int objY = 0; objY < OBJECTMAP_HEIGHT; objY++) {
            drawObjectTile(objX,objY);
        }
    }
}

Vector2 oldCursorPos = {256, 256};
void drawCursor() {
    m3_plot((SCREEN_WIDTH - OBJECTMAP_WIDTH)/2 + cursorPos.x, (SCREEN_HEIGHT - OBJECTMAP_HEIGHT)/2 + cursorPos.y, RGB15(31,31,31));
    if (oldCursorPos.x != cursorPos.x || oldCursorPos.y != cursorPos.y) {
        m3_plot((SCREEN_WIDTH - OBJECTMAP_WIDTH)/2 + cursorPos.x, (SCREEN_HEIGHT - OBJECTMAP_HEIGHT)/2 + cursorPos.y, RGB15(31,31,31));
        drawObjectTile(oldCursorPos.x, oldCursorPos.y);
        oldCursorPos = cursorPos;
    }
};