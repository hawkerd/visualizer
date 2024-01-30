#include "list.h"

int list::random(int lower, int upper) {
    //returns a random number
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(lower,upper);
    int randomValue = distrib(gen);
    return randomValue;
}

list::list() {
    //initializes list to default
    
    this->min = lowerDefault;
    this->max = upperDefault;
    this->length = lengthDefault;
    this->contents = nullptr;
    
    this->reset();
}

list::list(int length, int minVal, int maxVal) {
    //initializes array according to given parameters

    this->contents = nullptr;
    this->length = length;
    this->min = minVal;
    this->max = maxVal;

    this->reset();
}

list::~list() {
    delete[] this->contents;
}

void list::reset() {
    //regenerates the contents of the array
    delete[] this->contents;
    this->contents = new int[this->length];

    for (int i = 0; i < length; i++) {
        *(this->contents + i) = random(this->min,this->max);
    }
}

void list::view() {
    int i;
    for (int i = 0; i < this->length; i++) {
        std::cout << *(this->contents + i) << ' ';
    }
    std::cout << std::endl;
}

void list::insertionSortVisualizeConsole() {
    int temp;
    int i;
    int j;
    int* p = this->contents;

    std::cout << "Starting insertion sort on the list:\n";
    std::cout << "Element 0 is already in place\n";
    this->view();

    for (int i = 1; i < this->length; i++) {
        std::cout << "Placing element: " << i << std::endl;
        temp = *(p + i);
        j = i - 1;
        this->view();
        while (j >= 0 && *(p + j) > temp) {
            *(p + j + 1) = *(p + j);
            j -= 1;
            this->view();
        }
        *(p + j + 1) = temp;
        this->view();
        std::cout << "Placed element: " << i << std::endl;
        std::cout << "The first " << i+1 << " element(s) are sorted\n";

    }

    std::cout << "Done!";
}