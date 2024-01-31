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
    this->visualize();
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
void list::visualize() {
    //initializes glfw
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    //creates a windowed mode window and its opengl context
    GLFWwindow* window = glfwCreateWindow(720,400,"Visualizer",NULL,NULL);
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


    //render something here!
    visualizeInsertionSort(window);
    reset();

    //close the window
    glfwTerminate();
}

void list::drawBar(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
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

void list::visualizeInsertionSort(GLFWwindow* window) {
    //variables for the algorithm
    bool isSorting = false;
    int i = 1;
    int j;
    int temp;
    
    //variables for delay
    double lastUpdateTime = glfwGetTime();
    double currentTime;
    double delay = 0.1;


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        drawList();

        currentTime = glfwGetTime();
        if (currentTime - lastUpdateTime > delay) {
            lastUpdateTime = currentTime;
            
            //start or continue one iteration of the outer loop
            if (!isSorting && i < len) {
                temp = contents[i];
                j = i - 1;
                isSorting = true;
            }

            //perform one step of insertion sort
            if (isSorting) {
                if (j >=0 && contents[j] > temp) {
                    contents[j+1] = contents[j];
                    j--;
                    drawList();
                } else {
                    contents[j+1] = temp;
                    drawList();
                    i++;
                    isSorting = false;
                }
            }
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}