#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Camera.h"
#include "Importer.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera camera;
const unsigned int HEIGHT = 600;
const unsigned int WIDTH = 800;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void fov_slider_callback(GLFWwindow *window, double xoffset, double yoffset);

glm::vec3 lightPos(0.0f, 0.0f, 2.0f);

int main(int argc, char *argv[]) {
  if (!glfwInit()) return -1;
   
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Z-Renderer", nullptr, nullptr);
  if (window == NULL) {
    std::cerr << "Failed to create window" << std::endl;
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetScrollCallback(window, fov_slider_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to init Glad" << std::endl;
    return -1;
  }

  // TODO: Use an index buffer
  float vertices[] = {

      // position
      -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f,
      0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,

      -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,

      -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,

      0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f,
      0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,

      -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,
      0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f,

      -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f};

  Shader shader, lightShader;
  shader.Load("C:\\Users\\zyhru\\Projects\\Graphics\\vertex.vert",
              "C:\\Users\\zyhru\\Projects\\Graphics\\fragment.frag");



  #if 0
  lightShader.Load("C:\\Users\\zyhru\\Projects\\Graphics\\lightvertex.vert",
              "C:\\Users\\zyhru\\Projects\\Graphics\\lightfragment.frag");

  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
   (void*)0);
  glEnableVertexAttribArray(0);

  unsigned int lightVAO;
  glGenVertexArrays(1, &lightVAO);
  glBindVertexArray(lightVAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  #endif

 // glBindVertexArray(0); // TODO: Look this up
  glEnable(GL_DEPTH_TEST);

  // TODO: Fix absoulte path -> relative path
  Importer import;
  import.ReadFile("C:\\Users\\zyhru\\Projects\\Graphics\\box_stack.obj", QUADTOTRIANGLE);

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Processing Input
    // =========================================================
    camera.MoveCamera(window, deltaTime);

    // Looking around
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    camera.LookAround(xpos, ypos);

    // =========================================================

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // TODO: create a toggle 

    // Render
    shader.Use();

    #if 0
    // Set color
    glm::vec3 lightColor  = glm::vec3(1.0, 1.0f, 1.0f);
    glm::vec3 objectColor = glm::vec3(0.5f, 0.2f, 0.4f);
    int lightColorLocation, objectColorLocation;
    lightColorLocation  = glGetUniformLocation(shader._shaderID, "lightColor");
    objectColorLocation = glGetUniformLocation(shader._shaderID, "objectColor");
    glUniform3f(lightColorLocation, lightColor.x, lightColor.y, lightColor.z);
    glUniform3f(objectColorLocation, objectColor.x, objectColor.y, objectColor.z);
    #endif

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(camera._fov), 800.0f / 600.0f, 0.1f, 100.0f);
    view = camera.LookAtMatrix();
    shader.SetMat4("projection", projection);
    shader.SetMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    shader.SetMat4("model", model);
    import.Render(shader);
    
    // Render Light Cube (Acts as a lamp)
    #if 0
    lightShader.Use();
    lightShader.SetMat4("projection", projection);
    lightShader.SetMat4("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    lightShader.SetMat4("model", model);
    import.Render(lightShader);
    #endif
    
    //glBindVertexArray(lightVAO);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    //glBindVertexArray(0);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  return 0;
}

void fov_slider_callback(GLFWwindow *window, double xoffset, double yoffset) {
  camera.AdjustFov(yoffset);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
