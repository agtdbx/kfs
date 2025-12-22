#--- Basic functions ----------------------------------------------------------
COMPILE_ASM	:= nasm
COMPILE_C	:= gcc
LINKER		:= ld
ISO_MAKER	:= grub-mkrescue
EMULATOR	:= qemu-system-i386
FLAGS_ASM	:= -f elf32
FLAGS_C		:= -c -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector\
				-nostartfiles -nodefaultlibs
FLAGS_LD	:= -m elf_i386

#--- File paths ----------------------------------------------------------------
SRC_DIR			:=	./src/
SRC_BOOT_DIR	:=	${SRC_DIR}boot/
SRC_KERNEL_DIR	:=	${SRC_DIR}kernel/
BIN_DIR			:=	./.bin/
KERNEL_BIN_DIR	:=	${BIN_DIR}boot/
GRUB_CONF_DIR	:=	${BIN_DIR}boot/grub/

FILE_LINKER		:=	linker.ld
FILE_BOOTLOADER	:=	bootloader.asm
KERNEL_BIN		:=	kernel.bin
GRUB_CONF_FILE	:=	grub.cfg
ISO_FILE		:=	kfs.iso
KERNEL_FILES	:=	kernel.c \
					libstr.c

LINKER_PATH		:=	${SRC_BOOT_DIR}${FILE_LINKER}
BOOTLOADER_PATH	:=	${SRC_BOOT_DIR}${FILE_BOOTLOADER}
KERNEL_PATH		:=	${KERNEL_BIN_DIR}${KERNEL_BIN}
GRUB_CONF_PATH	:=	${GRUB_CONF_DIR}${GRUB_CONF_FILE}
ISO_PATH		:=	${BIN_DIR}${ISO_FILE}

BOOTLOADER_OBJ	:=	${BIN_DIR}$(FILE_BOOTLOADER:%.asm=%.o)
KERNEL_OBJS		:=	$(KERNEL_FILES:%.c=${BIN_DIR}%.o)


#--- Rules --------------------------------------------------------------------
all: ${ISO_PATH}

# Create directory if not exist
${GRUB_CONF_DIR}:
	mkdir -p ${GRUB_CONF_DIR}

# Compile asm to .o
${BOOTLOADER_OBJ}: ${GRUB_CONF_DIR}
	${COMPILE_ASM} ${FLAGS_ASM} -o $@ ${BOOTLOADER_PATH}

# TODO: Compile C kernel to .o
${BIN_DIR}%.o: ${SRC_KERNEL_DIR}%.c
	${COMPILE_C} ${FLAGS_C} -o $@ $<

# Create the .bin of the kernel
${KERNEL_PATH}: ${BOOTLOADER_OBJ} ${KERNEL_OBJS}
	${LINKER} ${FLAGS_LD} -T ${LINKER_PATH} -o $@ $^

# Create grub config file if not exist
${GRUB_CONF_PATH}: ${GRUB_CONF_DIR}
	echo 'set timeout=5' >> $@
	echo 'set default=0' >> $@
	echo 'menuentry "Kfs" {' >> $@
	echo '	multiboot /boot/kernel.bin' >> $@
	echo '	boot' >> $@
	echo '}' >> $@

${ISO_PATH}: ${KERNEL_PATH} ${GRUB_CONF_PATH}
	${ISO_MAKER} -o $@ ${BIN_DIR}

fclean:
	rm -rf ${BIN_DIR}

re: fclean all

run:
	${EMULATOR} -cdrom ${ISO_PATH}

rerun: re run

.PHONY: fclean re run rerun
