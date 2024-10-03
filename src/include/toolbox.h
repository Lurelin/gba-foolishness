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

//signed and unsigned char typedefs
typedef signed char s8;
typedef unsigned char u8;
typedef volatile s8 vs8;
typedef volatile u8 vu8;
typedef const s8 cs8;
typedef const u8 cu8;

#define INLINE static inline //inline functions compile by direct subsitution with function call instead of branching; inline functions reduce function overhead

#define ALIGN4 __attribute__((aligned(4))) //Force word alignment.

#define IWRAM_DATA __attribute__((section(".iwram"))) //Put variable in IWRAM (default).

#define EWRAM_DATA __attribute__((section(".ewram"))) //Put variable in EWRAM.

//Screen width and height
#define SCREEN_WIDTH   240
#define SCREEN_HEIGHT  160

//memory locations
#define MEM_IO 0x04000000 //IO memory
#define MEM_PALETTES 0x05000000 //Palette memory
#define MEM_VRAM 0x06000000 //Video memory
#define MEM_OAM 0x07000000 //Object memory

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
// one dimensional sprite mapping
#define DCNT_OBJ_1D 0x0040
#define DCNT_OBJ_2D 0x0000

//BGCNT BITS
#define BG_4BPP				 0	//4bpp (16 color) bg (no effect on affine bg)
#define BG_8BPP	0x0080	//8bpp (256 color) bg (no effect on affine bg)
#define BG_PRIO(n) (n << 0)      //Background priority, 3-0, 0 is highest
#define BG_PRIO_MASK 0x0003
#define BG_CBB(n) (n << 2)      //Dictates which charblock(block of tile data) is used for the background
#define BG_CBB_MASK 0x000C
#define BG_SBB(n) (n << 8)      //Dictates which screenblock(map of tiles) is used for the background
#define BG_SBB_MASK	0x1F00

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
#define bg_tile4_mem ((CHARBLOCK4*)(MEM_VRAM))
#define bg_tile8_mem ((CHARBLOCK8*)(MEM_VRAM))
#define obj_tile4_mem ((TILE4*)(MEM_VRAM + 0x010000)) //Sprite tile RAM
#define obj_tile8_mem ((TILE8*)(MEM_VRAM + 0x010000)) 

//TILE MAPPING
typedef u16 SCR_ENTRY; //A SCR_ENTRY contains a tile index and per tile settings
typedef SCR_ENTRY SCREENBLOCK[1024]; //A screenblock is a map of references to tiledata
#define scrb_mem ((SCREENBLOCK*)(MEM_VRAM)) //Note that SCREENBLOCKs use the same memory as CHARBLOCKS, but are 1/8th of the size. 

//SCR_ENTRY DATA
#define SE_ID(n) n; //Tile index
#define SE_ID_MASK 0x03FF //Tile index mask
#define SE_PALBANK(n) (n<<12) //Palette index
#define SE_PALBANK_MASK 0xF000 //Palette index mask

#define SE_HFLIP		0x0400	//Horizontal flip
#define SE_VFLIP		0x0800	//Vertical flip

typedef struct OBJ_ATTR //Object attributes struct. Note that this is interlaced with OBJ_AFFINE struct
{
	u16 attr0;
	u16 attr1;
	u16 attr2;
	s16 fill;
} ALIGN4 OBJ_ATTR;

#define obj_attr_mem ((OBJ_ATTR*)(MEM_OAM))

//OBJ_ATTR0 BITS
#define ATTR0_SHOW 0x0000 //Show object.
#define ATTR0_HIDE 0x0200 //Hide object.

#define ATTR0_4BPP 0x0000 //Use 4bpp (16 color) tiles
#define ATTR0_8BPP 0x2000 //Use 8bpp (256 color) tiles

#define ATTR0_SQUARE 0x0000 //Square shape
#define ATTR0_WIDE 0x4000 //Wide shape
#define ATTR0_TALL 0x8000 //Tall shape

#define ATTR0_Y(n) n //y value selected, 0-511
#define ATTR0_Y_MASK 0x00FF //Apply this mask to just show the y value

//OBJ_ATTR1 BITS
#define ATTR1_HFLIP	0x1000	//Horizontal flip
#define ATTR1_VFLIP	0x2000	//Vertical flip

// Square sizes (Bits 14-15 are unset)
#define ATTR1_SIZE_1x1  0x0000 //8x8 px object
#define ATTR1_SIZE_2x2	0x4000 //16x16 px object
#define ATTR1_SIZE_4x4	0x8000 //32x32 px object
#define ATTR1_SIZE_8x8	0xC000 //64x64 px object
// Wide sizes (Bit 14 is set)
#define ATTR1_SIZE_2x1 0x0000 //16x8 px object
#define ATTR1_SIZE_4x1 0x4000 //32x8 px object
#define ATTR1_SIZE_4x2 0x8000 //32x16 px object
#define ATTR1_SIZE_8x4 0xC000 //64x32 px object
// Tall sizes (Bit 15 is set)
#define ATTR1_SIZE_1x2 0x0000 //8x16 px object
#define ATTR1_SIZE_1x4 0x4000 //8x32 px object
#define ATTR1_SIZE_2x4 0x8000 //16x32 px object
#define ATTR1_SIZE_4x8 0xC000 //32x64 px object

