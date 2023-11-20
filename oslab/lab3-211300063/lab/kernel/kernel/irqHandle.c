#include "device.h"
#include "x86.h"
// #define IRQ_NESTING
// #define TEST_COMSISTENCY_DISPLAY

extern int displayRow;
extern int displayCol;
extern int current;
extern TSS tss;
extern ProcessTable pcb[MAX_PCB_NUM];

void GProtectFaultHandle(struct StackFrame *sf);
void timerHandle(struct StackFrame *sf);
void syscallHandle(struct StackFrame *sf);

void syscallWrite(struct StackFrame *sf);
void syscallPrint(struct StackFrame *sf);
void syscallExec(struct StackFrame *sf);
void syscallFork(struct StackFrame *sf);
void syscallSleep(struct StackFrame *sf);
void syscallExit(struct StackFrame *sf);


void irqHandle(struct StackFrame *sf) {  // pointer sf = esp
    /* Reassign segment register */
    asm volatile("movw %%ax, %%ds" ::"a"(KSEL(SEG_KDATA)));
    /* Save esp to stackTop */
    uint32_t tmpStackTop = pcb[current].stackTop;
    pcb[current].prevStackTop = pcb[current].stackTop;
    pcb[current].stackTop = (uint32_t)sf;

    switch (sf->irq) {
        case -1:
            break;
        case 0xd:
            GProtectFaultHandle(sf);
            break;
        case 0x20:
            timerHandle(sf);
            break;
        case 0x80:
            syscallHandle(sf);
            break;
        default:
            assert(0);
    }

    /* Recover stackTop */
    pcb[current].stackTop = tmpStackTop;
}

void GProtectFaultHandle(struct StackFrame *sf) {
    assert(0);
    return;
}

void syscallHandle(struct StackFrame *sf) {
    switch (sf->eax) {  // syscall number
        case 0:
            syscallWrite(sf);
            break;  // for SYS_WRITE (0)
        /*TODO Add Fork,Sleep... */
        case 1:
            syscallFork(sf);
            break;
        case 2:
            syscallExec(sf);
            break;
        case 3:
            syscallSleep(sf);
            break;
        case 4:
            syscallExit(sf);
            break;
        default:
            break;
    }
}

// void timerHandle(struct StackFrame *sf) {
//     // TODO in lab3
//     // 1. 遍历pcb，将状态为 STATE_BLOCKED 的进程的 sleepTime 减⼀，如果进程的sleepTime变为0，重新设
//     // 为 STATE_RUNNABLE
//     // 2. 将当前进程的 timeCount 加⼀，如果时间⽚⽤完（timeCount==MAX_TIME_COUNT）且有其它 状态
//     // 为 STATE_RUNNABLE 的进程，切换，否则继续执⾏当前进程
//     for (int i = 0; i < MAX_PCB_NUM; i++) {
//         if (pcb[i].state == STATE_BLOCKED) {
//             if (--pcb[i].sleepTime == 0)  
//                 pcb[i].state = STATE_RUNNABLE;
//         }
//     }
//     if (++pcb[current].timeCount >= MAX_TIME_COUNT || pcb[current].state != STATE_RUNNING) {
//         int next = 0, i = 1;
//         for (; i < MAX_PCB_NUM; i++) {
//             if (pcb[i].state == STATE_RUNNABLE) {
//                 next = i;
//                 break;
//             }
//         }
//         if (next != MAX_PCB_NUM && next != current) {
//             pcb[next].state = STATE_RUNNING;
// 			if (pcb[current].state == STATE_RUNNING)
// 				pcb[current].state = STATE_RUNNABLE;
// 			pcb[current].timeCount = 0;
// 			uint32_t tmpStackTop = pcb[next].stackTop;
// 			pcb[next].stackTop = pcb[next].prevStackTop;
// 			tss.esp0 = (uint32_t) & (pcb[next].stackTop);
// 			current = next;
// 			asm volatile("movl %0, %%esp" ::"m"(tmpStackTop)); // switch kernel stack
// 			asm volatile("popl %gs");
// 			asm volatile("popl %fs");
// 			asm volatile("popl %es");
// 			asm volatile("popl %ds");
// 			asm volatile("popal");
// 			asm volatile("addl $8, %esp");
// 			asm volatile("iret");
//         }
//     }
// }

void timerHandle(struct StackFrame *sf) {
    // TODO in lab3
    // 1. 遍历pcb，将状态为 STATE_BLOCKED 的进程的 sleepTime 减⼀，如果进程的sleepTime变为0，重新设
    // 为 STATE_RUNNABLE
    // 2. 将当前进程的 timeCount 加⼀，如果时间⽚⽤完（timeCount==MAX_TIME_COUNT）且有其它 状态
    // 为 STATE_RUNNABLE 的进程，切换，否则继续执⾏当前进程
    for (int i = 0; i < MAX_PCB_NUM; i++) {
        if (pcb[i].state == STATE_BLOCKED) {
            if (--pcb[i].sleepTime == 0)  
                pcb[i].state = STATE_RUNNABLE;
        }
    }
    if (++pcb[current].timeCount >= MAX_TIME_COUNT || pcb[current].state != STATE_RUNNING) {
        int next = current, i = 1; //next指向下一个要调度的进程
        for (; i < MAX_PCB_NUM; i++) { // 从current进程开始，向后循环遍历pcb一遍，找到处于STATE_RUNNABLE的进程
            if (pcb[(current + i) % MAX_PCB_NUM].state == STATE_RUNNABLE) {
                next = (current + i) % MAX_PCB_NUM;
                break;
            }
        }
        if (next != MAX_PCB_NUM && next != current) {
            pcb[next].state = STATE_RUNNING;
			if (pcb[current].state == STATE_RUNNING)
				pcb[current].state = STATE_RUNNABLE;
			pcb[current].timeCount = 0;
			uint32_t tmpStackTop = pcb[next].stackTop;
			pcb[next].stackTop = pcb[next].prevStackTop;
			tss.esp0 = (uint32_t) & (pcb[next].stackTop);
			current = next;
			asm volatile("movl %0, %%esp" ::"m"(tmpStackTop)); // switch kernel stack
			asm volatile("popl %gs");
			asm volatile("popl %fs");
			asm volatile("popl %es");
			asm volatile("popl %ds");
			asm volatile("popal");
			asm volatile("addl $8, %esp");
			asm volatile("iret");
        }
    }
}

