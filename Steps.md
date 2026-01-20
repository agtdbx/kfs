# Steps done for making project
## Install Requirements :
Mandatory
- nix (curl -L https://nixos.org/nix/install | sh -s -- --daemon)
To build without nix
- grub-common
- grub-pc-bin
- xorriso
- nasm
- gcc
- make

## Set up makefile base
Add variables for compilators, linkers, flags and vm test.

## Create nix flake file
Set up nix environment
```bash
nix flake init
```
Modify fake.nix to add all dependencies needed.<br>
Now I can use the dev shell by doing this :
```bash
nix develop
```
or doing this (flag may be requiered) :
```bash
nix develop --extra-experimental-features nix-command --extra-experimental-features flakes
```

## Create the linker and bootloader
Basing on OSdev, write linker to define sections, and then define bootloader that implement some section to allow grub to detect the bootloader.

## Complete makefile for creating .iso file

## Create the kernel
After create the simple kernel in c, compile it into .o, then add it to linker.
Then precise how load it from the bootloader.

## Patch memory by not using gcc
Install new compiler
```bash
sudo apt update
sudo apt install -y build-essential bison flex libgmp3-dev libmpc-dev \
libmpfr-dev texinfo libisl-dev nasm grub-pc-bin xorriso qemu-system-x86

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

mkdir -p ~/src
cd ~/src

wget https://ftp.gnu.org/gnu/binutils/binutils-2.40.tar.gz
wget https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.gz

tar -xf binutils-2.40.tar.gz
tar -xf gcc-13.2.0.tar.gz

mkdir build-binutils
cd build-binutils
../binutils-2.40/configure --target=$TARGET --prefix="$PREFIX" \
--with-sysroot --disable-nls --disable-werror
make -j$(nproc)
make install
cd ..

mkdir build-gcc
cd build-gcc
../gcc-13.2.0/configure --target=$TARGET --prefix="$PREFIX" \
--disable-nls --enable-languages=c --without-headers
make all-gcc -j$(nproc)
make all-target-libgcc -j$(nproc)
make install-gcc
make install-target-libgcc

$PREFIX/bin/i686-elf-gcc --version

echo '' >> ~/.bashrc
echo 'export PATH="$HOME/opt/cross/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
```
