#include "Nemo.h"
#include <Util.h>

Nemo::Nemo() : x(0), y(0), width(0.1f), height(0.1f), speed(0.01f), tex(0), VAO(0) {
    zPressedLastFrame = false;
}

void Nemo::Init(GLuint texture, float startX, float startY, float w, float h) {
    tex = texture;
    x = startX;
    y = startY;
    width = w;
    height = h;
    facingRight = true;
    MakeQuad();

    bubbleTex = LoadTexture("Resources/bubble.png");
}

void Nemo::Update(GLFWwindow* window) {
    
    bool zPressedNow = glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS;

    if (zPressedNow && !zPressedLastFrame) {
        float spacingY = 0.03f; 
        float offsetsX[3] = { 0.02f, -0.02f, 0.0f }; 

        for (int i = 0; i < 3; i++) {
            Bubble b;
            float offsetX = offsetsX[i];
            float offsetY = i * spacingY;  // 0, 0.03, 0.06
            b.Init(bubbleTex, x + offsetX, y + height + offsetY, 0.02f, 0.005f);
            bubbles.push_back(b);
        }
    }

    zPressedLastFrame = zPressedNow;

    for (auto& b : bubbles) {
        b.Update(0.2f);
    }
    bubbles.erase(
        std::remove_if(bubbles.begin(), bubbles.end(),
            [](Bubble& b) { return !b.active; }),
        bubbles.end()
    );

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) y += speed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) y -= speed;
    
    bool movedLeft = false;
    bool movedRight = false;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        x -= speed;
        movedLeft = true;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        x += speed;
        movedRight = true;
    }
    if (movedLeft && facingRight) facingRight = false;
    if (movedRight && !facingRight) facingRight = true;

    if (x - width < -1.0f) x = -1.0f + width;
    if (x + width > 1.0f) x = 1.0f - width;

    float topLimit = 0.2f;
    if (y + height > topLimit) y = topLimit - height;

    if (y - height < -1.0f) y = -1.0f + height;

}

void Nemo::Render(GLuint shader) {

    for (auto& b : bubbles) {
        b.Render(shader);
    }

    float u1 = facingRight ? 0.0f : 1.0f;
    float u2 = facingRight ? 1.0f : 0.0f;

    float quad[] = {
        x - width, y - height,  u1, 0,
        x + width, y - height,  u2, 0,
        x + width, y + height,  u2, 1,
        x - width, y + height,  u1, 1
    };

    glUseProgram(shader);
    glBindTexture(GL_TEXTURE_2D, tex);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
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
