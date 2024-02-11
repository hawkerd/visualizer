#include "list.h"

//constructors and destructor
list::list() {
    //initializes list to default
    this->min = minDef;
    this->max = maxDef;
    this->len = lenDef;
    this->contents = nullptr;
    reset();
}

list::list(int len, int min, int max) {
    //initializes array according to given parameters

    this->contents = nullptr;
    this->len = len;
    this->min = min;
    this->max = max;

    reset();
}

list::~list() {
    delete[] this->contents;
}
// Copy constructor
list::list(const list& other) {
    len = other.len;
    min = other.min;
    max = other.max;
    contents = new int[len];
    std::copy(other.contents, other.contents + len, contents);
}

// Copy assignment operator
list& list::operator=(const list& other) {
    if (this != &other) {
        delete[] contents;
        len = other.len;
        min = other.min;
        max = other.max;
        contents = new int[len];
        std::copy(other.contents, other.contents + len, contents);
    }
    return *this;
}

//PRIVATE:
//utility functions
int list::random(int min, int max) {
    //returns a random number
    //static funtion
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min,max);
    int randomValue = distrib(gen);
    return randomValue;
}

void list::reset() {
    //regenerates the contents of the array
    delete[] contents;
    contents = new int[len];

    for (int i = 0; i < len; i++) {
        *(contents + i) = random(min,max);
    }
}
