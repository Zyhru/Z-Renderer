#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
  this->_vertices = vertices;
  this->_indices  = indices;

  initMesh();
} 

void Mesh::initMesh() {

  // Generate
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), &_vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), &_indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

}

// We can pass in shader from main.cpp
void Mesh::Render(Shader &shader) {
  // Render mesh
  shader.Use();
  

  // TODO: Figure out how to properly chain the meshes together

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, &_indices);
  
}
