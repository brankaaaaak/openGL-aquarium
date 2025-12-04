#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Chest {
public:
    Chest();
    ~Chest();

    void Init(unsigned int textures[2]);

    void Update(GLFWwindow* window);

    void Render(unsigned int shader);

private:
    unsigned int VAO, VBO;
    unsigned int textures[2]; 
    int state;        
    bool opening;        
    bool keyCPressedLastFrame;
};
