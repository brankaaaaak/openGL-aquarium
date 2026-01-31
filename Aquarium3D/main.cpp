#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

#include "Header Files/shader.hpp"
#include "Header Files/mesh.hpp"
#include "Header Files/model.hpp"
#include <vector>
#include <iostream>
#include "Header Files/goldfish.hpp"
#include "Header Files/nemo.hpp"

bool depthTestEnabled = true;
bool faceCullEnabled = false;
bool tKeyPressed = false;
bool cKeyPressed = false;
bool gKeyPressed = false;
bool chestOpen = false;
float lidAngle = 0.0f; 
const float maxLidAngle = 80.0f; 

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Taster T - Depth Test
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && !tKeyPressed) {
        depthTestEnabled = !depthTestEnabled;
        if (depthTestEnabled) glEnable(GL_DEPTH_TEST);
        else glDisable(GL_DEPTH_TEST);
        std::cout << "Depth Test: " << (depthTestEnabled ? "ON" : "OFF") << std::endl;
        tKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE) tKeyPressed = false;

    // Taster C - Face Culling
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !cKeyPressed) {
        faceCullEnabled = !faceCullEnabled;
        if (faceCullEnabled) glEnable(GL_CULL_FACE);
        else glDisable(GL_CULL_FACE);
        std::cout << "Face Culling: " << (faceCullEnabled ? "ON" : "OFF") << std::endl;
        cKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) cKeyPressed = false;
}

