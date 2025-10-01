#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "camera.h"
#include "settings.h"

extern bool firstMouse;
extern bool cameraLockedOnObject;
extern double mouseX, mouseY;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Camera& camera, float deltaTime);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void countFPS();