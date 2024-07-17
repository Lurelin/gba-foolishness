#pragma once
//signed and unsigned int typedefs
typedef signed int s32;
typedef unsigned int u32;
typedef volatile s32 vs32;
typedef volatile u32 vu32;
typedef const s32 cs32;
typedef const u32 cu32;

//signed and unsigned short typedefs
typedef signed short s16;
typedef unsigned short u16;
typedef volatile s16 vs16;
typedef volatile u16 vu16;
typedef const s16 cs16;
typedef const u16 cu16;

// tile 8x8@4bpp: 32bytes; 8 ints
typedef struct {u32 data[8];} TILE;
// charblock 32x16 tiles
typedef TILE CHARBLOCK[512];

#define INLINE static inline //inline functions compile by direct subsitution with function call instead of branching; inline functions reduce function overhead

//memory locations
#define MEM_IO 0x04000000
#define MEM_VRAM 0x06000000
#define vid_mem ((u16*)MEM_VRAM)


#define REG_DISPCNT *((vu32*)(MEM_IO)) //Display control register
//REG_DISPCNT useful bits
// display modes
#define DCNT_MODE0 0x0000 //4 bit per pixel tile mode
#define DCNT_MODE3 0x0003 //Bitmap mode, made for still images
// layers
#define DCNT_BG0 0x0100
#define DCNT_BG1 0x0200
#define DCNT_BG2 0x0400
#define DCNT_BG3 0x0800
#define DCNT_OBJ 0x1000

//Screen width and height
#define SCREEN_WIDTH   240
#define SCREEN_HEIGHT  160

//Plotting function for mode 3
INLINE void m3_plot(int x, int y, u16 clr)
{
    vid_mem[y*SCREEN_WIDTH+x] = clr;
}