#pragma once
#include "toolbox.h"
#include "graphics.h"
#define OBJECTMAP_WIDTH 128
#define OBJECTMAP_HEIGHT 128

extern EWRAM_DATA u8 objectMap[OBJECTMAP_WIDTH][OBJECTMAP_HEIGHT] ALIGN4; //Map of object IDs
extern EWRAM_DATA u8 flowMap[OBJECTMAP_WIDTH][OBJECTMAP_HEIGHT] ALIGN4; //Map of object IDs

enum objectTypes {
    OBJECTS_NONE, OBJECTS_SOURCE, OBJECTS_PIPE_VERTICAL, OBJECTS_PIPE_HORIZONTAL, 
};

void createObject(Vector2 pos, char objectID);
void removeObject(Vector2 pos);