#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Goldfish {
public:
    float x, y;
    float width, height;
    float speed;
    GLuint tex;
    unsigned int VAO;

    Goldfish();
    void Init(GLuint texture, float startX, float startY, float w = 0.1f, float h = 0.1f);
    void Update(GLFWwindow* window);  
    void Render(GLuint shader);
private:
    void MakeQuad();
};
