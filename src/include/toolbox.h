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

#define INLINE static inline //inline functions compile by direct subsitution with function call instead of branching; inline functions reduce function overhead

//Screen width and height
#define SCREEN_WIDTH   240
#define SCREEN_HEIGHT  160

//memory locations
#define MEM_IO 0x04000000 //IO memory
#define MEM_PALETTES 0x05000000 //Palette memory
#define MEM_VRAM 0x06000000 //Video memory

//REGISTERS
#define REG_DISPCNT *((vu32*)(MEM_IO)) //Display control register

//Background controller registers
#define REG_BG0CNT *((vu16*)(MEM_IO + 0x08))
#define REG_BG1CNT *((vu16*)(MEM_IO + 0x0A))
#define REG_BG2CNT *((vu16*)(MEM_IO + 0x0C))
#define REG_BG3CNT *((vu16*)(MEM_IO + 0x0E))

#define REG_VCOUNT (*(vu16*)(MEM_IO + 0x06)) //vertical draw count tracking register

//BACKGROUND OFFSET REGISTERS
#define BG0HOFS *((vu16*)(MEM_IO + 0x10)) //Bits 0-8 are used (0-511) for horizontal offset of bg0
#define BG0VOFS *((vu16*)(MEM_IO + 0x12)) //Bits 0-8 are used (0-511) for vertical offset of bg0
#define BG1HOFS *((vu16*)(MEM_IO + 0x14))
#define BG1VOFS *((vu16*)(MEM_IO + 0x16))
#define BG2HOFS *((vu16*)(MEM_IO + 0x18))
#define BG2VOFS *((vu16*)(MEM_IO + 0x1A))
#define BG3HOFS *((vu16*)(MEM_IO + 0x1C))
#define BG3VOFS *((vu16*)(MEM_IO + 0x1E))

//REG_DISPCNT BITS
// display modes
#define DCNT_MODE0 0x0000 //tile mode
#define DCNT_MODE3 0x0003 //Bitmap mode, made for still images
// layer controls(on/off)
#define DCNT_BG0 0x0100
#define DCNT_BG1 0x0200
#define DCNT_BG2 0x0400
#define DCNT_BG3 0x0800
#define DCNT_OBJ 0x1000

//BGCNT BITS
#define BG_4BPP				 0	//4bpp (16 color) bg (no effect on affine bg)
#define BG_8BPP			0x0080	//8bpp (256 color) bg (no effect on affine bg)
#define BG_CBB(n) (n << 2)      //Dictates which charblock(block of tile data) is used for the background
#define BG_SBB(n) (n << 8)      //Dictates which screenblock(map of tiles) is used for the background
//Bg size value. Note that bigger backgrounds require more screenblocks
#define BG_SIZE_32x32 0x0000 //1 screenblock, 256x256 px
#define BG_SIZE_64x32 0x4000 //2 screenblocks 512x256 px
#define BG_SIZE_32x64 0x8000 //2 screenblocks 256x512 px
#define BG_SIZE_64x64 0xC000 //4 screenblocks 512x512 px

//TILE DATA
typedef struct {u32 data[8];} TILE4; //tile4 (4 bits per pixel), 16 colour palette
typedef struct {u32 data[16];} TILE8; //tile8 (8 bits per pixel, 256 colour palette)
//tile block contains data for 32x16 tile4s or 16x16 tile8s
typedef TILE4 CHARBLOCK4[512];
typedef TILE8 CHARBLOCK8[256];
//vid_mem represented in terms of charblocks instead of u32s
#define tile4_mem ((CHARBLOCK4*)(MEM_VRAM))
#define tile8_mem ((CHARBLOCK8*)(MEM_VRAM))

//TILE MAPPING
typedef u16 SCR_ENTRY; //A SCR_ENTRY contains a tile index and per tile settings
typedef SCR_ENTRY SCREENBLOCK[1024]; //A screenblock is a map of references to tiledata
#define scrb_mem ((SCREENBLOCK*)(MEM_VRAM)) //Note that SCREENBLOCKs use the same memory as CHARBLOCKS, but are 1/8th of the size. 

//SCR_ENTRY DATA
#define SE_ID(n) (n); //Tile index
#define SE_PALBANK(n) ((n)<<12) //Palette bank
#define SE_HFLIP		0x0400	//Horizontal flip
#define SE_VFLIP		0x0800	//Vertical flip

//PALETTES
#define colour(r, g, b) (r | g << 5 | b << 10) //A colour uses two bytes
typedef struct {u16 colours[16];} palette; //A single palette contains 16 colours
#define obj_palette_mem ((u16*)(MEM_PALETTES))
#define bg_palette_mem ((u16*)(MEM_PALETTES+0x0200))

//Vsyncing function
void vid_vsync();

#define vid_mem ((u16*)MEM_VRAM)
//Plotting function for mode 3
INLINE void m3_plot(int x, int y, u16 clr)
{
    vid_mem[y*SCREEN_WIDTH+x] = clr;
}

