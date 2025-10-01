#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "shader.h"
#include "camera.h"
#include "utils.h"
#include "tile.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera(glm::vec3(0.0f), 5.0f, 0.0f, -17.0f);


int main()
{
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Demo game", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, nullptr);
    glfwSetWindowUserPointer(window, &camera);
	glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);	
    glfwSwapInterval(0);

    Shader objectShader("../shaders/objectShader.vs", "../shaders/objectShader.fs");

    camera.UpdatePosition();

    Tile tile(0.0f, 0.0f, TileType::Field);
    tile.buildMesh();
    tile.upload();

    Tile tile2(1.732f, 0.0f, TileType::Field);
    tile2.buildMesh();
    tile2.upload();

    Tile tile3(0.866f, 1.5f, TileType::Field);
    tile3.buildMesh();
    tile3.upload();


    while(!glfwWindowShouldClose(window))
    {
    	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    	float currentFrame = static_cast<float>(glfwGetTime());
    	deltaTime = currentFrame - lastFrame;
    	lastFrame = currentFrame;

    	processInput(window, camera, deltaTime);
        countFPS();


    	glm::mat4 model = glm::mat4(1.0f);
    	glm::mat4 view = camera.GetViewMatrix();
    	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);

    	objectShader.use();
    	objectShader.setMat4("model", model);
    	objectShader.setMat4("view", view);
    	objectShader.setMat4("projection", projection);
    	objectShader.setVec3("baseColor", 0.7f, 0.7f, 0.7f);

    	camera.UpdatePosition();


    	tile.render(objectShader);
        tile2.render(objectShader);
        tile3.render(objectShader);


    	glfwSwapBuffers(window);
    	glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}