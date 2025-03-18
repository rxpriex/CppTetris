# Tetris

A classic Tetris game implemented in C++ using SDL2 for graphics and input handling. This project is built with CMake and targets the MinGW toolchain, making it compatible with Windows via MSYS2.

## Features
- Classic Tetris gameplay: Move, rotate, and drop tetrominoes to clear lines.
- Score tracking and increasing difficulty as the game progresses.
- Smooth graphics and input handling powered by SDL2.
- Cross-platform build system using CMake.

## Prerequisites
Before building the project, ensure you have the following installed:
- **MSYS2**: A modern Unix-like environment for Windows. [Download here](https://www.msys2.org/).
- **MinGW Toolchain**: Provides the compiler and tools for building.
- **CMake**: Build system for generating makefiles.
- **SDL2**: Graphics library for rendering the game.
- **Git**: For cloning the repository (optional).

## Installation
Follow these steps to set up your environment and build the Tetris project.

### 1. Install MSYS2 and MinGW Toolchain
- Download and install MSYS2 from the official website.
- Update MSYS2 and install the MinGW toolchain, CMake, and Make:
  ```bash
  pacman -Syu
  pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-cmake