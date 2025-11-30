#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Chest.h"
#include "Seaweed.h"
#include "Nemo.h"
#include "Goldfish.h"
#include "FoodParticle.h"

class Aquarium {
public:
    Aquarium(int screenWidth, int screenHeight);
    ~Aquarium();

    void Init();
    void Render();
    void Update(bool chestOpening, GLFWwindow* window);

private:
    int screenWidth;
    int screenHeight;
    float borderPx;

    unsigned int texShader;
    unsigned int colorShader;
    unsigned int bgTex;
    unsigned int sandTex;

    unsigned int VAO_bg;
    unsigned int VAO_fill;
    unsigned int VAO_bottom, VAO_leftB, VAO_rightB;
    unsigned int VAO_sand;

    Chest chest;
    Seaweed seaweed1, seaweed2;
    Nemo nemo;
    Goldfish goldfish;

    std::vector<FoodParticle> food;
    GLuint foodTex;

    unsigned int MakeTexturedQuad(float* data);
    unsigned int MakeQuadVAO(float* data);
};
