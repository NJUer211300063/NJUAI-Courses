
kMain.elf：     文件格式 elf32-i386


Disassembly of section .text:

00100000 <abort>:
  100000:	55                   	push   %ebp
  100001:	89 e5                	mov    %esp,%ebp
  100003:	57                   	push   %edi
  100004:	56                   	push   %esi
  100005:	53                   	push   %ebx
  100006:	83 ec 1c             	sub    $0x1c,%esp
  100009:	e8 95 00 00 00       	call   1000a3 <__x86.get_pc_thunk.bx>
  10000e:	81 c3 f2 2f 00 00    	add    $0x2ff2,%ebx
  100014:	8b 4d 08             	mov    0x8(%ebp),%ecx
  100017:	fa                   	cli    
  100018:	8a 11                	mov    (%ecx),%dl
  10001a:	8d 83 32 00 00 00    	lea    0x32(%ebx),%eax
  100020:	84 d2                	test   %dl,%dl
  100022:	74 0b                	je     10002f <abort+0x2f>
  100024:	41                   	inc    %ecx
  100025:	40                   	inc    %eax
  100026:	88 50 ff             	mov    %dl,-0x1(%eax)
  100029:	8a 11                	mov    (%ecx),%dl
  10002b:	84 d2                	test   %dl,%dl
  10002d:	75 f5                	jne    100024 <abort+0x24>
  10002f:	8d 70 01             	lea    0x1(%eax),%esi
  100032:	c6 00 3a             	movb   $0x3a,(%eax)
  100035:	8d 8b 3d 01 00 00    	lea    0x13d(%ebx),%ecx
  10003b:	bf 0a 00 00 00       	mov    $0xa,%edi
  100040:	49                   	dec    %ecx
  100041:	8b 45 0c             	mov    0xc(%ebp),%eax
  100044:	99                   	cltd   
  100045:	f7 ff                	idiv   %edi
  100047:	8d 42 30             	lea    0x30(%edx),%eax
  10004a:	88 45 e7             	mov    %al,-0x19(%ebp)
  10004d:	88 01                	mov    %al,(%ecx)
  10004f:	b8 67 66 66 66       	mov    $0x66666667,%eax
  100054:	f7 6d 0c             	imull  0xc(%ebp)
  100057:	c1 fa 02             	sar    $0x2,%edx
  10005a:	8b 45 0c             	mov    0xc(%ebp),%eax
  10005d:	c1 f8 1f             	sar    $0x1f,%eax
  100060:	29 c2                	sub    %eax,%edx
  100062:	89 55 0c             	mov    %edx,0xc(%ebp)
  100065:	75 d9                	jne    100040 <abort+0x40>
  100067:	41                   	inc    %ecx
  100068:	46                   	inc    %esi
  100069:	8a 45 e7             	mov    -0x19(%ebp),%al
  10006c:	88 46 ff             	mov    %al,-0x1(%esi)
  10006f:	8a 01                	mov    (%ecx),%al
  100071:	88 45 e7             	mov    %al,-0x19(%ebp)
  100074:	84 c0                	test   %al,%al
  100076:	75 ef                	jne    100067 <abort+0x67>
  100078:	c6 06 0a             	movb   $0xa,(%esi)
  10007b:	0f be 83 20 00 00 00 	movsbl 0x20(%ebx),%eax
  100082:	84 c0                	test   %al,%al
  100084:	74 1a                	je     1000a0 <abort+0xa0>
  100086:	8d b3 20 00 00 00    	lea    0x20(%ebx),%esi
  10008c:	83 ec 0c             	sub    $0xc,%esp
  10008f:	50                   	push   %eax
  100090:	e8 8f 00 00 00       	call   100124 <putChar>
  100095:	46                   	inc    %esi
  100096:	0f be 06             	movsbl (%esi),%eax
  100099:	83 c4 10             	add    $0x10,%esp
  10009c:	84 c0                	test   %al,%al
  10009e:	75 ec                	jne    10008c <abort+0x8c>
  1000a0:	f4                   	hlt    
  1000a1:	eb fd                	jmp    1000a0 <abort+0xa0>

001000a3 <__x86.get_pc_thunk.bx>:
  1000a3:	8b 1c 24             	mov    (%esp),%ebx
  1000a6:	c3                   	ret    
  1000a7:	90                   	nop

001000a8 <kEntry>:
  1000a8:	55                   	push   %ebp
  1000a9:	89 e5                	mov    %esp,%ebp
  1000ab:	53                   	push   %ebx
  1000ac:	50                   	push   %eax
  1000ad:	e8 f1 ff ff ff       	call   1000a3 <__x86.get_pc_thunk.bx>
  1000b2:	81 c3 4e 2f 00 00    	add    $0x2f4e,%ebx
  1000b8:	e8 23 00 00 00       	call   1000e0 <initSerial>
  1000bd:	e8 ce 0b 00 00       	call   100c90 <initIdt>
  1000c2:	e8 4d 0d 00 00       	call   100e14 <initIntr>
  1000c7:	e8 04 01 00 00       	call   1001d0 <initSeg>
  1000cc:	e8 63 02 00 00       	call   100334 <initVga>
  1000d1:	e8 8a 03 00 00       	call   100460 <initKeyTable>
  1000d6:	e8 d9 01 00 00       	call   1002b4 <loadUMain>
  1000db:	eb fe                	jmp    1000db <kEntry+0x33>
  1000dd:	66 90                	xchg   %ax,%ax
  1000df:	90                   	nop

001000e0 <initSerial>:
  1000e0:	55                   	push   %ebp
  1000e1:	89 e5                	mov    %esp,%ebp
  1000e3:	56                   	push   %esi
  1000e4:	53                   	push   %ebx
  1000e5:	31 db                	xor    %ebx,%ebx
  1000e7:	be f9 03 00 00       	mov    $0x3f9,%esi
  1000ec:	88 d8                	mov    %bl,%al
  1000ee:	89 f2                	mov    %esi,%edx
  1000f0:	ee                   	out    %al,(%dx)
  1000f1:	b9 fb 03 00 00       	mov    $0x3fb,%ecx
  1000f6:	b0 80                	mov    $0x80,%al
  1000f8:	89 ca                	mov    %ecx,%edx
  1000fa:	ee                   	out    %al,(%dx)
  1000fb:	b0 01                	mov    $0x1,%al
  1000fd:	ba f8 03 00 00       	mov    $0x3f8,%edx
  100102:	ee                   	out    %al,(%dx)
  100103:	88 d8                	mov    %bl,%al
  100105:	89 f2                	mov    %esi,%edx
  100107:	ee                   	out    %al,(%dx)
  100108:	b0 03                	mov    $0x3,%al
  10010a:	89 ca                	mov    %ecx,%edx
  10010c:	ee                   	out    %al,(%dx)
  10010d:	b0 c7                	mov    $0xc7,%al
  10010f:	ba fa 03 00 00       	mov    $0x3fa,%edx
  100114:	ee                   	out    %al,(%dx)
  100115:	b0 0b                	mov    $0xb,%al
  100117:	ba fc 03 00 00       	mov    $0x3fc,%edx
  10011c:	ee                   	out    %al,(%dx)
  10011d:	5b                   	pop    %ebx
  10011e:	5e                   	pop    %esi
  10011f:	5d                   	pop    %ebp
  100120:	c3                   	ret    
  100121:	8d 76 00             	lea    0x0(%esi),%esi

00100124 <putChar>:
  100124:	55                   	push   %ebp
  100125:	89 e5                	mov    %esp,%ebp
  100127:	8b 4d 08             	mov    0x8(%ebp),%ecx
  10012a:	ba fd 03 00 00       	mov    $0x3fd,%edx
  10012f:	90                   	nop
  100130:	ec                   	in     (%dx),%al
  100131:	a8 20                	test   $0x20,%al
  100133:	74 fb                	je     100130 <putChar+0xc>
  100135:	ba f8 03 00 00       	mov    $0x3f8,%edx
  10013a:	88 c8                	mov    %cl,%al
  10013c:	ee                   	out    %al,(%dx)
  10013d:	5d                   	pop    %ebp
  10013e:	c3                   	ret    
  10013f:	90                   	nop

00100140 <waitDisk>:
  100140:	55                   	push   %ebp
  100141:	89 e5                	mov    %esp,%ebp
  100143:	ba f7 01 00 00       	mov    $0x1f7,%edx
  100148:	ec                   	in     (%dx),%al
  100149:	83 e0 c0             	and    $0xffffffc0,%eax
  10014c:	3c 40                	cmp    $0x40,%al
  10014e:	75 f8                	jne    100148 <waitDisk+0x8>
  100150:	5d                   	pop    %ebp
  100151:	c3                   	ret    
  100152:	66 90                	xchg   %ax,%ax

00100154 <readSect>:
  100154:	55                   	push   %ebp
  100155:	89 e5                	mov    %esp,%ebp
  100157:	53                   	push   %ebx
  100158:	8b 4d 0c             	mov    0xc(%ebp),%ecx
  10015b:	bb f7 01 00 00       	mov    $0x1f7,%ebx
  100160:	89 da                	mov    %ebx,%edx
  100162:	ec                   	in     (%dx),%al
  100163:	83 e0 c0             	and    $0xffffffc0,%eax
  100166:	3c 40                	cmp    $0x40,%al
  100168:	75 f6                	jne    100160 <readSect+0xc>
  10016a:	b0 01                	mov    $0x1,%al
  10016c:	ba f2 01 00 00       	mov    $0x1f2,%edx
  100171:	ee                   	out    %al,(%dx)
  100172:	ba f3 01 00 00       	mov    $0x1f3,%edx
  100177:	88 c8                	mov    %cl,%al
  100179:	ee                   	out    %al,(%dx)
  10017a:	89 c8                	mov    %ecx,%eax
  10017c:	c1 f8 08             	sar    $0x8,%eax
  10017f:	ba f4 01 00 00       	mov    $0x1f4,%edx
  100184:	ee                   	out    %al,(%dx)
  100185:	89 c8                	mov    %ecx,%eax
  100187:	c1 f8 10             	sar    $0x10,%eax
  10018a:	ba f5 01 00 00       	mov    $0x1f5,%edx
  10018f:	ee                   	out    %al,(%dx)
  100190:	89 c8                	mov    %ecx,%eax
  100192:	c1 f8 18             	sar    $0x18,%eax
  100195:	83 c8 e0             	or     $0xffffffe0,%eax
  100198:	ba f6 01 00 00       	mov    $0x1f6,%edx
  10019d:	ee                   	out    %al,(%dx)
  10019e:	b0 20                	mov    $0x20,%al
  1001a0:	89 da                	mov    %ebx,%edx
  1001a2:	ee                   	out    %al,(%dx)
  1001a3:	ba f7 01 00 00       	mov    $0x1f7,%edx
  1001a8:	ec                   	in     (%dx),%al
  1001a9:	83 e0 c0             	and    $0xffffffc0,%eax
  1001ac:	3c 40                	cmp    $0x40,%al
  1001ae:	75 f8                	jne    1001a8 <readSect+0x54>
  1001b0:	8b 4d 08             	mov    0x8(%ebp),%ecx
  1001b3:	8d 99 00 02 00 00    	lea    0x200(%ecx),%ebx
  1001b9:	ba f0 01 00 00       	mov    $0x1f0,%edx
  1001be:	66 90                	xchg   %ax,%ax
  1001c0:	ed                   	in     (%dx),%eax
  1001c1:	89 01                	mov    %eax,(%ecx)
  1001c3:	83 c1 04             	add    $0x4,%ecx
  1001c6:	39 d9                	cmp    %ebx,%ecx
  1001c8:	75 f6                	jne    1001c0 <readSect+0x6c>
  1001ca:	5b                   	pop    %ebx
  1001cb:	5d                   	pop    %ebp
  1001cc:	c3                   	ret    
  1001cd:	66 90                	xchg   %ax,%ax
  1001cf:	90                   	nop

