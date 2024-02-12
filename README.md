# Visualizer

## Overview

This Visualizer is a C++ application designed to graphically represent various sorting algorithms. It leverages modern graphics libraries such as GLFW, GLEW, and OpenGL for rendering, along with ImGui for an interactive user interface. It uses SQLite to create a client side database to store preferences. This tool offers an intuitive and insightful way to understand and analyze the behavior of different sorting algorithms.

### Features

- **Graphical Rendering**: Utilizes OpenGL for high-performance graphics rendering.
- **Library Integration**: Incorporates GLFW for window management, GLEW for OpenGL function handling, and ImGui for the graphical user interface.
- **Database Integration**: Uses SQLite to manage user preferences, such as sorting speed and visual settings.
- **Modular Structure**: Well-organized codebase with separate directories for source files, object files, and executables.

## Installation and Execution

### Prerequisites
- GCC Compiler (with C++11 support)
- OpenGL installed on your system.

### Executino Instructions (MacOS)

- **Installing GLFW and GLEW**:
    ```bash
    brew install glfw glew
    ```
    or
    ```bash
    sudo port install glfw glew
    ```
- **Cloning Repository**:
    ```bash
    git clone https://github.com/hawkerd/visualizer.git
    ```
- **Execution**:
    ```bash
    cd visualizer
    make run
    ```