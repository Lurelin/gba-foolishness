#include "data.h"
palette palette_game = {
	0x0000,0x0948,0x160E,0x22B4,0x2F5A,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
};

cu32 tiles_background[8] ALIGN4 = {
	0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,
};
cu32 tiles_cursor_large[32] ALIGN4 = {
	0x00004444,0x00000004,0x00000004,0x00000004,0x00000000,0x00000000,0x00000000,0x00000000,
	0x44440000,0x40000000,0x40000000,0x40000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000004,0x00000004,0x00000004,0x00004444,
	0x00000000,0x00000000,0x00000000,0x00000000,0x40000000,0x40000000,0x40000000,0x44440000,
};
cu32 tiles_cursor_small[8] ALIGN4 = {
	0x44000044,0x40000004,0x00000000,0x00000000,0x00000000,0x00000000,0x40000004,0x44000044,
};
cu32 tiles_pipe_horizontal_large[32] ALIGN4 = {
	0x11111111,0x11111111,0x11111114,0x44444444,0x44344434,0x43434343,0x34333433,0x33333333,
	0x11111111,0x11111111,0x41111111,0x44444444,0x44344434,0x43434343,0x34333433,0x33333333,
	0x33333333,0x33323332,0x23232323,0x22322232,0x22222222,0x11111112,0x11111111,0x11111111,
	0x33333333,0x33323332,0x23232323,0x22322232,0x22222222,0x21111111,0x11111111,0x11111111,
};
cu32 tiles_pipe_horizontal_small[8] ALIGN4 = {
	0x11111111,0x44444444,0x34343434,0x33333333,0x33333333,0x23232323,0x22222222,0x11111111,
};
cu32 tiles_pipe_vertical_large[32] ALIGN4 = {
	0x32322211,0x33232111,0x33322111,0x33222111,0x32322111,0x33232111,0x33322111,0x33222111,
	0x11444333,0x11143433,0x11144343,0x11144433,0x11144333,0x11143433,0x11144343,0x11144433,
	0x32322111,0x33232111,0x33322111,0x33222111,0x32322111,0x33232111,0x33322111,0x33222211,
	0x11144333,0x11143433,0x11144343,0x11144433,0x11144333,0x11143433,0x11144343,0x11444433,
};
cu32 tiles_pipe_vertical_small[8] ALIGN4 = {
	0x14433321,0x14333221,0x14433321,0x14333221,0x14433321,0x14333221,0x14433321,0x14333221,
};
cu32 tiles_popup_placeholder[32] ALIGN4 = {
	0x22222222, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
	0x00000002, 0x00000002, 0x00000002, 0x00000002, 0x00000002, 0x00000002, 0x00000002, 0x00000002, 
	0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x20000000, 
};