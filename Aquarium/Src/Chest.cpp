#include "Chest.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Chest::Chest() : VAO(0), texArray(nullptr), state(0), lastUpdateTime(0) {}

Chest::~Chest() {
    glDeleteVertexArrays(1, &VAO);
}

void Chest::Init(unsigned int* textures) {
    texArray = textures;
    float chestX = 0.6f;
    float chestY = -1.0f + 0.45f * 0.2f; 
    float chestWidth = 0.2f;
    float chestHeight = 0.15f;
    float chestQuad[] = {
        chestX, chestY, 0,0,
        chestX + chestWidth, chestY, 1,0,
        chestX + chestWidth, chestY + chestHeight, 1,1,
        chestX, chestY + chestHeight, 0,1
    };
    VAO = MakeTexturedQuad(chestQuad);
}

void Chest::Update(bool opening) {
    double currentTime = glfwGetTime();
    if (currentTime - lastUpdateTime < 0.066) return; 
    lastUpdateTime = currentTime;

    if (opening && state < 4) state++;
    else if (!opening && state > 0) state--;
}

void Chest::Render(unsigned int shader) {
    glUseProgram(shader);
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, texArray[state]);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

unsigned int Chest::MakeTexturedQuad(float* data) {
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
