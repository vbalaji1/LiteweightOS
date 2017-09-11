global load_tss

load_tss:
	mov ax, 0x2B
	ltr ax
	ret 
