#include "utils.h"


bool firstMouse = true;
bool cameraLockedOnObject = false;
double mouseX, mouseY;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, Camera& camera, float deltaTime)
{
  static bool leftMousePressedLastFrame = false;

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  float rotationSpeed = 80.0f;
  float moveSpeed = 2.0f;

  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    camera.Yaw += rotationSpeed * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    camera.Yaw -= rotationSpeed * deltaTime;

  glm::vec3 flatFront = glm::normalize(glm::vec3(camera.Front.x, 0.0f, camera.Front.z));
  glm::vec3 right = glm::normalize(glm::cross(flatFront, camera.WorldUp));

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.Target += flatFront * moveSpeed * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.Target -= flatFront * moveSpeed * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.Target -= right * moveSpeed * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.Target += right * moveSpeed * deltaTime;

  camera.UpdatePosition();
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

  if (camera)
    camera->ProcessMouseScroll((float)yoffset);
}

void countFPS()
{
  static double lastTime = glfwGetTime();
  static int frameCount = 0;

  double currentTime = glfwGetTime();
  frameCount++;

  if (currentTime - lastTime >= 1.0)
  {
    std::cout << "FPS: " << frameCount << std::endl;
    frameCount = 0;
    lastTime = currentTime;
  }
}
