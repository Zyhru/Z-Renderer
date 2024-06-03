#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"


struct Vertex {
	glm::vec3 vertex;
};

class Mesh {

	public:
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		
		unsigned int VAO, VBO, EBO;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
		void Render(Shader &shader);

	private:
		void initMesh();
		void processVertices();
		void processIndices();
		

};
