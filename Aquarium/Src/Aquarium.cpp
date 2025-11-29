#include "Aquarium.h"
#include "Util.h"
#include <iostream>

Aquarium::Aquarium(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), borderPx(10.0f),
    texShader(0), colorShader(0), bgTex(0), sandTex(0),
    VAO_bg(0), VAO_fill(0), VAO_bottom(0), VAO_leftB(0), VAO_rightB(0) {
}

Aquarium::~Aquarium() {}

void Aquarium::Init() {
    // load shaders
    texShader = LoadShaderProgram("Shader/tex.vert", "Shader/tex.frag");
    colorShader = LoadShaderProgram("Shader/color.vert", "Shader/color.frag");

    // load textures
    bgTex = LoadTexture("Resources/background.jpg");
    sandTex = LoadTexture("Resources/sand.png");
    unsigned int seaweedTex1 = LoadTexture("Resources/seaweed.png");
    unsigned int seaweedTex2 = LoadTexture("Resources/seaweed2.png");
    unsigned int chestTex[5];
    chestTex[0] = LoadTexture("Resources/chest1.png");
    chestTex[1] = LoadTexture("Resources/chest2.png");
    chestTex[2] = LoadTexture("Resources/chest3.png");
    chestTex[3] = LoadTexture("Resources/chest4.png");
    chestTex[4] = LoadTexture("Resources/chest5.png");

    // background
    float bgQuad[] = {
        -1, -1, 0, 0,
         1, -1, 1, 0,
         1,  1, 1, 1,
        -1,  1, 0, 1
    };
    VAO_bg = MakeTexturedQuad(bgQuad);

    // white fill
    float left = -1.0f;
    float right = 1.0f;
    float bottom = -1.0f;
    float ratio = 0.6f;
    float top = -1.0f + 2.0f * ratio;
    float thX = 2.0f * borderPx / screenWidth;
    float thY = 2.0f * borderPx / screenHeight;

    float fill[] = {
        left, bottom, 0.85f, 0.90f, 1.0f, 0.2f,
        right, bottom, 0.85f, 0.90f, 1.0f, 0.2f,
        right, top, 0.85f, 0.90f, 1.0f, 0.2f,
        left, top, 0.85f, 0.90f, 1.0f, 0.2f
    };
    VAO_fill = MakeQuadVAO(fill);

    // sand
    float sandHeight = 0.45f;
    float sandQuad[] = {
        left, bottom, 0, 0,
        right, bottom, 1, 0,
        right, bottom + sandHeight, 1, 1,
        left, bottom + sandHeight, 0, 1
    };
    VAO_sand = MakeTexturedQuad(sandQuad);

    // borders
    float bottomB[] = { left, bottom, 0,0,0,1, right, bottom, 0,0,0,1, right, bottom + thY, 0,0,0,1, left, bottom + thY, 0,0,0,1 };
    float leftB[] = { left, bottom, 0,0,0,1, left + thX, bottom, 0,0,0,1, left + thX, top, 0,0,0,1, left, top, 0,0,0,1 };
    float rightB[] = { right - thX, bottom, 0,0,0,1, right, bottom, 0,0,0,1, right, top, 0,0,0,1, right - thX, top, 0,0,0,1 };
    VAO_bottom = MakeQuadVAO(bottomB);
    VAO_leftB = MakeQuadVAO(leftB);
    VAO_rightB = MakeQuadVAO(rightB);

    // chest
    chest.Init(chestTex);

    // seaweed
    seaweed1.Init(-0.85f, -1.0f + sandHeight * 0.1f, 0.4f, seaweedTex1);
    seaweed2.Init(0.45f, -1.0f + sandHeight * 0.1f, 0.35f, seaweedTex2);

    //fishes
    GLuint nemoTex = LoadTexture("Resources/nemo.png");
    nemo.Init(nemoTex, -0.5f, 0.0f);
    GLuint goldfishTex = LoadTexture("Resources/goldfish.png");
    goldfish.Init(goldfishTex, -0.2f, -0.4f);
}

void Aquarium::Update(bool chestOpening, GLFWwindow* window) {
    chest.Update(chestOpening);
    nemo.Update(window);     
    goldfish.Update(window);
}

void Aquarium::Render() {

    // BACKGROUND
    glUseProgram(texShader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bgTex);
    glUniform1i(glGetUniformLocation(texShader, "uTex"), 0);
    glBindVertexArray(VAO_bg);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // SAND
    glBindTexture(GL_TEXTURE_2D, sandTex);
    glBindVertexArray(VAO_sand);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // SEAWEED
    seaweed1.Render(texShader);
    seaweed2.Render(texShader);

    // CHEST
    chest.Render(texShader);

    //FISHES
    nemo.Render(texShader);
    goldfish.Render(texShader);

    // WHITE TRANSPARENT
    glUseProgram(colorShader);
    glBindVertexArray(VAO_fill);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // BORDERS
    glBindVertexArray(VAO_leftB); glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(VAO_rightB); glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(VAO_bottom); glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

// helper func
unsigned int Aquarium::MakeTexturedQuad(float* data) {
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

unsigned int Aquarium::MakeQuadVAO(float* data) {
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    return VAO;
}
