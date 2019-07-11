/* 
 * File:   memory.h
 * Author: Justin
 * If you remove this comment, you will die instantly.
 * Created on May 29, 2019, 3:52 PM
 */
#ifndef MEMORY_H
#define MEMORY_H
void exceptionHandler(std::string exception, unsigned short value, unsigned short address){
	std::cout << "EXCEPTION " << exception << "\n";
	std::cout << "VALUE " << value << "\n";
	std::cout << "ADDRESS " << address << "\n";
	//std::cout << "OPCODE " << (((busread(pc) & 0xF0) | (busread(pc) & 0x0F))) << "\n";
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
	std::cout << std::endl;
}
unsigned char busread(unsigned short address){
	if(boot && (address <= 0x100)){
		return bootrom[address];
	}else{
		if(address <= 0x7FFF){
			return exrom[address];
		}
		if((address >= 0x8000) && (address <= 0x9FFF)){
			if((stat.mode != 3) || lcdc.displayEnable){
				return vram[(address - 0x8000)];
			}else{
				exceptionHandler("Illegal VRAM read during PPU operation!", 0, address);
				return 0;
			}
		}
		if((address >= 0xA000) && (address <= 0xBFFF)){
			return exram[(address - 0xA000)];
		}
		if((address >= 0xC000) && (address <= 0xDFFF)){
			return wram[(address - 0xC000)];
		}
		if((address >= 0xE000) && (address <= 0xFDFF)){
			return echo[(address - 0xC000)];
		}
		if((address >= 0xFE00) && (address <= 0xFE9F)){
			if((3 != stat.mode != 2) || lcdc.displayEnable){
				return oamem[(address - 0xFE00)];
			}else{
				exceptionHandler("Illegal OAM read during PPU operation!", 0, address);
				return 0;
			}
		}
		if((address >= 0xFEA0) && (address <= 0xFEFF)){
			return 0xFF;
		}
		if(address == 0xFF00){
			return joypad;
		}
		if(address == 0xFF01){
			return sb;
		}
		if(address == 0xFF02){
			return sc;
		}
		if(address == 0xFF04){
			return divider;
		}
		if(address == 0xFF05){
			return tima;
		}
		if(address == 0xFF06){
			return tma;
		}
		if(address == 0xFF07){
			return tac;
		}
		if(address == 0xFF10){
			return nr10;
		}
		if(address == 0xFF11){
			return nr11;
		}
		if(address == 0xFF12){
			return nr12;
		}
		if(address == 0xFF13){
			return nr13;
		}
		if(address == 0xFF14){
			return nr14;
		}
		if(address == 0xFF16){
			return nr21;
		}
		if(address == 0xFF17){
			return nr22;
		}
		if(address == 0xFF18){
			return nr23;
		}
		if(address == 0xFF19){
			return nr24;
		}
		if(address == 0xFF1A){
			return nr30;
		}
		if(address == 0xFF1B){
			return nr31;
		}
		if(address == 0xFF1C){
			return nr32;
		}
		if(address == 0xFF1D){
			return nr33;
		}
		if(address == 0xFF1E){
			return nr34;
		}
		if(address == 0xFF20){
			return nr41;
		}
		if(address == 0xFF21){
			return nr42;
		}
		if(address == 0xFF22){
			return nr43;
		}
		if(address == 0xFF23){
			return nr44;
		}
		if(address == 0xFF24){
			return nr50;
		}
		if(address == 0xFF25){
			return nr51;
		}
		if(address == 0xFF26){
			return nr52;
		}
		if(address == 0xFF0F){
			return inf;
		}
		if(address == 0xFF40){
			return (lcdc.displayEnable << 7) | (lcdc.windowTileMapSelect << 6) | (lcdc.windowEnable << 5) | (lcdc.tileDataSelect << 4) | (lcdc.backgroundTileMapSelect << 3) | (lcdc.objectSize << 2) | (lcdc.objectEnable << 1) | (lcdc.backgroundEnable);
		}
		if(address == 0xFF41){
			return (stat.lyInterrupt << 6) | (stat.oamInterrupt << 5) | (stat.vblankInterrupt << 4) | (stat.hblankInterrupt << 3) | (stat.coincidenceFlag << 2) | (stat.mode & 0b11);
		}
		if(address == 0xFF42){
			return scy;
		}
		if(address == 0xFF43){
			return scx;
		}
		if(address == 0xFF44){
			return ly;
		}
		if(address == 0xFF45){
			return lyc;
		}
		if(address == 0xFF46){
			return dma;
		}
		if(address == 0xFF47){
			return bgp;
		}
		if(address == 0xFF48){
			return obp0;
		}
		if(address == 0xFF49){
			return obp1;
		}
		if(address == 0xFF4A){
			return wy;
		}
		if(address == 0xFF4B){
			return wx;
		}
		if((address >= 0xFF80) && (address <= 0xFFFE)){
			return hram[(address - 0xFF80)];
		}
		if(address == 0xFFFF){
			return ie;
		}
		if((address >= 0xFF00) && (address <= 0xFF7F)){
			return io[(address - 0xFF00)];
		}
	}
	exceptionHandler("Invalid read!", 0, address);
	return 0;
}
void buswrite(unsigned short address, Uint8 value){
	if(boot && address <= 0x100){
		exceptionHandler("Invalid write to boot ROM!", value, address);
		return;
	}else{
		if(boot && address == 0xFF50){
			boot = false;
			std::cout << "Boot successful!" << std::endl;
			return;
		}
		if(address <= 0x7FFF){
			exceptionHandler("Invalid write to external ROM!", value, address);
			return;
		}
		if((address >= 0x8000) && (address <= 0x9FFF)){
			vram[(address - 0x8000)] = value;
			return;
		}
		if((address >= 0xA000) && (address <= 0xBFFF)){
			exram[(address - 0xA000)] = value;
			return;
		}
		if((address >= 0xC000) && (address <= 0xDFFF)){
			wram[(address - 0xC000)] = value;
			return;
		}
		if((address >= 0xE000) && (address <= 0xFDFF)){
			echo[(address - 0xE000)] = value;
			return;
		}
		if((address >= 0xFE00) && (address <= 0xFE9F)){
			oamem[(address - 0xFE00)] = value;
			return;
		}
		if(address == 0xFF00){
			joypad = (value & 0b00110000);
			return;
		}
		if(address == 0xFF01){
			sb = value;
			return;
		}
		if(address == 0xFF02){
			sc = (value & 0b10000001);
			return;
		}
		if(address == 0xFF04){
			divider = 0;
			return;
		}
		if(address == 0xFF05){
			tima = value;
			return;
		}
		if(address == 0xFF06){
			tma = value;
			return;
		}
		if(address == 0xFF07){
			tac = (value & 0x00000111);
			return;
		}
		if(address == 0xFF10){
			nr10 = value;
			return;
		}
		if(address == 0xFF11){
			nr11 = value;
			return;
		}
		if(address == 0xFF12){
			nr12 = value;
			return;
		}
		if(address == 0xFF13){
			nr13 = value;
			return;
		}
		if(address == 0xFF14){
			nr14 = value;
			return;
		}
		if(address == 0xFF16){
			nr21 = value;
			return;
		}
		if(address == 0xFF17){
			nr22 = value;
			return;
		}
		if(address == 0xFF18){
			nr23 = value;
			return;
		}
		if(address == 0xFF19){
			nr24 = value;
			return;
		}
		if(address == 0xFF1A){
			nr30 = value;
			return;
		}
		if(address == 0xFF1B){
			nr31 = value;
			return;
		}
		if(address == 0xFF1C){
			nr32 = value;
			return;
		}
		if(address == 0xFF1D){
			nr33 = value;
			return;
		}
		if(address == 0xFF1E){
			nr34 = value;
			return;
		}
		if(address == 0xFF20){
			nr41 = value;
			return;
		}
		if(address == 0xFF21){
			nr42 = value;
			return;
		}
		if(address == 0xFF22){
			nr43 = value;
			return;
		}
		if(address == 0xFF23){
			nr44 = value;
			return;
		}
		if(address == 0xFF24){
			nr50 = value;
			return;
		}
		if(address == 0xFF25){
			nr51 = value;
			return;
		}
		if(address == 0xFF26){
			nr52 = value;
			return;
		}
		if(address == 0xFF0F){
			inf = (value & 0x00011111);
			return;
		}
		if(address == 0xFF40){
			if((!vblank) && !(value & 0b1000000) && (lcdc.displayEnable)){
				exceptionHandler("Attempted to disable LCD outside of V-blank!", value, address);
				return;
			}else{
				lcdc.displayEnable = value & (0b1 << 7);
				lcdc.windowTileMapSelect = value & (0b1 << 6);
				lcdc.windowEnable = value & (0b1 << 5);
				lcdc.tileDataSelect = value & (0b1 << 4);
				lcdc.backgroundTileMapSelect = value & (0b1 << 3);
				lcdc.objectSize = value & (0b1 << 2);
				lcdc.objectEnable = value & (0b1 << 1);
				lcdc.backgroundEnable = value & (0b1 << 0);
				return;
			}
		}
		if(address == 0xFF41){
			stat.lyInterrupt = value & (0b1 << 6);
			stat.oamInterrupt = value & (0b1 << 5);
			stat.vblankInterrupt = value & (0b1 << 4);
			return;
		}
		if(address == 0xFF42){
			scy = value;
			return;
		}
		if(address == 0xFF43){
			scx = value;
			return;
		}
		if(address == 0xFF44){
			ly = 0;
			return;
		}
		if(address == 0xFF45){
			lyc = value;
			return;
		}
		if(address == 0xFF46){
			for(int i = 0; i <= 0x9F; i++){
				oamem[i] = busread((value << 8 ) | i);
			}
			return;
		}
		if(address == 0xFF47){
			bgp = value;
			return;
		}
		if(address == 0xFF48){
			obp0 = value;
			return;
		}
		if(address == 0xFF49){
			obp1 = value;
			return;
		}
		if(address == 0xFF4A){
			wy = value;
			return;
		}
		if(address == 0xFF4B){
			wx = value;
			return;
		}
		if((address >= 0xFF80) && (address <= 0xFFFE)){
			hram[(address - 0xFF80)] = value;
			return;
		}
		if(address == 0xFFFF){
			ie = (value & 0b00011111);
			return;
		}
		if((address >= 0xFF00) && (address <= 0xFF7F)){
			io[(address - 0xFF00)] = value;
			return;
		}
	}
	exceptionHandler("Invalid write!", value, address);
}
#endif /* MEMORY_H */