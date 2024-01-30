#include "list.h"
#include "gl.h"

int main() {
    list myList(11,1,15);
    myList.view();
    myList.insertionSortVisualizeConsole();
    myList.view();
    return 0;
}