#include "renderer.h"

const std::vector<float> renderer::defaultColor = {1.0, 1.0, 1.0};

renderer::renderer() {
    //initializes everything and starts the rendering loop

    currentState = AppState::Menu;
    myList = list();
    myDatabase = database();
    myDatabase.init();
    myDatabase.readUserPreferences(1, delay, barColor);

    numElements = myList.len;
    //barColor = defaultColor;
    //delay = 0.0;
    
    
    initialize();
    render();
}

renderer::~renderer() {
    //cleanup

    glfwTerminate();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void renderer::initialize(){
    //function to initialize glfw, glew, and imgui

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
    io->IniFilename = "bin/imgui.ini";
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 120");
}


//Utility functions for rendering
void renderer::menu() {
    //Function to switch app state for proper rendering

    // ImGui frame start
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::BeginGroup();
    ImGui::Text("Available Algorithms:");
    if (ImGui::Button("Insertion Sort")) {
        currentState = AppState::InsertionSort;
    }
    if (ImGui::Button("Selection Sort")) {
        currentState = AppState::SelectionSort;
    }
    if (ImGui::Button("Bubble Sort")) {
        currentState = AppState::BubbleSort;
    }
    if (ImGui::Button("Merge Sort")) {
        currentState = AppState::MergeSort;
    }
    if (ImGui::Button("Quit")) {
        glfwSetWindowShouldClose(window, true);
    }
    ImGui::EndGroup();

    ImGui::SameLine();    
    ImGui::BeginGroup();

    ImGui::Text("Settings");
    ImGui::Text("Number of elements:");
    ImGui::SliderInt("##",&numElements, 1, 250);
    ImGui::Text("Bar Color:");
    ImGui::ColorEdit3("##color", barColor.data());
    ImGui::Text("Delay:");
    ImGui::SliderFloat("##delay", &delay, 0.0f, 0.5f, "%.3f seconds");
    if (ImGui::Button("Save Preferences")) {
        myList.len = numElements;
        myList.reset();
        myDatabase.writeUserPreferences(1, delay, barColor);
    }

    ImGui::EndGroup();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
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
            drawBar((-1 + i * barWidth), -1, barWidth, barHeight, barColor);
        }
    }
}
void renderer::insertionSort() {
    //variables for the algorithm
    myList.reset();
    int len = myList.len;
    int* contents = myList.contents;
    bool innerLoop = false;
    int i = 1;
    int j;
    int temp;
    
    //variabless for the visualizer
    bool paused = false;
    bool menu = false;
    double lastUpdateTime = 0;
    double currentTime;

    while (!glfwWindowShouldClose(window)) {
        if (menu) {
            return;
        }

        glClear(GL_COLOR_BUFFER_BIT);

        currentTime = glfwGetTime();

        //renders
        if (i >= len || paused) { //paused or completed
            drawList();
        } else if (currentTime - lastUpdateTime < delay) { //delayed
            drawList(j);
        } else { //proceed
            lastUpdateTime = currentTime;

            //draw list and perform one step
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
        }
        
    

        //IMGUI
        // ImGui frame start
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // ImGui Buttons
        ImGui::BeginGroup();
        ImGui::Text("Options:");
        if (ImGui::Button(paused ? "Resume" : "Stop")) {
            paused = !paused;
        }
        if (ImGui::Button("Reset")) {
            myList.reset();
            contents = myList.contents;
            i = 1;
            j = 0;
            innerLoop = false;
        }
        if (ImGui::Button("Menu")) {
            currentState = AppState::Menu;
            menu = true;
        }
        ImGui::EndGroup();
        ImGui::SameLine();    
        ImGui::BeginGroup();
        ImGui::Text("Settings");
        ImGui::Text("Bar Color:");
        ImGui::ColorEdit3("##color", barColor.data());
        ImGui::Text("Delay:");
        ImGui::SliderFloat("##delay", &delay, 0.0f, 0.5f, "%.3f seconds");
        ImGui::EndGroup();
        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
void renderer::selectionSort() {
    //variables for the algorithm
    myList.reset();
    int len = myList.len;
    int* contents = myList.contents;
    int min_index;
    int i = 0;
    int j;
    int temp;
    bool innerLoop = false;
    
    //variables for the visualizer
    bool paused = false;
    bool menu = false;
    double currentTime;
    double lastUpdateTime;

    while (!glfwWindowShouldClose(window)) {
        if(menu) {
            return;
        }
        glClear(GL_COLOR_BUFFER_BIT);


        //renders
        currentTime = glfwGetTime();
        if (i >= len || paused) { //paused
            drawList();
        } else if (currentTime - lastUpdateTime < delay) { //delayed
            drawList(j);
        } else { //proceed
            lastUpdateTime = currentTime;
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
        }

        //IMGUI
        // ImGui frame start
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // ImGui Buttons
        ImGui::BeginGroup();
        ImGui::Text("Options:");
        if (ImGui::Button(paused ? "Resume" : "Stop")) {
            paused = !paused;
        }
        if (ImGui::Button("Reset")) {
            myList.reset();
            contents = myList.contents;
            i = 0;
            innerLoop = false;
        }
        if (ImGui::Button("Menu")) {
            currentState = AppState::Menu;
            menu = true;
        }
        ImGui::EndGroup();
        ImGui::SameLine();    
        ImGui::BeginGroup();
        ImGui::Text("Settings");
        ImGui::Text("Bar Color:");
        ImGui::ColorEdit3("##color", barColor.data());
        ImGui::Text("Delay:");
        ImGui::SliderFloat("##delay", &delay, 0.0f, 0.5f, "%.3f seconds");
        ImGui::EndGroup();
        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
void renderer::bubbleSort() {
    //variables for the algorithm
    myList.reset();
    int len = myList.len;
    int* contents = myList.contents;
    int i = 0;
    int j = -1;
    int temp;
    bool innerLoop = false;
    bool swapped = false;
    
    //variables for the visualizer
    bool paused = false;
    bool menu = false;
    double currentTime;
    double lastUpdateTime;

    while (!glfwWindowShouldClose(window)) {
        if (menu) {
            return;
        }
        glClear(GL_COLOR_BUFFER_BIT);

        //renders
        currentTime = glfwGetTime();
        if (i >= len || paused) { //paused or completed
            drawList();
        } else if (currentTime - lastUpdateTime < delay){
            drawList(j);
        } else {
            lastUpdateTime = currentTime;
            //draws list and iterates once
            drawList(j);
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
        }
        
        //IMGUI
        // ImGui frame start
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // ImGui Buttons
        ImGui::BeginGroup();
        ImGui::Text("Options:");
        if (ImGui::Button(paused ? "Resume" : "Stop")) {
            paused = !paused;
        }
        if (ImGui::Button("Reset")) {
            myList.reset();
            contents = myList.contents;
            i = 0;
            j = -1;
            swapped = false;
            innerLoop = false;
        }
        if (ImGui::Button("Menu")) {
            currentState = AppState::Menu;
            menu = true;
        }
        ImGui::EndGroup();
        ImGui::SameLine();    
        ImGui::BeginGroup();
        ImGui::Text("Settings");
        ImGui::Text("Bar Color:");
        ImGui::ColorEdit3("##color", barColor.data());
        ImGui::Text("Delay:");
        ImGui::SliderFloat("##delay", &delay, 0.0f, 0.5f, "%.3f seconds");
        ImGui::EndGroup();
        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
void renderer::mergeSort() {}
//main render loop
void renderer::render() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        switch (currentState) {
            case AppState::Menu:
                menu();
                break;
            case AppState::InsertionSort:
                insertionSort();
                break;
            case AppState::SelectionSort:
                selectionSort();
                break;
            case AppState::BubbleSort:
                bubbleSort();
                break;
            case AppState::MergeSort:
                bubbleSort();
                break;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}