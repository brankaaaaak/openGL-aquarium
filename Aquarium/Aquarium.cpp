#include <iostream>
#include <thread>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Util.h"


unsigned int MakeTexturedQuad(float* data)
{
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

unsigned int MakeQuadVAO(float* data)
{
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


int main()
{
    glfwInit();

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    int screenWidth = mode->width;
    int screenHeight = mode->height;

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Akvarijum", monitor, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD failed" << std::endl;
        return -1;
    }

    unsigned int texShader = LoadShaderProgram("shaders/tex.vert", "shaders/tex.frag");
    unsigned int colorShader = LoadShaderProgram("shaders/color.vert", "shaders/color.frag");

    unsigned int bgTex = LoadTexture("resources/background.jpg");
    unsigned int sandTex = LoadTexture("resources/sand.png");

    float bgQuad[] = {
        -1, -1,  0, 0,
         1, -1,  1, 0,
         1,  1,  1, 1,
        -1,  1,  0, 1
    };

    unsigned int VAO_bg = MakeTexturedQuad(bgQuad);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // AQUARIUM
    float left = -1.0f;
    float right = 1.0f;
    float bottom = -1.0f;

    float ratio = 0.60f;  // 60%
    float top = -1.0f + 2.0f * ratio;

    float borderPx = 10.0f;
    float thX = 2.0f * borderPx / screenWidth;
    float thY = 2.0f * borderPx / screenHeight;

    // WHITE TRANSPARENT
    float fill[] = {
        left,  bottom,  0.85f, 0.90f, 1.0f, 0.2f,
        right, bottom,  0.85f, 0.90f, 1.0f, 0.2f,
        right, top,     0.85f, 0.90f, 1.0f, 0.2f,
        left,  top,     0.85f, 0.90f, 1.0f, 0.2f
    };
    unsigned int VAO_fill = MakeQuadVAO(fill);

    // SAND
    float sandHeight = 0.45f;

    float sandQuad[] = {
        left,  bottom,              0, 0,
        right, bottom,              1, 0,
        right, bottom + sandHeight, 1, 1,
        left,  bottom + sandHeight, 0, 1
    };

    unsigned int VAO_sand = MakeTexturedQuad(sandQuad);

    // BORDERS  
    float bottomB[] = {
        left, bottom,        0,0,0,1,
        right, bottom,       0,0,0,1,
        right, bottom + thY,   0,0,0,1,
        left,  bottom + thY,   0,0,0,1
    };
    unsigned int VAO_bottom = MakeQuadVAO(bottomB);

    float leftB[] = {
        left, bottom,       0,0,0,1,
        left + thX, bottom,   0,0,0,1,
        left + thX, top,      0,0,0,1,
        left, top,          0,0,0,1
    };
    unsigned int VAO_leftB = MakeQuadVAO(leftB);

    float rightB[] = {
        right - thX, bottom,  0,0,0,1,
        right, bottom,      0,0,0,1,
        right, top,         0,0,0,1,
        right - thX, top,     0,0,0,1
    };
    unsigned int VAO_rightB = MakeQuadVAO(rightB);


    double frameTime = 1.0 / 75.0;

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        double start = glfwGetTime();

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

        // WHITE 
        glUseProgram(colorShader);
        glBindVertexArray(VAO_fill);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // BORDERS
        glBindVertexArray(VAO_leftB);   glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glBindVertexArray(VAO_rightB);  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glBindVertexArray(VAO_bottom);  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();

        double elapsed = glfwGetTime() - start;
        if (elapsed < frameTime)
            std::this_thread::sleep_for(std::chrono::duration<double>(frameTime - elapsed));
    }

    glfwTerminate();
    return 0;
}