001001d0 <initSeg>:
  1001d0:	55                   	push   %ebp
  1001d1:	89 e5                	mov    %esp,%ebp
  1001d3:	53                   	push   %ebx
  1001d4:	e8 55 01 00 00       	call   10032e <__x86.get_pc_thunk.dx>
  1001d9:	81 c2 27 2e 00 00    	add    $0x2e27,%edx
  1001df:	c7 c0 60 32 10 00    	mov    $0x103260,%eax
  1001e5:	c7 40 08 ff ff 00 00 	movl   $0xffff,0x8(%eax)
  1001ec:	c7 40 0c 00 9a cf 00 	movl   $0xcf9a00,0xc(%eax)
  1001f3:	c7 40 10 ff ff 00 00 	movl   $0xffff,0x10(%eax)
  1001fa:	c7 40 14 00 92 cf 00 	movl   $0xcf9200,0x14(%eax)
  100201:	c7 40 18 ff 00 00 00 	movl   $0xff,0x18(%eax)
  100208:	c7 40 1c 20 fa c0 00 	movl   $0xc0fa20,0x1c(%eax)
  10020f:	c7 40 20 ff 00 00 00 	movl   $0xff,0x20(%eax)
  100216:	c7 40 24 20 f2 c0 00 	movl   $0xc0f220,0x24(%eax)
  10021d:	66 c7 40 28 63 00    	movw   $0x63,0x28(%eax)
  100223:	c7 c1 a0 32 10 00    	mov    $0x1032a0,%ecx
  100229:	66 89 48 2a          	mov    %cx,0x2a(%eax)
  10022d:	89 cb                	mov    %ecx,%ebx
  10022f:	c1 eb 10             	shr    $0x10,%ebx
  100232:	88 58 2c             	mov    %bl,0x2c(%eax)
  100235:	66 c7 40 2d 89 40    	movw   $0x4089,0x2d(%eax)
  10023b:	89 cb                	mov    %ecx,%ebx
  10023d:	c1 eb 18             	shr    $0x18,%ebx
  100240:	88 58 2f             	mov    %bl,0x2f(%eax)
  100243:	66 c7 82 40 01 00 00 	movw   $0x37,0x140(%edx)
  10024a:	37 00 
  10024c:	66 89 82 42 01 00 00 	mov    %ax,0x142(%edx)
  100253:	c1 e8 10             	shr    $0x10,%eax
  100256:	66 89 82 44 01 00 00 	mov    %ax,0x144(%edx)
  10025d:	8d 82 40 01 00 00    	lea    0x140(%edx),%eax
  100263:	0f 01 10             	lgdtl  (%eax)
  100266:	c7 41 04 ff ff 1f 00 	movl   $0x1fffff,0x4(%ecx)
  10026d:	c7 41 08 10 00 00 00 	movl   $0x10,0x8(%ecx)
  100274:	b8 28 00 00 00       	mov    $0x28,%eax
  100279:	0f 00 d8             	ltr    %ax
  10027c:	b8 10 00 00 00       	mov    $0x10,%eax
  100281:	8e d8                	mov    %eax,%ds
  100283:	8e d0                	mov    %eax,%ss
  100285:	31 c0                	xor    %eax,%eax
  100287:	0f 00 d0             	lldt   %ax
  10028a:	5b                   	pop    %ebx
  10028b:	5d                   	pop    %ebp
  10028c:	c3                   	ret    
  10028d:	8d 76 00             	lea    0x0(%esi),%esi

00100290 <enterUserSpace>:
  100290:	55                   	push   %ebp
  100291:	89 e5                	mov    %esp,%ebp
  100293:	b8 23 00 00 00       	mov    $0x23,%eax
  100298:	50                   	push   %eax
  100299:	b8 ff ff 2f 00       	mov    $0x2fffff,%eax
  10029e:	50                   	push   %eax
  10029f:	9c                   	pushf  
  1002a0:	58                   	pop    %eax
  1002a1:	80 cc 02             	or     $0x2,%ah
  1002a4:	50                   	push   %eax
  1002a5:	b8 1b 00 00 00       	mov    $0x1b,%eax
  1002aa:	50                   	push   %eax
  1002ab:	8b 45 08             	mov    0x8(%ebp),%eax
  1002ae:	50                   	push   %eax
  1002af:	cf                   	iret   
  1002b0:	5d                   	pop    %ebp
  1002b1:	c3                   	ret    
  1002b2:	66 90                	xchg   %ax,%ax

001002b4 <loadUMain>:
  1002b4:	55                   	push   %ebp
  1002b5:	89 e5                	mov    %esp,%ebp
  1002b7:	57                   	push   %edi
  1002b8:	56                   	push   %esi
  1002b9:	53                   	push   %ebx
  1002ba:	83 ec 0c             	sub    $0xc,%esp
  1002bd:	e8 e1 fd ff ff       	call   1000a3 <__x86.get_pc_thunk.bx>
  1002c2:	81 c3 3e 2d 00 00    	add    $0x2d3e,%ebx
  1002c8:	be c9 00 00 00       	mov    $0xc9,%esi
  1002cd:	bf 00 00 20 00       	mov    $0x200000,%edi
  1002d2:	66 90                	xchg   %ax,%ax
  1002d4:	83 ec 08             	sub    $0x8,%esp
  1002d7:	56                   	push   %esi
  1002d8:	57                   	push   %edi
  1002d9:	e8 76 fe ff ff       	call   100154 <readSect>
  1002de:	81 c7 00 02 00 00    	add    $0x200,%edi
  1002e4:	46                   	inc    %esi
  1002e5:	83 c4 10             	add    $0x10,%esp
  1002e8:	81 fe 91 01 00 00    	cmp    $0x191,%esi
  1002ee:	75 e4                	jne    1002d4 <loadUMain+0x20>
  1002f0:	8b 15 18 00 20 00    	mov    0x200018,%edx
  1002f6:	b8 00 10 20 00       	mov    $0x201000,%eax
  1002fb:	90                   	nop
  1002fc:	8a 08                	mov    (%eax),%cl
  1002fe:	88 88 00 f0 ff ff    	mov    %cl,-0x1000(%eax)
  100304:	40                   	inc    %eax
  100305:	3d 00 a0 21 00       	cmp    $0x21a000,%eax
  10030a:	75 f0                	jne    1002fc <loadUMain+0x48>
  10030c:	b8 23 00 00 00       	mov    $0x23,%eax
  100311:	50                   	push   %eax
  100312:	b8 ff ff 2f 00       	mov    $0x2fffff,%eax
  100317:	50                   	push   %eax
  100318:	9c                   	pushf  
  100319:	58                   	pop    %eax
  10031a:	80 cc 02             	or     $0x2,%ah
  10031d:	50                   	push   %eax
  10031e:	b8 1b 00 00 00       	mov    $0x1b,%eax
  100323:	50                   	push   %eax
  100324:	52                   	push   %edx
  100325:	cf                   	iret   
  100326:	8d 65 f4             	lea    -0xc(%ebp),%esp
  100329:	5b                   	pop    %ebx
  10032a:	5e                   	pop    %esi
  10032b:	5f                   	pop    %edi
  10032c:	5d                   	pop    %ebp
  10032d:	c3                   	ret    

0010032e <__x86.get_pc_thunk.dx>:
  10032e:	8b 14 24             	mov    (%esp),%edx
  100331:	c3                   	ret    
  100332:	66 90                	xchg   %ax,%ax

00100334 <initVga>:
  100334:	55                   	push   %ebp
  100335:	89 e5                	mov    %esp,%ebp
  100337:	56                   	push   %esi
  100338:	53                   	push   %ebx
  100339:	e8 1d 01 00 00       	call   10045b <__x86.get_pc_thunk.ax>
  10033e:	05 c2 2c 00 00       	add    $0x2cc2,%eax
  100343:	c7 80 50 01 00 00 00 	movl   $0x0,0x150(%eax)
  10034a:	00 00 00 
  10034d:	c7 80 4c 01 00 00 00 	movl   $0x0,0x14c(%eax)
  100354:	00 00 00 
  100357:	c7 80 48 01 00 00 00 	movl   $0x0,0x148(%eax)
  10035e:	00 00 00 
  100361:	b8 00 80 0b 00       	mov    $0xb8000,%eax
  100366:	ba 00 0c 00 00       	mov    $0xc00,%edx
  10036b:	90                   	nop
  10036c:	66 89 10             	mov    %dx,(%eax)
  10036f:	83 c0 02             	add    $0x2,%eax
  100372:	3d a0 8f 0b 00       	cmp    $0xb8fa0,%eax
  100377:	75 f3                	jne    10036c <initVga+0x38>
  100379:	be d4 03 00 00       	mov    $0x3d4,%esi
  10037e:	b0 0f                	mov    $0xf,%al
  100380:	89 f2                	mov    %esi,%edx
  100382:	ee                   	out    %al,(%dx)
  100383:	31 c9                	xor    %ecx,%ecx
  100385:	bb d5 03 00 00       	mov    $0x3d5,%ebx
  10038a:	88 c8                	mov    %cl,%al
  10038c:	89 da                	mov    %ebx,%edx
  10038e:	ee                   	out    %al,(%dx)
  10038f:	b0 0e                	mov    $0xe,%al
  100391:	89 f2                	mov    %esi,%edx
  100393:	ee                   	out    %al,(%dx)
  100394:	88 c8                	mov    %cl,%al
  100396:	89 da                	mov    %ebx,%edx
  100398:	ee                   	out    %al,(%dx)
  100399:	5b                   	pop    %ebx
  10039a:	5e                   	pop    %esi
  10039b:	5d                   	pop    %ebp
  10039c:	c3                   	ret    
  10039d:	8d 76 00             	lea    0x0(%esi),%esi

