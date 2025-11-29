#pragma once
#include <glad/glad.h>

class Bubble {
public:
    float x, y;
    float radius;
    float speed;
    GLuint tex;
    unsigned int VAO;
    bool active;

    Bubble();
    void Init(GLuint texture, float startX, float startY, float r = 0.02f, float s = 0.005f);
    void Update(float topLimit);
    void Render(GLuint shader);

private:
    void MakeQuad();
};
