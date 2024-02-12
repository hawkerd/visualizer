#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "list.h"
#include "database.h"

#ifndef RENDERER_H
#define RENDERER_H

enum class AppState {
    Menu,
    InsertionSort,
    SelectionSort,
    BubbleSort,
    MergeSort
};

class renderer {
    public:
        //FUNCTIONS:
        
        //constructor and destructor
        renderer();
        ~renderer();

        //main rendering loop
        void render();
        
    private:
        //FUNCTIONS:

        //initialization functions
        void initialize();
        
        //visualizer functions
        void menu();
        void insertionSort();
        void selectionSort();
        void bubbleSort();
        void mergeSort();
        void drawBar(float x, float y, float width, float height, const std::vector<float>& color);
        void drawList(int elementBeingSorted);

        //VARIABLES
        list myList;
        database myDatabase;
        GLFWwindow* window;
        const static std::vector<float> defaultColor;
        ImGuiIO* io;
        AppState currentState;

        //render settings
        int numElements;
        std::vector<float> barColor;
        float delay;
};

#endif