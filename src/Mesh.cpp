#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
  m_vertices = vertices;
  m_indices  = indices;
  initMesh();
} 

void Mesh::initMesh() {
  
  std::cout << "initMesh\n";

  // Generate
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
 
  glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

}

void Mesh::Render(Shader &shader) {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Mesh::processVertices() {
  std::cout  << "[";
  for(auto& x : m_vertices) {
    std::cout << x.x << "," << x.y << "," << x.z << std::endl; 
  }
  std::cout  << "]";

}

void Mesh::processIndices() {
  std::cout  << "\n[";
  for(auto& x : m_indices) {
    std::cout  << x << std::endl;
  }
  std::cout  << "]\n";

}
