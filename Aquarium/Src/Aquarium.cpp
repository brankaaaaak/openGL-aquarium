#include <iostream>
#include <thread>
#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Util.h"
#include "Chest.h"
#include "Seaweed.h"

unsigned int MakeTexturedQuad(float* data) {
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return VAO;
}

unsigned int MakeQuadVAO(float* data) {
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return VAO;
}

int main() {

    glfwInit();
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    int screenWidth = mode->width;
    int screenHeight = mode->height;

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Aquarium", monitor, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD failed" << std::endl;
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // load
    unsigned int texShader = LoadShaderProgram("Shader/tex.vert", "Shader/tex.frag");
    unsigned int colorShader = LoadShaderProgram("Shader/color.vert", "Shader/color.frag");

    unsigned int bgTex = LoadTexture("Resources/background.jpg");
    unsigned int sandTex = LoadTexture("Resources/sand.png");
    unsigned int seaweedTex1 = LoadTexture("Resources/seaweed.png");
    unsigned int seaweedTex2 = LoadTexture("Resources/seaweed2.png");

    unsigned int chestTex[5];
    chestTex[0] = LoadTexture("Resources/chest1.png");
    chestTex[1] = LoadTexture("Resources/chest2.png");
    chestTex[2] = LoadTexture("Resources/chest3.png");
    chestTex[3] = LoadTexture("Resources/chest4.png");
    chestTex[4] = LoadTexture("Resources/chest5.png");

    // set up aquarium
    float bgQuad[] = {
        -1, -1, 0, 0,
         1, -1, 1, 0,
         1,  1, 1, 1,
        -1,  1, 0, 1
    };
    unsigned int VAO_bg = MakeTexturedQuad(bgQuad);

    float left = -1.0f;
    float right = 1.0f;
    float bottom = -1.0f;
    float ratio = 0.60f;
    float top = -1.0f + 2.0f * ratio;
    float borderPx = 10.0f;
    float thX = 2.0f * borderPx / screenWidth;
    float thY = 2.0f * borderPx / screenHeight;

    // WHITE TRANSPARENT
    float fill[] = {
        left, bottom, 0.85f, 0.90f, 1.0f, 0.2f,
        right, bottom, 0.85f, 0.90f, 1.0f, 0.2f,
        right, top, 0.85f, 0.90f, 1.0f, 0.2f,
        left, top, 0.85f, 0.90f, 1.0f, 0.2f
    };
    unsigned int VAO_fill = MakeQuadVAO(fill);

    // SAND
    float sandHeight = 0.45f;
    float sandQuad[] = {
        left, bottom, 0, 0,
        right, bottom, 1, 0,
        right, bottom + sandHeight, 1, 1,
        left, bottom + sandHeight, 0, 1
    };
    unsigned int VAO_sand = MakeTexturedQuad(sandQuad);

    // BORDERS
    float bottomB[] = { left, bottom, 0,0,0,1, right, bottom, 0,0,0,1, right, bottom + thY, 0,0,0,1, left, bottom + thY, 0,0,0,1 };
    float leftB[] = { left, bottom, 0,0,0,1, left + thX, bottom, 0,0,0,1, left + thX, top, 0,0,0,1, left, top, 0,0,0,1 };
    float rightB[] = { right - thX, bottom, 0,0,0,1, right, bottom, 0,0,0,1, right, top, 0,0,0,1, right - thX, top, 0,0,0,1 };
    unsigned int VAO_bottom = MakeQuadVAO(bottomB);
    unsigned int VAO_leftB = MakeQuadVAO(leftB);
    unsigned int VAO_rightB = MakeQuadVAO(rightB);

    // chest
    Chest chest;
    chest.Init(chestTex);

    //seaweed
    Seaweed seaweed1, seaweed2;
    seaweed1.Init(-0.85f, -1.0f + sandHeight * 0.1f, 0.4f, seaweedTex1);
    seaweed2.Init(0.45f, -1.0f + sandHeight * 0.1f, 0.35f, seaweedTex2);

    bool chestOpening = false;
    bool keyCPressed = false;

    double frameTime = 1.0 / 75.0;

    // loop
    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        double start = glfwGetTime();

        // chest opening
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !keyCPressed) {
            keyCPressed = true;
            chestOpening = !chestOpening;
        }
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
            keyCPressed = false;

        chest.Update(chestOpening);

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        // BACKGROUND
        glUseProgram(texShader);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, bgTex);
        glUniform1i(glGetUniformLocation(texShader, "uTex"), 0);
        glBindVertexArray(VAO_bg);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // SAND
        glBindTexture(GL_TEXTURE_2D, sandTex);
        glBindVertexArray(VAO_sand);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // SEAWEED
        seaweed1.Render(texShader);
        seaweed2.Render(texShader);

        // CHEST
        chest.Render(texShader);

        // WHITE TRANSPARENT
        glUseProgram(colorShader);
        glBindVertexArray(VAO_fill);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // BORDERS
        glBindVertexArray(VAO_leftB); glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glBindVertexArray(VAO_rightB); glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glBindVertexArray(VAO_bottom); glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();

        double elapsed = glfwGetTime() - start;
        if (elapsed < frameTime)
            std::this_thread::sleep_for(std::chrono::duration<double>(frameTime - elapsed));
    }

    glfwTerminate();
    return 0;
}
