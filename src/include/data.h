#pragma once
#include "toolbox.h"
enum charBlockDesignations {
    BLOCK_TILES = 0,
    BLOCK_UI = 1,
    //etc...
};
enum buildingTileLocations {
    INDEX_BG = 0,
    INDEX_PIPE_V_S = 1,
    INDEX_PIPE_V_L = 2,
    INDEX_PIPE_H_S = 6,
    INDEX_PIPE_H_L = 7,
};

enum uiTileLocations {
    UI_INDEX_NA = 0,
    UI_INDEX_LINE_H = 1,
    UI_INDEX_LINE_V = 2,
    UI_INDEX_CORNER = 3,
    UI_INDEX_FILL = 4,
};
#define UI_FONT_START 5
extern palette palette_game;
extern cu32 tiles_cursor_large[32] ALIGN4;
extern cu32 tiles_cursor_small[8] ALIGN4;
extern cu32 tiles_background[8] ALIGN4;
extern cu32 tiles_pipe_vertical_large[32] ALIGN4;
extern cu32 tiles_pipe_vertical_small[8] ALIGN4;
extern cu32 tiles_pipe_horizontal_large[32] ALIGN4;
extern cu32 tiles_pipe_horizontal_small[8] ALIGN4;
extern cu32 tiles_popup_background[32] ALIGN4;

extern void loadData();