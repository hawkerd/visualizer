# Visualizer

## Overview

The Visualizer is a C++ application designed to graphically represent various sorting algorithms. It utilizes modern graphics libraries such as GLFW, GLEW, and OpenGL for rendering, and ImGui for an interactive user interface. This tool offers an intuitive and interactive way to understand and analyze the behavior of different sorting algorithms.

## Features

- **Graphical Rendering**: High-performance graphics rendering using OpenGL.
- **Library Integration**: GLFW for window management, GLEW for OpenGL function handling, and ImGui for graphical user interface.
- **Dynamic Visualization**: Capable of visualizing various data types.
- **Modular Structure**: Well-organized codebase with separate directories for source files, object files, and executables.

## Prerequisites

To run this project (not on MacOS), you need:

- GCC Compiler (with C++11 support)

## Running the Project

### For macOS Users

- **Pre-compiled Binary**: 
  - If you are on macOS, you can download the pre-compiled binary from the [Releases](https://github.com/hawkerd/visualizer/releases) section of the GitHub repository.
  - Simply download the binary and run it on your macOS system.

### For Other Systems

- **Compiling from Source**:
  1. **Clone the Repository**: Obtain a copy of the source code from the project's GitHub repository.
     ```
     git clone https://github.com/hawkerd/visualizer.git
     ```
  2. **Build and Run the Project**:
     - Navigate to the root directory of the project.
     - Run the following command:
       ```
       make run
       ```
