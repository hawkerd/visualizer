#include <string>
#include <vector>
#include <iostream>
#include <random>
#include "dependencies/include/GL/glew.h"
#include "dependencies/include/GLFW/glfw3.h"



#ifndef LIST_H
#define LIST_H

class list {
    private:
        //FUNCTIONS:
        
        //functions involved in algorithm visualization
        void drawBar(float x, float y, float width, float height, const std::vector<float>& color); //draws a bar of the specified color, or in white
        void drawList(int elementBeingSorted); //draws the list in its current state
        void visualizeInsertionSort();
        void visualizeSelectionSort();
        void visualizeBubbleSort();
        void initializeOpenGL();

        //utility functions
        static int random(int min, int max);
        void reset();
        
        
        //VARIABLES:
                
        //variables that charactarize the list
        int* contents;
        int min;
        int max;
        int len;
        static const int minDef = 0;
        static const int maxDef = 35;
        static const int lenDef = 40;

        //variables necessary for rendering
        GLFWwindow* window;
        const static std::vector<float> defaultColor;
        //FT_Library ft;
        //FT_Face face;

        public:
            //constructors and destructor
            list();
            list(int len, int min, int max);
            ~list();

            //algorithm visualization
            void visualize(int input);
};



#endif