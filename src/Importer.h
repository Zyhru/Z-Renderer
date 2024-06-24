#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include <fstream>
#include <string>
#include "Mesh.h"
#include "Shader.h"

enum PolygonMode {
	NORMAL,
	QUADTOTRIANGLE
};


enum DataType {
	FLOAT, 
	UNSIGNED_INT,
	STRING,
	UNKNOWN
};

struct Material {
	float Ns;
	glm::vec3 Ka; // ambient color
	glm::vec3 Kd; //
	glm::vec3 Ks;
	glm::vec3 Ke;
	float Ni;
	float d;
	uint8_t illum;
};


// Read the obj file and save it to an object that will contain each mesh and that mesh will contain -> v, vt, vn, f
class Importer {
	public:
		void ReadFile(std::string file, PolygonMode mode);
		void Render(Shader &shader);
		std::vector<Mesh> m_meshes;
		
	private:
		template <typename T> std::vector<T> split(std::string str, std::string delim);
		void createMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
		std::vector<unsigned int> triangulateQuads(std::vector<unsigned int>& indexBuffer);
};

