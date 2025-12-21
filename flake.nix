{
  inputs = {
    # Link for src file to downloads
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  # Define dev shell
  outputs = inputs:
    # Make a loop for each system
    inputs.flake-utils.lib.eachDefaultSystem (system:
      # Define the variables pkgs that change for each system
      let
        pkgs = import inputs.nixpkgs { inherit system; };
      in {

        # Define all dependencies to install into dev shell
        devShells.default = pkgs.mkShell {
          shell = pkgs.bash; # Define the default shell

          buildInputs = [
            pkgs.bash # Install bash for shell
            pkgs.mtools # Utilities for working with images
            pkgs.qemu # Emulator that run my kernel
            pkgs.grub2 # Bootloader
            pkgs.wget # Download file from web
            pkgs.unzip # Unzip
            pkgs.nasm # 'Compiler' for asm
            pkgs.gcc # C compiler
            pkgs.binutils # Linker ld
          ];

          # Start my dev shell after install
          shellHook = ''
            exec bash
          '';
        };
      });
}
