#include "list.h"

int main() {
    list myList(11,1,15);
    myList.view();
    myList.reset();
    myList.view();
    return 0;
}