#include "Nemo.h"

Nemo::Nemo() : x(0), y(0), width(0.1f), height(0.1f), speed(0.01f), tex(0), VAO(0) {}

void Nemo::Init(GLuint texture, float startX, float startY, float w, float h) {
    tex = texture;
    x = startX;
    y = startY;
    width = w;
    height = h;
    MakeQuad();
}

void Nemo::Update(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) y += speed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) y -= speed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) x -= speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) x += speed;

    if (x - width < -1.0f) x = -1.0f + width;
    if (x + width > 1.0f) x = 1.0f - width;

    float topLimit = 0.2f;
    if (y + height > topLimit) y = topLimit - height;

    if (y - height < -1.0f) y = -1.0f + height;
}


void Nemo::Render(GLuint shader) {
    glUseProgram(shader);
    glBindTexture(GL_TEXTURE_2D, tex);

    float quad[] = {
        x - width, y - height, 0, 0,
        x + width, y - height, 1, 0,
        x + width, y + height, 1, 1,
        x - width, y + height, 0, 1
    };

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VAO);  // update buffer
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(quad), quad);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Nemo::MakeQuad() {
    float quad[] = {
        x - width, y - height, 0, 0,
        x + width, y - height, 1, 0,
        x + width, y + height, 1, 1,
        x - width, y + height, 0, 1
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
