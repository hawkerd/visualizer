# Visualizer

## Overview

This Visualizer is a C++ application designed to graphically represent various sorting algorithms. Leveraging modern graphics libraries such as GLFW, GLEW, and OpenGL for rendering, along with ImGui for an interactive user interface, this tool offers an intuitive and insightful way to understand and analyze the behavior of different sorting algorithms.

## Features

- **Graphical Rendering**: Utilizes OpenGL for high-performance graphics rendering.
- **Library Integration**: Incorporates GLFW for window management, GLEW for OpenGL function handling, and ImGui for the graphical user interface.
- **Modular Structure**: Well-organized codebase with separate directories for source files, object files, and executables.

## Prerequisites

To build and run this project, you will need:

- GCC Compiler (with C++11 support)
- GLFW, GLEW, and OpenGL installed on your system.

### Installation Instructions

- **GLFW and GLEW**:
  - For macOS:
    ```bash
    brew install glfw glew
    ```
  - For Ubuntu/Debian:
    ```bash
    sudo apt-get install libglfw3 libglfw3-dev libglew-dev
    ```
- **OpenGL**: Usually comes pre-installed with the operating system. If not, install it using your system's package manager.

## Running the Project

- **Compiling from Source**:
  1. **Clone the Repository**:
     ```
     git clone https://github.com/hawkerd/visualizer.git
     ```
  2. **Build and Run the Project**:
     - Navigate to the root directory of the project.
     - Execute the following command:
       ```
       make run
       ```

