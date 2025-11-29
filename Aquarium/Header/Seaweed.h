#pragma once
#include <glad/glad.h>

class Seaweed {
public:
    Seaweed();
    ~Seaweed();

    void Init(float x, float bottomY, float height, unsigned int texture);
    void Render(unsigned int shader);

private:
    unsigned int VAO;
    unsigned int tex;
    unsigned int MakeTexturedQuad(float* data);
};
