#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef LIST_H
#define LIST_H

class list {
    private:
        //FUNCTIONS:
        
        //functions involved in algorithm visualization
        void drawBar(float x, float y, float width, float height); //draws a bar
        void drawList(); //draws the list in its current state
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

    public:
        //constructors and destructor
        list();
        list(int len, int min, int max);
        ~list();

        //algorithm visualization
        void visualize(int input);
};



#endif