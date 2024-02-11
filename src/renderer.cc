#include "renderer.h"

const std::vector<float> renderer::defaultColor = {1.0, 1.0, 1.0};

renderer::renderer() {
    initialize();
    myList = list();
}

renderer::~renderer() {
    glfwTerminate();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void renderer::initialize(){
    //initializes glfw
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    //creates a windowed mode window and its opengl context
    window = glfwCreateWindow(1600,900,"Visualizer",NULL,NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    //make the window's context current
    glfwMakeContextCurrent(window);

    //initialize glew
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLEW");;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

//Utility functions for the visualizers
void renderer::drawBar(float x, float y, float width, float height, const std::vector<float>& color = defaultColor) {
    glBegin(GL_QUADS);
    glColor3f(color[0], color[1], color[2]);
    glVertex2f(x, y); //bottom left vertex
    glVertex2f(x + width, y); //bottom right
    glVertex2f(x + width, y + height); //top right
    glVertex2f(x, y + height); //top left
    glEnd();
}
void renderer::drawList(int elementBeingSorted = -1) {
    int len = myList.len;
    int* contents = myList.contents;
    int max = myList.max;

    float barHeight;
    float barWidth;

    barWidth = 2.0 / len;

    for (int i = 0; i < len; i++) {
        barHeight = (*(contents + i) / static_cast<float>(max)) * 2;
        if (i == elementBeingSorted) {
            drawBar((-1 + i * barWidth), -1, barWidth, barHeight, {0.0, 1.0, 0.0});
        } else {
            drawBar((-1 + i * barWidth), -1, barWidth, barHeight);
        }
    }
}

//Visualizes different sorting algorithms
void renderer::visualizeInsertionSort() {
    int len = myList.len;
    int* contents = myList.contents;

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
        
        drawList(j);

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
void renderer::visualizeSelectionSort() {
    int len = myList.len;
    int* contents = myList.contents;

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

        drawList(j);

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
void renderer::visualizeBubbleSort() {
    int len = myList.len;
    int* contents = myList.contents;
    int i = 0;
    int j;
    int temp;
    bool innerLoop = false;
    bool swapped;

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
            j = 0;
            innerLoop = true;
            swapped = false;
        } else { //in the inner loop
            if (j < len - i - 1) { //j still iterating
                if (contents[j] > contents[j+1]) {
                    int temp = contents[j];
                    contents[j] = contents[j+1];
                    contents[j+1] = temp;
                    swapped = true;
                }
                j++;
            } else { //j done iterating, increase i and check swapped
                i++;
                innerLoop = false;
                if (swapped == false) {
                    i = len;
                }

            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}