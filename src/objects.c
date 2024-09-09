#include "toolbox.h"
#include "objects.h"
void drawBackgroundTile(int X, int Y) {
    if (displayMode == BITS_8) {
        scrb_mem[8][32*(Y)+X] = 0;
    } else if (displayMode == BITS_16) {
        scrb_mem[8][32*(Y*2)+X*2] = 0;
        scrb_mem[8][32*(Y*2)+X*2 + 1] = 1;
        scrb_mem[8][32*(Y*2 + 1)+X*2] = 2;
        scrb_mem[8][32*(Y*2 + 1)+X*2 + 1] = 3;
    }
};

void drawPlaceholderTile(int X, int Y) {
    if (displayMode == BITS_8) {
        scrb_mem[8][32*(Y)+X] = SE_PALBANK(1) | SE_ID(8);
    } else if (displayMode == BITS_16) {
        scrb_mem[8][32*(Y*2)+X*2] = SE_PALBANK(1) | SE_ID(4);
        scrb_mem[8][32*(Y*2)+X*2 + 1] = SE_PALBANK(1) | SE_ID(5);
        scrb_mem[8][32*(Y*2 + 1)+X*2] = SE_PALBANK(1) | SE_ID(6);
        scrb_mem[8][32*(Y*2 + 1)+X*2 + 1] = SE_PALBANK(1) | SE_ID(7);
    }
};
