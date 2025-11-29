#include "Bubble.h"
#include <GLFW/glfw3.h>

Bubble::Bubble() : x(0), y(0), radius(0.02f), speed(0.005f), tex(0), VAO(0), active(false) {}

void Bubble::Init(GLuint texture, float startX, float startY, float r, float s) {
    tex = texture;
    x = startX;
    y = startY;
    radius = r;
    speed = s;
    active = true;
    MakeQuad();
}

void Bubble::Update(float topLimit) {
    if (!active) return;
    y += speed;
    if (y + radius >= topLimit) active = false;
}


void Bubble::Render(GLuint shader) {
    if (!active) return;

    float quad[] = {
        x - radius, y - radius, 0, 0,
        x + radius, y - radius, 1, 0,
        x + radius, y + radius, 1, 1,
        x - radius, y + radius, 0, 1
    };

    glUseProgram(shader);
    glBindTexture(GL_TEXTURE_2D, tex);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VAO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(quad), quad);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Bubble::MakeQuad() {
    float quad[] = {
        x - radius, y - radius, 0, 0,
        x + radius, y - radius, 1, 0,
        x + radius, y + radius, 1, 1,
        x - radius, y + radius, 0, 1
    };

    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}