001003a0 <clearScreen>:
  1003a0:	55                   	push   %ebp
  1003a1:	89 e5                	mov    %esp,%ebp
  1003a3:	b8 00 80 0b 00       	mov    $0xb8000,%eax
  1003a8:	ba 00 0c 00 00       	mov    $0xc00,%edx
  1003ad:	8d 76 00             	lea    0x0(%esi),%esi
  1003b0:	66 89 10             	mov    %dx,(%eax)
  1003b3:	83 c0 02             	add    $0x2,%eax
  1003b6:	3d a0 8f 0b 00       	cmp    $0xb8fa0,%eax
  1003bb:	75 f3                	jne    1003b0 <clearScreen+0x10>
  1003bd:	5d                   	pop    %ebp
  1003be:	c3                   	ret    
  1003bf:	90                   	nop

001003c0 <updateCursor>:
  1003c0:	55                   	push   %ebp
  1003c1:	89 e5                	mov    %esp,%ebp
  1003c3:	56                   	push   %esi
  1003c4:	53                   	push   %ebx
  1003c5:	8b 45 08             	mov    0x8(%ebp),%eax
  1003c8:	8d 0c 80             	lea    (%eax,%eax,4),%ecx
  1003cb:	c1 e1 04             	shl    $0x4,%ecx
  1003ce:	03 4d 0c             	add    0xc(%ebp),%ecx
  1003d1:	be d4 03 00 00       	mov    $0x3d4,%esi
  1003d6:	b0 0f                	mov    $0xf,%al
  1003d8:	89 f2                	mov    %esi,%edx
  1003da:	ee                   	out    %al,(%dx)
  1003db:	bb d5 03 00 00       	mov    $0x3d5,%ebx
  1003e0:	88 c8                	mov    %cl,%al
  1003e2:	89 da                	mov    %ebx,%edx
  1003e4:	ee                   	out    %al,(%dx)
  1003e5:	b0 0e                	mov    $0xe,%al
  1003e7:	89 f2                	mov    %esi,%edx
  1003e9:	ee                   	out    %al,(%dx)
  1003ea:	89 c8                	mov    %ecx,%eax
  1003ec:	c1 f8 08             	sar    $0x8,%eax
  1003ef:	89 da                	mov    %ebx,%edx
  1003f1:	ee                   	out    %al,(%dx)
  1003f2:	5b                   	pop    %ebx
  1003f3:	5e                   	pop    %esi
  1003f4:	5d                   	pop    %ebp
  1003f5:	c3                   	ret    
  1003f6:	66 90                	xchg   %ax,%ax

001003f8 <scrollScreen>:
  1003f8:	55                   	push   %ebp
  1003f9:	89 e5                	mov    %esp,%ebp
  1003fb:	e8 2e ff ff ff       	call   10032e <__x86.get_pc_thunk.dx>
  100400:	81 c2 00 2c 00 00    	add    $0x2c00,%edx
  100406:	b8 00 80 0b 00       	mov    $0xb8000,%eax
  10040b:	c7 c2 20 33 10 00    	mov    $0x103320,%edx
  100411:	8d 76 00             	lea    0x0(%esi),%esi
  100414:	66 8b 08             	mov    (%eax),%cx
  100417:	66 89 8c 10 00 80 f4 	mov    %cx,-0xb8000(%eax,%edx,1)
  10041e:	ff 
  10041f:	83 c0 02             	add    $0x2,%eax
  100422:	3d a0 8f 0b 00       	cmp    $0xb8fa0,%eax
  100427:	75 eb                	jne    100414 <scrollScreen+0x1c>
  100429:	b8 00 80 0b 00       	mov    $0xb8000,%eax
  10042e:	66 90                	xchg   %ax,%ax
  100430:	66 8b 8c 10 a0 80 f4 	mov    -0xb7f60(%eax,%edx,1),%cx
  100437:	ff 
  100438:	66 89 08             	mov    %cx,(%eax)
  10043b:	83 c0 02             	add    $0x2,%eax
  10043e:	3d 00 8f 0b 00       	cmp    $0xb8f00,%eax
  100443:	75 eb                	jne    100430 <scrollScreen+0x38>
  100445:	ba 00 0c 00 00       	mov    $0xc00,%edx
  10044a:	66 90                	xchg   %ax,%ax
  10044c:	66 89 10             	mov    %dx,(%eax)
  10044f:	83 c0 02             	add    $0x2,%eax
  100452:	3d a0 8f 0b 00       	cmp    $0xb8fa0,%eax
  100457:	75 f3                	jne    10044c <scrollScreen+0x54>
  100459:	5d                   	pop    %ebp
  10045a:	c3                   	ret    

0010045b <__x86.get_pc_thunk.ax>:
  10045b:	8b 04 24             	mov    (%esp),%eax
  10045e:	c3                   	ret    
  10045f:	90                   	nop

00100460 <initKeyTable>:
  100460:	55                   	push   %ebp
  100461:	89 e5                	mov    %esp,%ebp
  100463:	e8 c6 fe ff ff       	call   10032e <__x86.get_pc_thunk.dx>
  100468:	81 c2 98 2b 00 00    	add    $0x2b98,%edx
  10046e:	c7 c0 e0 46 10 00    	mov    $0x1046e0,%eax
  100474:	c7 00 00 00 00 00    	movl   $0x0,(%eax)
  10047a:	c7 c0 c0 42 10 00    	mov    $0x1042c0,%eax
  100480:	c7 00 00 00 00 00    	movl   $0x0,(%eax)
  100486:	c7 82 60 01 00 00 00 	movl   $0x0,0x160(%edx)
  10048d:	00 00 00 
  100490:	8d 82 e0 01 00 00    	lea    0x1e0(%edx),%eax
  100496:	89 82 64 01 00 00    	mov    %eax,0x164(%edx)
  10049c:	31 c0                	xor    %eax,%eax
  10049e:	66 90                	xchg   %ax,%ax
  1004a0:	c6 84 10 e0 01 00 00 	movb   $0x0,0x1e0(%eax,%edx,1)
  1004a7:	00 
  1004a8:	c6 84 10 80 01 00 00 	movb   $0x0,0x180(%eax,%edx,1)
  1004af:	00 
  1004b0:	40                   	inc    %eax
  1004b1:	83 f8 59             	cmp    $0x59,%eax
  1004b4:	75 ea                	jne    1004a0 <initKeyTable+0x40>
  1004b6:	c7 82 e2 01 00 00 31 	movl   $0x34333231,0x1e2(%edx)
  1004bd:	32 33 34 
  1004c0:	c7 82 e6 01 00 00 35 	movl   $0x38373635,0x1e6(%edx)
  1004c7:	36 37 38 
  1004ca:	c7 82 ea 01 00 00 39 	movl   $0x3d2d3039,0x1ea(%edx)
  1004d1:	30 2d 3d 
  1004d4:	c7 82 82 01 00 00 21 	movl   $0x24234021,0x182(%edx)
  1004db:	40 23 24 
  1004de:	c7 82 86 01 00 00 25 	movl   $0x2a265e25,0x186(%edx)
  1004e5:	5e 26 2a 
  1004e8:	c7 82 8a 01 00 00 28 	movl   $0x2b5f2928,0x18a(%edx)
  1004ef:	29 5f 2b 
  1004f2:	c7 82 f0 01 00 00 71 	movl   $0x72657771,0x1f0(%edx)
  1004f9:	77 65 72 
  1004fc:	c7 82 f4 01 00 00 74 	movl   $0x69757974,0x1f4(%edx)
  100503:	79 75 69 
  100506:	c7 82 f8 01 00 00 6f 	movl   $0x5d5b706f,0x1f8(%edx)
  10050d:	70 5b 5d 
  100510:	c6 82 fc 01 00 00 0a 	movb   $0xa,0x1fc(%edx)
  100517:	c7 82 90 01 00 00 51 	movl   $0x52455751,0x190(%edx)
  10051e:	57 45 52 
  100521:	c7 82 94 01 00 00 54 	movl   $0x49555954,0x194(%edx)
  100528:	59 55 49 
  10052b:	c7 82 98 01 00 00 4f 	movl   $0x7d7b504f,0x198(%edx)
  100532:	50 7b 7d 
  100535:	c6 82 9c 01 00 00 0a 	movb   $0xa,0x19c(%edx)
  10053c:	c7 82 fe 01 00 00 61 	movl   $0x66647361,0x1fe(%edx)
  100543:	73 64 66 
  100546:	c7 82 02 02 00 00 67 	movl   $0x6b6a6867,0x202(%edx)
  10054d:	68 6a 6b 
  100550:	c7 82 06 02 00 00 6c 	movl   $0x60273b6c,0x206(%edx)
  100557:	3b 27 60 
  10055a:	c7 82 9e 01 00 00 41 	movl   $0x46445341,0x19e(%edx)
  100561:	53 44 46 
  100564:	c7 82 a2 01 00 00 47 	movl   $0x4b4a4847,0x1a2(%edx)
  10056b:	48 4a 4b 
  10056e:	c7 82 a6 01 00 00 4c 	movl   $0x7e223a4c,0x1a6(%edx)
  100575:	3a 22 7e 
  100578:	c7 82 0b 02 00 00 5c 	movl   $0x63787a5c,0x20b(%edx)
  10057f:	7a 78 63 
  100582:	c7 82 0f 02 00 00 76 	movl   $0x6d6e6276,0x20f(%edx)
  100589:	62 6e 6d 
  10058c:	66 c7 82 13 02 00 00 	movw   $0x2e2c,0x213(%edx)
  100593:	2c 2e 
  100595:	c6 82 15 02 00 00 2f 	movb   $0x2f,0x215(%edx)
  10059c:	c7 82 ab 01 00 00 7c 	movl   $0x43585a7c,0x1ab(%edx)
  1005a3:	5a 58 43 
  1005a6:	c7 82 af 01 00 00 56 	movl   $0x4d4e4256,0x1af(%edx)
  1005ad:	42 4e 4d 
  1005b0:	66 c7 82 b3 01 00 00 	movw   $0x3e3c,0x1b3(%edx)
  1005b7:	3c 3e 
  1005b9:	c6 82 b5 01 00 00 3f 	movb   $0x3f,0x1b5(%edx)
  1005c0:	c6 82 19 02 00 00 20 	movb   $0x20,0x219(%edx)
  1005c7:	c6 82 b9 01 00 00 20 	movb   $0x20,0x1b9(%edx)
  1005ce:	5d                   	pop    %ebp
  1005cf:	c3                   	ret    

