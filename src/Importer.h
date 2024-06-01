#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Mesh.h"
#include "Shader.h"

// Read the obj file and save it to an object that will contain each mesh and that mesh will contain -> v, vt, vn, f

class Importer {
	public:
		void ReadFile(std::string file);
		void Render(Shader &shader);
		std::vector<Mesh> m_meshes;
		
	private:
		template <typename T> std::vector<T> split(std::string str, std::string delim);
};


enum DataType {
	FLOAT, 
	UNSIGNED_INT,
	UNKNOWN
};


// turn into class?
typedef struct Obj {
	std::vector<Mesh> meshes;
	
	//functions?

} Obj;
