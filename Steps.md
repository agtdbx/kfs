# Steps done for making project
## Install Requirements :
- nix
- grub-common
- grub-pc-bin
- xorriso

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
