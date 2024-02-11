#include <vector>
#include <iostream>
#include "../dependencies/include/GL/glew.h"
#include "../dependencies/include/GLFW/glfw3.h"
//#include "../dependencies/imgui/imgui.h"
//#include "../dependencies/imgui/imgui_impl_glfw.h"
//#include "../dependencies/imgui/imgui_impl_opengl3.h"
#include "list.h"

#ifndef RENDERER_H
#define RENDERER_H

class renderer {
    public:
        //FUNCTIONS:
        
        //constructor and destructor
        renderer();
        ~renderer();

        //visualizers
        void visualizeInsertionSort();
        void visualizeSelectionSort();
        void visualizeBubbleSort();
        
    private:
        //FUNCTIONS:
        void initialize();

        void drawBar(float x, float y, float width, float height, const std::vector<float>& color);
        void drawList(int elementBeingSorted);

        //VARIABLES
        list myList;
        GLFWwindow* window;
        const static std::vector<float> defaultColor;
        //ImGuiIO* io;
};

#endif