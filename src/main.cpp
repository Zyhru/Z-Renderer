#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "Camera.h"
#include "Importer.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int HEIGHT = 600;
const int WIDTH  = 800;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void fov_slider_callback(GLFWwindow* window, double xoffset, double yoffset);
void importObjFile();

Camera camera;

int main(int argc, char* argv[]) {

  if(!glfwInit()) return -1;

  GLFWwindow* window = nullptr;
  window = glfwCreateWindow(WIDTH, HEIGHT, "Z-Renderer", nullptr, nullptr);
  
  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetScrollCallback(window, fov_slider_callback);
  
  if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to init Glad" << std::endl;
    return -1;
  }

// TODO: Use an index buffer
float vertices[] = {

    // position
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

  Shader shader;
  shader.Load("C:\\Users\\zyhru\\Projects\\Graphics\\vertex.vert", "C:\\Users\\zyhru\\Projects\\Graphics\\fragment.frag");

  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  //glBindVertexArray(0); // TODO: Look this up
  glEnable(GL_DEPTH_TEST);

  // TODO: Fix absoulte path -> relative path
  Importer import;
  Obj obj = import.ReadFile("C:\\Users\\zyhru\\Projects\\Graphics\\box.obj");

  // Iterate through each mesh and print out its vertices
  std::cout << "Printing .obj contents" << std::endl;
  for(auto& x : obj.meshes) {

    /* Printing out vertices in all meshes */
    for(auto& y : x._vertices) {
      std::cout << "{" << y.x << "," << y.y << "," << y.z << "}" << std::endl;
    }

    /* Printing out indices in all meshes */
    std::cout << "\n"; 
    for(auto& z : x._indices) {
      std::cout << z << std::endl;
    }
  } 

  while(!glfwWindowShouldClose(window)) {

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

    // Render
    shader.Use();

    int modelLocation, projectionLocation, viewLocation;
    glm::mat4 view = glm::mat4(1.0f); // Camera
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(camera._fov), 800.0f / 600.0f , 0.1f, 100.0f);
    view = camera.LookAtMatrix();
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    projectionLocation = glGetUniformLocation(shader._shaderID, "projection");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
   
    viewLocation = glGetUniformLocation(shader._shaderID, "view");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    
    // 3D Object
    glBindVertexArray(VAO);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float) glfwGetTime() * 0.5f, glm::vec3(1.0f, 1.0f, 0.0f));
    //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.0f));
    //model = glm::scale(model, glm::vec3(1.0f, 0.0f, 1.0f));
    modelLocation = glGetUniformLocation(shader._shaderID, "model");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  return 0;

}


// void importObjFile() {
  //const Obj* obj = Importer::ReadFile("box.obj");
//}

void fov_slider_callback(GLFWwindow *window, double xoffset, double yoffset) {
  camera.AdjustFov(yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0,0,width,height);
}
