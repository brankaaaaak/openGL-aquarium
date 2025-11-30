#pragma once
#include <glad/glad.h>

class FoodParticle {
public:
    float x, y;
    float width, height;
    float vy;       // brzina 
    bool active;
    GLuint tex;
    unsigned int VAO;

    FoodParticle();
    void Init(GLuint texture, float startX, float startY, float w = 0.02f, float h = 0.02f);
    void Update(float waterLevel, float sandLevel);
    void Render(GLuint shader);
};