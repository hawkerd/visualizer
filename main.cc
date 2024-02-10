#include "list.h"

int main() {
    int input = 1;

    list myList;
    
    std::cout << "Welcome! This program offers visualization for different algorithms\n";
    std::cout << "Input a number corresponding to an algorithm, or 0 to quit\n";
    
    while (input != 0) {
        std::cout << "-------Menu-------\n";
        std::cout << "0. Quit\n";
        std::cout << "1. Insertion Sort\n";
        std::cout << "2. Selection Sort\n";
        std::cout << "3. Bubble Sort\n";
        std::cout << "------------------\n";

        std:: cin >> input;

        if(input == 0 || input < 0 || input > 3) {
            break;
        } else {
            myList.visualize(input);
        }
    }
}