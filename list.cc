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

void list::visualize() {
    //initializes glfw
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    //creates a windowed mode window and its opengl context
    GLFWwindow* window = glfwCreateWindow(1600,900,"Visualizer",NULL,NULL);
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


    //loop until the window is closed
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        //render here!

        drawList();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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
    float xpos;

    barWidth = 2.0 / this->length;
    for (int i = 0; i < this->length; i++) {
        barHeight = (*(this->contents + i) / static_cast<float>(this->max)) * 2;
        xpos = (i * barWidth) - 1;
        this->drawBar(xpos, -1, barWidth, barHeight);
    }
}