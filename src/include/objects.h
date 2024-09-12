#pragma once
extern char displayMode;
enum DISP_MODE {DISPMODE_1PX = 0, DISPMODE_8PX = 1, DISPMODE_16PX = 2}; 
enum OBJECTS {OBJ_ID_BACKGROUNDTILE = 0, OBJ_ID_VERTICALPIPE = 1, OBJ_ID_HORIZONTALPIPE = 2};
extern u16 objectColours[256] ALIGN4;
void drawBackgroundTile(int X, int Y);
void drawVerticalPipe(int X, int Y);
void drawHorizontalPipe(int X, int Y);
void drawTile(int objectID, int X, int Y);