001005d0 <getKeyCode>:
  1005d0:	55                   	push   %ebp
  1005d1:	89 e5                	mov    %esp,%ebp
  1005d3:	57                   	push   %edi
  1005d4:	56                   	push   %esi
  1005d5:	53                   	push   %ebx
  1005d6:	e8 6d 01 00 00       	call   100748 <__x86.get_pc_thunk.di>
  1005db:	81 c7 25 2a 00 00    	add    $0x2a25,%edi
  1005e1:	ba 60 00 00 00       	mov    $0x60,%edx
  1005e6:	ec                   	in     (%dx),%al
  1005e7:	0f b6 d8             	movzbl %al,%ebx
  1005ea:	ba 61 00 00 00       	mov    $0x61,%edx
  1005ef:	ec                   	in     (%dx),%al
  1005f0:	89 c6                	mov    %eax,%esi
  1005f2:	83 c8 80             	or     $0xffffff80,%eax
  1005f5:	ee                   	out    %al,(%dx)
  1005f6:	89 f0                	mov    %esi,%eax
  1005f8:	ee                   	out    %al,(%dx)
  1005f9:	81 fb d8 00 00 00    	cmp    $0xd8,%ebx
  1005ff:	77 4b                	ja     10064c <getKeyCode+0x7c>
  100601:	80 fb 3a             	cmp    $0x3a,%bl
  100604:	74 52                	je     100658 <getKeyCode+0x88>
  100606:	0f 86 9c 00 00 00    	jbe    1006a8 <getKeyCode+0xd8>
  10060c:	80 fb b6             	cmp    $0xb6,%bl
  10060f:	74 7f                	je     100690 <getKeyCode+0xc0>
  100611:	80 fb ba             	cmp    $0xba,%bl
  100614:	75 72                	jne    100688 <getKeyCode+0xb8>
  100616:	83 bf 60 01 00 00 02 	cmpl   $0x2,0x160(%edi)
  10061d:	0f 85 dd 00 00 00    	jne    100700 <getKeyCode+0x130>
  100623:	c7 87 60 01 00 00 00 	movl   $0x0,0x160(%edi)
  10062a:	00 00 00 
  10062d:	8d 87 e0 01 00 00    	lea    0x1e0(%edi),%eax
  100633:	39 87 64 01 00 00    	cmp    %eax,0x164(%edi)
  100639:	0f 84 ab 00 00 00    	je     1006ea <getKeyCode+0x11a>
  10063f:	89 87 64 01 00 00    	mov    %eax,0x164(%edi)
  100645:	bb ba 00 00 00       	mov    $0xba,%ebx
  10064a:	eb 02                	jmp    10064e <getKeyCode+0x7e>
  10064c:	31 db                	xor    %ebx,%ebx
  10064e:	89 d8                	mov    %ebx,%eax
  100650:	5b                   	pop    %ebx
  100651:	5e                   	pop    %esi
  100652:	5f                   	pop    %edi
  100653:	5d                   	pop    %ebp
  100654:	c3                   	ret    
  100655:	8d 76 00             	lea    0x0(%esi),%esi
  100658:	8b 87 60 01 00 00    	mov    0x160(%edi),%eax
  10065e:	85 c0                	test   %eax,%eax
  100660:	75 52                	jne    1006b4 <getKeyCode+0xe4>
  100662:	c7 87 60 01 00 00 01 	movl   $0x1,0x160(%edi)
  100669:	00 00 00 
  10066c:	8d 87 e0 01 00 00    	lea    0x1e0(%edi),%eax
  100672:	39 87 64 01 00 00    	cmp    %eax,0x164(%edi)
  100678:	74 5a                	je     1006d4 <getKeyCode+0x104>
  10067a:	89 87 64 01 00 00    	mov    %eax,0x164(%edi)
  100680:	bb 3a 00 00 00       	mov    $0x3a,%ebx
  100685:	eb c7                	jmp    10064e <getKeyCode+0x7e>
  100687:	90                   	nop
  100688:	80 fb aa             	cmp    $0xaa,%bl
  10068b:	75 c1                	jne    10064e <getKeyCode+0x7e>
  10068d:	8d 76 00             	lea    0x0(%esi),%esi
  100690:	8d 87 e0 01 00 00    	lea    0x1e0(%edi),%eax
  100696:	39 87 64 01 00 00    	cmp    %eax,0x164(%edi)
  10069c:	74 6e                	je     10070c <getKeyCode+0x13c>
  10069e:	89 87 64 01 00 00    	mov    %eax,0x164(%edi)
  1006a4:	eb a8                	jmp    10064e <getKeyCode+0x7e>
  1006a6:	66 90                	xchg   %ax,%ax
  1006a8:	80 fb 2a             	cmp    $0x2a,%bl
  1006ab:	74 e3                	je     100690 <getKeyCode+0xc0>
  1006ad:	80 fb 36             	cmp    $0x36,%bl
  1006b0:	75 9c                	jne    10064e <getKeyCode+0x7e>
  1006b2:	eb dc                	jmp    100690 <getKeyCode+0xc0>
  1006b4:	48                   	dec    %eax
  1006b5:	74 09                	je     1006c0 <getKeyCode+0xf0>
  1006b7:	bb 3a 00 00 00       	mov    $0x3a,%ebx
  1006bc:	eb 90                	jmp    10064e <getKeyCode+0x7e>
  1006be:	66 90                	xchg   %ax,%ax
  1006c0:	c7 87 60 01 00 00 02 	movl   $0x2,0x160(%edi)
  1006c7:	00 00 00 
  1006ca:	bb 3a 00 00 00       	mov    $0x3a,%ebx
  1006cf:	e9 7a ff ff ff       	jmp    10064e <getKeyCode+0x7e>
  1006d4:	8d 87 80 01 00 00    	lea    0x180(%edi),%eax
  1006da:	89 87 64 01 00 00    	mov    %eax,0x164(%edi)
  1006e0:	bb 3a 00 00 00       	mov    $0x3a,%ebx
  1006e5:	e9 64 ff ff ff       	jmp    10064e <getKeyCode+0x7e>
  1006ea:	8d 87 80 01 00 00    	lea    0x180(%edi),%eax
  1006f0:	89 87 64 01 00 00    	mov    %eax,0x164(%edi)
  1006f6:	bb ba 00 00 00       	mov    $0xba,%ebx
  1006fb:	e9 4e ff ff ff       	jmp    10064e <getKeyCode+0x7e>
  100700:	bb ba 00 00 00       	mov    $0xba,%ebx
  100705:	e9 44 ff ff ff       	jmp    10064e <getKeyCode+0x7e>
  10070a:	66 90                	xchg   %ax,%ax
  10070c:	8d 87 80 01 00 00    	lea    0x180(%edi),%eax
  100712:	89 87 64 01 00 00    	mov    %eax,0x164(%edi)
  100718:	e9 31 ff ff ff       	jmp    10064e <getKeyCode+0x7e>
  10071d:	8d 76 00             	lea    0x0(%esi),%esi

00100720 <getChar>:
  100720:	55                   	push   %ebp
  100721:	89 e5                	mov    %esp,%ebp
  100723:	e8 06 fc ff ff       	call   10032e <__x86.get_pc_thunk.dx>
  100728:	81 c2 d8 28 00 00    	add    $0x28d8,%edx
  10072e:	8b 45 08             	mov    0x8(%ebp),%eax
  100731:	83 f8 57             	cmp    $0x57,%eax
  100734:	77 0e                	ja     100744 <getChar+0x24>
  100736:	8b 92 64 01 00 00    	mov    0x164(%edx),%edx
  10073c:	8a 04 02             	mov    (%edx,%eax,1),%al
  10073f:	5d                   	pop    %ebp
  100740:	c3                   	ret    
  100741:	8d 76 00             	lea    0x0(%esi),%esi
  100744:	31 c0                	xor    %eax,%eax
  100746:	5d                   	pop    %ebp
  100747:	c3                   	ret    

00100748 <__x86.get_pc_thunk.di>:
  100748:	8b 3c 24             	mov    (%esp),%edi
  10074b:	c3                   	ret    

0010074c <GProtectFaultHandle>:
  10074c:	55                   	push   %ebp
  10074d:	89 e5                	mov    %esp,%ebp
  10074f:	53                   	push   %ebx
  100750:	83 ec 0c             	sub    $0xc,%esp
  100753:	e8 4b f9 ff ff       	call   1000a3 <__x86.get_pc_thunk.bx>
  100758:	81 c3 a8 28 00 00    	add    $0x28a8,%ebx
  10075e:	68 de 00 00 00       	push   $0xde
  100763:	8d 83 9a de ff ff    	lea    -0x2166(%ebx),%eax
  100769:	50                   	push   %eax
  10076a:	e8 91 f8 ff ff       	call   100000 <abort>
  10076f:	83 c4 10             	add    $0x10,%esp
  100772:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  100775:	c9                   	leave  
  100776:	c3                   	ret    
  100777:	90                   	nop

