#include <string>
#include <vector>
#include <iostream>
#include <random>

#ifndef LIST_H
#define LIST_H

class list {
    private:
        //utility
        static int random(int min, int max);

        static const int minDef = 0;
        static const int maxDef = 35;
        static const int lenDef = 40;

    public:
        //constructors and destructor
        list();
        list(int len, int min, int max);
        ~list();
        list(const list& other);
        list& operator=(const list& other);

        void reset();

        //variables
        int* contents;
        int min;
        int max;
        int len;
        
        //algorithm visualization
        void visualize(int input);
};



#endif