#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned int LoadShaderProgram(const char* vertexPath, const char* fragmentPath);
unsigned int LoadTexture(const char* path);
GLFWcursor* LoadImageToCursor(const char* filePath);
