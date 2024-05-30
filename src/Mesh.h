#pragma once

#include <vector>
#include <glad/glad.h>
#include "Shader.h"


struct Vertex {
	float x;
	float y;
	float z;
};

class Mesh {

	public:
		std::vector<Vertex> _vertices;
		std::vector<unsigned int> _indices;

		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
		void initMesh();
		void Render(Shader &shader);
		//Mesh();


};
