#include "Seaweed.h"
#include <glad/glad.h>

Seaweed::Seaweed() : VAO(0), tex(0) {}
Seaweed::~Seaweed() {
    glDeleteVertexArrays(1, &VAO);
}

void Seaweed::Init(float x, float bottomY, float height, unsigned int texture) {
    tex = texture;
    float quad[] = {
        x - 0.1f, bottomY, 0,0,
        x + 0.1f, bottomY, 1,0,
        x + 0.1f, bottomY + height, 1,1,
        x - 0.1f, bottomY + height, 0,1
    };
    VAO = MakeTexturedQuad(quad);
}

void Seaweed::Render(unsigned int shader) {
    glUseProgram(shader);
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, tex);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

unsigned int Seaweed::MakeTexturedQuad(float* data) {
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
