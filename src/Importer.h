#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Mesh.h"

// Read the obj file and save it to an object that will contain each mesh and that mesh will contain -> v, vt, vn, f
//
//

class Importer {
	public:
		struct Obj ReadFile(std::string file);  // Return parsed obj -> mesh -> v, vt, vn, f
	private:
		//std::vector<float> split(std::string str, std::string delim);
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
	//
	//

} Obj;