00100778 <KeyboardHandle>:
  100778:	55                   	push   %ebp
  100779:	89 e5                	mov    %esp,%ebp
  10077b:	57                   	push   %edi
  10077c:	56                   	push   %esi
  10077d:	53                   	push   %ebx
  10077e:	83 ec 1c             	sub    $0x1c,%esp
  100781:	e8 1d f9 ff ff       	call   1000a3 <__x86.get_pc_thunk.bx>
  100786:	81 c3 7a 28 00 00    	add    $0x287a,%ebx
  10078c:	e8 3f fe ff ff       	call   1005d0 <getKeyCode>
  100791:	83 f8 0e             	cmp    $0xe,%eax
  100794:	74 7e                	je     100814 <KeyboardHandle+0x9c>
  100796:	83 f8 1c             	cmp    $0x1c,%eax
  100799:	74 31                	je     1007cc <KeyboardHandle+0x54>
  10079b:	3d 80 00 00 00       	cmp    $0x80,%eax
  1007a0:	0f 86 aa 00 00 00    	jbe    100850 <KeyboardHandle+0xd8>
  1007a6:	c7 c0 4c 31 10 00    	mov    $0x10314c,%eax
  1007ac:	8b 00                	mov    (%eax),%eax
  1007ae:	c7 c2 50 31 10 00    	mov    $0x103150,%edx
  1007b4:	8b 12                	mov    (%edx),%edx
  1007b6:	83 ec 08             	sub    $0x8,%esp
  1007b9:	50                   	push   %eax
  1007ba:	52                   	push   %edx
  1007bb:	e8 00 fc ff ff       	call   1003c0 <updateCursor>
  1007c0:	83 c4 10             	add    $0x10,%esp
  1007c3:	8d 65 f4             	lea    -0xc(%ebp),%esp
  1007c6:	5b                   	pop    %ebx
  1007c7:	5e                   	pop    %esi
  1007c8:	5f                   	pop    %edi
  1007c9:	5d                   	pop    %ebp
  1007ca:	c3                   	ret    
  1007cb:	90                   	nop
  1007cc:	c7 c6 50 31 10 00    	mov    $0x103150,%esi
  1007d2:	8b 06                	mov    (%esi),%eax
  1007d4:	8d 50 01             	lea    0x1(%eax),%edx
  1007d7:	89 16                	mov    %edx,(%esi)
  1007d9:	c7 c1 c0 42 10 00    	mov    $0x1042c0,%ecx
  1007df:	8b 01                	mov    (%ecx),%eax
  1007e1:	c7 c7 e0 42 10 00    	mov    $0x1042e0,%edi
  1007e7:	c7 04 87 0a 00 00 00 	movl   $0xa,(%edi,%eax,4)
  1007ee:	40                   	inc    %eax
  1007ef:	89 01                	mov    %eax,(%ecx)
  1007f1:	c7 c7 4c 31 10 00    	mov    $0x10314c,%edi
  1007f7:	c7 07 00 00 00 00    	movl   $0x0,(%edi)
  1007fd:	c7 83 3c 02 00 00 00 	movl   $0x0,0x23c(%ebx)
  100804:	00 00 00 
  100807:	83 fa 19             	cmp    $0x19,%edx
  10080a:	0f 84 d4 00 00 00    	je     1008e4 <KeyboardHandle+0x16c>
  100810:	31 c0                	xor    %eax,%eax
  100812:	eb a2                	jmp    1007b6 <KeyboardHandle+0x3e>
  100814:	c7 c1 4c 31 10 00    	mov    $0x10314c,%ecx
  10081a:	8b 01                	mov    (%ecx),%eax
  10081c:	c7 c2 50 31 10 00    	mov    $0x103150,%edx
  100822:	8b 12                	mov    (%edx),%edx
  100824:	3b 83 3c 02 00 00    	cmp    0x23c(%ebx),%eax
  10082a:	7e 8a                	jle    1007b6 <KeyboardHandle+0x3e>
  10082c:	85 c0                	test   %eax,%eax
  10082e:	7e 86                	jle    1007b6 <KeyboardHandle+0x3e>
  100830:	48                   	dec    %eax
  100831:	89 01                	mov    %eax,(%ecx)
  100833:	8d 0c 92             	lea    (%edx,%edx,4),%ecx
  100836:	c1 e1 04             	shl    $0x4,%ecx
  100839:	01 c1                	add    %eax,%ecx
  10083b:	01 c9                	add    %ecx,%ecx
  10083d:	81 c1 00 80 0b 00    	add    $0xb8000,%ecx
  100843:	be 00 0c 00 00       	mov    $0xc00,%esi
  100848:	66 89 31             	mov    %si,(%ecx)
  10084b:	e9 66 ff ff ff       	jmp    1007b6 <KeyboardHandle+0x3e>
  100850:	83 ec 0c             	sub    $0xc,%esp
  100853:	50                   	push   %eax
  100854:	e8 c7 fe ff ff       	call   100720 <getChar>
  100859:	83 c4 10             	add    $0x10,%esp
  10085c:	84 c0                	test   %al,%al
  10085e:	0f 84 42 ff ff ff    	je     1007a6 <KeyboardHandle+0x2e>
  100864:	83 ec 0c             	sub    $0xc,%esp
  100867:	0f be f0             	movsbl %al,%esi
  10086a:	88 45 e7             	mov    %al,-0x19(%ebp)
  10086d:	56                   	push   %esi
  10086e:	e8 b1 f8 ff ff       	call   100124 <putChar>
  100873:	c7 c1 c0 42 10 00    	mov    $0x1042c0,%ecx
  100879:	8b 11                	mov    (%ecx),%edx
  10087b:	c7 c7 e0 42 10 00    	mov    $0x1042e0,%edi
  100881:	89 34 97             	mov    %esi,(%edi,%edx,4)
  100884:	42                   	inc    %edx
  100885:	83 c4 10             	add    $0x10,%esp
  100888:	81 e2 ff 00 00 80    	and    $0x800000ff,%edx
  10088e:	66 0f be 45 e7       	movsbw -0x19(%ebp),%ax
  100893:	79 08                	jns    10089d <KeyboardHandle+0x125>
  100895:	4a                   	dec    %edx
  100896:	81 ca 00 ff ff ff    	or     $0xffffff00,%edx
  10089c:	42                   	inc    %edx
  10089d:	89 11                	mov    %edx,(%ecx)
  10089f:	c7 c6 50 31 10 00    	mov    $0x103150,%esi
  1008a5:	8b 16                	mov    (%esi),%edx
  1008a7:	c7 c7 4c 31 10 00    	mov    $0x10314c,%edi
  1008ad:	80 cc 0c             	or     $0xc,%ah
  1008b0:	8d 0c 92             	lea    (%edx,%edx,4),%ecx
  1008b3:	c1 e1 04             	shl    $0x4,%ecx
  1008b6:	03 0f                	add    (%edi),%ecx
  1008b8:	01 c9                	add    %ecx,%ecx
  1008ba:	81 c1 00 80 0b 00    	add    $0xb8000,%ecx
  1008c0:	66 89 01             	mov    %ax,(%ecx)
  1008c3:	8b 07                	mov    (%edi),%eax
  1008c5:	40                   	inc    %eax
  1008c6:	89 07                	mov    %eax,(%edi)
  1008c8:	83 f8 50             	cmp    $0x50,%eax
  1008cb:	0f 85 e5 fe ff ff    	jne    1007b6 <KeyboardHandle+0x3e>
  1008d1:	42                   	inc    %edx
  1008d2:	89 16                	mov    %edx,(%esi)
  1008d4:	c7 07 00 00 00 00    	movl   $0x0,(%edi)
  1008da:	83 fa 19             	cmp    $0x19,%edx
  1008dd:	0f 85 2d ff ff ff    	jne    100810 <KeyboardHandle+0x98>
  1008e3:	90                   	nop
  1008e4:	e8 0f fb ff ff       	call   1003f8 <scrollScreen>
  1008e9:	c7 07 00 00 00 00    	movl   $0x0,(%edi)
  1008ef:	c7 06 18 00 00 00    	movl   $0x18,(%esi)
  1008f5:	ba 18 00 00 00       	mov    $0x18,%edx
  1008fa:	31 c0                	xor    %eax,%eax
  1008fc:	e9 b5 fe ff ff       	jmp    1007b6 <KeyboardHandle+0x3e>
  100901:	8d 76 00             	lea    0x0(%esi),%esi

