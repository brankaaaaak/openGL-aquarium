#ifndef GOLDFISH_H
#define GOLDFISH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Header Files/model.hpp"
#include "Header Files/shader.hpp"

class Goldfish {
public:
    glm::vec3 position;
    float rotation;       // trenutna rotacija oko Y ose
    float targetRotation; // rotacija kojoj teži
    float scale;
    float speed;
    Model* model;

    Goldfish(Model* modelPtr, glm::vec3 startPos) {
        model = modelPtr;
        position = startPos;
        rotation = 0.0f;
        targetRotation = 0.0f;
        scale = 0.04f;
        speed = 0.10f; // još sporije?
    }

    void update(GLFWwindow* window) {
        bool moving = false;

        // W - ide ka -z
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            position.z -= speed;
            targetRotation = 180.0f; 
            moving = true;
        }
        // S - ide ka +z
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            position.z += speed;
            targetRotation = 0.0f;   
            moving = true;
        }
        // A - ide ka -x
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            position.x -= speed;
            targetRotation = -90.0f; 
            moving = true;
        }
        // D - ide ka +x
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            position.x += speed;
            targetRotation = 90.0f;  
            moving = true;
        }

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) position.y += speed; // gore
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) position.y -= speed; // dole

        if (moving) {
            float lerpFactor = 0.1f;
            float diff = targetRotation - rotation;

            if (diff > 180.0f) diff -= 360.0f;
            if (diff < -180.0f) diff += 360.0f;

            rotation += diff * lerpFactor;
        }

        // granice
        float limitXZ = 7.5f; 
        if (position.x > limitXZ)  position.x = limitXZ;
        if (position.x < -limitXZ) position.x = -limitXZ;
        if (position.z > limitXZ)  position.z = limitXZ;
        if (position.z < -limitXZ) position.z = -limitXZ;

        if (position.y > 4.5f)  position.y = 4.5f;  // gore
        if (position.y < -2.0f) position.y = -2.0f; // dole
    }

    void draw(Shader& shader) {
        glm::mat4 modelMat = glm::mat4(1.0f);
        modelMat = glm::translate(modelMat, position);

        // rotacija oko Y ose 
        modelMat = glm::rotate(modelMat, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

        modelMat = glm::scale(modelMat, glm::vec3(scale));

        shader.setMat4("uM", modelMat);
        model->Draw(shader);
    }
};

#endif