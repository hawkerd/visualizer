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
        //functions involved in visualize()
        void drawBar(float x, float y, float width, float height);
        void drawList();
        
        //list
        int* contents;
        
        //function to generate random number, used in the constructor
        static int random(int lower, int upper);
        
        //variables that characterize the list
        static const int lowerDefault = 0;
        static const int upperDefault = 35;
        static const int lengthDefault = 20;;
        int min;
        int max;
        int length;

    public:
        //constructors and destructor
        list();
        list(int length, int maxVal, int minVal);
        ~list();

        void reset();
        void view();

        void insertionSortVisualizeConsole();

        void visualize();
};



#endif