00100904 <syscallPrint>:
  100904:	55                   	push   %ebp
  100905:	89 e5                	mov    %esp,%ebp
  100907:	57                   	push   %edi
  100908:	56                   	push   %esi
  100909:	53                   	push   %ebx
  10090a:	83 ec 2c             	sub    $0x2c,%esp
  10090d:	e8 7a 03 00 00       	call   100c8c <__x86.get_pc_thunk.cx>
  100912:	81 c1 ee 26 00 00    	add    $0x26ee,%ecx
  100918:	89 4d d0             	mov    %ecx,-0x30(%ebp)
  10091b:	8b 45 08             	mov    0x8(%ebp),%eax
  10091e:	c7 45 e4 23 00 00 00 	movl   $0x23,-0x1c(%ebp)
  100925:	8b 70 14             	mov    0x14(%eax),%esi
  100928:	8b 40 10             	mov    0x10(%eax),%eax
  10092b:	8e 45 e4             	mov    -0x1c(%ebp),%es
  10092e:	c7 c1 50 31 10 00    	mov    $0x103150,%ecx
  100934:	8b 19                	mov    (%ecx),%ebx
  100936:	85 c0                	test   %eax,%eax
  100938:	0f 8e 9a 00 00 00    	jle    1009d8 <syscallPrint+0xd4>
  10093e:	01 f0                	add    %esi,%eax
  100940:	89 45 d4             	mov    %eax,-0x2c(%ebp)
  100943:	8b 45 d0             	mov    -0x30(%ebp),%eax
  100946:	c7 c7 4c 31 10 00    	mov    $0x10314c,%edi
  10094c:	eb 2b                	jmp    100979 <syscallPrint+0x75>
  10094e:	66 90                	xchg   %ax,%ax
  100950:	66 0f be d2          	movsbw %dl,%dx
  100954:	80 ce 0c             	or     $0xc,%dh
  100957:	8d 04 9b             	lea    (%ebx,%ebx,4),%eax
  10095a:	c1 e0 04             	shl    $0x4,%eax
  10095d:	03 07                	add    (%edi),%eax
  10095f:	01 c0                	add    %eax,%eax
  100961:	05 00 80 0b 00       	add    $0xb8000,%eax
  100966:	66 89 10             	mov    %dx,(%eax)
  100969:	8b 07                	mov    (%edi),%eax
  10096b:	40                   	inc    %eax
  10096c:	89 07                	mov    %eax,(%edi)
  10096e:	83 f8 50             	cmp    $0x50,%eax
  100971:	74 3d                	je     1009b0 <syscallPrint+0xac>
  100973:	46                   	inc    %esi
  100974:	3b 75 d4             	cmp    -0x2c(%ebp),%esi
  100977:	74 1c                	je     100995 <syscallPrint+0x91>
  100979:	26 8a 16             	mov    %es:(%esi),%dl
  10097c:	80 fa 0a             	cmp    $0xa,%dl
  10097f:	75 cf                	jne    100950 <syscallPrint+0x4c>
  100981:	c7 07 00 00 00 00    	movl   $0x0,(%edi)
  100987:	43                   	inc    %ebx
  100988:	83 fb 19             	cmp    $0x19,%ebx
  10098b:	74 31                	je     1009be <syscallPrint+0xba>
  10098d:	89 19                	mov    %ebx,(%ecx)
  10098f:	46                   	inc    %esi
  100990:	3b 75 d4             	cmp    -0x2c(%ebp),%esi
  100993:	75 e4                	jne    100979 <syscallPrint+0x75>
  100995:	83 ec 08             	sub    $0x8,%esp
  100998:	ff 37                	pushl  (%edi)
  10099a:	53                   	push   %ebx
  10099b:	8b 5d d0             	mov    -0x30(%ebp),%ebx
  10099e:	e8 1d fa ff ff       	call   1003c0 <updateCursor>
  1009a3:	83 c4 10             	add    $0x10,%esp
  1009a6:	8d 65 f4             	lea    -0xc(%ebp),%esp
  1009a9:	5b                   	pop    %ebx
  1009aa:	5e                   	pop    %esi
  1009ab:	5f                   	pop    %edi
  1009ac:	5d                   	pop    %ebp
  1009ad:	c3                   	ret    
  1009ae:	66 90                	xchg   %ax,%ax
  1009b0:	43                   	inc    %ebx
  1009b1:	89 19                	mov    %ebx,(%ecx)
  1009b3:	c7 07 00 00 00 00    	movl   $0x0,(%edi)
  1009b9:	83 fb 19             	cmp    $0x19,%ebx
  1009bc:	75 b5                	jne    100973 <syscallPrint+0x6f>
  1009be:	c7 01 18 00 00 00    	movl   $0x18,(%ecx)
  1009c4:	89 4d cc             	mov    %ecx,-0x34(%ebp)
  1009c7:	8b 5d d0             	mov    -0x30(%ebp),%ebx
  1009ca:	e8 29 fa ff ff       	call   1003f8 <scrollScreen>
  1009cf:	8b 4d cc             	mov    -0x34(%ebp),%ecx
  1009d2:	8b 19                	mov    (%ecx),%ebx
  1009d4:	eb 9d                	jmp    100973 <syscallPrint+0x6f>
  1009d6:	66 90                	xchg   %ax,%ax
  1009d8:	8b 45 d0             	mov    -0x30(%ebp),%eax
  1009db:	c7 c7 4c 31 10 00    	mov    $0x10314c,%edi
  1009e1:	eb b2                	jmp    100995 <syscallPrint+0x91>
  1009e3:	90                   	nop

001009e4 <syscallWrite>:
  1009e4:	55                   	push   %ebp
  1009e5:	89 e5                	mov    %esp,%ebp
  1009e7:	8b 45 08             	mov    0x8(%ebp),%eax
  1009ea:	8b 40 18             	mov    0x18(%eax),%eax
  1009ed:	85 c0                	test   %eax,%eax
  1009ef:	74 03                	je     1009f4 <syscallWrite+0x10>
  1009f1:	5d                   	pop    %ebp
  1009f2:	c3                   	ret    
  1009f3:	90                   	nop
  1009f4:	5d                   	pop    %ebp
  1009f5:	e9 0a ff ff ff       	jmp    100904 <syscallPrint>
  1009fa:	66 90                	xchg   %ax,%ax

001009fc <syscallGetChar>:
  1009fc:	55                   	push   %ebp
  1009fd:	89 e5                	mov    %esp,%ebp
  1009ff:	57                   	push   %edi
  100a00:	56                   	push   %esi
  100a01:	53                   	push   %ebx
  100a02:	83 ec 1c             	sub    $0x1c,%esp
  100a05:	e8 99 f6 ff ff       	call   1000a3 <__x86.get_pc_thunk.bx>
  100a0a:	81 c3 f6 25 00 00    	add    $0x25f6,%ebx
  100a10:	e8 bb fb ff ff       	call   1005d0 <getKeyCode>
  100a15:	85 c0                	test   %eax,%eax
  100a17:	74 f7                	je     100a10 <syscallGetChar+0x14>
  100a19:	c7 c7 50 31 10 00    	mov    $0x103150,%edi
  100a1f:	8b 17                	mov    (%edi),%edx
  100a21:	8d 14 92             	lea    (%edx,%edx,4),%edx
  100a24:	c1 e2 04             	shl    $0x4,%edx
  100a27:	c7 c6 4c 31 10 00    	mov    $0x10314c,%esi
  100a2d:	03 16                	add    (%esi),%edx
  100a2f:	8d 0c 12             	lea    (%edx,%edx,1),%ecx
  100a32:	89 4d e0             	mov    %ecx,-0x20(%ebp)
  100a35:	83 ec 0c             	sub    $0xc,%esp
  100a38:	50                   	push   %eax
  100a39:	e8 e2 fc ff ff       	call   100720 <getChar>
  100a3e:	88 45 e7             	mov    %al,-0x19(%ebp)
  100a41:	66 98                	cbtw   
  100a43:	80 cc 0c             	or     $0xc,%ah
  100a46:	8b 4d e0             	mov    -0x20(%ebp),%ecx
  100a49:	8d 91 00 80 0b 00    	lea    0xb8000(%ecx),%edx
  100a4f:	66 89 02             	mov    %ax,(%edx)
  100a52:	8b 06                	mov    (%esi),%eax
  100a54:	40                   	inc    %eax
  100a55:	89 06                	mov    %eax,(%esi)
  100a57:	83 c4 10             	add    $0x10,%esp
  100a5a:	83 f8 50             	cmp    $0x50,%eax
  100a5d:	74 55                	je     100ab4 <syscallGetChar+0xb8>
  100a5f:	8b 17                	mov    (%edi),%edx
  100a61:	83 ec 08             	sub    $0x8,%esp
  100a64:	50                   	push   %eax
  100a65:	52                   	push   %edx
  100a66:	e8 55 f9 ff ff       	call   1003c0 <updateCursor>
  100a6b:	83 c4 10             	add    $0x10,%esp
  100a6e:	66 90                	xchg   %ax,%ax
  100a70:	e8 5b fb ff ff       	call   1005d0 <getKeyCode>
  100a75:	83 ec 0c             	sub    $0xc,%esp
  100a78:	50                   	push   %eax
  100a79:	e8 a2 fc ff ff       	call   100720 <getChar>
  100a7e:	83 c4 10             	add    $0x10,%esp
  100a81:	3c 0a                	cmp    $0xa,%al
  100a83:	75 eb                	jne    100a70 <syscallGetChar+0x74>
  100a85:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
  100a8b:	8b 07                	mov    (%edi),%eax
  100a8d:	83 f8 19             	cmp    $0x19,%eax
  100a90:	74 3a                	je     100acc <syscallGetChar+0xd0>
  100a92:	31 d2                	xor    %edx,%edx
  100a94:	83 ec 08             	sub    $0x8,%esp
  100a97:	52                   	push   %edx
  100a98:	50                   	push   %eax
  100a99:	e8 22 f9 ff ff       	call   1003c0 <updateCursor>
  100a9e:	0f be 45 e7          	movsbl -0x19(%ebp),%eax
  100aa2:	8b 55 08             	mov    0x8(%ebp),%edx
  100aa5:	89 42 1c             	mov    %eax,0x1c(%edx)
  100aa8:	83 c4 10             	add    $0x10,%esp
  100aab:	8d 65 f4             	lea    -0xc(%ebp),%esp
  100aae:	5b                   	pop    %ebx
  100aaf:	5e                   	pop    %esi
  100ab0:	5f                   	pop    %edi
  100ab1:	5d                   	pop    %ebp
  100ab2:	c3                   	ret    
  100ab3:	90                   	nop
  100ab4:	8b 07                	mov    (%edi),%eax
  100ab6:	8d 50 01             	lea    0x1(%eax),%edx
  100ab9:	89 17                	mov    %edx,(%edi)
  100abb:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
  100ac1:	83 fa 19             	cmp    $0x19,%edx
  100ac4:	74 1a                	je     100ae0 <syscallGetChar+0xe4>
  100ac6:	31 c0                	xor    %eax,%eax
  100ac8:	eb 97                	jmp    100a61 <syscallGetChar+0x65>
  100aca:	66 90                	xchg   %ax,%ax
  100acc:	c7 07 18 00 00 00    	movl   $0x18,(%edi)
  100ad2:	e8 21 f9 ff ff       	call   1003f8 <scrollScreen>
  100ad7:	8b 16                	mov    (%esi),%edx
  100ad9:	8b 07                	mov    (%edi),%eax
  100adb:	eb b7                	jmp    100a94 <syscallGetChar+0x98>
  100add:	8d 76 00             	lea    0x0(%esi),%esi
  100ae0:	c7 07 18 00 00 00    	movl   $0x18,(%edi)
  100ae6:	e8 0d f9 ff ff       	call   1003f8 <scrollScreen>
  100aeb:	8b 06                	mov    (%esi),%eax
  100aed:	e9 6d ff ff ff       	jmp    100a5f <syscallGetChar+0x63>
  100af2:	66 90                	xchg   %ax,%ax

