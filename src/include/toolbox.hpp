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
#define MEM_PALETTES 0x05000000
#define MEM_VRAM 0x06000000
#define vid_mem ((u16*)MEM_VRAM)


#define REG_DISPCNT *((vu32*)(MEM_IO)) //Display control register
//REG_DISPCNT useful bits
// display modes
#define DCNT_MODE0 0x0000 //tile mode
#define DCNT_MODE3 0x0003 //Bitmap mode, made for still images
// layer controls(on/off)
#define DCNT_BG0 0x0100
#define DCNT_BG1 0x0200
#define DCNT_BG2 0x0400
#define DCNT_BG3 0x0800
#define DCNT_OBJ 0x1000

//Background controller registers
#define REG_BG0CNT *((vu16*)(MEM_IO + 0x8))
#define REG_BG1CNT *((vu16*)(MEM_IO + 0xA))
#define REG_BG2CNT *((vu16*)(MEM_IO + 0xC))
#define REG_BG3CNT *((vu16*)(MEM_IO + 0xE))

#define BG_4BPP				 0	//4bpp (16 color) bg (no effect on affine bg)
#define BG_8BPP			0x0080	//8bpp (256 color) bg (no effect on affine bg)
#define BG_CBB(n) (n << 2)      //Dictates which charblock(block of tile data) is used for the background
#define BG_SBB(n) (n << 8)      //Dictates which screenblock(map of tiles) is used for the background
//Bg size value. Note that bigger backgrounds require more screenblocks
#define BG_SIZE_32x32 0x0000
#define BG_SIZE_64x32 0x4000
#define BG_SIZE_32x64 0x8000
#define BG_SIZE_64x64 0xC000

//Vsyncing function
#define REG_VCOUNT (*(vu16*)(0x04000006))
void vid_vsync();

//Screen width and height
#define SCREEN_WIDTH   240
#define SCREEN_HEIGHT  160

//Plotting function for mode 3
INLINE void m3_plot(int x, int y, u16 clr)
{
    vid_mem[y*SCREEN_WIDTH+x] = clr;
}

//Tile data storage
//tile4 (4 bits per pixel), 16 colour palette
typedef struct {u32 data[8];} TILE4;
//tile8 (8 bits per pixel, 256 colour palette)
typedef struct {u32 data[16];} TILE8;
//tile block: 32x16 tile4s, 16x16 tile8s
typedef TILE4 CHARBLOCK4[512];
typedef TILE8 CHARBLOCK8[256];
//vid_mem represented in terms of charblocks instead of u32s
#define tile4_mem ((CHARBLOCK4*)(MEM_VRAM))
#define tile8_mem ((CHARBLOCK8*)(MEM_VRAM))

//Tile grid mapping
//A SCR_ENTRY is an entry in a screenblock, points to the tile & bits can be changed to edit settings for it.
typedef u16 SCR_ENTRY;
//A screenblock is like a map of references to tiledata
typedef SCR_ENTRY SCREENBLOCK[1024];
//Note that SCREENBLOCKs use the same memory as CHARBLOCKS, but are 1/8th of the size. 
#define scrb_mem ((SCREENBLOCK*)(MEM_VRAM))

//SCR_ENTRY DATA
#define SE_ID(n) (n); //Tile index
#define SE_PALBANK(n) ((n)<<12) //Palette bank
#define SE_HFLIP		0x0400	//Horizontal flip
#define SE_VFLIP		0x0800	//Vertical flip

//Palettes
typedef u16 COLOUR;
#define obj_palette_mem ((COLOUR*)(MEM_PALETTES))
#define bg_palette_mem ((COLOUR*)(MEM_PALETTES+0x0200))
