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
