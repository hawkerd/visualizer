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

//PUBLIC:
//algorithm visualization functions
void list::insertionSort() {
    initializeOpenGL();
    visualizeInsertionSort();
    glfwTerminate();
    reset();
}

void list::selectionSort() {
    initializeOpenGL();
    visualizeSelectionSort();
    glfwTerminate();
    reset();
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


//visualization helper functions
//TODO:make visualize call the proper sorting algorithm visualizer by taking in a parameter that determines what algorithm is called
void list::initializeOpenGL() {
    //initializes glfw
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    //creates a windowed mode window and its opengl context
    window = glfwCreateWindow(1600,900,"Visualizer",NULL,NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    //make the window's context current
    glfwMakeContextCurrent(window);

    //initialize glew
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return;
    }

    //close the window
    //glfwTerminate();
}

void list::drawBar(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.2, 0.7);
    glVertex2f(x, y); //bottom left vertex
    glVertex2f(x + width, y); //bottom right
    glVertex2f(x + width, y + height); //top right
    glVertex2f(x, y + height); //top left
    glEnd();
}

void list::drawList() {
    float barHeight;
    float barWidth;

    barWidth = 2.0 / len;
    for (int i = 0; i < len; i++) {
        barHeight = (*(contents + i) / static_cast<float>(max)) * 2;
        drawBar((-1 + i * barWidth), -1, barWidth, barHeight);
    }
}

void list::visualizeInsertionSort() {
    //variables for the algorithm
    bool innerLoop = false;
    int i = 1;
    int j;
    int temp;
    
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        //keeps rendering the completed list
        if (i >= len) {
            drawList();
            glfwSwapBuffers(window);
            glfwPollEvents();
            continue;
        }
        
        drawList();

        if (!innerLoop) { //in the outer loop
            temp = contents[i];
            j = i - 1;
            innerLoop = true;
        } else { //in the outer loop
            if (j >=0 && contents[j] > temp) { //j still decrementing
                contents[j+1] = contents[j];
                j--;
            } else { //j done decrementing, time to swap in temp
                contents[j+1] = temp;
                i++;
                innerLoop = false;
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void list::visualizeSelectionSort() {
    int min_index;
    int i = 0;
    int j;
    int temp;
    bool innerLoop = false;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        //keeps rendering the completed list
        if (i >= len - 1) {
            drawList();
            glfwSwapBuffers(window);
            glfwPollEvents();
            continue;
        }

        drawList();

        if (!innerLoop) { //in the outer loop
            j = i + 1;
            innerLoop = true;
            min_index = i;
        } else { //in the inner loop
            if (j < len) { //j still iterating
                if (contents[j] < contents[min_index]) {
                    min_index = j;
                }
                j++;
            } else { //j done iterating, time to swap
                if (min_index != i) {
                    // swap
                    temp = contents[i];
                    contents[i] = contents[min_index];
                    contents[min_index] = temp;
                }
                i++;
                innerLoop = false;

            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

