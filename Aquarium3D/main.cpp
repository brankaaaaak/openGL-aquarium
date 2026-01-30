#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLM zaglavlja
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

// FPS limiter (75 FPS po zadatku)
const double targetFPS = 75.0;
const double timePerFrame = 1.0 / targetFPS;

int main() {
    // 1. Inicijalizacija GLFW
    if (!glfwInit()) return -1;

    // 2. Fullscreen mod po zadatku
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "3D Aquarium", monitor, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // 3. Omogući Depth Test (Obavezno za 3D!)
    glEnable(GL_DEPTH_TEST);
    // Omogući providnost (za staklo i mehuriće)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window)) {
        double startTime = glfwGetTime();

        // Izlaz na ESC
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Brišemo i depth buffer!

        // Ovde će ići Render kod...

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Frame limiter
        while (glfwGetTime() - startTime < timePerFrame);
    }

    glfwTerminate();
    return 0;
}