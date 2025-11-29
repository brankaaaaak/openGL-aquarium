#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Bubble.h"
#include <vector>

class Nemo {
public:
    float x, y;
    float width, height;
    float speed;
    GLuint tex;
    unsigned int VAO;
    bool facingRight;
    std::vector<Bubble> bubbles;  
    GLuint bubbleTex;
    bool zPressedLastFrame;

    Nemo();
    void Init(GLuint texture, float startX, float startY, float w = 0.1f, float h = 0.1f);
    void Update(GLFWwindow* window);  
    void Render(GLuint shader);
private:
    void MakeQuad();
};
