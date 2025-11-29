#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>
#include "Aquarium.h"

int main() {
    glfwInit();
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    int screenWidth = mode->width;
    int screenHeight = mode->height;

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Aquarium", monitor, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Aquarium aquarium(screenWidth, screenHeight);
    aquarium.Init();

    bool chestOpening = false;
    bool keyCPressed = false;
    double frameTime = 1.0 / 75.0;

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        //C
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !keyCPressed) {
            keyCPressed = true;
            chestOpening = !chestOpening;
        }
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
            keyCPressed = false;

        aquarium.Update(chestOpening, window);

        glClear(GL_COLOR_BUFFER_BIT);
        aquarium.Render();

        glfwSwapBuffers(window);
        glfwPollEvents();

        std::this_thread::sleep_for(std::chrono::duration<double>(frameTime));
    }

    glfwTerminate();
    return 0;
}
