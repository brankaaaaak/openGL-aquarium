#ifndef NEMOFISH_H
#define NEMOFISH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Header Files/model.hpp"
#include "Header Files/shader.hpp"

class NemoFish {
public:
    glm::vec3 position;
    float rotation;
    float targetRotation;
    float scale;
    float speed;
    Model* model;
    float thicknessOffset = 0.0f; 

    NemoFish(Model* modelPtr, glm::vec3 startPos) {
        model = modelPtr;
        position = startPos;
        rotation = 180.0f;
        targetRotation = 180.0f;
        scale = 0.04f;  // Povecana skala da ne bude mala
        speed = 0.12f;
    }

    void update(GLFWwindow* window) {
        bool moving = false;

        // --- KRETANJE (STRELICE) ---
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            position.z -= speed;
            targetRotation = 180.0f;
            moving = true;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            position.z += speed;
            targetRotation = 0.0f;
            moving = true;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            position.x -= speed;
            targetRotation = -90.0f;
            moving = true;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            position.x += speed;
            targetRotation = 90.0f;
            moving = true;
        }

        // --- GORE/DOLE (K i L) ---
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) position.y += speed; // K ide GORE
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) position.y -= speed; // L ide DOLE

        // --- GLATKA ROTACIJA ---
        if (moving) {
            float lerpFactor = 0.1f;
            float diff = targetRotation - rotation;
            while (diff < -180.0f) diff += 360.0f;
            while (diff > 180.0f) diff -= 360.0f;
            rotation += diff * lerpFactor;
        }

        // --- GRANICE (USKLAĐENO SA SMANJENIM AKVARIJUMOM) ---
        float limitXZ = 7.5f;
        if (position.x > limitXZ)  position.x = limitXZ;
        if (position.x < -limitXZ) position.x = -limitXZ;
        if (position.z > limitXZ)  position.z = limitXZ;
        if (position.z < -limitXZ) position.z = -limitXZ;

        // Visina (da ne izlazi gore)
        if (position.y > 4.2f)  position.y = 4.2f;  // Spušten plafon
        if (position.y < -2.2f) position.y = -2.2f; // Iznad peska
    }

    void draw(Shader& shader) {
        glm::mat4 modelMat = glm::mat4(1.0f);
        modelMat = glm::translate(modelMat, position);
        modelMat = glm::rotate(modelMat, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

        modelMat = glm::scale(modelMat, glm::vec3(scale, scale + thicknessOffset, scale));

        shader.setMat4("uM", modelMat);
        model->Draw(shader);
    }
};

#endif