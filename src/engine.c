#include "engine.h"
EWRAM_DATA u8 objectMap[OBJECTMAP_WIDTH][OBJECTMAP_HEIGHT] ALIGN4; //Map of object IDs
EWRAM_DATA u8 flowMap[OBJECTMAP_WIDTH][OBJECTMAP_HEIGHT] ALIGN4; //Map of flow

enum inputDirection { //direction an input is GOING
    NONE, UP, RIGHT, DOWN, LEFT 
};

void createObject(Vector2 pos, char objectID) {
    objectMap[pos.x][pos.y] = objectID;
    drawObjectTile(pos.x, pos.y);

}
void removeObject(Vector2 pos) {
    objectMap[pos.x][pos.y] = OBJECTS_NONE;
    drawObjectTile(pos.x, pos.y);
}

void doHorizontalPipe(Vector2 pos, int inputDir) {
    
}