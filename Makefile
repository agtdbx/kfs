COMPILE_ASM	:= nasm
COMPILE_C	:= gcc
LINKER		:= ld
GRUB		:= grub-mkrescue
EMULATOR	:= qemu-system-i386
FLAGS_ASM	:= -f elf32
FLAGS_C		:= -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector\
				-nostartfiles -nodefaultlibs
