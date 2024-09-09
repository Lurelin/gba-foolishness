#pragma once
extern char displayMode;
enum DISP_MODE {BITS_8 = 0, BITS_16 = 1}; 
enum OBJECTS {OBJ_ID_BACKGROUND = 0, OBJ_ID_PLACEHOLDER = 1};
void drawBackgroundTile(int X, int Y);
void drawPlaceholderTile(int X, int Y);
