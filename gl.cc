#include "gl.h"

void test() {
    //initializes glfw
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    //creates a windowed mode window and its opengl context
    GLFWwindow* window = glfwCreateWindow(640,480,"Simple Window",NULL,NULL);
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

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //close the window
    glfwTerminate();
}