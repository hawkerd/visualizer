#include "list.h"
#include "renderer.h"

int main() {
    renderer* myRenderer;
    int input = 1;
    
    std::cout << "--------------------------------------------------------------------\n";
    std::cout << "Welcome! This program offers visualization for different algorithms.\n";
    std::cout << "Input a number corresponding to an algorithm, or 0 to quit.\n";
    
    
    while (input != 0) {
        myRenderer = new renderer();
        std::cout << "-------Menu-------\n";
        std::cout << "0. Quit\n";
        std::cout << "1. Insertion Sort\n";
        std::cout << "2. Selection Sort\n";
        std::cout << "3. Bubble Sort\n";
        std::cout << "------------------\n";

        std:: cin >> input;

        if(input == 0) {
            std::cout << "Goodbye!\n";
        } else if (input == 1) {
            myRenderer->visualizeInsertionSort();
        } else if (input == 2) {
            myRenderer->visualizeSelectionSort();
        } else if (input == 3) {
            myRenderer->visualizeBubbleSort();
        } else {
            std::cout << "Invalid input. Please try again.\n";
        }
        delete myRenderer;
    }
    return 0;
}