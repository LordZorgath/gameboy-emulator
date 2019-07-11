/* 
 * File:  interpreter.h
 * Author: Justin
 * If you remove this comment, you will die instantly.
 * Created on May 15, 2019, 9:37 AM
 */
#ifndef CPUINT_H
#define CPUINT_H
void ukopcode(){
	exceptionHandler("Unknown opcode!", 0, 0);
}
void opcode00(){
	//Do either jack shit or fuck all.
}
void opcode01(){
	//Load immediate word into register bc.
	ciscIsGayTimer = 11;
	reg.bc = ((busread(pc+2) << 8) | busread(pc+1));
	pc+=2;
}
void opcode02(){
	//Load A with byte from address in BC
	ciscIsGayTimer = 7;
	reg.a = busread(reg.bc);
}
void opcode03(){
	//Increase the value of BC
	reg.bc++;
}
void opcode04(){
	//Increase B
	n = false;
	h = (reg.b & 0xF) == 0xF;
	reg.b++;
	z = !(reg.b);
}
void opcode05(){
	//Decrease B
	n = true;
	h = (reg.b == 0);
	reg.b--;
	z = !(reg.b);
}
void opcode06(){
	//Load immediate byte into B
	ciscIsGayTimer = 7;
	pc++;
	reg.b = busread(pc);
}
void opcode07(){
	//Rotate accumulator left through carry
	bool ret = (reg.a & 0b10000000); 
	reg.a <<= 1;
	reg.a &= 0b11111110;
	reg.a |= ret;
	z = false;
	n = false;
	h = false;
	c = ret;
}
void opcode08(){
	//Load SP into word at immediate word
	ciscIsGayTimer = 19;
	buswrite((busread(pc+1)), ((sp & 0xFF00) >> 8));
	buswrite((busread(pc+2)), (sp & 0x00FF));
	pc+=2;
}
void opcode09(){
	//Add BC to HL
	ciscIsGayTimer = 7;
	h = (reg.hl + reg.bc > 0xF);
	c = (reg.hl + reg.bc > 0xFF);
	reg.hl += reg.bc;
	n = false;
}
void opcode0A(){
	//Load byte at address BC into A
	ciscIsGayTimer = 7;
	reg.a = busread(reg.bc);
}
void opcode0B(){
	//Decrease BC
	ciscIsGayTimer = 7;
	reg.bc--;
}
void opcode0C(){
	//Increase C
	n = false;
	h = (reg.c & 0xF) == 0xF;
	reg.c++;
	z = !(reg.c);
}
void opcode0D(){
	//Decrease C
	n = true;
	h = (reg.c == 0);
	reg.c--;
	z = !(reg.c);
}
void opcode0E(){
	//Load immediate byte into C
	ciscIsGayTimer = 7;
	pc++;
	reg.c = busread(pc);
}
void opcode0F(){
	//Rotate accumulator right through carry
	bool ret = (reg.a & 0b00000001); 
	reg.a >>= 1;
	reg.a &= 0b01111111;
	reg.a |= (ret << 7);
	z = false;
	n = false;
	h = false;
	c = ret;
}
void opcode10(){
	//do this later
}
void opcode11(){
	//Load immediate word into register de.
	ciscIsGayTimer = 11;
	reg.de = ((busread(pc+2) << 8) | (busread(pc+1)));
	pc+=2;
}
void opcode12(){
	//Load A with byte from address in DE.
	ciscIsGayTimer = 7;
	reg.a = busread(reg.de);
}
void opcode13(){
	//Increase the value of DE
	ciscIsGayTimer = 7;
	reg.de++;
}
void opcode14(){
	//Increase D
	n = false;
	h = (reg.d & 0xF) == 0xF;
	reg.d++;
	z = !(reg.d);
}
void opcode15(){
	//Decrease D
	n = true;
	h = (reg.d == 0);
	reg.d--;
	z = !(reg.d);
}
void opcode16(){
	//Load immediate byte into D
	ciscIsGayTimer = 7;
	pc++;
	reg.d = busread(pc);
}
void opcode17(){
	//Rotate accumulator left
	bool ret = (reg.a & 0b10000000); 
	reg.a <<= 1;
	reg.a &= 0b11111110;
	reg.a |= c;
	z = false;
	n = false;
	h = false;
	c = ret;
}
void opcode18(){
	//Relative jump to immediate signed byte.
	ciscIsGayTimer = 11;
	pc++;
	pc += (signed char)(busread(pc));
}
void opcode19(){
	//Add DE to HL
	ciscIsGayTimer = 7;
	h = (reg.hl + reg.de > 0xF);
	c = (reg.hl + reg.de > 0xFF);
	reg.hl += reg.de;
	n = false;
}
void opcode1A(){
	//Load byte at address DE into A
	ciscIsGayTimer = 7;
	reg.a = busread(reg.de);
}
void opcode1B(){
	//Decrease DE
	ciscIsGayTimer = 7;
	reg.de--;
}
void opcode1C(){
	//Increase E
	n = false;
	h = (reg.e & 0xF) == 0xF;
	reg.e++;
	z = !(reg.e);
}
void opcode1D(){
	//Decrease E
	n = true;
	h = (reg.e == 0);
	reg.e--;
	z = !(reg.e);
}
void opcode1E(){
	//Load immediate byte into E
	ciscIsGayTimer = 7;
	pc++;
	reg.e = busread(pc);
}
void opcode1F(){
	//Rotate accumulator right
	bool ret = (reg.a & 0b00000001); 
	reg.a >>= 1;
	reg.a |= (c << 7);
	z = false;
	n = false;
	h = false;
	c = ret;
}
void opcode20(){
	//Conditional relative jump if !Z
	ciscIsGayTimer = 7;
	if(!z){
		ciscIsGayTimer = 11;
		pc += (signed char)((busread(pc+1)));
		pc++;
	}else{
		pc++;
	}
}
void opcode21(){
	//Load immediate word into register hl.
	ciscIsGayTimer = 11;
	reg.hl = ((busread(pc+2) << 8) | busread(pc+1));
	pc+=2;
}
void opcode22(){
	//Add 1 to HL, load A into byte at address HL
	ciscIsGayTimer = 7;
	reg.hl++;
	buswrite(reg.hl, reg.a);
}
void opcode23(){
	//Increase the value of HL
	ciscIsGayTimer = 7;
	reg.hl++;
}
void opcode24(){
	//Increase H
	n = false;
	h = (reg.h & 0xF) == 0xF;
	reg.h++;
	z = !(reg.h);
}
void opcode25(){
	//Decrease H
	n = true;
	h = (reg.h == 0);
	reg.h--;
	z = !(reg.h);
}
void opcode26(){
	//Load immediate byte into H
	ciscIsGayTimer = 7;
	pc++;
	reg.h = busread(pc);
}
void opcode27(){
	//Do some BCD fuckery idk
	if((reg.a & 0x0F) > 0x0A){
		reg.a += ((reg.a & 0x0F) - 0x0A);
	}
	if((reg.a & 0xF0) > 0xA0){
		reg.a += ((reg.a & 0xF0) - 0xA0);
	}
}
void opcode28(){
	//Conditional relative jump if Z
	ciscIsGayTimer = 7;
	if(z){
		ciscIsGayTimer = 11;
		pc += (signed char)((busread(pc+1)));
		pc++;
	}else{
		pc++;
	}
}
void opcode29(){
	//Add HL to... HL?
	ciscIsGayTimer = 7;
	h = (reg.hl + reg.hl > 0xF);
	c = (reg.hl + reg.hl > 0xFF);
	reg.hl += reg.hl;
	n = false;
}
void opcode2A(){
	//Add 1 to HL, load byte at address HL into A
	ciscIsGayTimer = 7;
	reg.hl++;
	reg.a = busread(reg.hl);
}
void opcode2B(){
	//Decrease HL
	ciscIsGayTimer = 7;
	reg.hl--;
}
void opcode2C(){
	//Increase L
	n = false;
	h = (reg.l & 0xF) == 0xF;
	reg.l++;
	z = !(reg.l);
}
void opcode2D(){
	//Decrease L
	n = true;
	h = (reg.l == 0);
	reg.l--;
	z = !(reg.l);
}
void opcode2E(){
	//Load immediate byte into L
	ciscIsGayTimer = 7;
	pc++;
	reg.l = busread(pc);
}
void opcode2F(){
	//A xor FF I guess.
	reg.a ^= 0xFF;
	n = 1;
	h = 1;
}
void opcode30(){
	//Conditional relative jump if !C
	ciscIsGayTimer = 7;
	if(!c){
		ciscIsGayTimer = 11;
		pc += (signed char)((busread(pc+1)));
		pc++;
	}else{
		pc++;
	}
}
void opcode31(){
	//Load immediate word into register sp
	ciscIsGayTimer = 11;
	sp = ((busread(pc+2) << 8) | busread(pc+1));
	pc+=2;
}
void opcode32(){
	//Subtract 1 from HL, load A into byte at address HL
	ciscIsGayTimer = 7;
	reg.hl--;
	buswrite(reg.hl, reg.a);
}
void opcode33(){
	//Increase the value of SP
	ciscIsGayTimer = 7;
	sp++;
}
void opcode34(){
	//Increase byte at address HL
	ciscIsGayTimer = 11;
	n = false;
	h = (busread(reg.hl) & 0xF) == 0xF;
	buswrite(reg.hl, (busread(reg.hl) + 1));
	z = !(busread(reg.hl));
}
void opcode35(){
	//Decrease byte at address HL
	ciscIsGayTimer = 11;
	n = true;
	h = (busread(reg.hl) == 0xF);
	buswrite(reg.hl, (busread(reg.hl) - 1));
	z = !(busread(reg.hl));
}
void opcode36(){
	//Load immediate byte into byte at address HL
	ciscIsGayTimer = 11;
	pc++;
	buswrite(reg.hl, busread(pc));
}
void opcode37(){
	//C = 1
	c = 1;
	n = false;
	h = false;
}
void opcode38(){
	//Conditional relative jump if C
	ciscIsGayTimer = 7;
	if(c){
		ciscIsGayTimer = 11;
		pc += (signed char)((busread(pc+1)));
		pc++;
	}else{
		pc++;
	}
}
void opcode39(){
	//Add SP to HL
	ciscIsGayTimer = 7;
	n = false;
	h = (reg.hl + reg.bc > 0xF);
	c = (reg.hl + reg.bc > 0xFF);
	reg.hl += sp;
}
void opcode3A(){
	//Subtract 1 from HL, load byte at address HL into A
	ciscIsGayTimer = 7;
	reg.a = busread(reg.hl--);
}
void opcode3B(){
	//Decrease SP
	ciscIsGayTimer = 7;
	sp--;
}
void opcode3C(){
	//Increase A
	n = false;
	h = (reg.a & 0xF) == 0xF;
	reg.a++;
	z = !(reg.a);
}
void opcode3D(){
	//Decrease A
	n = true;
	h = (reg.a == 0);
	reg.a--;
	z = !(reg.a);
}
void opcode3E(){
	//Load immediate byte into A
	ciscIsGayTimer = 7;
	pc++;
	reg.a = busread(pc);
}
void opcode3F(){
	//C xor 1
	c ^= 1;
	n = 0;
	h = 0;
}
void opcode40(){
	//Load B into... B?
}
void opcode41(){
	//Load C into B
	reg.b = reg.c;
}
void opcode42(){
	//Load D into B
	reg.b = reg.d;
}
void opcode43(){
	//Load E into B
	reg.b = reg.e;
}
void opcode44(){
	//Load H into B
	reg.b = reg.h;
}
void opcode45(){
	//Load L into B
	reg.b = reg.l;
}
void opcode46(){
	//Load byte at address HL into B
	ciscIsGayTimer = 7;
	reg.b = busread(reg.hl);
}
void opcode47(){
	//Load A into B
	reg.b = reg.a;
}
void opcode48(){
	//Load B into C
	reg.c = reg.b;
}
void opcode49(){
	//Load C into... C?
}
void opcode4A(){
	//Load D into C
	reg.c = reg.d;
}
void opcode4B(){
	//Load E into C
	reg.c = reg.e;
}
void opcode4C(){
	//Load H into C
	reg.c = reg.h;
}
void opcode4D(){
	//Load L into C
	reg.c = reg.l;
}
void opcode4E(){
	//Load byte at address HL into C
	ciscIsGayTimer = 7;
	reg.c = busread(reg.hl);
}
void opcode4F(){
	//Load A into C
	reg.c = reg.a;
}
void opcode50(){
	//Load B into D
	reg.d = reg.b;
}
void opcode51(){
	//Load C into D
	reg.d = reg.c;
}
void opcode52(){
	//Load D into... D?
}
void opcode53(){
	//Load E into D
	reg.d = reg.e;
}
void opcode54(){
	//Load H into D
	reg.d = reg.h;
}
void opcode55(){
	//Load L into D
	reg.d = reg.l;
}
void opcode56(){
	//Load byte at address HL into D
	ciscIsGayTimer = 7;
	reg.d = busread(reg.hl);
}
void opcode57(){
	//Load A into D
	reg.d = reg.a;
}
void opcode58(){
	//Load B into E
	reg.e = reg.b;
}
void opcode59(){
	//Load C into E
	reg.e = reg.c;
}
void opcode5A(){
	//Load D into E
	reg.e = reg.d;
}
void opcode5B(){
	//Load E into... E?
}
void opcode5C(){
	//Load H into E
	reg.e = reg.h;
}
void opcode5D(){
	//Load L into E
	reg.e = reg.l;
}
void opcode5E(){
	//Load byte at address HL into E
	ciscIsGayTimer = 7;
	reg.e = busread(reg.hl);
}
void opcode5F(){
	//Load accumulator into E
	reg.e = reg.a;
}
void opcode60(){
	//Load B into H
	reg.h = reg.b;
}
void opcode61(){
	//Load C into H
	reg.h = reg.c;
}
void opcode62(){
	//Load D into H
	reg.h = reg.d;
}
void opcode63(){
	//Load E into H
	reg.h = reg.e;
}
void opcode64(){
	//Load H into... H?
}
void opcode65(){
	//Load L into H
	reg.h = reg.l;
}
void opcode66(){
	//Load byte at address HL into H
	ciscIsGayTimer = 7;
	reg.h = busread(reg.hl);
}
void opcode67(){
	//Load accumulator into H
	reg.h = reg.a;
}
void opcode68(){
	//Load B into L
	reg.l = reg.b;
}
void opcode69(){
	//Load C into L
	reg.l = reg.c;
}
void opcode6A(){
	//Load D into L
	reg.l = reg.d;
}
void opcode6B(){
	//Load E into L
	reg.l = reg.e;
}
void opcode6C(){
	//Load H into L
	reg.l = reg.h;
}
void opcode6D(){
	//Load L into... L?
}
void opcode6E(){
	//Load byte at address HL into L
	ciscIsGayTimer = 7;
	reg.l = busread(reg.hl);
}
void opcode6F(){
	//Load accumulator into L
	reg.l = reg.a;
}
void opcode70(){
	//Load B into address at HL
	ciscIsGayTimer = 7;
	buswrite(reg.hl, reg.b);
}
void opcode71(){
	//Load C into address at HL
	ciscIsGayTimer = 7;
	buswrite(reg.hl, reg.c);
}
void opcode72(){
	//Load D into address at HL
	ciscIsGayTimer = 7;
	buswrite(reg.hl, reg.d);
}
void opcode73(){
	//Load E into address at HL
	ciscIsGayTimer = 7;
	buswrite(reg.hl, reg.e);
}
void opcode74(){
	//Load H into address at HL
	ciscIsGayTimer = 7;
	buswrite(reg.hl, reg.h);
}
void opcode75(){
	//Load L into address at HL
	ciscIsGayTimer = 7;
	buswrite(reg.hl, reg.l);
}
void opcode76(){
	//Do this later
	pc-=1;
}
void opcode77(){
	//Load A into address at HL
	ciscIsGayTimer = 7;
	buswrite(reg.hl, reg.a);
}
void opcode78(){
	//Load B into A
	reg.a = reg.b;
}
void opcode79(){
	//Load C into A
	reg.a = reg.c;
}
void opcode7A(){
	//Load D into A
	reg.a = reg.d;
}
void opcode7B(){
	//Load E into A
	reg.a = reg.e;
}
void opcode7C(){
	//Load H into A
	reg.a = reg.h;
}
void opcode7D(){
	//Load L into A
	reg.a = reg.l;
}
void opcode7E(){
	//Load byte at address HL into A
	ciscIsGayTimer = 7;
	reg.a = busread(reg.hl);
}
void opcode7F(){
	//Load A into... A?
}
void opcode80(){
	//Add B to A
	n = false;
	h = (reg.a + reg.b > 0xF);
	c = (reg.a + reg.b > 0xFF);
	reg.a += reg.b;
	z = !(reg.a);
}
void opcode81(){
	//Add C to A
	n = false;
	h = (reg.a + reg.c > 0xF);
	c = (reg.a + reg.c > 0xFF);
	reg.a += reg.c;
	z = !(reg.a);
}
void opcode82(){
	//Add D to A
	n = false;
	h = (reg.a + reg.d > 0xF);
	c = (reg.a + reg.d > 0xFF);
	reg.a += reg.d;
	z = !(reg.a);
}
void opcode83(){
	//Add E to A
	n = false;
	h = (reg.a + reg.e > 0xF);
	c = (reg.a + reg.e > 0xFF);
	reg.a += reg.e;
	z = !(reg.a);
}
void opcode84(){
	//Add H to A
	n = false;
	h = (reg.a + reg.h > 0xF);
	c = (reg.a + reg.h > 0xFF);
	reg.a += reg.h;
	z = !(reg.a);
}
void opcode85(){
	//Add L to A
	n = false;
	h = (reg.a + reg.l > 0xF);
	c = (reg.a + reg.l > 0xFF);
	reg.a += reg.l;
	z = !(reg.a);
}
void opcode86(){
	//Add byte at address HL to A
	ciscIsGayTimer = 7;
	n = false;
	h = (reg.a + busread(reg.hl) > 0xF);
	c = (reg.a + busread(reg.hl) > 0xFF);
	reg.a += busread(reg.hl);
	z = !(reg.a);
}
void opcode87(){
	//Add A to A
	n = false;
	h = (reg.a + reg.a > 0xF);
	c = (reg.a + reg.a > 0xFF);
	reg.a += reg.a;
	z = !(reg.a);
}
void opcode88(){
	//Add B to A and add the carry flag
	n = false;
	h = (reg.a + reg.b + c > 0xF);
	c = (reg.a + reg.b + c > 0xFF);
	reg.a += (reg.b + c);
	z = !(reg.a);
}
void opcode89(){
	//Add C to A and add the carry flag.
	n = false;
	h = (reg.a + reg.c + c > 0xF);
	c = (reg.a + reg.c + c > 0xFF);
	reg.a += (reg.c + c);
	z = !(reg.a);
}
void opcode8A(){
	//Add D to A and add the carry flag
	n = false;
	h = (reg.a + reg.d + c > 0xF);
	c = (reg.a + reg.d + c > 0xFF);
	reg.a += (reg.d + c);
	z = !(reg.a);
}
void opcode8B(){
	//Add E to A and add the carry flag.
	n = false;
	h = (reg.a + reg.e + c > 0xF);
	c = (reg.a + reg.e + c > 0xFF);
	reg.a += (reg.e + c);
	z = !(reg.a);
}
void opcode8C(){
	//Add H to A and add the carry flag
	n = false;
	h = (reg.a + reg.h + c > 0xF);
	c = (reg.a + reg.h + c > 0xFF);
	reg.a += (reg.h + c);
	z = !(reg.a);
}
void opcode8D(){
	//Add L to A and add the carry flag.
	n = false;
	h = (reg.a + reg.l + c > 0xF);
	c = (reg.a + reg.l + c > 0xFF);
	reg.a += (reg.l + c);
	z = !(reg.a);
}
void opcode8E(){
	//Add byte at HL to A and add the carry flag.
	ciscIsGayTimer = 7;
	n = false;
	h = (reg.a + (busread(reg.hl)) + c > 0xF);
	c = (reg.a + (busread(reg.hl)) + c > 0xFF);
	reg.a += ((busread(reg.hl)) + c);
	z = !(reg.a);
}
void opcode8F(){
	//Add A to A and add the carry flag.
	n = false;
	h = (reg.a + reg.a + c > 0xF);
	c = (reg.a + reg.a + c > 0xFF);
	reg.a += (reg.a + c);
	z = !(reg.a);
}
void opcode90(){
	//Subtract B from A
	n = true;
	h = (reg.a - reg.b < 0x0);
	c = (reg.a - reg.b < 0x00);
	reg.a -= reg.b;
	z = !(reg.a);
}
void opcode91(){
	//Subtract C from A
	n = true;
	h = (reg.a - reg.c < 0x0);
	c = (reg.a - reg.c < 0x00);
	reg.a -= reg.c;
	z = !(reg.a);
}
void opcode92(){
	//Subtract D from A
	n = true;
	h = (reg.a - reg.d < 0x0);
	c = (reg.a - reg.d < 0x00);
	reg.a -= reg.d;
	z = !(reg.a);
}
void opcode93(){
	//Subtract E from A
	n = true;
	h = (reg.a - reg.e < 0x0);
	c = (reg.a - reg.e < 0x00);
	reg.a -= reg.e;
	z = !(reg.a);
}
void opcode94(){
	//Subtract H from A
	n = true;
	h = (reg.a - reg.h < 0x0);
	c = (reg.a - reg.h < 0x00);
	reg.a -= reg.h;
	z = !(reg.a);
}
void opcode95(){
	//Subtract L from A
	n = true;
	h = (reg.a - reg.l < 0x0);
	c = (reg.a - reg.l < 0x00);
	reg.a -= reg.l;
	z = !(reg.a);
}
void opcode96(){
	//Subtract byte at address HL from A
	ciscIsGayTimer = 7;
	n = true;
	h = (reg.a - busread(reg.hl) < 0x0);
	c = (reg.a - busread(reg.hl) < 0x00);
	reg.a -= busread(reg.hl);
	z = !(reg.a);
}
void opcode97(){
	//Subtract A from A
	n = true;
	h = (reg.a - reg.a < 0x0);
	c = (reg.a - reg.a < 0x00);
	reg.a -= reg.a;
	z = !(reg.a);
}
void opcode98(){
	//Subtract B from A and subtract the carry flag
	n = true;
	h = (reg.a - (reg.b - c) < 0x0);
	c = (reg.a - (reg.b - c) < 0x00);
	reg.a -= (reg.b - c);
	z = !(reg.a);
}
void opcode99(){
	//Subtract C from A and subtract the carry flag.
	n = true;
	h = (reg.a - (reg.c - c) < 0x0);
	c = (reg.a - (reg.c - c) < 0x00);
	reg.a -= (reg.c - c);
	z = !(reg.a);
}
void opcode9A(){
	//Subtract D from A and subtract the carry flag
	n = true;
	h = (reg.a - (reg.d - c) < 0x0);
	c = (reg.a - (reg.d - c) < 0x00);
	reg.a -= (reg.d - c);
	z = !(reg.a);
}
void opcode9B(){
	//Subtract E from A and subtract the carry flag.
	n = true;
	h = (reg.a - (reg.e - c) < 0x0);
	c = (reg.a - (reg.e - c) < 0x00);
	reg.a -= (reg.e - c);
	z = !(reg.a);
}
void opcode9C(){
	//Subtract H from A and subtract the carry flag
	n = true;
	h = (reg.a - (reg.h - c) < 0x0);
	c = (reg.a - (reg.h - c) < 0x00);
	reg.a -= (reg.h - c);
	z = !(reg.a);
}
void opcode9D(){
	//Subtract L from A and subtract the carry flag.
	n = true;
	h = (reg.a - (reg.l - c) < 0x0);
	c = (reg.a - (reg.l - c) < 0x00);
	reg.a -= (reg.l - c);
	z = !(reg.a);
}
void opcode9E(){
	//Subtract byte at HL from A and subtract the carry flag.
	ciscIsGayTimer = 7;
	n = true;
	h = (reg.a - (busread(reg.hl) - c) < 0x0);
	c = (reg.a - (busread(reg.hl) - c) < 0x00);
	reg.a -= (busread(reg.hl) - c);
	z = !(reg.a);
}
void opcode9F(){
	//Subtract A from A and subtract the carry flag.
	n = true;
	h = (reg.a - (reg.a - c) < 0x0);
	c = (reg.a - (reg.a - c) < 0x00);
	reg.a -= (reg.a - c);
	z = !(reg.a);
}
void opcodeA0(){
	//Bitwise AND A and B
	reg.a &= reg.b;
	z = !(reg.a);
	n = false;
	h = true;
	c = false;
}
void opcodeA1(){
	//Bitwise AND A and C 
	reg.a &= reg.c;
	z = !(reg.a);
	n = false;
	h = true;
	c = false;
}
void opcodeA2(){
	//Bitwise AND A and D
	reg.a &= reg.d;
	z = !(reg.a);
	n = false;
	h = true;
	c = false;
}
void opcodeA3(){
	//Bitwise AND A and E
	reg.a &= reg.e;
	z = !(reg.a);
	n = false;
	h = true;
	c = false;
}
void opcodeA4(){
	//Bitwise AND A and H
	reg.a &= reg.h;
	z = !(reg.a);
	n = false;
	h = true;
	c = false;
}
void opcodeA5(){
	//Bitwise AND A and L
	reg.a &= reg.l;
	z = !(reg.a);
	n = false;
	h = true;
	c = false;
}
void opcodeA6(){
	ciscIsGayTimer = 7;
	//Bitwise AND A and byte at address HL
	reg.a &= busread(reg.hl);
	z = !(reg.a);
	n = false;
	h = true;
	c = false;
}
void opcodeA7(){
	//Bitwise AND A and... A?
	reg.a &= reg.a;
	z = !(reg.a);
	n = false;
	h = true;
	c = false;
}
void opcodeA8(){
	//Bitwise XOR A and B
	reg.a ^= reg.b;
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeA9(){
	//Bitwise XOR A and C
	reg.a ^= reg.c;
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeAA(){
	//Bitwise XOR A and D
	reg.a ^= reg.d;
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeAB(){
	//Bitwise XOR A and E
	reg.a ^= reg.e;
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeAC(){
	//Bitwise XOR A and H
	reg.a ^= reg.e;
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeAD(){
	//Bitwise XOR A and L
	reg.a ^= reg.l;
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeAE(){
	//Bitwise XOR A and byte at address HL
	ciscIsGayTimer = 7;
	reg.a ^= busread(reg.hl);
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeAF(){
	//Bitwise XOR A and A
	reg.a ^= reg.a;
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeB0(){
	//Bitwise OR A and B
	reg.a |= reg.b;
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeB1(){
	//Bitwise OR A and C 
	reg.a |= reg.c;
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeB2(){
	//Bitwise OR A and D
	reg.a |= reg.d;
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeB3(){
	//Bitwise OR A and E
	reg.a |= reg.e;
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeB4(){
	//Bitwise OR A and H
	reg.a |= reg.h;
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeB5(){
	//Bitwise OR A and L
	reg.a |= reg.l;
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeB6(){
	ciscIsGayTimer = 7;
	//Bitwise OR A and byte at address HL
	reg.a |= busread(reg.hl);
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeB7(){
	//Bitwise OR A and... A?
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeB8(){
	//Compare B and A
	z = (reg.a == reg.b);
	n = true;
	h = ((reg.a - reg.b) & 0xF) < 0;
	c = (reg.a - reg.b) < 0;
}
void opcodeB9(){
	//Compare C and A
	z = (reg.a == reg.c);
	n = true;
	h = ((reg.a - reg.c) & 0xF) < 0;
	c = (reg.a - reg.c) < 0;
}
void opcodeBA(){
	//Compare D and A
	z = (reg.a == reg.d);
	n = true;
	h = ((reg.a - reg.d) & 0xF) < 0;
	c = (reg.a - reg.d) < 0;
}
void opcodeBB(){
	//Compare E and A
	z = (reg.a == reg.e);
	n = true;
	h = ((reg.a - reg.e) & 0xF) < 0;
	c = (reg.a - reg.e) < 0;
}
void opcodeBC(){
	//Compare H and A
	z = (reg.a == reg.h);
	n = true;
	h = ((reg.a - reg.h) & 0xF) < 0;
	c = (reg.a - reg.h) < 0;
}
void opcodeBD(){
	//Compare L and A
	z = (reg.a == reg.l);
	n = true;
	h = ((reg.a - reg.l) & 0xF) < 0;
	c = (reg.a - reg.l) < 0;
}
void opcodeBE(){
	//Compare byte at address HL and A
	ciscIsGayTimer = 7;
	z = (reg.a == busread(reg.hl));
	n = true;
	h = ((reg.a - busread(reg.hl)) & 0xF) < 0;
	c = (reg.a - busread(reg.hl)) < 0;
}
void opcodeBF(){
	//Compare A and A
	z = true;
	n = true;
	h = false;
	c = false;
}
void opcodeC0(){
	//Conditional return if !Z
	ciscIsGayTimer = 7;
	if(!z){
		ciscIsGayTimer = 19;
		pc = ((busread(sp) << 8) | busread(sp-1));
		sp+=2;
		pc--;
	}
}
void opcodeC1(){
	//Pop two bytes from the stack into register BC, increment SP twice
	ciscIsGayTimer = 11;
	reg.bc = ((busread(sp+1) << 8) | busread(sp));
	sp+=2;
}
void opcodeC2(){
	//Conditional jump to immediate address if !Z
	ciscIsGayTimer = 11;
	if(!z){
		ciscIsGayTimer = 15;
		pc = ((busread(pc+2) << 8) | busread(pc+1));
		pc--;
	}else{
		pc+=2;
	}
}
void opcodeC3(){
	//Jump to immediate address
	ciscIsGayTimer = 15;
	pc = ((busread(pc+2) << 8) | busread(pc+1));
	pc--;
}
void opcodeC4(){
	//Conditional call to immediate address if !Z
	ciscIsGayTimer = 11;
	if(!z){
		ciscIsGayTimer = 23;
		sp-=2;
		pc+=3;
		buswrite(sp, ((pc & 0xFF00) >> 8));
		buswrite((sp+1), (pc & 0x00FF));
		pc = busread(pc-1) << 8 | busread(pc-2);
		pc--;
	}else{
		pc+=2;
	}
}
void opcodeC5(){
	//Push BC into the stack
	ciscIsGayTimer = 15;
	sp-=2;
	buswrite((sp+1), (reg.b));
	buswrite(sp, (reg.c));
}
void opcodeC6(){
	//Add A to immediate byte
	ciscIsGayTimer = 7;
	c = ((reg.a += busread(pc+1)) > 0xFF);
	z = !(reg.a);
	n = false;
	h = (reg.a > 0x000F);
}
void opcodeC7(){
	//Call to 0x00
	ciscIsGayTimer = 15;
	sp-=2;
	pc++;
	buswrite(sp, ((pc & 0xFF00) >> 8));
	buswrite((sp+1), (pc & 0x00FF));
	pc = 0x00;
	pc--;
}
void opcodeC8(){
	//Conditional return if Z
	ciscIsGayTimer = 7;
	if(z){
		ciscIsGayTimer = 20;
		pc = ((busread(sp) << 8) | busread(sp+1));
		sp+=2;
		pc--;
	}
}
void opcodeC9(){
	//Return from a subroutine
	ciscIsGayTimer = 15;
	pc = ((busread(sp) << 8) | busread(sp+1));
	sp+=2;
	pc--;
}
void opcodeCA(){
	//Conditional jump to immediate address if Z
	ciscIsGayTimer = 11;
	if(z){
		ciscIsGayTimer = 15;
		pc = ((busread(pc+2) << 8) | busread(pc+1));
		pc--;
	}else{
		pc+=2;
	}
}
void opcodeCB(){
	//Put the CPU in CB mode
	cb = true;
}
void opcodeCC(){
	//Condtional call to immediate address if Z
	ciscIsGayTimer = 11;
	if(z){
		ciscIsGayTimer = 23;
		sp-=2;
		pc+=3;
		buswrite(sp, ((pc & 0xFF00) >> 8));
		buswrite((sp+1), (pc & 0x00FF));
		pc = busread(pc-1) << 8 | busread(pc-2);
		pc--;
	}
}
void opcodeCD(){
	//Call to immediate address
	ciscIsGayTimer = 23;
	sp-=2;
	pc+=3;
	buswrite(sp, ((pc & 0xFF00) >> 8));
	buswrite((sp+1), (pc & 0x00FF));
	pc = busread(pc-1) << 8 | busread(pc-2);
	pc--;
}
void opcodeCE(){
	//Add immediate byte and flag C to A
	ciscIsGayTimer = 7;
	c = false;
	if((reg.a += (busread(pc+1) + c)) > 0xFF){
		c = true;
	}
	z = !(reg.a);
	h = (reg.a > 0x000F);
	n = false;
}
void opcodeCF(){
	//Call to 0x08
	ciscIsGayTimer = 15;
	sp-=2;
	pc++;
	buswrite(sp, ((pc & 0xFF00) >> 8));
	buswrite((sp+1), (pc & 0x00FF));
	pc = 0x08;
	pc--;
}
void opcodeD0(){
	//Conditional return if !C
	ciscIsGayTimer = 7;
	if(!c){
		ciscIsGayTimer = 19;
		pc = ((busread(sp) << 8) | busread(sp+1));
		sp+=2;
		pc--;
	}
}
void opcodeD1(){
	//Pop two bytes from the stack into register DE, increment SP twice
	ciscIsGayTimer = 11;
	reg.de = ((busread(sp) << 8) | busread(sp-1));
	sp+=2;
}
void opcodeD2(){
	//Conditional jump to immediate address if !C
	ciscIsGayTimer = 11;
	if(!c){
		ciscIsGayTimer = 15;
		pc = ((busread(pc+2) << 8) | busread(pc+1));
		pc--;
	}else{
		pc+=2;
	}
}
void opcodeD4(){
	//Conditional call to immediate address if !C
	ciscIsGayTimer = 11;
	if(!c){
		ciscIsGayTimer = 23;
		sp-=2;
		pc+=3;
		buswrite(sp, ((pc & 0xFF00) >> 8));
		buswrite((sp+1), (pc & 0x00FF));
		pc = busread(pc-1) << 8 | busread(pc-2);
		pc--;
	}else{
		pc+=2;
	}
}
void opcodeD5(){
	//Push DE into the stack
	ciscIsGayTimer = 15;
	sp-=2;
	buswrite((sp+1), reg.d);
	buswrite(sp, reg.e);
}
void opcodeD6(){
	//Subtract immediate byte from A
	ciscIsGayTimer = 7;
	c = false;
	if((reg.a -= busread(pc+1)) > 0xFF){
		c = true;
	}
	z = !(reg.a);
	h = (reg.a > 0x000F);
	n = true;
}
void opcodeD7(){
	//Call to 0x10
	ciscIsGayTimer = 15;
	sp-=2;
	pc++;
	buswrite(sp, ((pc & 0xFF00) >> 8));
	buswrite((sp+1), (pc & 0x00FF));
	pc = 0x10;
	pc--;
}
void opcodeD8(){
	//Conditional return if C
	ciscIsGayTimer = 7;
	if(c){
		ciscIsGayTimer = 19;
		pc = ((busread(sp) << 8) | busread(sp+1));
		sp+=2;
		pc--;
	}
}
void opcodeD9(){
	//Return and enable interrupts
	ciscIsGayTimer = 15;
	pc = ((busread(sp) << 8) | busread(sp+1));
	pc--;
	sp+=2;
	ime = true;
}
void opcodeDA(){
	//Conditional jump to immediate address if C
	ciscIsGayTimer = 11;
	if(c){
		ciscIsGayTimer = 15;
		pc = ((busread(pc+2) << 8) | busread(pc+1));
		pc--;
	}else{
		pc+=2;
	}
}
void opcodeDC(){
	//Conditional call to immediate address if C
	ciscIsGayTimer = 11;
	if(c){
		ciscIsGayTimer = 23;
		sp-=2;
		pc+=3;
		buswrite(sp, ((pc & 0xFF00) >> 8));
		buswrite((sp+1), (pc & 0x00FF));
		pc = busread(pc-1) << 8 | busread(pc-2);
		pc--;
	}else{
		pc+=2;
	}
}
void opcodeDE(){
	//Subtract flag C and immediate byte from A
	ciscIsGayTimer = 7;
	c = false;
	if((reg.a -= (busread(pc+1) - c)) > 0xFF){
		c = true;
	}
	z = !(reg.a);
	h = (reg.a > 0x000F);
	n = true;
}
void opcodeDF(){
	//Call to 0x18
	ciscIsGayTimer = 15;
	sp-=2;
	pc++;
	buswrite(sp, ((pc & 0xFF00) >> 8));
	buswrite((sp+1), (pc & 0x00FF));
	pc = 0x18;
	pc--;
}
void opcodeE0(){
	//Load A into 0xFF00 + immediate addres
	ciscIsGayTimer = 11;
	pc++;
	buswrite((0xFF00 | busread(pc)), reg.a);
}
void opcodeE1(){
	//Pop two bytes from the stack into register HL, increment SP twice
	ciscIsGayTimer = 11;
	reg.hl = ((busread(sp) << 8) | busread(sp-1));
	sp+=2;
}
void opcodeE2(){
	//Load A into 0xFF00 + C
	ciscIsGayTimer = 7;
	buswrite((0xFF00 + reg.c), reg.a);
}
void opcodeE5(){
	//Push HL into the stack
	ciscIsGayTimer = 15;
	sp-=2;
	buswrite((sp+1), reg.h);
	buswrite(sp, reg.l);
}
void opcodeE6(){
	//Bitwise AND A with immediate byte
	ciscIsGayTimer = 7;
	c = false;
	if((reg.a &= busread(pc+1)) > 0xFF){
		c = true;
	}
	z = !(reg.a);
	n = false;
	h = true;
	c = false;
}
void opcodeE7(){
	//Call to 0x20
	ciscIsGayTimer = 15;
	sp-=2;
	pc++;
	buswrite(sp, ((pc & 0xFF00) >> 8));
	buswrite((sp+1), (pc & 0x00FF));
	pc = 0x20;
	pc--;
}
void opcodeE8(){	
	//Add immediate signed byte to SP
	ciscIsGayTimer = 15;
	c = false;
	if(sp + (signed char)busread(pc+1) > 0xFF){
		c = true;
	}
	sp += (signed char)busread(pc+1);
	z = false;
	n = false;
	h = (sp > 0x000F);
}
void opcodeE9(){
	//Jump to HL
	pc = reg.hl;
	pc--;
}
void opcodeEA(){
	//Load A into immediate address
	ciscIsGayTimer = 15;
	buswrite(((busread(pc+2) << 8) | busread(pc+1)), reg.a);
	pc+=2;
}
void opcodeEE(){
	//XOR A with immediate byte
	ciscIsGayTimer = 7;
	pc++;
	reg.a ^= busread(pc);
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeEF(){
	//Call to 0x28
	ciscIsGayTimer = 15;
	sp-=2;
	pc++;
	buswrite(sp, ((pc & 0xFF00) >> 8));
	buswrite((sp+1), (pc & 0x00FF));
	pc = 0x28;
	pc--;
}
void opcodeF0(){
	//Load 0xFF00 + immediate address into A
	ciscIsGayTimer = 11;
	pc++;
	reg.a = busread((0xFF00 + busread(pc)));
}
void opcodeF1(){
	//Pop two bytes from the stack into register AF, increment SP twice
	reg.a = (busread(sp) << 8);
	z = (busread(sp-1) & 0b0000000010000000);
	n = (busread(sp-1) & 0b0000000001000000);
	h = (busread(sp-1) & 0b0000000000100000);
	c = (busread(sp-1) & 0b0000000000010000);
	sp+=2;
}
void opcodeF2(){
	//Load 0xFF00 + C into A
	ciscIsGayTimer = 7;
	reg.a = busread((0xFF00 + reg.c));
}
void opcodeF3(){
	//Disable interrupts
	ime = false;
}
void opcodeF5(){
	//Push AF into the stack
	ciscIsGayTimer = 15;
	sp-=2;
	buswrite((sp+1), reg.a);
	buswrite(sp, ((z << 7) | (n << 6) | (h << 5) | (c << 4)));
}
void opcodeF6(){
	//Bitwise OR A with immediate byte
	ciscIsGayTimer = 7;
	c = ((reg.a |= busread(pc+1)) > 0x00FF);
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void opcodeF7(){
	//Call to 0x30
	ciscIsGayTimer = 15;
	sp-=2;
	pc++;
	buswrite(sp, ((pc & 0xFF00) >> 8));
	buswrite((sp+1), (pc & 0x00FF));
	pc = 0x30;
	pc--;
}
void opcodeF8(){
	//Load immediate word into high byte, SP into low byte of HL
	ciscIsGayTimer = 11;
	reg.hl = (sp + (signed char)busread(pc+1));
	z = false;
	n = false;
	h = (reg.hl & 0xF) == 0xF;
	c = (reg.hl > 0x00FF);
}
void opcodeF9(){
	//Load HL into SP
	ciscIsGayTimer = 8;
	sp = reg.hl;
}
void opcodeFA(){
	//Load byte at immediate address into A
	ciscIsGayTimer = 15;
	reg.a = busread(((busread(pc+2) << 8) | busread(pc+1)));
	pc+=2;
}
void opcodeFB(){
	//Enable interrupts
	ime = true;
}
void opcodeFE(){
	//Compare A and immediate byte
	ciscIsGayTimer = 7;
	pc++;
	z = (reg.a == busread(pc));
	n = true;
	h = ((reg.a - busread(pc)) & 0xF) < 0;
	c = (reg.a - busread(pc)) < 0;
}
void opcodeFF(){
	//Call to 0x38
	ciscIsGayTimer = 15;
	sp-=2;
	pc++;
	buswrite(sp, ((pc & 0xFF00) >> 8));
	buswrite((sp+1), (pc & 0x00FF));
	pc = 0x38;
	pc--;
}
void cbcode00(){
	//Rotate B left
	bool ret = (reg.b & 0b10000000); 
	reg.b <<= 1;
	reg.b &= 0b11111110;
	reg.b |= ret;
	z = !(reg.b);
	n = false;
	h = false;
	c = ret;
}
void cbcode01(){
	//Rotate C left
	bool ret = (reg.c & 0b10000000); 
	reg.c <<= 1;
	reg.c &= 0b11111110;
	reg.c |= ret;
	z = !(reg.c);
	n = false;
	h = false;
	c = ret;
}
void cbcode02(){
	//Rotate D left
	bool ret = (reg.d & 0b10000000); 
	reg.d <<= 1;
	reg.d &= 0b11111110;
	reg.d |= ret;
	z = !(reg.d);
	n = false;
	h = false;
	c = ret;
}
void cbcode03(){
	//Rotate E left
	bool ret = (reg.e & 0b10000000); 
	reg.e <<= 1;
	reg.e &= 0b11111110;
	reg.e |= ret;
	z = !(reg.e);
	n = false;
	h = false;
	c = ret;
}
void cbcode04(){
	//Rotate H left
	bool ret = (reg.h & 0b10000000); 
	reg.h <<= 1;
	reg.h &= 0b11111110;
	reg.h |= ret;
	z = !(reg.h);
	n = false;
	h = false;
	c = ret;
}
void cbcode05(){
	//Rotate L left
	bool ret = (reg.l & 0b10000000); 
	reg.l <<= 1;
	reg.l &= 0b11111110;
	reg.l |= ret;
	z = !(reg.l);
	n = false;
	h = false;
	c = ret;
}
void cbcode06(){
	//Rotate byte at address HL left
	ciscIsGayTimer = 11;
	char rot = busread(reg.hl);
	bool ret = (rot & 0b10000000); 
	rot <<= 1;
	rot &= 0b11111110;
	rot |= ret;
	buswrite(reg.hl, rot);
	z = !(reg.b);
	n = false;
	h = false;
	c = ret;
}
void cbcode07(){
	//Rotate A left
	bool ret = (reg.a & 0b10000000); 
	reg.a <<= 1;
	reg.a &= 0b11111110;
	reg.a |= ret;
	z = !(reg.a);
	n = false;
	h = false;
	c = ret;
}
void cbcode08(){
	//Rotate B right
	bool ret = (reg.b & 0b00000001); 
	reg.b >>= 1;
	reg.b &= 0b01111111;
	reg.b |= ret;
	z = !(reg.b);
	n = false;
	h = false;
	c = ret;
}
void cbcode09(){
	//Rotate C right
	bool ret = (reg.c & 0b00000001); 
	reg.c >>= 1;
	reg.c &= 0b01111111;
	reg.c |= ret;
	z = !(reg.c);
	n = false;
	h = false;
	c = ret;
}
void cbcode0A(){
	//Rotate D right
	bool ret = (reg.d & 0b00000001); 
	reg.d >>= 1;
	reg.d &= 0b01111111;
	reg.d |= ret;
	z = !(reg.d);
	n = false;
	h = false;
	c = ret;
}
void cbcode0B(){
	//Rotate E right
	bool ret = (reg.e & 0b00000001); 
	reg.e >>= 1;
	reg.e &= 0b01111111;
	reg.e |= ret;
	z = !(reg.e);
	n = false;
	h = false;
	c = ret;
}
void cbcode0C(){
	//Rotate H right
	bool ret = (reg.h & 0b00000001); 
	reg.h >>= 1;
	reg.h &= 0b01111111;
	reg.h |= ret;
	z = !(reg.h);
	n = false;
	h = false;
	c = ret;
}
void cbcode0D(){
	//Rotate L right
	bool ret = (reg.l & 0b00000001); 
	reg.l >>= 1;
	reg.l &= 0b01111111;
	reg.l |= ret;
	z = !(reg.l);
	n = false;
	h = false;
	c = ret;
}
void cbcode0E(){
	//Rotate byte at address HL right
	ciscIsGayTimer = 11;
	char rot = busread(reg.hl);
	bool ret = (rot & 0b00000001); 
	rot >>= 1;
	rot &= 0b01111111;
	rot |= ret;
	buswrite(reg.hl, rot);
	z = !(rot);
	n = false;
	h = false;
	c = ret;
}
void cbcode0F(){
	//Rotate A right
	bool ret = (reg.a & 0b00000001); 
	reg.a >>= 1;
	reg.a &= 0b01111111;
	reg.a |= ret;
	z = !(reg.a);
	n = false;
	h = false;
	c = ret;
}
void cbcode10(){
	//Rotate B left through carry
	bool ret = (reg.b & 0b10000000); 
	reg.b <<= 1;
	reg.b &= 0b11111110;
	reg.b |= c;
	z = false;
	n = false;
	h = false;
	c = (ret);
}
void cbcode11(){
	//Rotate C left through carry
	bool ret = (reg.c & 0b10000000); 
	reg.c <<= 1;
	reg.c &= 0b11111110;
	reg.c |= c;
	z = false;
	n = false;
	h = false;
	c = ret;
}
void cbcode12(){
	//Rotate D left through carry
	bool ret = (reg.d & 0b10000000); 
	reg.d <<= 1;
	reg.d &= 0b11111110;
	reg.d |= c;
	z = false;
	n = false;
	h = false;
	c = ret;
}
void cbcode13(){
	//Rotate E left through carry
	bool ret = (reg.e & 0b10000000); 
	reg.e <<= 1;
	reg.e &= 0b11111110;
	reg.e |= c;
	z = false;
	n = false;
	h = false;
	c = ret;
}
void cbcode14(){
	//Rotate H left through carry
	bool ret = (reg.h & 0b10000000); 
	reg.h <<= 1;
	reg.h &= 0b11111110;
	reg.h |= c;
	z = false;
	n = false;
	h = false;
	c = ret;
}
void cbcode15(){
	//Rotate L left through carry
	bool ret = (reg.l & 0b10000000); 
	reg.l <<= 1;
	reg.l &= 0b11111110;
	reg.l |= c;
	z = false;
	n = false;
	h = false;
	c = ret;
}
void cbcode16(){
	//Rotate byte at address HL left through carry
	ciscIsGayTimer = 15;
	bool ret = (busread(reg.hl) & 0b10000000);
	buswrite(reg.hl, (busread(reg.hl) << 1));
	buswrite(reg.hl, (busread(reg.hl) & 0b11111110));
	buswrite(reg.hl, (busread(reg.hl) | c));
	z = !(busread(reg.hl));
	n = false;
	h = false;
}
void cbcode17(){
	//Rotate A left through carry
	bool ret = (reg.a & 0b10000000); 
	reg.a <<= 1;
	reg.a &= 0b11111110;
	reg.a |= c;
	z = false;
	n = false;
	h = false;
	c = ret;
}
void cbcode18(){
	//Rotate B right through carry 
	bool ret = (reg.b & 0b00000001); 
	reg.b >>= 1;
	reg.b &= 0b01111111;
	reg.b |= (c << 7);
	z = false;
	n = false;
	h = false;
	c = ret;
}
void cbcode19(){
	//Rotate C right through carry 
	bool ret = (reg.c & 0b00000001); 
	reg.c >>= 1;
	reg.c &= 0b01111111;
	reg.c |= (c << 7);
	z = false;
	n = false;
	h = false;
	c = ret;
}
void cbcode1A(){
	//Rotate D right through carry 
	bool ret = (reg.d & 0b00000001); 
	reg.d >>= 1;
	reg.d &= 0b01111111;
	reg.d |= (c << 7);
	z = false;
	n = false;
	h = false;
	c = ret;
}
void cbcode1B(){
	//Rotate E right through carry 
	bool ret = (reg.e & 0b00000001); 
	reg.e >>= 1;
	reg.e &= 0b01111111;
	reg.e |= (c << 7);
	z = false;
	n = false;
	h = false;
	c = ret;
}
void cbcode1C(){
	//Rotate H right through carry 
	bool ret = (reg.h & 0b00000001); 
	reg.h >>= 1;
	reg.h &= 0b01111111;
	reg.h |= (c << 7);
	z = false;
	n = false;
	h = false;
	c = ret;
}
void cbcode1D(){
	//Rotate L right through carry 
	bool ret = (reg.l & 0b00000001); 
	reg.l >>= 1;
	reg.l &= 0b01111111;
	reg.l |= (c << 7);
	z = false;
	n = false;
	h = false;
	c = ret;
}
void cbcode1E(){
	//Rotate byte at address HL right through carry 
	ciscIsGayTimer = 15;
	bool rot = busread(reg.hl);
	bool ret = (rot & 0b00000001); 
	rot >>= 1;
	rot &= 0b01111111;
	rot |= (c << 7);
	buswrite(reg.hl, rot);
	z = false;
	n = false;
	h = false;
	c = ret;
}
void cbcode1F(){
	//Rotate A right through carry 
	bool ret = (reg.a & 0b00000001); 
	reg.a >>= 1;
	reg.a &= 0b01111111;
	reg.a |= (c << 7);
	z = false;
	n = false;
	h = false;
	c = ret;
}
void cbcode20(){
	//Shift B left into carry
	bool ret = (reg.b & 0b10000000); 
	reg.b <<= 1;
	z = !(reg.b);
	n = false;
	h = false;
	c = ret;
}
void cbcode21(){
	//Shift C left into carry
	bool ret = (reg.c & 0b10000000); 
	reg.c <<= 1;
	z = !(reg.c);
	n = false;
	h = false;
	c = ret;
}
void cbcode22(){
	//Shift D left into carry
	bool ret = (reg.d & 0b10000000); 
	reg.d <<= 1;
	z = !(reg.d);
	n = false;
	h = false;
	c = ret;
}
void cbcode23(){
	//Shift E left into carry
	bool ret = (reg.e & 0b10000000); 
	reg.e <<= 1;
	z = !(reg.e);
	n = false;
	h = false;
	c = ret;
}
void cbcode24(){
	//Shift H left into carry
	bool ret = (reg.h & 0b10000000); 
	reg.h <<= 1;
	z = !(reg.h);
	n = false;
	h = false;
	c = ret;
}
void cbcode25(){
	//Shift L left into carry
	bool ret = (reg.l & 0b10000000); 
	reg.l <<= 1;
	z = !(reg.l);
	n = false;
	h = false;
	c = ret;
}
void cbcode26(){
	//Shift byte at address HL left into carry
	ciscIsGayTimer = 11;
	int rot = busread(reg.hl);
	bool ret = (rot & 0b10000000); 
	rot <<= 1;
	buswrite(reg.hl, rot);
	z = !(rot);
	n = false;
	h = false;
	c = ret;
}
void cbcode27(){
	//Shift A left into carry
	bool ret = (reg.a & 0b10000000); 
	reg.a <<= 1;
	z = !(reg.a);
	n = false;
	h = false;
	c = ret;
}
void cbcode28(){
	//Shift B right into carry 
	bool ret = (reg.b & 0b00000001); 
	bool b7 = (reg.b & 0b10000000);
	reg.b >>= 1;
	reg.b &= (b7 << 7);
	z = !(reg.b);
	n = false;
	h = false;
	c = ret;
}
void cbcode29(){
	//Shift C right into carry 
	bool ret = (reg.c & 0b00000001); 
	bool b7 = (reg.c & 0b10000000);
	reg.c >>= 1;
	reg.c &= (b7 << 7);
	z = !(reg.c);
	n = false;
	h = false;
	c = ret;
}
void cbcode2A(){
	//Shift D right into carry 
	bool ret = (reg.d & 0b00000001); 
	bool b7 = (reg.d & 0b10000000);
	reg.d >>= 1;
	reg.d &= (b7 << 7);
	z = !(reg.d);
	n = false;
	h = false;
	c = ret;
}
void cbcode2B(){
	//Shift E right into carry 
	bool ret = (reg.e & 0b00000001); 
	bool b7 = (reg.e & 0b10000000);
	reg.e >>= 1;
	reg.e &= (b7 << 7);
	z = !(reg.e);
	n = false;
	h = false;
	c = ret;
}
void cbcode2C(){
	//Shift H right into carry 
	bool ret = (reg.h & 0b00000001); 
	bool b7 = (reg.h & 0b10000000);
	reg.h >>= 1;
	reg.h &= (b7 << 7);
	z = !(reg.h);
	n = false;
	h = false;
	c = ret;
}
void cbcode2D(){
	//Shift L right into carry 
	bool ret = (reg.l & 0b00000001); 
	bool b7 = (reg.l & 0b10000000);
	reg.l >>= 1;
	reg.l &= (b7 << 7);
	z = !(reg.l);
	n = false;
	h = false;
	c = ret;
}
void cbcode2E(){
	//Shift byte at address HL right into carry 
	ciscIsGayTimer = 11;
	int rot = busread(reg.hl);
	bool ret = (rot & 0b00000001); 
	bool b7 = (rot & 0b10000000);
	rot >>= 1;
	rot &= (b7 << 7);
	buswrite(reg.hl, rot);
	z = !(rot);
	n = false;
	h = false;
	c = ret;
}
void cbcode2F(){
	//Shift A right into carry 
	bool ret = (reg.a & 0b00000001);
	bool b7 = (reg.a & 0b10000000);
	reg.a >>= 1;
	reg.a &= (b7 << 7);
	z = !(reg.a);
	n = false;
	h = false;
	c = ret;
}
void cbcode30(){
	//Swap upper and lower nybbles of B
	char hi = (reg.b & 0x0F);
	char lo = ((reg.b & 0xF0) >> 4);
	reg.b &= 0x00;
	reg.b &= ((hi << 4) | lo);
	z = !(reg.b);
	n = false;
	h = false;
	c = false;
}
void cbcode31(){
	//Swap upper and lower nybbles of c
	char hi = (reg.c & 0x0F);
	char lo = ((reg.c & 0xF0) >> 4);
	reg.c &= 0x00;
	reg.c &= ((hi << 4) | lo);
	z = !(reg.c);
	n = false;
	h = false;
	c = false;
}
void cbcode32(){
	//Swap upper and lower nybbles of D
	char hi = (reg.d & 0x0F);
	char lo = ((reg.d & 0xF0) >> 4);
	reg.d &= 0x00;
	reg.d &= ((hi << 4) | lo);
	z = !(reg.d);
	n = false;
	h = false;
	c = false;
}
void cbcode33(){
	//Swap upper and lower nybbles of E
	char hi = (reg.e & 0x0F);
	char lo = ((reg.e & 0xF0) >> 4);
	reg.e &= 0x00;
	reg.e &= ((hi << 4) | lo);
	z = !(reg.e);
	n = false;
	h = false;
	c = false;
}
void cbcode34(){
	//Swap upper and lower nybbles of H
	char hi = (reg.h & 0x0F);
	char lo = ((reg.h & 0xF0) >> 4);
	reg.h &= 0x00;
	reg.h &= ((hi << 4) | lo);
	z = !(reg.h);
	n = false;
	h = false;
	c = false;
}
void cbcode35(){
	//Swap upper and lower nybbles of L
	char hi = (reg.l & 0x0F);
	char lo = ((reg.l & 0xF0) >> 4);
	reg.l &= 0x00;
	reg.l &= ((hi << 4) | lo);
	z = !(reg.l);
	n = false;
	h = false;
	c = false;
}
void cbcode36(){
	//Swap upper and lower nybbles of byte at address HL
	ciscIsGayTimer = 11;
	char rot = busread(reg.hl);
	char hi = (rot & 0x0F);
	char lo = ((rot & 0xF0) >> 4);
	rot &= 0x00;
	rot &= ((hi << 4) | lo);
	buswrite(reg.hl, rot);
	z = !(rot);
	n = false;
	h = false;
	c = false;
}
void cbcode37(){
	//Swap upper and lower nybbles of A
	char hi = (reg.a & 0x0F);
	char lo = ((reg.a & 0xF0) >> 4);
	reg.a &= 0x00;
	reg.a &= ((hi << 4) | lo);
	z = !(reg.a);
	n = false;
	h = false;
	c = false;
}
void cbcode38(){
	//Shift B right into carry, set most significant bit to 0 
	bool ret = (reg.b & 0b00000001);
	reg.b >>= 1;
	z = !(reg.b);
	n = false;
	h = false;
	c = ret;
}
void cbcode39(){
	//Shift C right into carry, set most significant bit to 0 
	bool ret = (reg.c & 0b00000001);
	reg.c >>= 1;
	z = !(reg.c);
	n = false;
	h = false;
	c = ret;
}
void cbcode3A(){
	//Shift D right into carry, set most significant bit to 0 
	bool ret = (reg.d & 0b00000001);
	reg.d >>= 1;
	z = !(reg.d);
	n = false;
	h = false;
	c = ret;
}
void cbcode3B(){
	//Shift E right into carry, set most significant bit to 0 
	bool ret = (reg.e & 0b00000001);
	reg.e >>= 1;
	z = !(reg.e);
	n = false;
	h = false;
	c = ret;
}
void cbcode3C(){
	//Shift H right into carry, set most significant bit to 0 
	bool ret = (reg.h & 0b00000001);
	reg.h >>= 1;
	z = !(reg.h);
	n = false;
	h = false;
	c = ret;
}
void cbcode3D(){
	//Shift L right into carry, set most significant bit to 0 
	bool ret = (reg.l & 0b00000001);
	reg.l >>= 1;
	z = !(reg.l);
	n = false;
	h = false;
	c = ret;
}
void cbcode3E(){
	//Shift byte at address HL right into carry, set most significant bit to 0 
	int rot = busread(reg.hl);
	bool ret = (rot & 0b00000001);
	rot >>= 1;
	buswrite(reg.hl, rot);
	z = !(rot);
	n = false;
	h = false;
	c = ret;
}
void cbcode3F(){
	//Shift A right into carry, set most significant bit to 0 
	bool ret = (reg.a & 0b00000001);
	reg.a >>= 1;
	z = !(reg.a);
	n = false;
	h = false;
	c = ret;
}
void cbcode40(){
	//Check bit 0 of B
	z = !(reg.b & (0b1));
	n = false;
	h = true;
}
void cbcode41(){
	//Check bit 0 of C
	z = !(reg.c & (0b1));
	n = false;
	h = true;
}
void cbcode42(){
	//Check bit 0 of D
	z = !(reg.d & (0b1));
	n = false;
	h = true;
}
void cbcode43(){
	//Check bit 0 of E
	z = !(reg.e & (0b1));
	n = false;
	h = true;
}
void cbcode44(){
	//Check bit 0 of H
	z = !(reg.h & (0b1));
	n = false;
	h = true;
}
void cbcode45(){
	//Check bit 0 of L
	z = !(reg.l & (0b1));
	n = false;
	h = true;
}
void cbcode46(){
	//Check bit 0 of byte at address HL
	ciscIsGayTimer = 11;
	z = !(busread(reg.hl) & (0b1));
	n = false;
	h = true;
}
void cbcode47(){
	//Check bit 0 of A
	z = !(reg.a & (0b1));
	n = false;
	h = true;
}
void cbcode48(){
	//Check bit 1 of B
	z = !(reg.b & (0b1 << 1));
	n = false;
	h = true;
}
void cbcode49(){
	//Check bit 1 of C
	z = !(reg.c & (0b1 << 1));
	n = false;
	h = true;
}
void cbcode4A(){
	//Check bit 1 of D
	z = !(reg.d & (0b1 << 1));
	n = false;
	h = true;
}
void cbcode4B(){
	//Check bit 1 of E
	z = !(reg.e & (0b1 << 1));
	n = false;
	h = true;
}
void cbcode4C(){
	//Check bit 1 of H
	z = !(reg.h & (0b1 << 1));
	n = false;
	h = true;
}
void cbcode4D(){
	//Check bit 1 of L
	z = !(reg.l & (0b1 << 1));
	n = false;
	h = true;
}
void cbcode4E(){
	//Check bit 1 of byte at address HL
	ciscIsGayTimer = 11;
	z = !(busread(reg.hl) & (0b1 << 1));
	n = false;
	h = true;
}
void cbcode4F(){
	//Check bit 1 of A
	z = !(reg.a & (0b1 << 1));
	n = false;
	h = true;
}
void cbcode50(){
	//Check bit 2 of B
	z = !(reg.b & (0b1 << 2));
	n = false;
	h = true;
}
void cbcode51(){
	//Check bit 2 of C
	z = !(reg.c & (0b1 << 2));
	n = false;
	h = true;
}
void cbcode52(){
	//Check bit 2 of D
	z = !(reg.d & (0b1 << 2));
	n = false;
	h = true;
}
void cbcode53(){
	//Check bit 2 of E
	z = !(reg.e & (0b1 << 2));
	n = false;
	h = true;
}
void cbcode54(){
	//Check bit 2 of H
	z = !(reg.h & (0b1 << 2));
	n = false;
	h = true;
}
void cbcode55(){
	//Check bit 2 of L
	z = !(reg.l & (0b1 << 2));
	n = false;
	h = true;
}
void cbcode56(){
	//Check bit 2 of byte at address HL
	ciscIsGayTimer = 11;
	z = !(busread(reg.hl) & (0b1 << 2));
	n = false;
	h = true;
}
void cbcode57(){
	//Check bit 2 of A
	z = !(reg.a & (0b1 << 2));
	n = false;
	h = true;
}
void cbcode58(){
	//Check bit 3 of B
	z = !(reg.b & (0b1 << 3));
	n = false;
	h = true;
}
void cbcode59(){
	//Check bit 3 of C
	z = !(reg.c & (0b1 << 3));
	n = false;
	h = true;
}
void cbcode5A(){
	//Check bit 3 of D
	z = !(reg.d & (0b1 << 3));
	n = false;
	h = true;
}
void cbcode5B(){
	//Check bit 3 of E
	z = !(reg.e & (0b1 << 3));
	n = false;
	h = true;
}
void cbcode5C(){
	//Check bit 3 of H
	z = !(reg.h & (0b1 << 3));
	n = false;
	h = true;
}
void cbcode5D(){
	//Check bit 3 of L
	z = !(reg.l & (0b1 << 3));
	n = false;
	h = true;
}
void cbcode5E(){
	//Check bit 3 of byte at address HL
	ciscIsGayTimer = 11;
	z = !(busread(reg.hl) & (0b1 << 3));
	n = false;
	h = true;
}
void cbcode5F(){
	//Check bit 3 of A
	z = !(reg.a & (0b1 << 3));
	n = false;
	h = true;
}
void cbcode60(){
	//Check bit 4 of B
	z = !(reg.b & (0b1 << 4));
	n = false;
	h = true;
}
void cbcode61(){
	//Check bit 4 of C
	z = !(reg.c & (0b1 << 4));
	n = false;
	h = true;
}
void cbcode62(){
	//Check bit 4 of D
	z = !(reg.d & (0b1 << 4));
	n = false;
	h = true;
}
void cbcode63(){
	//Check bit 4 of E
	z = !(reg.e & (0b1 << 4));
	n = false;
	h = true;
}
void cbcode64(){
	//Check bit 4 of H
	z = !(reg.h & (0b1 << 4));
	n = false;
	h = true;
}
void cbcode65(){
	//Check bit 4 of L
	z = !(reg.l & (0b1 << 4));
	n = false;
	h = true;
}
void cbcode66(){
	//Check bit 4 of byte at address HL
	ciscIsGayTimer = 11;
	z = !(busread(reg.hl) & (0b1 << 4));
	n = false;
	h = true;
}
void cbcode67(){
	//Check bit 4 of A
	z = !(reg.a & (0b1 << 4));
	n = false;
	h = true;
}
void cbcode68(){
	//Check bit 5 of B
	z = !(reg.b & (0b1 << 5));
	n = false;
	h = true;
}
void cbcode69(){
	//Check bit 5 of C
	z = !(reg.c & (0b1 << 5));
	n = false;
	h = true;
}
void cbcode6A(){
	//Check bit 5 of D
	z = !(reg.d & (0b1 << 5));
	n = false;
	h = true;
}
void cbcode6B(){
	//Check bit 5 of E
	z = !(reg.e & (0b1 << 5));
	n = false;
	h = true;
}
void cbcode6C(){
	//Check bit 5 of H
	z = !(reg.h & (0b1 << 5));
	n = false;
	h = true;
}
void cbcode6D(){
	//Check bit 5 of L
	z = !(reg.l & (0b1 << 5));
	n = false;
	h = true;
}
void cbcode6E(){
	//Check bit 5 of byte at address HL
	ciscIsGayTimer = 11;
	z = !(busread(reg.hl) & (0b1 << 5));
	n = false;
	h = true;
}
void cbcode6F(){
	//Check bit 5 of A
	z = !(reg.a & (0b1 << 5));
	n = false;
	h = true;
}
void cbcode70(){
	//Check bit 6 of B
	z = !(reg.b & (0b1 << 6));
	n = false;
	h = true;
}
void cbcode71(){
	//Check bit 6 of C
	z = !(reg.c & (0b1 << 6));
	n = false;
	h = true;
}
void cbcode72(){
	//Check bit 6 of D
	z = !(reg.d & (0b1 << 6));
	n = false;
	h = true;
}
void cbcode73(){
	//Check bit 6 of E
	z = !(reg.e & (0b1 << 6));
	n = false;
	h = true;
}
void cbcode74(){
	//Check bit 6 of H
	z = !(reg.h & (0b1 << 6));
	n = false;
	h = true;
}
void cbcode75(){
	//Check bit 6 of L
	z = !(reg.l & (0b1 << 6));
	n = false;
	h = true;
}
void cbcode76(){
	//Check bit 6 of byte at address HL
	ciscIsGayTimer = 11;
	z = !(busread(reg.hl) & (0b1 << 6));
	n = false;
	h = true;
}
void cbcode77(){
	//Check bit 6 of A
	z = !(reg.a & (0b1 << 6));
	n = false;
	h = true;
}
void cbcode78(){
	//Check bit 7 of B
	z = !(reg.b & (0b1 << 7));
	n = false;
	h = true;
}
void cbcode79(){
	//Check bit 7 of C
	z = !(reg.c & (0b1 << 7));
	n = false;
	h = true;
}
void cbcode7A(){
	//Check bit 7 of D
	z = !(reg.d & (0b1 << 7));
	n = false;
	h = true;
}
void cbcode7B(){
	//Check bit 7 of E
	z = !(reg.e & (0b1 << 7));
	n = false;
	h = true;
}
void cbcode7C(){
	//Check bit 7 of H
	z = !(reg.h & (0b1 << 7));
	n = false;
	h = true;
}
void cbcode7D(){
	//Check bit 7 of L
	z = !(reg.l & (0b1 << 7));
	n = false;
	h = true;
}
void cbcode7E(){
	//Check bit 7 of byte at address HL
	ciscIsGayTimer = 11;
	z = !(busread(reg.hl) & (0b1 << 7));
	n = false;
	h = true;
}
void cbcode7F(){
	//Check bit 7 of A
	z = !(reg.a & (0b1 << 7));
	n = false;
	h = true;
}
void cbcode80(){
	//Reset bit 0 of B
	reg.b &= (0b0);
}
void cbcode81(){
	//Reset bit 0 of C
	reg.c &= (0b0);
}
void cbcode82(){
	//Reset bit 0 of D
	reg.d &= (0b0);
}
void cbcode83(){
	//Reset bit 0 of E
	reg.e &= (0b0);
}
void cbcode84(){
	//Reset bit 0 of H
	reg.h &= (0b0);
}
void cbcode85(){
	//Reset bit 0 of L
	reg.l &= (0b0);
}
void cbcode86(){
	//Reset bit 0 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) & (0b0)));
}
void cbcode87(){
	//Reset bit 0 of A
	reg.a &= (0b0);
}
void cbcode88(){
	//Reset bit 1 of B
	reg.b &= (0b0 << 1);
}
void cbcode89(){
	//Reset bit 1 of C
	reg.c &= (0b0 << 1);
}
void cbcode8A(){
	//Reset bit 1 of D
	reg.d &= (0b0 << 1);
}
void cbcode8B(){
	//Reset bit 1 of E
	reg.e &= (0b0 << 1);
}
void cbcode8C(){
	//Reset bit 1 of H
	reg.h &= (0b0 << 1);
}
void cbcode8D(){
	//Reset bit 1 of L
	reg.l &= (0b0 << 1);
}
void cbcode8E(){
	//Reset bit 1 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) & (0b0 << 1)));
}
void cbcode8F(){
	//Reset bit 1 of A
	reg.a &= (0b0 << 1);
}
void cbcode90(){
	//Reset bit 2 of B
	reg.b &= (0b0 << 2);
}
void cbcode91(){
	//Reset bit 2 of C
	reg.c &= (0b0 << 2);
}
void cbcode92(){
	//Reset bit 2 of D
	reg.d &= (0b0 << 2);
}
void cbcode93(){
	//Reset bit 2 of E
	reg.e &= (0b0 << 2);
}
void cbcode94(){
	//Reset bit 2 of H
	reg.h &= (0b0 << 2);
}
void cbcode95(){
	//Reset bit 2 of L
	reg.l &= (0b0 << 2);
}
void cbcode96(){
	//Reset bit 2 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) & (0b0 << 2)));
}
void cbcode97(){
	//Reset bit 2 of A
	reg.a &= (0b0 << 2);	
}
void cbcode98(){
	//Reset bit 3 of B
	reg.b &= (0b0 << 3);
}
void cbcode99(){
	//Reset bit 3 of C
	reg.c &= (0b0 << 3);
}
void cbcode9A(){
	//Reset bit 3 of D
	reg.d &= (0b0 << 3);
}
void cbcode9B(){
	//Reset bit 3 of E
	reg.e &= (0b0 << 3);
}
void cbcode9C(){
	//Reset bit 3 of H
	reg.h &= (0b0 << 3);
}
void cbcode9D(){
	//Reset bit 3 of L
	reg.l &= (0b0 << 3);
}
void cbcode9E(){
	//Reset bit 3 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) & (0b0 << 3)));
}
void cbcode9F(){
	//Reset bit 3 of A
	reg.a &= (0b0 << 3);	
}
void cbcodeA0(){
	//Reset bit 4 of B
	reg.b &= (0b0 << 4);
}
void cbcodeA1(){
	//Reset bit 4 of C
	reg.c &= (0b0 << 4);
}
void cbcodeA2(){
	//Reset bit 4 of D
	reg.d &= (0b0 << 4);
}
void cbcodeA3(){
	//Reset bit 4 of E
	reg.e &= (0b0 << 4);
}
void cbcodeA4(){
	//Reset bit 4 of H
	reg.h &= (0b0 << 4);
}
void cbcodeA5(){
	//Reset bit 4 of L
	reg.l &= (0b0 << 4);
}
void cbcodeA6(){
	//Reset bit 4 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) & (0b0 << 4)));
}
void cbcodeA7(){
	//Reset bit 4 of A
	reg.a &= (0b0 << 4);
}
void cbcodeA8(){
	//Reset bit 5 of B
	reg.b &= (0b0 << 5);
}
void cbcodeA9(){
	//Reset bit 5 of C
	reg.c &= (0b0 << 5);
}
void cbcodeAA(){
	//Reset bit 5 of D
	reg.d &= (0b0 << 5);
}
void cbcodeAB(){
	//Reset bit 5 of E
	reg.e &= (0b0 << 5);
}
void cbcodeAC(){
	//Reset bit 5 of H
	reg.h &= (0b0 << 5);
}
void cbcodeAD(){
	//Reset bit 5 of L
	reg.l &= (0b0 << 5);
}
void cbcodeAE(){
	//Reset bit 5 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) & (0b0 << 5)));
}
void cbcodeAF(){
	//Reset bit 5 of A
	reg.a &= (0b0 << 5);
}
void cbcodeB0(){
	//Reset bit 6 of B
	reg.b &= (0b0 << 6);
}
void cbcodeB1(){
	//Reset bit 6 of C
	reg.c &= (0b0 << 6);
}
void cbcodeB2(){
	//Reset bit 6 of D
	reg.d &= (0b0 << 6);
}
void cbcodeB3(){
	//Reset bit 6 of E
	reg.e &= (0b0 << 6);
}
void cbcodeB4(){
	//Reset bit 6 of H
	reg.h &= (0b0 << 6);
}
void cbcodeB5(){
	//Reset bit 6 of L
	reg.l &= (0b0 << 6);
}
void cbcodeB6(){
	//Reset bit 6 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) & (0b0 << 6)));
}
void cbcodeB7(){
	//Reset bit 6 of A
	reg.a &= (0b0 << 6);
}
void cbcodeB8(){
	//Reset bit 7 of B
	reg.b &= (0b0 << 7);
}
void cbcodeB9(){
	//Reset bit 7 of C
	reg.c &= (0b0 << 7);
}
void cbcodeBA(){
	//Reset bit 7 of D
	reg.d &= (0b0 << 7);
}
void cbcodeBB(){
	//Reset bit 7 of E
	reg.e &= (0b0 << 7);
}
void cbcodeBC(){
	//Reset bit 7 of H
	reg.h &= (0b0 << 7);
}
void cbcodeBD(){
	//Reset bit 7 of L
	reg.l &= (0b0 << 7);
}
void cbcodeBE(){
	//Reset bit 7 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) & (0b0 << 7)));
}
void cbcodeBF(){
	//Reset bit 7 of A
	reg.a &= (0b0 << 7);	
}
void cbcodeC0(){
	//Set bit 0 of B
	reg.b |= (0b1);
}
void cbcodeC1(){
	//Set bit 0 of C
	reg.c |= (0b1);
}
void cbcodeC2(){
	//Set bit 0 of D
	reg.d |= (0b1);
}
void cbcodeC3(){
	//Set bit 0 of E
	reg.e |= (0b1);
}
void cbcodeC4(){
	//Set bit 0 of H
	reg.h |= (0b1);
}
void cbcodeC5(){
	//Set bit 0 of L
	reg.l |= (0b1);
}
void cbcodeC6(){
	//Set bit 0 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) | (0b1)));
}
void cbcodeC7(){
	//Set bit 0 of A
	reg.a |= (0b1);
}
void cbcodeC8(){
	//Set bit 1 of B
	reg.b |= (0b1 << 1);
}
void cbcodeC9(){
	//Set bit 1 of C
	reg.c |= (0b1 << 1);
}
void cbcodeCA(){
	//Set bit 1 of D
	reg.d |= (0b1 << 1);
}
void cbcodeCB(){
	//Set bit 1 of E
	reg.e |= (0b1 << 1);
}
void cbcodeCC(){
	//Set bit 1 of H
	reg.h |= (0b1 << 1);
}
void cbcodeCD(){
	//Set bit 1 of L
	reg.l |= (0b1 << 1);
}
void cbcodeCE(){
	//Set bit 1 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) | (0b1 << 1)));
}
void cbcodeCF(){
	//Set bit 1 of A
	reg.a |= (0b1 << 1);
}
void cbcodeD0(){
	//Set bit 2 of B
	reg.b |= (0b1 << 2);
}
void cbcodeD1(){
	//Set bit 2 of C
	reg.c |= (0b1 << 2);
}
void cbcodeD2(){
	//Set bit 2 of D
	reg.d |= (0b1 << 2);
}
void cbcodeD3(){
	//Set bit 2 of E
	reg.e |= (0b1 << 2);
}
void cbcodeD4(){
	//Set bit 2 of H
	reg.h |= (0b1 << 2);
}
void cbcodeD5(){
	//Set bit 2 of L
	reg.l |= (0b1 << 2);
}
void cbcodeD6(){
	//Set bit 2 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) | (0b1 << 2)));
}
void cbcodeD7(){
	//Set bit 2 of A
	reg.a |= (0b1 << 2);	
}
void cbcodeD8(){
	//Set bit 3 of B
	reg.b |= (0b1 << 3);
}
void cbcodeD9(){
	//Set bit 3 of C
	reg.c |= (0b1 << 3);
}
void cbcodeDA(){
	//Set bit 3 of D
	reg.d |= (0b1 << 3);
}
void cbcodeDB(){
	//Set bit 3 of E
	reg.e |= (0b1 << 3);
}
void cbcodeDC(){
	//Set bit 3 of H
	reg.h |= (0b1 << 3);
}
void cbcodeDD(){
	//Set bit 3 of L
	reg.l |= (0b1 << 3);
}
void cbcodeDE(){
	//Set bit 3 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) | (0b1 << 3)));
}
void cbcodeDF(){
	//Set bit 3 of A
	reg.a |= (0b1 << 3);	
}
void cbcodeE0(){
	//Set bit 4 of B
	reg.b |= (0b1 << 4);
}
void cbcodeE1(){
	//Set bit 4 of C
	reg.c |= (0b1 << 4);
}
void cbcodeE2(){
	//Set bit 4 of D
	reg.d |= (0b1 << 4);
}
void cbcodeE3(){
	//Set bit 4 of E
	reg.e |= (0b1 << 4);
}
void cbcodeE4(){
	//Set bit 4 of H
	reg.h |= (0b1 << 4);
}
void cbcodeE5(){
	//Set bit 4 of L
	reg.l |= (0b1 << 4);
}
void cbcodeE6(){
	//Set bit 4 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) | (0b1 << 4)));
}
void cbcodeE7(){
	//Set bit 4 of A
	reg.a |= (0b1 << 4);
}
void cbcodeE8(){
	//Set bit 5 of B
	reg.b |= (0b1 << 5);
}
void cbcodeE9(){
	//Set bit 5 of C
	reg.c |= (0b1 << 5);
}
void cbcodeEA(){
	//Set bit 5 of D
	reg.d |= (0b1 << 5);
}
void cbcodeEB(){
	//Set bit 5 of E
	reg.e |= (0b1 << 5);
}
void cbcodeEC(){
	//Set bit 5 of H
	reg.h |= (0b1 << 5);
}
void cbcodeED(){
	//Set bit 5 of L
	reg.l |= (0b1 << 5);
}
void cbcodeEE(){
	//Set bit 5 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) | (0b1 << 5)));
}
void cbcodeEF(){
	//Set bit 5 of A
	reg.a |= (0b1 << 5);
}
void cbcodeF0(){
	//Set bit 6 of B
	reg.b |= (0b1 << 6);
}
void cbcodeF1(){
	//Set bit 6 of C
	reg.c |= (0b1 << 6);
}
void cbcodeF2(){
	//Set bit 6 of D
	reg.d |= (0b1 << 6);
}
void cbcodeF3(){
	//Set bit 6 of E
	reg.e |= (0b1 << 6);
}
void cbcodeF4(){
	//Set bit 6 of H
	reg.h |= (0b1 << 6);
}
void cbcodeF5(){
	//Set bit 6 of L
	reg.l |= (0b1 << 6);
}
void cbcodeF6(){
	//Set bit 6 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) | (0b1 << 6)));
}
void cbcodeF7(){
	//Set bit 6 of A
	reg.a |= (0b1 << 6);
}
void cbcodeF8(){
	//Set bit 7 of B
	reg.b |= (0b1 << 7);
}
void cbcodeF9(){
	//Set bit 7 of C
	reg.c |= (0b1 << 7);
}
void cbcodeFA(){
	//Set bit 7 of D
	reg.d |= (0b1 << 7);
}
void cbcodeFB(){
	//Set bit 7 of E
	reg.e |= (0b1 << 7);
}
void cbcodeFC(){
	//Set bit 7 of H
	reg.h |= (0b1 << 7);
}
void cbcodeFD(){
	//Set bit 7 of L
	reg.l |= (0b1 << 7);
}
void cbcodeFE(){
	//Set bit 7 of byte at address HL
	ciscIsGayTimer = 11;
	buswrite(reg.hl, (busread(reg.hl) | (0b1 << 7)));
}
void cbcodeFF(){
	//Set bit 7 of A
	reg.a |= (0b1 << 7);	
}
#endif /* CPUINT_H */