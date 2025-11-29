#pragma once
#include <glad/glad.h>

class Chest {
public:
    Chest();
    ~Chest();

    void Init(unsigned int textures[5]);

    void Update(bool opening);

    void Render(unsigned int shader);

private:
    unsigned int VAO, VBO;
    unsigned int textures[5]; 
    int state;                
};
