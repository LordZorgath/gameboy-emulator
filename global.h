/* 
 * File:   global.h
 * Author: justin
 * If you remove this comment, you will die instantly.
 * Created on July 10, 2019, 2:47 PM
 */

#ifndef GLOBAL_H
#define GLOBAL_H
bool run = true;
bool warp9 = false;
bool debugMode = false;
bool boot = false;
bool testROM = true;
bool update = false;
int debugSpeed = 1;
unsigned long long tick = 0;
SDL_Window* gameWindow = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* screen = NULL;
SDL_Palette display;
SDL_Rect graphics[160][144];
int psize = 5;
unsigned int vblanks = 0;
unsigned int hblanks = 0;
unsigned int hdraws = 0;
unsigned int oamscans = 0;
const int SCREEN_WIDTH = (160 * psize);
const int SCREEN_HEIGHT = (144 * psize);
unsigned char bootrom[256];
unsigned char exrom[32768];
unsigned char vram[8192];
unsigned char exram[8192];
unsigned char wram[8192];
unsigned char echo[7680];
unsigned char oamem[160];
unsigned char hram[128];
unsigned char io[127];
struct lcdc{
	bool displayEnable;
	bool windowTileMapSelect;
	bool windowEnable;
	bool tileDataSelect;
	bool backgroundTileMapSelect;
	bool objectSize;
	bool objectEnable;
	bool backgroundEnable;
};
struct stat{
	bool lyInterrupt;
	bool oamInterrupt;
	bool vblankInterrupt;
	bool hblankInterrupt;
	bool coincidenceFlag;
	char mode;
};
lcdc lcdc;
stat stat;
unsigned char scy;
unsigned char scx;
unsigned char ly;
unsigned char lyc;
unsigned char dma;
unsigned char bgp;
unsigned char obp0;
unsigned char obp1;
unsigned char wy;
unsigned char wx;
unsigned char joypad;
unsigned char sb;
unsigned char sc;
unsigned char divider;
unsigned char tima;
unsigned char tma;
unsigned char tac;
unsigned char nr10;
unsigned char nr11;
unsigned char nr12;
unsigned char nr13;
unsigned char nr14;
unsigned char nr21;
unsigned char nr22;
unsigned char nr23;
unsigned char nr24;
unsigned char nr30;
unsigned char nr31;
unsigned char nr32;
unsigned char nr33;
unsigned char nr34;
unsigned char nr41;
unsigned char nr42;
unsigned char nr43;
unsigned char nr44;
unsigned char nr50;
unsigned char nr51;
unsigned char nr52;
unsigned char inf;
unsigned char ie;
bool vblank = false;
struct reg{
	Uint8 a;
	union{
		Uint16 bc;
		struct{
			Uint8 c;
			Uint8 b;
		};
	};
	union{
		Uint16 de;
		struct{
			Uint8 e;
			Uint8 d;
		};
	};
	union{
		Uint16 hl;
		struct{
			Uint8 l;
			Uint8 h;
		};
	};
};
unsigned short sp;
unsigned short pc = 0;
bool z;
bool n;
bool h;
bool c;
struct reg reg;
bool cb;
bool ime;
bool interruptMode = false;
bool interruptDelay = false;
unsigned short interruptStart;
int ciscIsGayTimer = 0;
bool backgroundTileset[2][256][256];
bool windowTileset[2][256][256];
bool colors[2][160][144];
bool objectPatterns[2][320][16];
int objectsPerLine[144];
struct object{
	char ypos;
	char xpos;
	char tilepat;
	bool priority;
	bool yflip;
	bool xflip; 
	bool palettenum;
};
struct tile{
	unsigned char line0a;
	unsigned char line0b;
	unsigned char line1a;
	unsigned char line1b;
	unsigned char line2a;
	unsigned char line2b;
	unsigned char line3a;
	unsigned char line3b;
	unsigned char line4a;
	unsigned char line4b;
	unsigned char line5a;
	unsigned char line5b;
	unsigned char line6a;
	unsigned char line6b;
	unsigned char line7a;
	unsigned char line7b;
};
object sprites[40];
tile background[256];
tile window[256];
char backgroundNumbers[32][32];
char windowNumbers[32][32];
tile backgroundDisplay[32][32];
tile windowDisplay[32][32];
#endif /* GLOBAL_H */

