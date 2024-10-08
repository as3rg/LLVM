let
  pkgs = (import <nixpkgs> {});
in pkgs.mkShell.override { stdenv = pkgs.llvmPackages_18.stdenv; } {
    packages = with pkgs; [
      clang_18
      llvm_18
      SDL2
      cmake
      ninja
  ];
}

