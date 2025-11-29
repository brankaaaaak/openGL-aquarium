#include "Chest.h"
#include <glad/glad.h>

Chest::Chest() : VAO(0), VBO(0), state(0) {}

Chest::~Chest() {
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
}

void Chest::Init(unsigned int tex[5]) {
    for (int i = 0; i < 5; ++i) {
        textures[i] = tex[i];
    }

    float chestX = 0.6f;
    float chestY = -0.85f; 
    float chestWidth = 0.2f;
    float chestHeight = 0.2f;

    float chestQuad[] = {
        chestX, chestY, 0.0f, 0.0f,                 // bottom-left
        chestX + chestWidth, chestY, 1.0f, 0.0f,   // bottom-right
        chestX + chestWidth, chestY + chestHeight, 1.0f, 1.0f, // top-right
        chestX, chestY + chestHeight, 0.0f, 1.0f   // top-left
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(chestQuad), chestQuad, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Chest::Update(bool opening) {
    if (opening && state < 4) {
        state++;
    }
    else if (!opening && state > 0) {
        state--;
    }
}

void Chest::Render(unsigned int shader) {
    glUseProgram(shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[state]);
    glUniform1i(glGetUniformLocation(shader, "uTex"), 0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}