#define ATTR1_X(n) n //x value selected, 0-511
#define ATTR1_X_MASK 0x01FF //Apply this mask to just show the x value

//OBJ_ATTR2 BITS
#define ATTR2_TILE_MASK 0x03FF //Masks to just show tile index
#define ATTR2_TILE(n) n //Starting tile index in obj mem. 0-1023

#define ATTR2_PRIO_MASK	0x0C00
#define ATTR2_PRIO(n) (n << 10) //Priority relative to BG, 0 is highest

#define ATTR2_PALBANK_MASK 0x0C00 
#define ATTR2_PALBANK(n) (n << 12) //Palette, uses obj_palette_mem

//PALETTES
#define RGB15(r, g, b) r | g << 5 | b << 10 //One 15 bit rgb colour. BBBBBGGGGGRRRRR
typedef struct {u16 colours[16];} ALIGN4 palette; //A single palette contains 16 colours
#define bg_palette_mem ((palette*)(MEM_PALETTES))
#define obj_palette_mem ((palette*)(MEM_PALETTES+0x0200))

//KEYPAD INPUT
#define REG_KEYINPUT *((vu16*)(MEM_IO + 0x0130))

//REG_KEYINPUT MASKS. Note that 0=pressed, 1=released
#define KEY_A 0x0001
#define KEY_B 0x0002
#define KEY_SELECT 0x0004
#define KEY_START 0x0008
#define KEY_RIGHT 0x0010
#define KEY_LEFT 0x0020
#define KEY_UP 0x0040
#define KEY_DOWN 0x0080
#define KEY_R 0x0100
#define KEY_L 0x0200

//SOUND
#define REG_SOUNDCNT_L *((vu16*)(MEM_IO + 0x080))
#define SOUNDCNT_L_RIGHT_VOLUME(n) n //master volume for channels 1-4 (0-7)
#define SOUNDCNT_L_LEFT_VOLUME(n) (n<<4) //master volume for channels 1-4 (0-7)
#define SOUNDCNT_L_RIGHT_CHANNEL1_ENABLE 0x0100
#define SOUNDCNT_L_RIGHT_CHANNEL2_ENABLE 0x0200
#define SOUNDCNT_L_RIGHT_CHANNEL3_ENABLE 0x0400
#define SOUNDCNT_L_RIGHT_CHANNEL4_ENABLE 0x0800
#define SOUNDCNT_L_LEFT_CHANNEL1_ENABLE 0x1000
#define SOUNDCNT_L_LEFT_CHANNEL2_ENABLE 0x2000
#define SOUNDCNT_L_LEFT_CHANNEL3_ENABLE 0x4000
#define SOUNDCNT_L_LEFT_CHANNEL4_ENABLE 0x8000

#define REG_SOUNDCNT_X *((vu32*)(MEM_IO + 0x084))
#define SOUNDCNT_X_CHANNEL1_ON 0x0001
#define SOUNDCNT_X_CHANNEL2_ON 0x0002
#define SOUNDCNT_X_CHANNEL3_ON 0x0004
#define SOUNDCNT_X_CHANNEL4_ON 0x0008
#define SOUNDCNT_X_MASTER_ON 0x0080

#define REG_SOUNDCNT_H *((vu16*)(MEM_IO + 0x082))
#define SOUNDCNT_H_VOL25 0
#define SOUNDCNT_H_VOL50 1
#define SOUNDCNT_H_VOL100 2

#define REG_SOUND1CNT_H *((vu16*)(MEM_IO + 0x062))
#define SOUND12CNT_H_LEN(n) n //controls length of sound, 6 bits, units of (64-n)/256s 
#define SOUND12CNT_H_DUTY_12 0x0000
#define SOUND12CNT_H_DUTY_25 0x0040
#define SOUND12CNT_H_DUTY_50 0x0080
#define SOUND12CNT_H_DUTY_75 0x00C0 
#define SOUND12CNT_ENV_TIME(n) (n<<8) //0-7, envelope step time. 0 = no envelope
#define SOUND12CNT_ENV_INCREASE 0x0800
#define SOUND12CNT_ENV_VOL (n<<12) //0-15, initial envelope volume

#define REG_SOUND1CNT_X *((vu16*)(MEM_IO + 0x064))
#define SOUND1CNT_X_LENGTH_ON 0x4000 
#define SOUND1CNT_X_TRIGGER 0x8000 
//Vsyncing function
INLINE void vid_vsync() {
	while(REG_VCOUNT >= 160);   // wait till VDraw
    while(REG_VCOUNT < 160);    // wait till VBlank
};

#define vid_mem ((u16*)MEM_VRAM)
//Plotting function for mode 3
INLINE void m3_plot(int x, int y, u16 clr)
{
    vid_mem[y*SCREEN_WIDTH+x] = clr;
}