void syscallWrite(struct StackFrame *sf) {
    switch (sf->ecx) {  // file descriptor
        case 0:
            syscallPrint(sf);
            break;  // for STD_OUT
        default:
            break;
    }
}

// Attention:
// This is optional homework, because now our kernel can not deal with
// consistency problem in syscallPrint. If you want to handle it, complete this
// function. But if you're not interested in it, don't change anything about it
void syscallPrint(struct StackFrame *sf) {
    int sel = sf->ds;  // TODO segment selector for user data, need further
                       // modification
    char *str = (char *)sf->edx;
    int size = sf->ebx;-
    int i = 0;
    int pos = 0;
    char character = 0;
    uint16_t data = 0;
    asm volatile("movw %0, %%es" ::"m"(sel));
    for (i = 0; i < size; i++) {
        asm volatile("movb %%es:(%1), %0" : "=r"(character) : "r"(str + i));
        if (character == '\n') {
            displayRow++;
            displayCol = 0;
            if (displayRow == 25) {
                displayRow = 24;
                displayCol = 0;
                scrollScreen();
            }
        } else {
            data = character | (0x0c << 8);
            pos = (80 * displayRow + displayCol) * 2;
            asm volatile("movw %0, (%1)" ::"r"(data), "r"(pos + 0xb8000));
            displayCol++;
            if (displayCol == 80) {
                displayRow++;
                displayCol = 0;
                if (displayRow == 25) {
                    displayRow = 24;
                    displayCol = 0;
                    scrollScreen();
                }
            }
        }
#ifdef TEST_COMSISTENCY_DISPLAY
		asm volatile("int $0x20"); //XXX Testing irqTimer during syscall
#endif
        // asm volatile("int $0x20":::"memory"); //XXX Testing irqTimer during
        // syscall
    }

    updateCursor(displayRow, displayCol);
    // TODO take care of return value
    return;
}

void syscallFork(struct StackFrame *sf) {
    // TODO in lab3
    int child_id = 1;
    for (; child_id < MAX_PCB_NUM; child_id++) {
        if (pcb[child_id].state == STATE_DEAD)
            break;
    }
    if (child_id != MAX_PCB_NUM) {
#ifdef IRQ_NESTING
        enableInterrupt();
        for (int j = 0; j < 0x100000; j++) {
            *(uint8_t *)(j + (child_id + 1) * 0x100000) = *(uint8_t *)(j + (current +1) * 0x100000);
            asm volatile("int $0x20"); //XXX Testing irqTimer during syscall
        }
        disableInterrupt();
#else
        for (int j = 0; j < 0x100000; j++) 
			*(uint8_t *)(j + (child_id + 1)*0x100000) = *(uint8_t *)(j + (current + 1)*0x100000);
#endif
        for (int j = 0; j < sizeof(ProcessTable); ++j)
			*((uint8_t *)(&pcb[child_id]) + j) = *((uint8_t *)(&pcb[current]) + j);  
		pcb[child_id].stackTop = (uint32_t) & (pcb[child_id].regs);
		pcb[child_id].prevStackTop = (uint32_t) & (pcb[child_id].stackTop);
		pcb[child_id].state = STATE_RUNNABLE;
		pcb[child_id].timeCount = 0;
		pcb[child_id].sleepTime = 0;
		pcb[child_id].pid = child_id;

		pcb[child_id].regs.ss = USEL(2 + 2 * child_id);
		pcb[child_id].regs.cs = USEL(1 + 2 * child_id);
		pcb[child_id].regs.ds = USEL(2 + 2 * child_id);
		pcb[child_id].regs.es = USEL(2 + 2 * child_id);
		pcb[child_id].regs.fs = USEL(2 + 2 * child_id);
		pcb[child_id].regs.gs = USEL(2 + 2 * child_id);

		pcb[child_id].regs.eax = 0;
		pcb[current].regs.eax = child_id;
    }  else pcb[current].regs.eax = -1;
}

void syscallSleep(struct StackFrame *sf) {
    // TODO in lab3
    if (sf->ecx <= 0)   assert(0);
    pcb[current].state = STATE_BLOCKED;
    pcb[current].sleepTime = sf->ecx;
    asm volatile("int $0x20");
}

void syscallExit(struct StackFrame *sf) {
    // TODO in lab3
    pcb[current].state = STATE_DEAD;
	asm volatile("int $0x20");
}

void syscallExec(struct StackFrame *sf) {

}