unsigned int cubeVAO = 0, cubeVBO = 0;
void renderCube() {
    if (cubeVAO == 0) {
        float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
        };
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindVertexArray(cubeVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

Mesh sandGenerator() {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    int width = 40, depth = 40;
    float scale = 0.5f;
    for (int z = 0; z < depth; z++) {
        for (int x = 0; x < width; x++) {
            Vertex v;
            float randHeight = (rand() % 100) / 400.0f;
            v.Position = glm::vec3(x * scale - 10.0f, randHeight, z * scale - 10.0f);
            v.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
            v.TexCoords = glm::vec2((float)x / width, (float)z / depth);
            vertices.push_back(v);
        }
    }
    for (int z = 0; z < depth - 1; z++) {
        for (int x = 0; x < width - 1; x++) {
            indices.push_back(z * width + x);
            indices.push_back((z + 1) * width + x);
            indices.push_back(z * width + (x + 1));
            indices.push_back((z + 1) * width + x);
            indices.push_back((z + 1) * width + (x + 1));
            indices.push_back(z * width + (x + 1));
        }
    }
    return Mesh(vertices, indices, {});
}

struct Bubble {
    glm::vec3 position;
    float speed;
    float horizontalOffset; // za pomijeranje njihovo
    float startTime;
    bool active;

    Bubble(glm::vec3 startPos) {
        position = startPos;
        speed = 0.03f + (rand() % 100 / 5000.0f); // nasumična brzina ka gore
        horizontalOffset = (rand() % 100 / 10.0f); // različit početak njihovog pomijeranja
        startTime = (float)glfwGetTime();
        active = true;
    }
};
//lista svih mjehurića u akvarijumu
std::vector<Bubble> bubbles;

struct Food {
    glm::vec3 position;
    bool active;
    float speed = 0.03f;
    Food(glm::vec3 pos) : position(pos), active(true) {}
};
std::vector<Food> fishFood;

int main() {
    glfwInit();
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Aquarium 3D", primary, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shader("Shader/basic.vert", "Shader/basic.frag");

    // modeli
    Model goldfishModel("res/Mesh_Goldfish.obj");
    Goldfish goldfish(&goldfishModel, glm::vec3(0.0f, 0.0f, 0.0f));

    Model nemoModel("res/Mesh_Fish.obj");
    NemoFish nemofish(&nemoModel, glm::vec3(3.0f, 0.0f, 0.0f));

    Model seaweedModel("res/PUSHILIN_kelp.obj");
    Model seaweed2Model("res/CHAHIN_ANEMONE.obj");

    Mesh sand = sandGenerator();
    unsigned int sandTex = TextureFromFile("sand.png", "res");
    unsigned int chestTex = TextureFromFile("MonasteryProps01_MonasteryProps01_Roughnes.png", "res"); 

    Model bubbleModel("res/model.obj"); 

    Model chestModel("res/Renaissance_Chest.obj");
    glm::vec3 chestPos = glm::vec3(-4.0f, -2.7f, 6.0f);

    Model foodModel("res/Rock1.obj");

    // pozicije biljaka
    glm::vec3 seaweedPos = glm::vec3(-6.0f, -3.0f, -5.0f);
    glm::vec3 seaweed2Pos = glm::vec3(5.0f, -3.0f, 2.0f);

    double lastFrameTime = 0.0;

    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        if (currentTime - lastFrameTime >= 1.0 / 75.0) {
            lastFrameTime = currentTime;

            processInput(window);

            static bool key1Pressed = false;
            static bool key2Pressed = false;

            // 1 - gold fish
            if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !key1Pressed) {
                bubbles.push_back(Bubble(goldfish.position + glm::vec3(0, 0.5f, 0)));
                key1Pressed = true;
            }
            if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE) key1Pressed = false;

            // 2 - druga riba
            if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && !key2Pressed) {
                bubbles.push_back(Bubble(nemofish.position + glm::vec3(0, 0.5f, 0)));
                key2Pressed = true;
            }
            if (glfwGetKey(window, GLFW_KEY_2) == GLFW_RELEASE) key2Pressed = false;

            // Logika za taster G
            if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && !gKeyPressed) {
                chestOpen = !chestOpen;
                gKeyPressed = true;
            }
            if (glfwGetKey(window, GLFW_KEY_G) == GLFW_RELEASE) gKeyPressed = false;

            static bool enterPressed = false;
            if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && !enterPressed) {
                for (int i = 0; i < 2; i++) { 
                    float rx = ((rand() % 100) / 100.0f) * 14.0f - 7.0f;
                    float rz = ((rand() % 100) / 100.0f) * 14.0f - 7.0f;
                    fishFood.push_back(Food(glm::vec3(rx, 10.0f, rz)));
                }
                enterPressed = true;
            }
            if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_RELEASE) enterPressed = false;

            // otvaranje i zatvaranje
            if (chestOpen && lidAngle < maxLidAngle) lidAngle += 2.0f;
            else if (!chestOpen && lidAngle > 0.0f) lidAngle -= 2.0f;

            glClearColor(0.0f, 0.1f, 0.25f, 1.0f); //tamnija
            //glClearColor(0.1f, 0.3f, 0.45f, 1.0f); //svjetlija
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader.use();
            shader.setBool("uUseTexture", true);

            // kamera i svjetlo
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)mode->width / mode->height, 0.1f, 100.0f);
            glm::mat4 view = glm::lookAt(glm::vec3(0, 8, 20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
            //glm::mat4 view = glm::lookAt(glm::vec3(0, -1, 2), glm::vec3(0, -1, 0), glm::vec3(0, 1, 0));
            shader.setMat4("uP", projection);
            shader.setMat4("uV", view);
            shader.setVec3("uLightPos", glm::vec3(5.0f, 10.0f, 5.0f));
            //shader.setVec3("uLightColor", glm::vec3(1.0f, 1.0f, 1.0f)); //bijela
            shader.setVec3("uLightColor", glm::vec3(1.0f, 0.75f, 0.85f)); //roza
            shader.setVec3("uViewPos", glm::vec3(0, 8, 20));

            float intensity = lidAngle / maxLidAngle;
            glm::vec3 goldColor = glm::vec3(1.0f, 0.6f, 0.0f); 
            shader.setVec3("uChestLightColor", goldColor * intensity * 3.5f); // povecati jacinu?

            // KOVČEG!!!!
            shader.use();
            shader.setBool("uUseTexture", true);
            shader.setBool("uUseTint", true);
            shader.setVec3("uTintColor", glm::vec3(0.45f, 0.25f, 0.15f)); 
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, chestTex);

            glm::mat4 modelChestBase = glm::translate(glm::mat4(1.0f), chestPos);
            modelChestBase = glm::scale(modelChestBase, glm::vec3(2.0f));
            modelChestBase = glm::rotate(modelChestBase, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            glm::vec3 chestLightLocal = glm::vec3(0.0f, 0.35f, 0.25f); // pozicija unutar kovčega
            glm::vec3 chestLightPosition = glm::vec3(modelChestBase * glm::vec4(chestLightLocal, 1.0f));
            shader.setVec3("uChestLightPos", chestLightPosition);

            shader.setMat4("uM", modelChestBase);
            chestModel.meshes[0].Draw(shader); // katanac
            chestModel.meshes[2].Draw(shader); // dno

            // poklopac
            glm::mat4 modelLid = modelChestBase;

            // osa na zadnjoj ivici
            glm::vec3 hingeOffset = glm::vec3(0.0f, 0.35f, 0.35f);

            modelLid = glm::translate(modelLid, hingeOffset);

            // - ispred lidAngle jer je obrnut da ide na gore
            modelLid = glm::rotate(modelLid, glm::radians(-lidAngle), glm::vec3(1.0f, 0.0f, 0.0f));

            modelLid = glm::translate(modelLid, -hingeOffset);

            shader.setMat4("uM", modelLid);
            chestModel.meshes[1].Draw(shader); // poklopac

            if (lidAngle > 5.0f) {
                glEnable(GL_BLEND);
                shader.setBool("uUseTexture", false);
                shader.setBool("uUseTint", false);
                shader.setVec4("uColor", glm::vec4(1.0f, 0.7f, 0.0f, intensity * 0.5f));

                glm::vec3 glowLocal = glm::vec3(0.0f, 0.5f, 0.0f);
                glm::vec3 glowWorld = glm::vec3(modelLid * glm::vec4(glowLocal, 1.0f));

                glm::mat4 modelGlow = glm::translate(glm::mat4(1.0f), glowWorld);
                modelGlow = glm::scale(modelGlow, glm::vec3(1.5f, 0.8f, 1.0f));
                shader.setMat4("uM", modelGlow);

                renderCube();
            }

            // ribe
            goldfish.update(window);
            nemofish.update(window);

            // sudar
            float fishDist = glm::distance(goldfish.position, nemofish.position);
            if (fishDist < 3.3f) {
                glm::vec3 pushDir = glm::normalize(goldfish.position - nemofish.position);
                float overlap = 3.3f - fishDist;
                goldfish.position += pushDir * (overlap * 0.5f);
                nemofish.position -= pushDir * (overlap * 0.5f);
            }
            float distToChestGold = glm::distance(goldfish.position, chestPos);
            if (distToChestGold < 2.5f) {
                glm::vec3 pushDir = glm::normalize(goldfish.position - chestPos);
                goldfish.position = chestPos + pushDir * 2.5f;
            }

            float distToChestNemo = glm::distance(nemofish.position, chestPos);
            if (distToChestNemo < 2.5f) {
                glm::vec3 pushDir = glm::normalize(nemofish.position - chestPos);
                nemofish.position = chestPos + pushDir * 2.5f;
            }
            float plantRadius = 3.2f;
            std::vector<glm::vec3*> fishPositions = { &goldfish.position, &nemofish.position };
            std::vector<float*> fishTargetRots = { &goldfish.targetRotation, &nemofish.targetRotation };
            std::vector<glm::vec3> plants = { seaweedPos, seaweed2Pos };

            for (int f = 0; f < 2; f++) {
                for (int p = 0; p < 2; p++) {
                    float dX = fishPositions[f]->x - plants[p].x;
                    float dZ = fishPositions[f]->z - plants[p].z;
                    float dist = sqrt(dX * dX + dZ * dZ);
                    if (dist < plantRadius) {
                        glm::vec3 pushDir = glm::normalize(glm::vec3(dX, 0.0f, dZ));
                        *fishPositions[f] += pushDir * (plantRadius - dist);
                        *fishTargetRots[f] = glm::degrees(atan2(pushDir.x, pushDir.z));
                    }
                }
            }

            shader.setBool("uUseTexture", true);
            goldfish.draw(shader);
            nemofish.draw(shader);

            // pijesak i biljke
            glm::mat4 modelSand = glm::translate(glm::mat4(1.0f), glm::vec3(0, -3.0f, 0));
            shader.setMat4("uM", modelSand);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, sandTex);
            sand.Draw(shader);

            glm::mat4 modelKelp = glm::translate(glm::mat4(1.0f), seaweedPos);
            modelKelp = glm::scale(modelKelp, glm::vec3(1.6f));
            shader.setMat4("uM", modelKelp);
            seaweedModel.Draw(shader);

            glm::mat4 modelAnemone = glm::translate(glm::mat4(1.0f), seaweed2Pos);
            modelAnemone = glm::scale(modelAnemone, glm::vec3(1.6f));
            shader.setMat4("uM", modelAnemone);
            seaweed2Model.Draw(shader);

            // stubovi i dno
            shader.setBool("uUseTexture", false);
            shader.setVec4("uColor", glm::vec4(0.05f, 0.05f, 0.05f, 1.0f));
            glm::mat4 modelBottom = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0, -3.2f, 0)), glm::vec3(20.0f, 0.2f, 20.0f));
            shader.setMat4("uM", modelBottom);
            renderCube();

            shader.setVec4("uColor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
            glm::vec3 pillars[] = { {-10,1,-10}, {10,1,-10}, {-10,1,10}, {10,1,10} };
            for (auto p : pillars) {
                glm::mat4 m = glm::scale(glm::translate(glm::mat4(1.0f), p), glm::vec3(0.5f, 8.0f, 0.5f));
                shader.setMat4("uM", m);
                renderCube();
            }

            for (int i = 0; i < fishFood.size(); i++) {
                if (!fishFood[i].active) continue;

                if (fishFood[i].position.y > -2.7f)
                    fishFood[i].position.y -= fishFood[i].speed;
                //da li ribe jedu
                if (glm::distance(fishFood[i].position, goldfish.position) < 1.2f) {
                    fishFood[i].active = false;
                    goldfish.thicknessOffset += 0.01f; 
                }
                if (glm::distance(fishFood[i].position, nemofish.position) < 1.2f) {
                    fishFood[i].active = false;
                    nemofish.thicknessOffset += 0.01f;
                }

                // crtanje hrane
                if (fishFood[i].active) {
                    shader.setBool("uUseTexture", false);
                    shader.setVec4("uColor", glm::vec4(0.5f, 0.3f, 0.1f, 1.0f)); 
                    glm::mat4 m = glm::translate(glm::mat4(1.0f), fishFood[i].position);
                    m = glm::scale(m, glm::vec3(0.15f)); 
                    shader.setMat4("uM", m);
                    if (foodModel.meshes.size() > 1) {
                        foodModel.meshes[1].Draw(shader); 
                    }
                    else {
                        foodModel.Draw(shader); 
                    }
                }
            }
            // čišćenje pojedene hrane
            fishFood.erase(std::remove_if(fishFood.begin(), fishFood.end(), [](const Food& f) { return !f.active; }), fishFood.end());

            // mjehurići
            for (int i = 0; i < bubbles.size(); i++) {
                if (bubbles[i].active) {
                    bubbles[i].position.y += bubbles[i].speed;
                    float waveTime = (float)glfwGetTime() * 3.0f;
                    float wave = sin(waveTime + bubbles[i].horizontalOffset) * 0.15f;

                    if (bubbles[i].position.y > 4.5f) {
                        bubbles[i].active = false;
                        continue;
                    }

                    shader.setBool("uUseTexture", false);
                    shader.setVec4("uColor", glm::vec4(0.8f, 0.9f, 1.0f, 0.4f));

                    glm::mat4 modelBubble = glm::mat4(1.0f);
                    modelBubble = glm::translate(modelBubble, bubbles[i].position + glm::vec3(wave, 0, 0));
                    modelBubble = glm::scale(modelBubble, glm::vec3(2.0f, 2.0f, 2.0f));
                    shader.setMat4("uM", modelBubble);

                    bubbleModel.Draw(shader); 
                }
            }
            bubbles.erase(std::remove_if(bubbles.begin(), bubbles.end(),
                [](const Bubble& b) { return !b.active; }), bubbles.end());


            // stakla
            shader.setBool("uUseTexture", false);
            shader.setVec4("uColor", glm::vec4(0.0f, 0.5f, 1.0f, 0.2f));
            auto drawGlass = [&](glm::vec3 pos, glm::vec3 sc) {
                shader.setMat4("uM", glm::scale(glm::translate(glm::mat4(1.0f), pos), sc));
                renderCube();
                };
            drawGlass({ 0, 1, -10 }, { 20, 8, 0.1f });
            drawGlass({ 0, 1, 10 }, { 20, 8, 0.1f });
            drawGlass({ -10, 1, 0 }, { 0.1f, 8, 20 });
            drawGlass({ 10, 1, 0 }, { 0.1f, 8, 20 });

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}