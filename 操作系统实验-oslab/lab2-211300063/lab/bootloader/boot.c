#include "boot.h"

#define SECTSIZE 512

/*
void bootMain(void) {
	int i = 0;
	void (*elf)(void);
	elf = (void(*)(void))0x100000; // kernel is loaded to location 0x100000
	for (i = 0; i < 200; i ++) {
		//readSect((void*)elf + i*512, i+1);
		readSect((void*)elf + i*512, i+9);
	}
	elf(); // jumping to the loaded program
}
*/

void bootMain(void) {
	int i = 0;
	int phoff = 0x34;
	int offset = 0x1000;
	unsigned int elf = 0x100000;
	void (*kMainEntry)(void);
	kMainEntry = (void(*)(void))0x100000;

	// 从磁盘读入kernel的代码和数据
	for (i = 0; i < 200; i++) {
		readSect((void*)(elf + i*512), 1+i);
	}

	// TODO: 填写kMainEntry、phoff、offset
	struct ELFHeader elfheader;
	struct ProgramHeader programheader;
	elfheader = *(struct ELFHeader *)elf;
	kMainEntry = (void(*)(void))elfheader.entry;
	phoff = (int)elfheader.phoff;
	programheader = *(struct ProgramHeader *)(elf + phoff);
	offset = (int)programheader.off;

	for (i = 0; i < 200 * 512; i++) {
		*(unsigned char *)(elf + i) = *(unsigned char *)(elf + i + offset);
	}

	kMainEntry();
}

void waitDisk(void) { // waiting for disk
	while((inByte(0x1F7) & 0xC0) != 0x40);
}

void readSect(void *dst, int offset) { // reading a sector of disk
	int i;
	waitDisk();
	outByte(0x1F2, 1);
	outByte(0x1F3, offset);
	outByte(0x1F4, offset >> 8);
	outByte(0x1F5, offset >> 16);
	outByte(0x1F6, (offset >> 24) | 0xE0);
	outByte(0x1F7, 0x20);

	waitDisk();
	for (i = 0; i < SECTSIZE / 4; i ++) {
		((int *)dst)[i] = inLong(0x1F0);
	}
}
