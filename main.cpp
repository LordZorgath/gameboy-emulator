/* 
 * Author: Justin
 * Created on May 7, 2019, 2:20 PM
 * If you remove this comment, you will die instantly.
 */
#define NULL 0;
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include "SDL2/SDL.h"
#include "global.h"
#include "memory.h"
#include "cpuint.h"
#include "ppuint.h"
//Note: Master GB tick is 4194304Hz, or 2^22Hz
void sdl_setup(){
	SDL_Init(SDL_INIT_EVERYTHING);
	gameWindow = SDL_CreateWindow("GameBoy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(gameWindow, -1, SDL_SWSURFACE | SDL_RENDERER_PRESENTVSYNC);
	screen = SDL_GetWindowSurface(gameWindow);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for(int x = 0; x < 160; x++){
		for(int y = 0; y < 144; y++){
			graphics[x][y].w = psize;
			graphics[x][y].h = psize;
			graphics[x][y].x = x * psize;
			graphics[x][y].y = y * psize;
		}
	}
}
void updateDisplay(){
	SDL_SetRenderDrawColor(renderer, 0, 64, 0, 255);
	SDL_RenderClear(renderer);
	for(unsigned int y = 0; y < 144; y++){
		for(unsigned int x = 0; x < 160; x++){
			if(lcdc.displayEnable){
				if(!colors[0][x][y] && !colors[1][x][y]){
					SDL_SetRenderDrawColor(renderer, 0, 64, 0, 255);
					if((SDL_RenderFillRect(renderer, &graphics[x][y])) != 0){
						std::cout << "Graphics error\n";
					}
				}
				if(colors[0][x][y] && !colors[1][x][y]){
					SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
					if((SDL_RenderFillRect(renderer, &graphics[x][y])) != 0){
						std::cout << "Graphics error\n";
					}
				}
				if(!colors[0][x][y] && colors[1][x][y]){
					SDL_SetRenderDrawColor(renderer, 0, 192, 0, 255);
					if((SDL_RenderFillRect(renderer, &graphics[x][y])) != 0){
						std::cout << "Graphics error\n";
					}
				}
				if(colors[0][x][y] && colors[1][x][y]){
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
					if((SDL_RenderFillRect(renderer, &graphics[x][y])) != 0){
						std::cout << "Graphics error\n";
					}
				}
			}else{
				SDL_SetRenderDrawColor(renderer, (rand() % 256), (rand() % 256), (rand() % 256), 255);
				if((SDL_RenderFillRect(renderer, &graphics[x][y])) != 0){
						std::cout << "Graphics error\n";
				}
			}
		}
	}
	SDL_RenderPresent(renderer);
}
void (* iterateCPU[2][16][16])() = {
	{
	{opcode00, opcode01, opcode02, opcode03, opcode04, opcode05, opcode06, opcode07, opcode08, opcode09, opcode0A, opcode0B, opcode0C, opcode0D, opcode0E, opcode0F},
	{opcode10, opcode11, opcode12, opcode13, opcode14, opcode15, opcode16, opcode17, opcode18, opcode19, opcode1A, opcode1B, opcode1C, opcode1D, opcode1E, opcode1F},
	{opcode20, opcode21, opcode22, opcode23, opcode24, opcode25, opcode26, opcode27, opcode28, opcode29, opcode2A, opcode2B, opcode2C, opcode2D, opcode2E, opcode2F},
	{opcode30, opcode31, opcode32, opcode33, opcode34, opcode35, opcode36, opcode37, opcode38, opcode39, opcode3A, opcode3B, opcode3C, opcode3D, opcode3E, opcode3F},
	{opcode40, opcode41, opcode42, opcode43, opcode44, opcode45, opcode46, opcode47, opcode48, opcode49, opcode4A, opcode4B, opcode4C, opcode4D, opcode4E, opcode4F},
	{opcode50, opcode51, opcode52, opcode53, opcode54, opcode55, opcode56, opcode57, opcode58, opcode59, opcode5A, opcode5B, opcode5C, opcode5D, opcode5E, opcode5F},
	{opcode60, opcode61, opcode62, opcode63, opcode64, opcode65, opcode66, opcode67, opcode68, opcode69, opcode6A, opcode6B, opcode6C, opcode6D, opcode6E, opcode6F},
	{opcode70, opcode71, opcode72, opcode73, opcode74, opcode75, opcode76, opcode77, opcode78, opcode79, opcode7A, opcode7B, opcode7C, opcode7D, opcode7E, opcode7F},
	{opcode80, opcode81, opcode82, opcode83, opcode84, opcode85, opcode86, opcode87, opcode88, opcode89, opcode8A, opcode8B, opcode8C, opcode8D, opcode8E, opcode8F},
	{opcode90, opcode91, opcode92, opcode93, opcode94, opcode95, opcode96, opcode97, opcode98, opcode99, opcode9A, opcode9B, opcode9C, opcode9D, opcode9E, opcode9F},
	{opcodeA0, opcodeA1, opcodeA2, opcodeA3, opcodeA4, opcodeA5, opcodeA6, opcodeA7, opcodeA8, opcodeA9, opcodeAA, opcodeAB, opcodeAC, opcodeAD, opcodeAE, opcodeAF},
	{opcodeB0, opcodeB1, opcodeB2, opcodeB3, opcodeB4, opcodeB5, opcodeB6, opcodeB7, opcodeB8, opcodeB9, opcodeBA, opcodeBB, opcodeBC, opcodeBD, opcodeBE, opcodeBF},
	{opcodeC0, opcodeC1, opcodeC2, opcodeC3, opcodeC4, opcodeC5, opcodeC6, opcodeC7, opcodeC8, opcodeC9, opcodeCA, opcodeCB, opcodeCC, opcodeCD, opcodeCE, opcodeCF},
	{opcodeD0, opcodeD1, opcodeD2, ukopcode, opcodeD4, opcodeD5, opcodeD6, opcodeD7, opcodeD8, opcodeD9, opcodeDA, ukopcode, opcodeDC, ukopcode, opcodeDE, opcodeDF},
	{opcodeE0, opcodeE1, opcodeE2, ukopcode, ukopcode, opcodeE5, opcodeE6, opcodeE7, opcodeE8, opcodeE9, opcodeEA, ukopcode, ukopcode, ukopcode, opcodeEE, opcodeEF},
	{opcodeF0, opcodeF1, opcodeF2, opcodeF3, ukopcode, opcodeF5, opcodeF6, opcodeF7, opcodeF8, opcodeF9, opcodeFA, opcodeFB, ukopcode, ukopcode, opcodeFE, opcodeFF}
	},
	{
	{cbcode00, cbcode01, cbcode02, cbcode03, cbcode04, cbcode05, cbcode06, cbcode07, cbcode08, cbcode09, cbcode0A, cbcode0B, cbcode0C, cbcode0D, cbcode0E, cbcode0F},
	{cbcode10, cbcode11, cbcode12, cbcode13, cbcode14, cbcode15, cbcode16, cbcode17, cbcode18, cbcode19, cbcode1A, cbcode1B, cbcode1C, cbcode1D, cbcode1E, cbcode1F},
	{cbcode20, cbcode21, cbcode22, cbcode23, cbcode24, cbcode25, cbcode26, cbcode27, cbcode28, cbcode29, cbcode2A, cbcode2B, cbcode2C, cbcode2D, cbcode2E, cbcode2F},
	{cbcode30, cbcode31, cbcode32, cbcode33, cbcode34, cbcode35, cbcode36, cbcode37, cbcode38, cbcode39, cbcode3A, cbcode3B, cbcode3C, cbcode3D, cbcode3E, cbcode3F},
	{cbcode40, cbcode41, cbcode42, cbcode43, cbcode44, cbcode45, cbcode46, cbcode47, cbcode48, cbcode49, cbcode4A, cbcode4B, cbcode4C, cbcode4D, cbcode4E, cbcode4F},
	{cbcode50, cbcode51, cbcode52, cbcode53, cbcode54, cbcode55, cbcode56, cbcode57, cbcode58, cbcode59, cbcode5A, cbcode5B, cbcode5C, cbcode5D, cbcode5E, cbcode5F},
	{cbcode60, cbcode61, cbcode62, cbcode63, cbcode64, cbcode65, cbcode66, cbcode67, cbcode68, cbcode69, cbcode6A, cbcode6B, cbcode6C, cbcode6D, cbcode6E, cbcode6F},
	{cbcode70, cbcode71, cbcode72, cbcode73, cbcode74, cbcode75, cbcode76, cbcode77, cbcode78, cbcode79, cbcode7A, cbcode7B, cbcode7C, cbcode7D, cbcode7E, cbcode7F},
	{cbcode80, cbcode81, cbcode82, cbcode83, cbcode84, cbcode85, cbcode86, cbcode87, cbcode88, cbcode89, cbcode8A, cbcode8B, cbcode8C, cbcode8D, cbcode8E, cbcode8F},
	{cbcode90, cbcode91, cbcode92, cbcode93, cbcode94, cbcode95, cbcode96, cbcode97, cbcode98, cbcode99, cbcode9A, cbcode9B, cbcode9C, cbcode9D, cbcode9E, cbcode9F},
	{cbcodeA0, cbcodeA1, cbcodeA2, cbcodeA3, cbcodeA4, cbcodeA5, cbcodeA6, cbcodeA7, cbcodeA8, cbcodeA9, cbcodeAA, cbcodeAB, cbcodeAC, cbcodeAD, cbcodeAE, cbcodeAF},
	{cbcodeB0, cbcodeB1, cbcodeB2, cbcodeB3, cbcodeB4, cbcodeB5, cbcodeB6, cbcodeB7, cbcodeB8, cbcodeB9, cbcodeBA, cbcodeBB, cbcodeBC, cbcodeBD, cbcodeBE, cbcodeBF},
	{cbcodeC0, cbcodeC1, cbcodeC2, cbcodeC3, cbcodeC4, cbcodeC5, cbcodeC6, cbcodeC7, cbcodeC8, cbcodeC9, cbcodeCA, cbcodeCB, cbcodeCC, cbcodeCD, cbcodeCE, cbcodeCF},
	{cbcodeD0, cbcodeD1, cbcodeD2, cbcodeD3, cbcodeD4, cbcodeD5, cbcodeD6, cbcodeD7, cbcodeD8, cbcodeD9, cbcodeDA, cbcodeDB, cbcodeDC, cbcodeDD, cbcodeDE, cbcodeDF},
	{cbcodeE0, cbcodeE1, cbcodeE2, cbcodeE3, cbcodeE4, cbcodeE5, cbcodeE6, cbcodeE7, cbcodeE8, cbcodeE9, cbcodeEA, cbcodeEB, cbcodeEC, cbcodeED, cbcodeEE, cbcodeEF},
	{cbcodeF0, cbcodeF1, cbcodeF2, cbcodeF3, cbcodeF4, cbcodeF5, cbcodeF6, cbcodeF7, cbcodeF8, cbcodeF9, cbcodeFA, cbcodeFB, cbcodeFC, cbcodeFD, cbcodeFE, cbcodeFF}
	}
};
void cpu(){
	if(ciscIsGayTimer == 0){
		if(ime){
			if(interruptDelay){
				interruptDelay = false;
				ciscIsGayTimer = 19;
			}else{
				if(!interruptMode){
					buswrite((sp++), pc);
					interruptMode = true;
				}
				if((ie & 0b00000001) && (inf & 0b00000001)){
					pc = 0x40;
					interruptStart = 0x40;
					ime = false;
					inf &= 0b11111110;
					return;
				}
				if((ie & 0b00000010) && (inf & 0b00000010)){
					pc = 0x48;
					interruptStart = 0x48;
					ime = false;
					inf &= 0b11111101;
					return;
				}
				if((ie & 0b00000100) && (inf & 0b00000100)){
					pc = 0x50;
					interruptStart = 0x50;
					ime = false;
					inf &= 0b11111011;
					return;
				}
				if((ie & 0b00001000) && (inf & 0b00001000)){
					pc = 0x58;
					interruptStart = 0x58;
					ime = false;
					inf &= 0b11110111;
					return;
				}
				if((ie & 0b00010000) && (inf & 0b00010000)){
					pc = 0x60;
					interruptStart = 0x60;
					ime = false;
					inf &= 0b11101111;
					return;
				}
			}
		}
		if(interruptMode && (pc == (interruptStart + 8))){
			pc = busread(sp--);
			interruptMode = false;
		}
		if(debugMode){
			std::cout << "OPCODE " << (((busread(pc) & 0xF0) | (busread(pc) & 0x0F))) << "\n";
			std::cout << "LCDC " << busread(0xFF40);
			std::cout << "PC " << pc << "\n";
			std::cout << "SP " << sp << "\n";
			std::cout << "A  " << (reg.a | 0x00) << "\n";
			std::cout << "LY " << (ly | 0x00) << "\n";
			std::cout << "BC " << reg.bc << "\n";
			std::cout << "DE " << reg.de << "\n";
			std::cout << "HL " << reg.hl << "\n";
			if(z){
				std::cout << "Z";
			}
			if(n){
				std::cout << "N";
			}
			if(h){
				std::cout << "H";
			}
			if(c){
				std::cout << "C";
			}
		}
		ciscIsGayTimer = 3;
		if(cb){
			iterateCPU[1][((busread(pc) & 0xF0) >> 4)][(busread(pc) & 0x0F)]();
			cb = false;
		}else{
			iterateCPU[0][((busread(pc) & 0xF0) >> 4)][(busread(pc) & 0x0F)]();
		}
		if(testROM){
			if(busread(0xFF02) == 0x81){
				char c = busread(0xFF01);
				std::cout << "C " << c << std::endl;
				buswrite(0xFF02, 0);
			}
		}
		pc++;
	}else{
		ciscIsGayTimer--;
	}
}
void ppu(unsigned long){
	if(tick == 65663){
		vblank = true;
		vblanks++;
		stat.mode = 1;
	}
	if(!(tick % 456)){
		ly++;
		if(!vblank){
			stat.mode = 2;
			oamscan();
			oamscans++;
		}
	}
	if((!((tick - 80) % 456)) && !vblank){
		stat.mode = 3;
		hdraw();
		hdraws++;
	}
	if((!((tick - 252) % 456)) && !vblank){
		stat.mode = 0;
		hblanks++;
	}
	if(tick == 70223){
		//std::cout << (oamscans | 0x00) << std::endl;
		//std::cout << (hdraws | 0x00) << std::endl;
		//std::cout << (hblanks | 0x00) << std::endl;
		//std::cout << (vblanks | 0x00) << std::endl;
		//std::cout << (ly | 0x00) << std::endl;
		//std::cout << tick << std::endl;
		//std::cout << std::endl;
		ly = 0;
		oamscans = 0;
		hdraws = 0;
		hblanks = 0;
		vblanks = 0;
		vblank = false;
		updateDisplay();
	}
}
void timer(){
	if(!warp9){
		if(!debugMode){
			for(tick = 0; tick < 70224; tick++){
				if((tima + 1) > 255){
					tima = tma;
					inf |= 0b00100000;
				}else{
					if(((tac & 0b00100000) >> 5)){
						if(((tac & 0b11000000) >> 6) == 0){
							if(!(tick % 4096)){
								tima++;
							}
						}
						if(((tac & 0b11000000) >> 6) == 1){
							if(!(tick % 64)){
								tima++;
							}
						}
						if(((tac & 0b11000000) >> 6) == 2){
							if(!(tick % 256)){
								tima++;
							}
						}
						if(((tac & 0b11000000) >> 6) == 3){
							if(!(tick % 1024)){
								tima++;
							}
						}
					}
				}
				cpu();
				if(lcdc.displayEnable){
					ppu(tick);
				}
				if(!(tick % 256)){
					divider++;
				}
			}
		}else{
			if(update){
				for(int i = 0; i < debugSpeed; i++){
					if(i >= 1){
						std::cout << "\n";
					}
					unsigned char ciscTimerTwo = ciscIsGayTimer;
					for(int j = 0; j <= ciscTimerTwo; j++){
						tick++;
						if((tima + 1) > 255){
							tima = tma;
							inf |= 0b00100000;
						}else{
							if(((tac & 0b00100000) >> 5)){
								if(((tac & 0b11000000) >> 6) == 0){
									if(!(tick % 4096)){
										tima++;
									}
								}
								if(((tac & 0b11000000) >> 6) == 1){
									if(!(tick % 64)){
										tima++;
									}
								}
								if(((tac & 0b11000000) >> 6) == 2){
									if(!(tick % 256)){
										tima++;
									}
								}
								if(((tac & 0b11000000) >> 6) == 3){
									if(!(tick % 1024)){
										tima++;
									}
								}
							}
						}
						cpu();
						if(lcdc.displayEnable){
							ppu(tick);
						}
						//OAM = 80
						//Hdraw = 172
						//Hblank = 204
						if(!(tick % 256)){
							divider++;
						}
						update = false;
					}
				}
				std::cout << std::endl;
			}
		}
	}else{
		while(true){
			tick++;
			if((tima + 1)> 255){
				tima = tma;
				inf |= 0b00100000;
			}else{
				if(((tac & 0b00100000) >> 5)){
					if(((tac & 0b11000000) >> 6) == 0){
						if(!(tick % 4096)){
							tima++;
						}
					}
					if(((tac & 0b11000000) >> 6) == 1){
						if(!(tick % 64)){
							tima++;
						}
					}
					if(((tac & 0b11000000) >> 6) == 2){
						if(!(tick % 256)){
							tima++;
						}
					}
					if(((tac & 0b11000000) >> 6) == 3){
						if(!(tick % 1024)){
							tima++;
						}
					}
				}
			}
			cpu();
			if(!(tick % 456)){
				ly++;
			}
			if(ly > 154){
				ly = 0;
			}
			if(!(tick % 256)){
				divider++;
			}
			if(!warp9){
				break;
			}
		}
	}
}
void bootup(){
	if(!boot){
		reg.a = 0x01;
		reg.bc = 0x0013;
		reg.de = 0x00D8;
		reg.hl = 0x014D;
		z = true;
		n = false;
		h = true;
		c = true;
		sp = 0xFFFE;
		tima = 0;
		tma = 0;
		tac = 0;
		nr10 = 0x80;
		nr11 = 0xBF;
		nr12 = 0xF3;
		nr14 = 0xBF;
		nr21 = 0x3F;
		nr22 = 0;
		nr24 = 0xBF;
		nr30 = 0x7F;
		nr31 = 0xFF;
		nr32 = 0x9F;
		nr33 = 0xBF;
		nr41 = 0xFF;
		nr42 = 0;
		nr43 = 0;
		nr50 = 0x77;
		nr51 = 0xF3;
		nr52 = 0xF1;
		lcdc.displayEnable = false;
		lcdc.windowTileMapSelect = true;
		lcdc.tileDataSelect = true;
		lcdc.backgroundTileMapSelect = true;
		lcdc.objectEnable = true;
		lcdc.backgroundEnable = true;
		scy = 0;
		scx = 0;
		lyc = 0;
		bgp = 0xFC;
		obp0 = 0xFF;
		obp1 = 0xFF;
		wy = 0;
		wx = 0;
		ie = 0;
		pc = 0x100;
	}
	stat.lyInterrupt = true;
	stat.coincidenceFlag = true;
	stat.mode = 0;
	updateDisplay();
}
int main(int argc, char** argv) {
	std::string game;
	std::cout << std::hex;
	std::ifstream bios;
	std::ifstream file;
	bios.open("bios/gbbios.gb", std::ifstream::binary);
	if(!bios.good()){
		std::cout << "File load error!\n";
	}else{
		bios.read((char*)bootrom, 256);
	}
	if(testROM){
		std::ifstream test;
		test.open("Test/05-op rp.gb", std::ifstream::binary);
		if(!test.good()){
			std::cout << "File load error!\n";
		}else{
			test.read((char*)exrom, 32768);
		}
	}else{
		std::cout << "Type the name of the ROM located in /games you want to load\n";
		std::cin >> game;
		file.open("Games/" + game, std::ifstream::binary);
		if(!file.good()){
			std::cout << "File load error!\n";
		}else{
			file.read((char*)exrom, 32768);
		}
	}
	sdl_setup();
	bootup();
	while(run){
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_QUIT:
				run = false;
				break;
			case SDL_KEYDOWN:
				if((event.key.keysym.scancode == SDL_SCANCODE_V) && (debugMode)){
					debugSpeed++;
				}
				if((event.key.keysym.scancode == SDL_SCANCODE_C) && (debugMode)){
					debugSpeed*=0x10;
				}
				if((event.key.keysym.scancode == SDL_SCANCODE_B) && (debugMode) && (debugSpeed > 1)){
					debugSpeed--;
				}
				if((event.key.keysym.scancode == SDL_SCANCODE_N) && (debugMode)){
					debugSpeed = 1;
				}
				if((event.key.keysym.scancode == SDL_SCANCODE_SPACE) && (debugMode)){
					update = true;
				}
				if(debugSpeed > 4389){
					debugSpeed = 4389;
				}
				if((event.key.keysym.scancode != SDL_SCANCODE_SPACE) && (debugMode)){
					std::cout << debugSpeed << std::endl;
				}
				break;
			}
		}
		timer();
	}
}