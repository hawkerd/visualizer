#include <string>
#include <vector>
#include <iostream>
#include <random>

#ifndef LIST_H
#define LIST_H

class list {
    private:
        int* contents;
        
        static int random(int lower, int upper);
        static const int lowerDefault = 0;
        static const int upperDefault = 35;
        static const int lengthDefault = 20;;
        
        int min;
        int max;
        int length;

    public:
        list();
        list(int length, int maxVal, int minVal);
        ~list();

        void reset();
        void view();

        void insertionSortVisualizeConsole();
};



#endif