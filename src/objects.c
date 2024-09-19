#include "toolbox.h"
#include "objects.h"

u16 objectColours[256] ALIGN4 = {
    RGB15(5,5,5), //Background
    RGB15(27,20,17), //Pipe (Vertical)
    RGB15(27,20,17)  //Pipe (Horizontal)
};

void drawBackgroundTile( int X, int Y, int scrbID, int dispMode) {
    if (dispMode == DISPMODE_8PX) {
        scrb_mem[scrbID][32*(Y)+X] = 0;
    } else if (dispMode == DISPMODE_16PX) {
        scrb_mem[scrbID][32*(Y*2)+X*2] = 0;
        scrb_mem[scrbID][32*(Y*2)+X*2 + 1] = 0;
        scrb_mem[scrbID][32*(Y*2 + 1)+X*2] = 0;
        scrb_mem[scrbID][32*(Y*2 + 1)+X*2 + 1] = 0;
    }
};
void drawVerticalPipe(int X, int Y, int scrbID, int dispMode) {
    if (dispMode == DISPMODE_8PX) {
        scrb_mem[scrbID][32*(Y)+X] = SE_PALBANK(0) | SE_ID(1);
    } else if (dispMode == DISPMODE_16PX) {
        scrb_mem[scrbID][32*(Y*2)+X*2] = SE_PALBANK(0) | SE_ID(2);
        scrb_mem[scrbID][32*(Y*2)+X*2 + 1] = SE_PALBANK(0) | SE_ID(3);
        scrb_mem[scrbID][32*(Y*2 + 1)+X*2] = SE_PALBANK(0) | SE_ID(4);
        scrb_mem[scrbID][32*(Y*2 + 1)+X*2 + 1] = SE_PALBANK(0) | SE_ID(5);
    }
};
void drawHorizontalPipe(int X, int Y, int scrbID, int dispMode) {
    if (dispMode == DISPMODE_8PX) {
        scrb_mem[scrbID][32*(Y)+X] = SE_PALBANK(0) | SE_ID(6);
    } else if (dispMode == DISPMODE_16PX) {
        scrb_mem[scrbID][32*(Y*2)+X*2] = SE_PALBANK(0) | SE_ID(7);
        scrb_mem[scrbID][32*(Y*2)+X*2 + 1] = SE_PALBANK(0) | SE_ID(8);
        scrb_mem[scrbID][32*(Y*2 + 1)+X*2] = SE_PALBANK(0) | SE_ID(9);
        scrb_mem[scrbID][32*(Y*2 + 1)+X*2 + 1] = SE_PALBANK(0) | SE_ID(10);
    }
};

void drawTile(int objectID, int X, int Y, int scrbID, int dispMode) {
    switch (objectID) {
        case OBJ_ID_BACKGROUNDTILE:
            drawBackgroundTile(X, Y, scrbID, dispMode);
            break;
        case OBJ_ID_VERTICALPIPE:
            drawVerticalPipe(X, Y, scrbID, dispMode);                    
            break;
        case OBJ_ID_HORIZONTALPIPE:
            drawHorizontalPipe(X, Y, scrbID, dispMode);                    
            break;
    }
}