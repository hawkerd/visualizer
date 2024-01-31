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
        
        //functions involved in visualize()
        void drawBar(float x, float y, float width, float height); //draws a bar
        void drawList(); //draws the list in its current state
        void reset();
        void visualizeInsertionSort(GLFWwindow* window);
        void visualize();

        //function to generate random number, used in the constructor
        static int random(int min, int max);
        
        
        //VARIABLES:
                
        //variables that charactarize the list
        int* contents;
        int min;
        int max;
        int len;
        static const int minDef = 0;
        static const int maxDef = 35;
        static const int lenDef = 20;;

    public:
        //FUNCTIONS:

        //constructors and destructor
        list();
        list(int len, int min, int max);
        ~list();

        //algorithm visualization
        void insertionSort();
};



#endif