00100af4 <syscallGetStr>:
  100af4:	55                   	push   %ebp
  100af5:	89 e5                	mov    %esp,%ebp
  100af7:	57                   	push   %edi
  100af8:	56                   	push   %esi
  100af9:	53                   	push   %ebx
  100afa:	83 ec 18             	sub    $0x18,%esp
  100afd:	e8 59 f9 ff ff       	call   10045b <__x86.get_pc_thunk.ax>
  100b02:	05 fe 24 00 00       	add    $0x24fe,%eax
  100b07:	8b 55 08             	mov    0x8(%ebp),%edx
  100b0a:	c7 c7 e0 46 10 00    	mov    $0x1046e0,%edi
  100b10:	89 7d dc             	mov    %edi,-0x24(%ebp)
  100b13:	c7 07 00 00 00 00    	movl   $0x0,(%edi)
  100b19:	c7 c1 c0 42 10 00    	mov    $0x1042c0,%ecx
  100b1f:	c7 01 00 00 00 00    	movl   $0x0,(%ecx)
  100b25:	8b 72 10             	mov    0x10(%edx),%esi
  100b28:	8b 5a 14             	mov    0x14(%edx),%ebx
  100b2b:	89 df                	mov    %ebx,%edi
  100b2d:	c7 c0 e0 42 10 00    	mov    $0x1042e0,%eax
  100b33:	89 45 e0             	mov    %eax,-0x20(%ebp)
  100b36:	89 c1                	mov    %eax,%ecx
  100b38:	8d 90 00 04 00 00    	lea    0x400(%eax),%edx
  100b3e:	66 90                	xchg   %ax,%ax
  100b40:	c7 00 00 00 00 00    	movl   $0x0,(%eax)
  100b46:	83 c0 04             	add    $0x4,%eax
  100b49:	39 d0                	cmp    %edx,%eax
  100b4b:	75 f3                	jne    100b40 <syscallGetStr+0x4c>
  100b4d:	31 d2                	xor    %edx,%edx
  100b4f:	85 f6                	test   %esi,%esi
  100b51:	7f 06                	jg     100b59 <syscallGetStr+0x65>
  100b53:	eb 5f                	jmp    100bb4 <syscallGetStr+0xc0>
  100b55:	8d 76 00             	lea    0x0(%esi),%esi
  100b58:	fb                   	sti    
  100b59:	8b 01                	mov    (%ecx),%eax
  100b5b:	85 c0                	test   %eax,%eax
  100b5d:	74 f9                	je     100b58 <syscallGetStr+0x64>
  100b5f:	8d 7a 01             	lea    0x1(%edx),%edi
  100b62:	fa                   	cli    
  100b63:	39 fe                	cmp    %edi,%esi
  100b65:	74 0b                	je     100b72 <syscallGetStr+0x7e>
  100b67:	83 c1 04             	add    $0x4,%ecx
  100b6a:	3c 0a                	cmp    $0xa,%al
  100b6c:	74 3d                	je     100bab <syscallGetStr+0xb7>
  100b6e:	89 fa                	mov    %edi,%edx
  100b70:	eb e7                	jmp    100b59 <syscallGetStr+0x65>
  100b72:	8d 3c 33             	lea    (%ebx,%esi,1),%edi
  100b75:	8b 45 dc             	mov    -0x24(%ebp),%eax
  100b78:	8b 00                	mov    (%eax),%eax
  100b7a:	c7 45 f0 23 00 00 00 	movl   $0x23,-0x10(%ebp)
  100b81:	8e 45 f0             	mov    -0x10(%ebp),%es
  100b84:	39 c2                	cmp    %eax,%edx
  100b86:	7e 17                	jle    100b9f <syscallGetStr+0xab>
  100b88:	01 da                	add    %ebx,%edx
  100b8a:	29 c2                	sub    %eax,%edx
  100b8c:	29 d8                	sub    %ebx,%eax
  100b8e:	8b 75 e0             	mov    -0x20(%ebp),%esi
  100b91:	8d 0c 86             	lea    (%esi,%eax,4),%ecx
  100b94:	8b 04 99             	mov    (%ecx,%ebx,4),%eax
  100b97:	26 88 03             	mov    %al,%es:(%ebx)
  100b9a:	43                   	inc    %ebx
  100b9b:	39 d3                	cmp    %edx,%ebx
  100b9d:	75 f5                	jne    100b94 <syscallGetStr+0xa0>
  100b9f:	26 c6 07 00          	movb   $0x0,%es:(%edi)
  100ba3:	83 c4 18             	add    $0x18,%esp
  100ba6:	5b                   	pop    %ebx
  100ba7:	5e                   	pop    %esi
  100ba8:	5f                   	pop    %edi
  100ba9:	5d                   	pop    %ebp
  100baa:	c3                   	ret    
  100bab:	01 df                	add    %ebx,%edi
  100bad:	8b 45 dc             	mov    -0x24(%ebp),%eax
  100bb0:	8b 00                	mov    (%eax),%eax
  100bb2:	eb c6                	jmp    100b7a <syscallGetStr+0x86>
  100bb4:	31 c0                	xor    %eax,%eax
  100bb6:	ba ff ff ff ff       	mov    $0xffffffff,%edx
  100bbb:	eb bd                	jmp    100b7a <syscallGetStr+0x86>
  100bbd:	8d 76 00             	lea    0x0(%esi),%esi

00100bc0 <syscallRead>:
  100bc0:	55                   	push   %ebp
  100bc1:	89 e5                	mov    %esp,%ebp
  100bc3:	8b 45 08             	mov    0x8(%ebp),%eax
  100bc6:	8b 40 18             	mov    0x18(%eax),%eax
  100bc9:	85 c0                	test   %eax,%eax
  100bcb:	74 0f                	je     100bdc <syscallRead+0x1c>
  100bcd:	48                   	dec    %eax
  100bce:	75 08                	jne    100bd8 <syscallRead+0x18>
  100bd0:	5d                   	pop    %ebp
  100bd1:	e9 1e ff ff ff       	jmp    100af4 <syscallGetStr>
  100bd6:	66 90                	xchg   %ax,%ax
  100bd8:	5d                   	pop    %ebp
  100bd9:	c3                   	ret    
  100bda:	66 90                	xchg   %ax,%ax
  100bdc:	5d                   	pop    %ebp
  100bdd:	e9 1a fe ff ff       	jmp    1009fc <syscallGetChar>
  100be2:	66 90                	xchg   %ax,%ax

00100be4 <syscallHandle>:
  100be4:	55                   	push   %ebp
  100be5:	89 e5                	mov    %esp,%ebp
  100be7:	8b 55 08             	mov    0x8(%ebp),%edx
  100bea:	8b 42 1c             	mov    0x1c(%edx),%eax
  100bed:	85 c0                	test   %eax,%eax
  100bef:	74 07                	je     100bf8 <syscallHandle+0x14>
  100bf1:	48                   	dec    %eax
  100bf2:	75 0b                	jne    100bff <syscallHandle+0x1b>
  100bf4:	5d                   	pop    %ebp
  100bf5:	eb c9                	jmp    100bc0 <syscallRead>
  100bf7:	90                   	nop
  100bf8:	8b 42 18             	mov    0x18(%edx),%eax
  100bfb:	85 c0                	test   %eax,%eax
  100bfd:	74 05                	je     100c04 <syscallHandle+0x20>
  100bff:	5d                   	pop    %ebp
  100c00:	c3                   	ret    
  100c01:	8d 76 00             	lea    0x0(%esi),%esi
  100c04:	5d                   	pop    %ebp
  100c05:	e9 fa fc ff ff       	jmp    100904 <syscallPrint>
  100c0a:	66 90                	xchg   %ax,%ax

00100c0c <irqHandle>:
  100c0c:	55                   	push   %ebp
  100c0d:	89 e5                	mov    %esp,%ebp
  100c0f:	53                   	push   %ebx
  100c10:	50                   	push   %eax
  100c11:	e8 8d f4 ff ff       	call   1000a3 <__x86.get_pc_thunk.bx>
  100c16:	81 c3 ea 23 00 00    	add    $0x23ea,%ebx
  100c1c:	b8 10 00 00 00       	mov    $0x10,%eax
  100c21:	8e d8                	mov    %eax,%ds
  100c23:	8b 45 08             	mov    0x8(%ebp),%eax
  100c26:	8b 40 20             	mov    0x20(%eax),%eax
  100c29:	83 f8 0d             	cmp    $0xd,%eax
  100c2c:	74 42                	je     100c70 <irqHandle+0x64>
  100c2e:	7e 1c                	jle    100c4c <irqHandle+0x40>
  100c30:	83 f8 21             	cmp    $0x21,%eax
  100c33:	74 0b                	je     100c40 <irqHandle+0x34>
  100c35:	83 c0 80             	add    $0xffffff80,%eax
  100c38:	75 1a                	jne    100c54 <irqHandle+0x48>
  100c3a:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  100c3d:	c9                   	leave  
  100c3e:	eb a4                	jmp    100be4 <syscallHandle>
  100c40:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  100c43:	c9                   	leave  
  100c44:	e9 2f fb ff ff       	jmp    100778 <KeyboardHandle>
  100c49:	8d 76 00             	lea    0x0(%esi),%esi
  100c4c:	40                   	inc    %eax
  100c4d:	75 05                	jne    100c54 <irqHandle+0x48>
  100c4f:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  100c52:	c9                   	leave  
  100c53:	c3                   	ret    
  100c54:	83 ec 08             	sub    $0x8,%esp
  100c57:	68 d9 00 00 00       	push   $0xd9
  100c5c:	8d 83 9a de ff ff    	lea    -0x2166(%ebx),%eax
  100c62:	50                   	push   %eax
  100c63:	e8 98 f3 ff ff       	call   100000 <abort>
  100c68:	83 c4 10             	add    $0x10,%esp
  100c6b:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  100c6e:	c9                   	leave  
  100c6f:	c3                   	ret    
  100c70:	83 ec 08             	sub    $0x8,%esp
  100c73:	68 de 00 00 00       	push   $0xde
  100c78:	8d 83 9a de ff ff    	lea    -0x2166(%ebx),%eax
  100c7e:	50                   	push   %eax
  100c7f:	e8 7c f3 ff ff       	call   100000 <abort>
  100c84:	83 c4 10             	add    $0x10,%esp
  100c87:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  100c8a:	c9                   	leave  
  100c8b:	c3                   	ret    

00100c8c <__x86.get_pc_thunk.cx>:
  100c8c:	8b 0c 24             	mov    (%esp),%ecx
  100c8f:	c3                   	ret    

