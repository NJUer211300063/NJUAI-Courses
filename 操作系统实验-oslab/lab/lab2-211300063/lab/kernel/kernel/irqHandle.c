#include "x86.h"
#include "device.h"

extern int displayRow;
extern int displayCol;

extern uint32_t keyBuffer[MAX_KEYBUFFER_SIZE];
extern int bufferHead;
extern int bufferTail;


void GProtectFaultHandle(struct TrapFrame *tf);

void KeyboardHandle(struct TrapFrame *tf);

void syscallHandle(struct TrapFrame *tf);
void syscallWrite(struct TrapFrame *tf);
void syscallPrint(struct TrapFrame *tf);
void syscallRead(struct TrapFrame *tf);
void syscallGetChar(struct TrapFrame *tf);
void syscallGetStr(struct TrapFrame *tf);

void irqHandle(struct TrapFrame *tf) { // pointer tf = esp
	/*
	 * 中断处理程序
	 */
	/* Reassign segment register */
	asm volatile("movw %%ax, %%ds"::"a"(KSEL(SEG_KDATA)));
	//asm volatile("movw %%ax, %%es"::"a"(KSEL(SEG_KDATA)));
	//asm volatile("movw %%ax, %%fs"::"a"(KSEL(SEG_KDATA)));
	//asm volatile("movw %%ax, %%gs"::"a"(KSEL(SEG_KDATA)));
	switch(tf->irq) {
		// TODO: 填好中断处理程序的调用
		case -1: break;
		case 0x21: KeyboardHandle(tf); break;
		case 0xd:  GProtectFaultHandle(tf); break;
		case 0x80: syscallHandle(tf); break;
		default: assert(0);
	}
}

void GProtectFaultHandle(struct TrapFrame *tf){
	assert(0);
	return;
}

#define MAX_DISPLAY_COL  80
#define MAX_DISPLAY_ROW  25

int append_keycode(uint32_t keycode) {
	// buffer is full
	if (bufferTail == MAX_KEYBUFFER_SIZE)
		return -1;
	keyBuffer[bufferTail++] = getChar(keycode);
	return 0;
}

// 以下这段代码可以将字符 character 显示在屏幕的 displayRow 行 displayCol 列
void printChar(char character) {
	uint16_t data = character | (0x0c << 8 );
	int pos = ( 80 *displayRow+displayCol)* 2 ;
	asm volatile("movw %0, (%1)"::"r"(data),"r"(pos+0xb8000));
}

void KeyboardHandle(struct TrapFrame *tf){
	uint32_t code = getKeyCode();
	if(code == 0xe){ // 退格符
		// TODO: 要求只能退格用户键盘输入的字符串，且最多退到当行行首
		if (displayCol != 0 && bufferTail != 0) {
			bufferTail -= 1;
			displayCol -= 1;
			printChar(' ');
		}
	} else if(code == 0x1c) { // 回车符
		// TODO: 处理回车情况
		if (displayRow == MAX_DISPLAY_ROW - 1)
			scrollScreen();
		else displayRow++;
		displayCol = 0;
		append_keycode(code);
	} else if (code < 0x81 ) { // 正常字符
		// TODO: 注意输入的大小写的实现、不可打印字符的处理
		if ((code > 1 && code < 0xe) || (code > 0xf && code != 0x1d && code != 0x2a && code != 0x36 && code != 0x38 && code != 0x3a && code < 0x45)) {
			printChar(getChar(code));
			append_keycode(code);
			if (displayCol == MAX_DISPLAY_COL - 1 && displayRow == MAX_DISPLAY_ROW - 1) {
				scrollScreen();
				displayCol = 0;
			} else if (displayCol == MAX_DISPLAY_COL - 1)	{
				displayRow += 1;
				displayCol = 0;
			}
			else displayCol += 1;
		}	else if (code == 0xf) { // 制表符
			append_keycode(code);
			for (int i = 0; i < 4; i++) {
				printChar(' ');
			}
		}
	}
	updateCursor(displayRow, displayCol);
}

void syscallHandle(struct TrapFrame *tf) {
	switch(tf->eax) { // syscall number
		case 0:
			syscallWrite(tf);
			break; // for SYS_WRITE
		case 1:
			syscallRead(tf);
			break; // for SYS_READ
		default:break;
	}
}

void syscallWrite(struct TrapFrame *tf) {
	switch(tf->ecx) { // file descriptor
		case 0:
			syscallPrint(tf);
			break; // for STD_OUT
		default: break;
	}
}

void syscallPrint(struct TrapFrame *tf) {
	int sel =  USEL(SEG_UDATA); //TODO: segment selector for user data, need further modification
	char *str = (char*)tf->edx;
	int size = tf->ebx;
	int i = 0;
	int pos = 0;
	char character = 0;
	uint16_t data = 0;
	asm volatile("movw %0, %%es"::"m"(sel));
	for (i = 0; i < size; i++) {
		asm volatile("movb %%es:(%1), %0":"=r"(character):"r"(str+i));
		// TODO: 完成光标的维护和打印到显存
		if(character == '\n'){   //  遇到回车符
			displayCol = 0;
			displayRow = displayRow + 1;
            if(displayRow == 25){   //  判断是否最后一行，如果是，滚屏换行
				displayRow = 24;
				scrollScreen();
			}
		}
		else{  // 正常情况
			pos = (displayCol + 80 * displayRow) * 2;
			data = character | (0x0c << 8);    //  这里根据vga.c中仿照来写
			asm volatile("movw %0,  (%1)"  :: "r"(data),  "r"(pos  +  0xb8000));
			displayCol = displayCol + 1;
			if(displayCol == 80){  //  判断是否最后一格，如果是，换行
				displayRow = displayRow + 1;
				displayCol = 0;
				if(displayRow == 25){    //  判断是否最后一行，如果是，滚屏换行
					displayRow = 24;
					scrollScreen();
				}
			}
		}
	}
	updateCursor(displayRow, displayCol);   //  更新屏幕
}

void syscallRead(struct TrapFrame *tf){
	switch(tf->ecx){ //file descriptor
		case 0:
			syscallGetChar(tf);
			break; // for STD_IN
		case 1:
			syscallGetStr(tf);
			break; // for STD_STR
		default: break;
	}
}

void syscallGetChar(struct TrapFrame *tf) {
	bufferHead = bufferTail = 0;
	enableInterrupt();
	while (!bufferTail || keyBuffer[bufferTail - 1] != '\n')  waitForInterrupt();
	disableInterrupt();
	tf->eax = keyBuffer[0];
}

void syscallGetStr(struct TrapFrame *tf){
	// TODO
	bufferTail=bufferHead=0;
	int dimension = (int)(tf->ebx);
	char* temp = (char*)(tf->edx);
	int j=0;
	int p = 0;
	char pc=0;
	for(p = 0; p<MAX_KEYBUFFER_SIZE; p++){
			keyBuffer[p]=0;
	}
	while(j < dimension && pc != '\n'){
		while(keyBuffer[j] == 0){
			enableInterrupt();
		}
		pc = keyBuffer[j++];
		disableInterrupt();
	}
	int usr_data = USEL(SEG_UDATA);
	int q = 0;
	int b = usr_data;
	b ++;
	//asm volatile("movl %0, %%es"::"m"(b));
	asm volatile("movw %0, %%es"::"m"(usr_data));
	for(int p = bufferHead; p<j-1; p++){
		asm volatile("movb %0, %%es:(%1)"::"r"(keyBuffer[p]),"r"(temp + q));
		q++;
	}
	asm volatile("movb $0x00, %%es:(%0)"::"r"(temp + j));
}



