; Defines for grub
%define	MAGIC_NUMBER	0x1BADB002 ; Specify to GRUB that is a bootload using multiboot 1
%define	FLAGS			0x00000003 ; Request page-aligned modules and memory info
%define	CHECKSUM		-(MAGIC_NUMBER + FLAGS) ; Checksum for grub

section .multiboot ; Section for grub multiboot define
align 4 ; Make sure that the header is well align
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

section .text ; Section for code location
global _start ;
_start:


hang: ; Infinite loop for keep the cpu here and avoid crash
	jmp hang
