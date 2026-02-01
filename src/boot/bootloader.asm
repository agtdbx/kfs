[BITS 32]

; Defines for grub
%define	MAGIC_NUMBER	0x1BADB002 ; Specify to GRUB that is a bootload using multiboot 1
%define	FLAGS			0x00000003 ; Request page-aligned modules and memory info
%define	CHECKSUM		-(MAGIC_NUMBER + FLAGS) ; Checksum for grub
section .multiboot ; Section for grub multiboot define
mb_header:
align 4 ; Make sure that the header is well align
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

section .note.GNU-stack
    ; Section to tell that the bootloader is executable

section .text ; Section for code location

lgdt [gdt_descriptor] ; Load the gdt
jmp 0x08:_flush_gdt ; Reload code segment with far jump
_flush_gdt: ; Reload data segments
	mov ax, 0x10  ; 0x10 = offset of data descriptor in GDT
	mov ds, ax
	mov es, ax
	mov ss, ax
	; fs and gs can stay as-is or be set to 0x10

global _start ;
global gdt_start ;
extern _sys_stack_top
_start:
	; Define stack
	mov esp, _sys_stack_top
	; Kernel main call
	extern kmain
	call kmain
	; Infinit loop for avoid crash
	cli
	hlt


section .gdt
; GDT define
gdt_start: ; Section to define gdt start with only 0
	dw 0x0
	dw 0x0
	dw 0x0
	dw 0x0

; gdt rights : 76543210
; 	7  -> descriptor valid (must be 1)
; 	65 -> privilege ring
; 	43 -> segment type (10 = code, 00 = data)
; 	2  -> conforming ?
; 	1  -> readable
; 	0  -> accessed

; gdt flags : 76543210
; 	7    -> granularity (1 = limit of 4 KB unit)
; 	6    -> 1 = 32 bit segment
; 	5    -> 0 = not 64 bit
; 	4    -> 0 = available for os (not used here)
; 	3210 -> limit high (0xF)

gdt_code: ; Section for code (read, exec)
	dw 0xffff ; End limit
	dw 0x0 ; Start limit
	db 0x0 ; Middle limit (db for 8 bit, not 16)
	db 10011010b ; Ring 0, code, readable+executable
	db 11001111b ; Flag
	db 0x0
gdt_data: ; Section for data (read, write)
	dw 0xffff
	dw 0x0
	db 0x0
	db 10010010b ; Ring 0, data, writable
	db 11001111b
	db 0x0
gdt_kernel_stack: ; Section for data (read, write)
	dw 0xffff
	dw 0x0
	db 0x0
	db 10010010b ; Ring 0, data, writable
	db 11001111b
	db 0x0
gdt_user_code:
	dw 0xffff
	dw 0x0
	db 0x0
	db 11111010b ; Ring 3, code, readable+executable
	db 11001111b
	db 0x0
gdt_user_data:
	dw 0xffff
	dw 0x0
	db 0x0
	db 11110010b ; Ring 3, data, writable
	db 11001111b
	db 0x0
gdt_user_stack:
	dw 0xffff
	dw 0x0
	db 0x0
	db 11110010b ; Ring 3, data, writable
	db 11001111b
	db 0x0

gdt_end: ; Section to define gdt end

gdt_descriptor: ; Section to define how load the gdt
	dw gdt_end - gdt_start - 1
	dd gdt_start
