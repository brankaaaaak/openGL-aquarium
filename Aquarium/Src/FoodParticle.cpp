#include "FoodParticle.h"

FoodParticle::FoodParticle() : x(0), y(0), width(0.02f), height(0.02f), vy(-0.0005f),
active(true), tex(0), VAO(0) {
}

void FoodParticle::Init(GLuint texture, float startX, float startY, float w, float h) {
    tex = texture;
    x = startX;
    y = startY;
    width = w;
    height = h;

    float quad[] = {
        x - width, y - height, 0,0,
        x + width, y - height, 1,0,
        x + width, y + height, 1,1,
        x - width, y + height, 0,1
    };

    GLuint VBO;
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
void FoodParticle::Update(float waterLevel, float sandLevel) {
    if (!active) return;

    if (y > waterLevel)
        vy -= 0.01f;
    else
        vy = -0.002f;   

    y += vy;

    float sandOffset = 0.06f;
    float sandSurface = sandLevel + sandOffset;


    if (y - height <= sandSurface) {
        y = sandSurface + height; 
        vy = 0;
    }
}

void FoodParticle::Render(GLuint shader) {
    if (!active) return;

    float quad[] = {
        x - width, y - height, 0,0,
        x + width, y - height, 1,0,
        x + width, y + height, 1,1,
        x - width, y + height, 0,1
    };

    glUseProgram(shader);
    glBindTexture(GL_TEXTURE_2D, tex);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VAO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(quad), quad);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