00100c90 <initIdt>:
  100c90:	55                   	push   %ebp
  100c91:	89 e5                	mov    %esp,%ebp
  100c93:	57                   	push   %edi
  100c94:	56                   	push   %esi
  100c95:	53                   	push   %ebx
  100c96:	e8 72 01 00 00       	call   100e0d <__x86.get_pc_thunk.si>
  100c9b:	81 c6 65 23 00 00    	add    $0x2365,%esi
  100ca1:	c7 c2 4f 0e 10 00    	mov    $0x100e4f,%edx
  100ca7:	89 d0                	mov    %edx,%eax
  100ca9:	c1 e8 10             	shr    $0x10,%eax
  100cac:	89 c3                	mov    %eax,%ebx
  100cae:	c7 c7 00 47 10 00    	mov    $0x104700,%edi
  100cb4:	8d 8f 00 08 00 00    	lea    0x800(%edi),%ecx
  100cba:	89 f8                	mov    %edi,%eax
  100cbc:	66 89 10             	mov    %dx,(%eax)
  100cbf:	c7 40 02 08 00 00 8f 	movl   $0x8f000008,0x2(%eax)
  100cc6:	66 89 58 06          	mov    %bx,0x6(%eax)
  100cca:	83 c0 08             	add    $0x8,%eax
  100ccd:	39 c1                	cmp    %eax,%ecx
  100ccf:	75 eb                	jne    100cbc <initIdt+0x2c>
  100cd1:	c7 c0 59 0e 10 00    	mov    $0x100e59,%eax
  100cd7:	66 89 47 40          	mov    %ax,0x40(%edi)
  100cdb:	c7 47 42 08 00 00 8f 	movl   $0x8f000008,0x42(%edi)
  100ce2:	c1 e8 10             	shr    $0x10,%eax
  100ce5:	66 89 47 46          	mov    %ax,0x46(%edi)
  100ce9:	c7 c0 5d 0e 10 00    	mov    $0x100e5d,%eax
  100cef:	66 89 47 50          	mov    %ax,0x50(%edi)
  100cf3:	c7 47 52 08 00 00 8f 	movl   $0x8f000008,0x52(%edi)
  100cfa:	c1 e8 10             	shr    $0x10,%eax
  100cfd:	66 89 47 56          	mov    %ax,0x56(%edi)
  100d01:	c7 c0 61 0e 10 00    	mov    $0x100e61,%eax
  100d07:	66 89 47 58          	mov    %ax,0x58(%edi)
  100d0b:	c7 47 5a 08 00 00 8f 	movl   $0x8f000008,0x5a(%edi)
  100d12:	c1 e8 10             	shr    $0x10,%eax
  100d15:	66 89 47 5e          	mov    %ax,0x5e(%edi)
  100d19:	c7 c0 65 0e 10 00    	mov    $0x100e65,%eax
  100d1f:	66 89 47 60          	mov    %ax,0x60(%edi)
  100d23:	c7 47 62 08 00 00 8f 	movl   $0x8f000008,0x62(%edi)
  100d2a:	c1 e8 10             	shr    $0x10,%eax
  100d2d:	66 89 47 66          	mov    %ax,0x66(%edi)
  100d31:	c7 c0 69 0e 10 00    	mov    $0x100e69,%eax
  100d37:	66 89 47 68          	mov    %ax,0x68(%edi)
  100d3b:	c7 47 6a 08 00 00 8f 	movl   $0x8f000008,0x6a(%edi)
  100d42:	c1 e8 10             	shr    $0x10,%eax
  100d45:	66 89 47 6e          	mov    %ax,0x6e(%edi)
  100d49:	c7 c0 6d 0e 10 00    	mov    $0x100e6d,%eax
  100d4f:	66 89 47 70          	mov    %ax,0x70(%edi)
  100d53:	c7 47 72 08 00 00 8f 	movl   $0x8f000008,0x72(%edi)
  100d5a:	c1 e8 10             	shr    $0x10,%eax
  100d5d:	66 89 47 76          	mov    %ax,0x76(%edi)
  100d61:	c7 c0 71 0e 10 00    	mov    $0x100e71,%eax
  100d67:	66 89 87 88 00 00 00 	mov    %ax,0x88(%edi)
  100d6e:	c7 87 8a 00 00 00 08 	movl   $0x8f000008,0x8a(%edi)
  100d75:	00 00 8f 
  100d78:	c1 e8 10             	shr    $0x10,%eax
  100d7b:	66 89 87 8e 00 00 00 	mov    %ax,0x8e(%edi)
  100d82:	c7 c0 75 0e 10 00    	mov    $0x100e75,%eax
  100d88:	66 89 87 f0 00 00 00 	mov    %ax,0xf0(%edi)
  100d8f:	c7 87 f2 00 00 00 08 	movl   $0x8f000008,0xf2(%edi)
  100d96:	00 00 8f 
  100d99:	c1 e8 10             	shr    $0x10,%eax
  100d9c:	66 89 87 f6 00 00 00 	mov    %ax,0xf6(%edi)
  100da3:	c7 c0 79 0e 10 00    	mov    $0x100e79,%eax
  100da9:	66 89 87 08 01 00 00 	mov    %ax,0x108(%edi)
  100db0:	c7 87 0a 01 00 00 08 	movl   $0x8f000008,0x10a(%edi)
  100db7:	00 00 8f 
  100dba:	c1 e8 10             	shr    $0x10,%eax
  100dbd:	66 89 87 0e 01 00 00 	mov    %ax,0x10e(%edi)
  100dc4:	c7 c0 7f 0e 10 00    	mov    $0x100e7f,%eax
  100dca:	66 89 87 00 04 00 00 	mov    %ax,0x400(%edi)
  100dd1:	c7 87 02 04 00 00 08 	movl   $0xee000008,0x402(%edi)
  100dd8:	00 00 ee 
  100ddb:	c1 e8 10             	shr    $0x10,%eax
  100dde:	66 89 87 06 04 00 00 	mov    %ax,0x406(%edi)
  100de5:	66 c7 86 40 02 00 00 	movw   $0x7ff,0x240(%esi)
  100dec:	ff 07 
  100dee:	66 89 be 42 02 00 00 	mov    %di,0x242(%esi)
  100df5:	c1 ef 10             	shr    $0x10,%edi
  100df8:	66 89 be 44 02 00 00 	mov    %di,0x244(%esi)
  100dff:	8d 86 40 02 00 00    	lea    0x240(%esi),%eax
  100e05:	0f 01 18             	lidtl  (%eax)
  100e08:	5b                   	pop    %ebx
  100e09:	5e                   	pop    %esi
  100e0a:	5f                   	pop    %edi
  100e0b:	5d                   	pop    %ebp
  100e0c:	c3                   	ret    

00100e0d <__x86.get_pc_thunk.si>:
  100e0d:	8b 34 24             	mov    (%esp),%esi
  100e10:	c3                   	ret    
  100e11:	66 90                	xchg   %ax,%ax
  100e13:	90                   	nop

00100e14 <initIntr>:
  100e14:	55                   	push   %ebp
  100e15:	89 e5                	mov    %esp,%ebp
  100e17:	53                   	push   %ebx
  100e18:	b0 11                	mov    $0x11,%al
  100e1a:	ba 20 00 00 00       	mov    $0x20,%edx
  100e1f:	ee                   	out    %al,(%dx)
  100e20:	ba a0 00 00 00       	mov    $0xa0,%edx
  100e25:	ee                   	out    %al,(%dx)
  100e26:	bb 21 00 00 00       	mov    $0x21,%ebx
  100e2b:	b0 20                	mov    $0x20,%al
  100e2d:	89 da                	mov    %ebx,%edx
  100e2f:	ee                   	out    %al,(%dx)
  100e30:	b9 a1 00 00 00       	mov    $0xa1,%ecx
  100e35:	b0 28                	mov    $0x28,%al
  100e37:	89 ca                	mov    %ecx,%edx
  100e39:	ee                   	out    %al,(%dx)
  100e3a:	b0 04                	mov    $0x4,%al
  100e3c:	89 da                	mov    %ebx,%edx
  100e3e:	ee                   	out    %al,(%dx)
  100e3f:	b0 02                	mov    $0x2,%al
  100e41:	89 ca                	mov    %ecx,%edx
  100e43:	ee                   	out    %al,(%dx)
  100e44:	b0 03                	mov    $0x3,%al
  100e46:	89 da                	mov    %ebx,%edx
  100e48:	ee                   	out    %al,(%dx)
  100e49:	89 ca                	mov    %ecx,%edx
  100e4b:	ee                   	out    %al,(%dx)
  100e4c:	5b                   	pop    %ebx
  100e4d:	5d                   	pop    %ebp
  100e4e:	c3                   	ret    

00100e4f <irqEmpty>:
  100e4f:	6a 00                	push   $0x0
  100e51:	6a ff                	push   $0xffffffff
  100e53:	eb 33                	jmp    100e88 <asmDoIrq>

00100e55 <irqErrorCode>:
  100e55:	6a ff                	push   $0xffffffff
  100e57:	eb 2f                	jmp    100e88 <asmDoIrq>

00100e59 <irqDoubleFault>:
  100e59:	6a ff                	push   $0xffffffff
  100e5b:	eb 2b                	jmp    100e88 <asmDoIrq>

00100e5d <irqInvalidTSS>:
  100e5d:	6a ff                	push   $0xffffffff
  100e5f:	eb 27                	jmp    100e88 <asmDoIrq>

00100e61 <irqSegNotPresent>:
  100e61:	6a ff                	push   $0xffffffff
  100e63:	eb 23                	jmp    100e88 <asmDoIrq>

00100e65 <irqStackSegFault>:
  100e65:	6a ff                	push   $0xffffffff
  100e67:	eb 1f                	jmp    100e88 <asmDoIrq>

00100e69 <irqGProtectFault>:
  100e69:	6a 0d                	push   $0xd
  100e6b:	eb 1b                	jmp    100e88 <asmDoIrq>

00100e6d <irqPageFault>:
  100e6d:	6a ff                	push   $0xffffffff
  100e6f:	eb 17                	jmp    100e88 <asmDoIrq>

00100e71 <irqAlignCheck>:
  100e71:	6a ff                	push   $0xffffffff
  100e73:	eb 13                	jmp    100e88 <asmDoIrq>

00100e75 <irqSecException>:
  100e75:	6a ff                	push   $0xffffffff
  100e77:	eb 0f                	jmp    100e88 <asmDoIrq>

00100e79 <irqKeyboard>:
  100e79:	6a 00                	push   $0x0
  100e7b:	6a 21                	push   $0x21
  100e7d:	eb 09                	jmp    100e88 <asmDoIrq>

00100e7f <irqSyscall>:
  100e7f:	6a 00                	push   $0x0
  100e81:	68 80 00 00 00       	push   $0x80
  100e86:	eb 00                	jmp    100e88 <asmDoIrq>

00100e88 <asmDoIrq>:
  100e88:	60                   	pusha  
  100e89:	54                   	push   %esp
  100e8a:	e8 7d fd ff ff       	call   100c0c <irqHandle>
  100e8f:	83 c4 04             	add    $0x4,%esp
  100e92:	61                   	popa   
  100e93:	83 c4 04             	add    $0x4,%esp
  100e96:	83 c4 04             	add    $0x4,%esp
  100e99:	cf                   	iret   
