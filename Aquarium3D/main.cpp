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
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE) {
        tKeyPressed = false;
    }

    // Taster C - Face Culling
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !cKeyPressed) {
        faceCullEnabled = !faceCullEnabled;
        if (faceCullEnabled) glEnable(GL_CULL_FACE);
        else glDisable(GL_CULL_FACE);
        std::cout << "Face Culling: " << (faceCullEnabled ? "ON" : "OFF") << std::endl;
        cKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) {
        cKeyPressed = false;
    }
}

unsigned int cubeVAO = 0;
unsigned int cubeVBO = 0;
void renderCube() {
    if (cubeVAO == 0) {
        float vertices[] = {
            // pozicije          // normale           // teksture
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
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
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

int main() {
    glfwInit();
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);

    // fullscreen
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Aquarium 3D", primary, NULL);
    if (window == NULL) {
        std::cout << "Error" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shader("Shader/basic.vert", "Shader/basic.frag");

    Mesh sand = sandGenerator();
    unsigned int sandTex = TextureFromFile("sand.png", "res");

    Model goldfishModel("res/Mesh_Goldfish.obj"); 
    Goldfish goldfish(&goldfishModel, glm::vec3(0.0f, 0.0f, 0.0f));

    Model nemoModel("res/Mesh_Fish.obj"); 
    NemoFish nemofish(&nemoModel, glm::vec3(3.0f, 0.0f, 0.0f)); 

    double lastFrameTime = 0.0;

    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        if (currentTime - lastFrameTime >= 1.0 / 75.0) { // Limit na 75 FPS
            lastFrameTime = currentTime;

            processInput(window); 

            glClearColor(0.0f, 0.1f, 0.25f, 1.0f); //tamna plava
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader.use();

            // matrica
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)mode->width / mode->height, 0.1f, 100.0f);
            glm::mat4 view = glm::lookAt(glm::vec3(0, 8, 20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
            shader.setMat4("uP", projection);
            shader.setMat4("uV", view);

            // svjetlo
            shader.setVec3("uLightPos", glm::vec3(5.0f, 10.0f, 5.0f));
            shader.setVec3("uLightColor", glm::vec3(1.0f, 1.0f, 1.0f));
            shader.setVec3("uViewPos", glm::vec3(0, 8, 20));

            //ribe
            goldfish.update(window);           // tasteri
            nemofish.update(window);

            float distance = glm::distance(goldfish.position, nemofish.position);
            float minDistance = 3.3f; 

            if (distance < minDistance) {
                glm::vec3 pushDir = glm::normalize(goldfish.position - nemofish.position);

                float overlap = minDistance - distance;
                goldfish.position += pushDir * (overlap * 0.5f);
                nemofish.position -= pushDir * (overlap * 0.5f);

                float angleGoldfish = glm::degrees(atan2(pushDir.x, pushDir.z));
                float angleNemo = glm::degrees(atan2(-pushDir.x, -pushDir.z));

                goldfish.targetRotation = angleGoldfish;
                nemofish.targetRotation = angleNemo;
            }

            shader.setBool("uUseTexture", true); 
            goldfish.draw(shader);             // nova pozicija
            nemofish.draw(shader);

            //pijesak
            glm::mat4 modelPesak = glm::translate(glm::mat4(1.0f), glm::vec3(0, -3.0f, 0));
            shader.setMat4("uM", modelPesak);
            shader.setBool("uUseTexture", true);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, sandTex);
            shader.setInt("uDiffMap1", 0);
            sand.Draw(shader);

            //crno dno ispod pijeska
            shader.setBool("uUseTexture", false);
            shader.setVec4("uColor", glm::vec4(0.05f, 0.05f, 0.05f, 1.0f)); 

            glm::mat4 modelBottom = glm::translate(glm::mat4(1.0f), glm::vec3(0, -3.2f, 0)); 
            modelBottom = glm::scale(modelBottom, glm::vec3(20.0f, 0.2f, 20.0f)); 
            shader.setMat4("uM", modelBottom);
            renderCube();

            shader.setVec4("uColor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)); // stubovi

            // ćoškovi
            glm::vec3 positions[] = {
                glm::vec3(-10.0f, 1.0f, -10.0f), // zadnji lijevi
                glm::vec3(10.0f, 1.0f, -10.0f), // zadnji desni
                glm::vec3(-10.0f, 1.0f,  10.0f), // prednji lijevi
                glm::vec3(10.0f, 1.0f,  10.0f)  // prednji desni
            };

            for (int i = 0; i < 4; i++) {
                glm::mat4 modelStub = glm::translate(glm::mat4(1.0f), positions[i]);
                modelStub = glm::scale(modelStub, glm::vec3(0.5f, 8.0f, 0.5f));
                shader.setMat4("uM", modelStub);
                renderCube();
            }

            //stakla
            // providnost 0.2 
            shader.setVec4("uColor", glm::vec4(0.0f, 0.5f, 1.0f, 0.2f));

            // zadnje
            glm::mat4 glassBack = glm::translate(glm::mat4(1.0f), glm::vec3(0, 1.0f, -10.0f));
            glassBack = glm::scale(glassBack, glm::vec3(20.0f, 8.0f, 0.1f));
            shader.setMat4("uM", glassBack);
            renderCube();

            // prednje
            glm::mat4 glassFront = glm::translate(glm::mat4(1.0f), glm::vec3(0, 1.0f, 10.0f));
            glassFront = glm::scale(glassFront, glm::vec3(20.0f, 8.0f, 0.1f));
            shader.setMat4("uM", glassFront);
            renderCube();

            // lijevo
            glm::mat4 glassLeft = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 1.0f, 0.0f));
            glassLeft = glm::scale(glassLeft, glm::vec3(0.1f, 8.0f, 20.0f));
            shader.setMat4("uM", glassLeft);
            renderCube();

            // desno
            glm::mat4 glassRight = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 1.0f, 0.0f));
            glassRight = glm::scale(glassRight, glm::vec3(0.1f, 8.0f, 20.0f));
            shader.setMat4("uM", glassRight);
            renderCube();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}