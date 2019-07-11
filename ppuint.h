/* 
 * File:   ppuint.h
 * Author: Justin
 * If you remove this comment, you will die instantly.
 * Created on May 25, 2019, 4:17 PM
 */
#ifndef PPUINT_H
#define PPUINT_H
void oamscan(){
	for(int obj = 0; obj <= 160; obj+=4){
		sprites[obj].ypos = oamem[obj];
		sprites[obj].xpos = oamem[obj+1];
		sprites[obj].tilepat = oamem[obj+2];
		sprites[obj].priority = (oamem[obj+3] & 0b1000000);
		sprites[obj].yflip = (oamem[obj+3] & 0b0100000);
		sprites[obj].xflip = (oamem[obj+3] & 0b0010000);
		sprites[obj].palettenum = (oamem[obj+3] & 0b0001000);
	}
}
void hdraw(){
	//Reading background tilesets
	if(lcdc.backgroundEnable){
		for(int tn = 0; tn < 96; tn++){
			if(lcdc.tileDataSelect){
				background[tn].line0a = (vram[(((tn * 16)) + 0)]);
				background[tn].line0b = (vram[(((tn * 16)) + 1)]);
				background[tn].line1a = (vram[(((tn * 16)) + 2)]);
				background[tn].line1b = (vram[(((tn * 16)) + 3)]);
				background[tn].line2a = (vram[(((tn * 16)) + 4)]);
				background[tn].line2b = (vram[(((tn * 16)) + 5)]);
				background[tn].line3a = (vram[(((tn * 16)) + 6)]);
				background[tn].line3b = (vram[(((tn * 16)) + 7)]);
				background[tn].line4a = (vram[(((tn * 16)) + 8)]);
				background[tn].line4b = (vram[(((tn * 16)) + 9)]);
				background[tn].line5a = (vram[(((tn * 16)) + 10)]);
				background[tn].line5b = (vram[(((tn * 16)) + 11)]);
				background[tn].line6a = (vram[(((tn * 16)) + 12)]);
				background[tn].line6b = (vram[(((tn * 16)) + 13)]);
				background[tn].line7a = (vram[(((tn * 16)) + 14)]);
				background[tn].line7b = (vram[(((tn * 16)) + 15)]);
			}else{
				background[tn].line0a = (vram[(0x800 + (((tn * 16)) + 0))]);
				background[tn].line0b = (vram[(0x800 + (((tn * 16)) + 1))]);
				background[tn].line1a = (vram[(0x800 + (((tn * 16)) + 2))]);
				background[tn].line1b = (vram[(0x800 + (((tn * 16)) + 3))]);
				background[tn].line2a = (vram[(0x800 + (((tn * 16)) + 4))]);
				background[tn].line2b = (vram[(0x800 + (((tn * 16)) + 5))]);
				background[tn].line3a = (vram[(0x800 + (((tn * 16)) + 6))]);
				background[tn].line3b = (vram[(0x800 + (((tn * 16)) + 7))]);
				background[tn].line4a = (vram[(0x800 + (((tn * 16)) + 8))]);
				background[tn].line4b = (vram[(0x800 + (((tn * 16)) + 9))]);
				background[tn].line5a = (vram[(0x800 + (((tn * 16)) + 10))]);
				background[tn].line5b = (vram[(0x800 + (((tn * 16)) + 11))]);
				background[tn].line6a = (vram[(0x800 + (((tn * 16)) + 12))]);
				background[tn].line6b = (vram[(0x800 + (((tn * 16)) + 13))]);
				background[tn].line7a = (vram[(0x800 + (((tn * 16)) + 14))]);
				background[tn].line7b = (vram[(0x800 + (((tn * 16)) + 15))]);
			}
		}
		//Reading the tile map
		for(int ty = 0; ty < 32; ty++){
			for(int tx = 0; tx < 32; tx++){
				if(lcdc.backgroundTileMapSelect){
					if(lcdc.tileDataSelect){
						backgroundNumbers[tx][ty] = (signed)vram[((0x1C00 + tx) + (ty * 32))];
					}else{
						backgroundNumbers[tx][ty] = (unsigned)vram[((0x1C00 + tx) + (ty * 32))];
					}
				}else{
					if(lcdc.tileDataSelect){
						backgroundNumbers[tx][ty] = (signed)vram[((0x1800 + tx) + (ty * 32))];
					}else{
						backgroundNumbers[tx][ty] = (unsigned)vram[((0x1800 + tx) + (ty * 32))];
					}
				}
			}
		}
		for(int dy = 0; dy < 32; dy++){
			for(int dx = 0; dx < 32; dx++){
				backgroundDisplay[dx][dy] = background[backgroundNumbers[dx][dy]];
			}
		}
		for(int bdy = 0; bdy < 32; bdy++){
			for(int bdx = 0; bdx < 32; bdx++){
				for(int bin = 0; bin < 8; bin++){
					backgroundTileset[0][((bdx*8) + bin)][((bdy*8) + 0)] = (backgroundDisplay[bdx][bdy].line0a & (0x80 >> bin));
					backgroundTileset[1][((bdx*8) + bin)][((bdy*8) + 0)] = (backgroundDisplay[bdx][bdy].line0b & (0x80 >> bin));
					backgroundTileset[0][((bdx*8) + bin)][((bdy*8) + 1)] = (backgroundDisplay[bdx][bdy].line1a & (0x80 >> bin));
					backgroundTileset[1][((bdx*8) + bin)][((bdy*8) + 1)] = (backgroundDisplay[bdx][bdy].line1b & (0x80 >> bin));
					backgroundTileset[0][((bdx*8) + bin)][((bdy*8) + 2)] = (backgroundDisplay[bdx][bdy].line2a & (0x80 >> bin));
					backgroundTileset[1][((bdx*8) + bin)][((bdy*8) + 2)] = (backgroundDisplay[bdx][bdy].line2b & (0x80 >> bin));
					backgroundTileset[0][((bdx*8) + bin)][((bdy*8) + 3)] = (backgroundDisplay[bdx][bdy].line3a & (0x80 >> bin));
					backgroundTileset[1][((bdx*8) + bin)][((bdy*8) + 3)] = (backgroundDisplay[bdx][bdy].line3b & (0x80 >> bin));
					backgroundTileset[0][((bdx*8) + bin)][((bdy*8) + 4)] = (backgroundDisplay[bdx][bdy].line4a & (0x80 >> bin));
					backgroundTileset[1][((bdx*8) + bin)][((bdy*8) + 4)] = (backgroundDisplay[bdx][bdy].line4b & (0x80 >> bin));
					backgroundTileset[0][((bdx*8) + bin)][((bdy*8) + 5)] = (backgroundDisplay[bdx][bdy].line5a & (0x80 >> bin));
					backgroundTileset[1][((bdx*8) + bin)][((bdy*8) + 5)] = (backgroundDisplay[bdx][bdy].line5b & (0x80 >> bin));
					backgroundTileset[0][((bdx*8) + bin)][((bdy*8) + 6)] = (backgroundDisplay[bdx][bdy].line6a & (0x80 >> bin));
					backgroundTileset[1][((bdx*8) + bin)][((bdy*8) + 6)] = (backgroundDisplay[bdx][bdy].line6b & (0x80 >> bin));
					backgroundTileset[0][((bdx*8) + bin)][((bdy*8) + 7)] = (backgroundDisplay[bdx][bdy].line7a & (0x80 >> bin));
					backgroundTileset[1][((bdx*8) + bin)][((bdy*8) + 7)] = (backgroundDisplay[bdx][bdy].line7b & (0x80 >> bin));
				}
			}
		}
	}
	if(lcdc.windowEnable){
		for(int tn = 0; tn < 96; tn++){
			window[tn].line0a = (vram[(0x800 + (((tn * 16)) + 0))]);
			window[tn].line0b = (vram[(0x800 + (((tn * 16)) + 1))]);
			window[tn].line1a = (vram[(0x800 + (((tn * 16)) + 2))]);
			window[tn].line1b = (vram[(0x800 + (((tn * 16)) + 3))]);
			window[tn].line2a = (vram[(0x800 + (((tn * 16)) + 4))]);
			window[tn].line2b = (vram[(0x800 + (((tn * 16)) + 5))]);
			window[tn].line3a = (vram[(0x800 + (((tn * 16)) + 6))]);
			window[tn].line3b = (vram[(0x800 + (((tn * 16)) + 7))]);
			window[tn].line4a = (vram[(0x800 + (((tn * 16)) + 8))]);
			window[tn].line4b = (vram[(0x800 + (((tn * 16)) + 9))]);
			window[tn].line5a = (vram[(0x800 + (((tn * 16)) + 10))]);
			window[tn].line5b = (vram[(0x800 + (((tn * 16)) + 11))]);
			window[tn].line6a = (vram[(0x800 + (((tn * 16)) + 12))]);
			window[tn].line6b = (vram[(0x800 + (((tn * 16)) + 13))]);
			window[tn].line7a = (vram[(0x800 + (((tn * 16)) + 14))]);
			window[tn].line7b = (vram[(0x800 + (((tn * 16)) + 15))]);
		}
		//Reading the tile map
		for(int ty = 0; ty < 32; ty++){
			for(int tx = 0; tx < 32; tx++){
				if(lcdc.windowTileMapSelect){
					if(lcdc.tileDataSelect){
						windowNumbers[tx][ty] = (signed)vram[((0x1C00 + tx) + (ty * 32))];
					}else{
						windowNumbers[tx][ty] = (unsigned)vram[((0x1C00 + tx) + (ty * 32))];
					}
				}else{
					if(lcdc.tileDataSelect){
						windowNumbers[tx][ty] = (signed)vram[((0x1800 + tx) + (ty * 32))];
					}else{
						windowNumbers[tx][ty] = (unsigned)vram[((0x1800 + tx) + (ty * 32))];
					}
				}
			}
		}
		for(int dy = 0; dy < 32; dy++){
			for(int dx = 0; dx < 32; dx++){
				windowDisplay[dx][dy] = window[windowNumbers[dx][dy]];
			}
		}
		for(int bdy = 0; bdy < 32; bdy++){
			for(int bdx = 0; bdx < 32; bdx++){
				for(int bin = 0; bin < 8; bin++){
					windowTileset[0][((bdx*8) + bin)][((bdy*8) + 0)] = (windowDisplay[bdx][bdy].line0a & (0x80 >> bin));
					windowTileset[1][((bdx*8) + bin)][((bdy*8) + 0)] = (windowDisplay[bdx][bdy].line0b & (0x80 >> bin));
					windowTileset[0][((bdx*8) + bin)][((bdy*8) + 1)] = (windowDisplay[bdx][bdy].line1a & (0x80 >> bin));
					windowTileset[1][((bdx*8) + bin)][((bdy*8) + 1)] = (windowDisplay[bdx][bdy].line1b & (0x80 >> bin));
					windowTileset[0][((bdx*8) + bin)][((bdy*8) + 2)] = (windowDisplay[bdx][bdy].line2a & (0x80 >> bin));
					windowTileset[1][((bdx*8) + bin)][((bdy*8) + 2)] = (windowDisplay[bdx][bdy].line2b & (0x80 >> bin));
					windowTileset[0][((bdx*8) + bin)][((bdy*8) + 3)] = (windowDisplay[bdx][bdy].line3a & (0x80 >> bin));
					windowTileset[1][((bdx*8) + bin)][((bdy*8) + 3)] = (windowDisplay[bdx][bdy].line3b & (0x80 >> bin));
					windowTileset[0][((bdx*8) + bin)][((bdy*8) + 4)] = (windowDisplay[bdx][bdy].line4a & (0x80 >> bin));
					windowTileset[1][((bdx*8) + bin)][((bdy*8) + 4)] = (windowDisplay[bdx][bdy].line4b & (0x80 >> bin));
					windowTileset[0][((bdx*8) + bin)][((bdy*8) + 5)] = (windowDisplay[bdx][bdy].line5a & (0x80 >> bin));
					windowTileset[1][((bdx*8) + bin)][((bdy*8) + 5)] = (windowDisplay[bdx][bdy].line5b & (0x80 >> bin));
					windowTileset[0][((bdx*8) + bin)][((bdy*8) + 6)] = (windowDisplay[bdx][bdy].line6a & (0x80 >> bin));
					windowTileset[1][((bdx*8) + bin)][((bdy*8) + 6)] = (windowDisplay[bdx][bdy].line6b & (0x80 >> bin));
					windowTileset[0][((bdx*8) + bin)][((bdy*8) + 7)] = (windowDisplay[bdx][bdy].line7a & (0x80 >> bin));
					windowTileset[1][((bdx*8) + bin)][((bdy*8) + 7)] = (windowDisplay[bdx][bdy].line7b & (0x80 >> bin));
				}
			}
		}
	}
	for(int obj = 0; obj < 40; obj++){
		if(lcdc.objectSize){
			for(int objy = 0; objy < 16; objy++){
				for(int bin = 0; bin < 8; bin+=2){
					if(sprites[obj].yflip){
						if(sprites[obj].xflip){
							objectPatterns[0][bin][(16 - objy)] = (vram[(((sprites[obj].tilepat) * objy))] & (0b1 << bin));
							objectPatterns[1][bin][(16 - objy)] = (vram[(((sprites[obj].tilepat) * objy)+1)] & (0b1 << (bin+1)));
						}else{
							objectPatterns[0][bin][(16 - objy)] = (vram[(((sprites[obj].tilepat) * objy))] & (0x80 >> bin));
							objectPatterns[1][bin][(16 - objy)] = (vram[(((sprites[obj].tilepat) * objy)+1)] & (0x80 >> (bin+1)));
						}
					}else{
						if(sprites[obj].xflip){
							objectPatterns[0][bin][objy] = (vram[(((sprites[obj].tilepat) * objy))] & (0b1 << bin));
							objectPatterns[1][bin][objy] = (vram[(((sprites[obj].tilepat) * objy)+1)] & (0b1 << (bin+1)));
						}else{
							objectPatterns[0][bin][objy] = (vram[(((sprites[obj].tilepat) * objy))] & (0x80 >> bin));
							objectPatterns[1][bin][objy] = (vram[(((sprites[obj].tilepat) * objy)+1)] & (0x80 >> (bin+1)));
						}
					}
				}
			}
		}else{
			for(int objy = 0; objy < 8; objy++){
				for(int bin = 0; bin < 8; bin+=2){
					if(sprites[obj].yflip){
						if(sprites[obj].xflip){
							objectPatterns[0][bin][(8 - objy)] = (vram[(((sprites[obj].tilepat) * objy))] & (0b1 << bin));
							objectPatterns[1][bin][(8 - objy)] = (vram[(((sprites[obj].tilepat) * objy)+1)] & (0b1 << (bin+1)));
						}else{
							objectPatterns[0][bin][(8 - objy)] = (vram[(((sprites[obj].tilepat) * objy))] & (0x80 >> bin));
							objectPatterns[1][bin][(8 - objy)] = (vram[(((sprites[obj].tilepat) * objy)+1)] & (0x80 >> (bin+1)));
						}
					}else{
						if(sprites[obj].xflip){
							objectPatterns[0][bin][objy] = (vram[(((sprites[obj].tilepat) * objy))] & (0b1 << bin));
							objectPatterns[1][bin][objy] = (vram[(((sprites[obj].tilepat) * objy)+1)] & (0b1 << (bin+1)));
						}else{
							objectPatterns[0][bin][objy] = (vram[(((sprites[obj].tilepat) * objy))] & (0x80 >> bin));
							objectPatterns[1][bin][objy] = (vram[(((sprites[obj].tilepat) * objy)+1)] & (0x80 >> (bin+1)));
						}
					}
					
				}
			}
		}
	}
	//Drawing to the display
	for(unsigned long scan = scx; scan < (scx + 160); scan++){
		for(int spLoop = 0; spLoop < 40; spLoop++){
			if(lcdc.objectEnable && ((sprites[spLoop].xpos + 8) == (scan % 160)) && sprites[spLoop].priority){
				for(int bin = 0; bin < 8; bin++){
					if(lcdc.objectSize){
						if(((sprites[spLoop].ypos + 16) >= ly) && ((sprites[spLoop].ypos + 16) < (ly + 16))){
							colors[0][(scan % 160)][ly] = objectPatterns[0][((sprites[spLoop].tilepat * 8) & (0x80 << bin))][(sprites[spLoop].ypos - ly)];
							colors[1][(scan % 160)][ly] = objectPatterns[1][((sprites[spLoop].tilepat * 8) & (0x80 << bin))][(sprites[spLoop].ypos - ly)];
						}
					}else{
						if(((sprites[spLoop].ypos + 16) >= ly) && ((sprites[spLoop].ypos + 16) < (ly + 8))){
							colors[0][(scan % 160)][ly] = objectPatterns[0][((sprites[spLoop].tilepat * 8) & (0x80 << bin))][(sprites[spLoop].ypos - ly)];
							colors[1][(scan % 160)][ly] = objectPatterns[1][((sprites[spLoop].tilepat * 8) & (0x80 << bin))][(sprites[spLoop].ypos - ly)];
						}
					}
				}
			}
		}
		if(lcdc.backgroundEnable){
			colors[0][(scan % 160)][ly] = backgroundTileset[0][scan][((ly + scy) % 256)];
			colors[1][(scan % 160)][ly] = backgroundTileset[1][scan][((ly + scy) % 256)];
		}
		if(lcdc.windowEnable && (((scan % 160) - 7) >= wx) && ly >= wy){
			colors[0][(scan % 160)][ly] = windowTileset[0][(scan % 160)][ly];
			colors[1][(scan % 160)][ly] = windowTileset[1][(scan % 160)][ly];
		}
		for(int spLoop = 0; spLoop < 40; spLoop++){
			if(lcdc.objectEnable && ((sprites[spLoop].xpos + 8) == (scan % 160)) && !sprites[spLoop].priority){
				for(int bin = 0; bin < 8; bin++){
					if(lcdc.objectSize){
						if(((sprites[spLoop].ypos + 16) >= ly) && ((sprites[spLoop].ypos + 16) < (ly + 16))){
							colors[0][(scan % 160)][ly] = objectPatterns[0][((sprites[spLoop].tilepat * 8) & (0x80 << bin))][(sprites[spLoop].ypos - ly)];
						}
					}else{
						if(((sprites[spLoop].ypos + 16) >= ly) && ((sprites[spLoop].ypos + 16) < (ly + 8))){
							colors[0][(scan % 160)][ly] = objectPatterns[0][((sprites[spLoop].tilepat * 8) & (0x80 << bin))][(sprites[spLoop].ypos - ly)];
						}
					}
				}
			}
		}
	}
}
#endif /* PPUINT_H */