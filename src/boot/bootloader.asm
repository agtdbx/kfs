[BITS 32]
; Defines for grub
%define	MAGIC_NUMBER	0x1BADB002 ; Specify to GRUB that is a bootload using multiboot 1
%define	FLAGS			0x00000003 ; Request page-aligned modules and memory info
%define	CHECKSUM		-(MAGIC_NUMBER + FLAGS) ; Checksum for grub

section .note.GNU-stack
    ; Section to tell that the bootloader is executable

section .multiboot ; Section for grub multiboot define
align 4 ; Make sure that the header is well align
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

section .text ; Section for code location
global _start ;
_start:
	; Define stack
	mov esp, _sys_stack
	; Kernel main call
	extern kmain
	call kmain
	; Infinit loop for avoid crash
	cli
	hlt
_sys_stack:
