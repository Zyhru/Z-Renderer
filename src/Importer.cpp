#include "Importer.h"
#include <cstdlib>

template <typename T> std::vector<T> Importer::split(std::string str, std::string delim) {
 
	size_t start_pos = 0;
	size_t end_pos   = 0;

	std::vector<T> tokens;
	std::string token;

	DataType t;
	if(std::is_same<T, float>::value) {
		//std::cout << "Using {F32} split" << std::endl;
		t = FLOAT;
	} else if(std::is_same<T, unsigned int>::value) {
		t = UNSIGNED_INT;
		//std::cout << "Using {U32} split" << std::endl;
	} else {
		t = UNKNOWN;
		//std::cout << "Using {UNKNOWN datatype} split" << std::endl;
	}
	
	while((end_pos = str.find(delim, start_pos)) != std::string::npos) {
		token = str.substr(start_pos, end_pos - start_pos);
		start_pos = end_pos + delim.length();
		
		// TODO: Duplicated code -> convert to a function
		T item;
		switch(t) {
			case FLOAT:
				item = std::atof(token.c_str()); 
				break;
			case UNSIGNED_INT:
				item = (unsigned int) std::atoi(token.c_str());
				break;
			case UNKNOWN:
				// error handling I guess
				break;
		}
		tokens.push_back(item);
	}

	// TODO: Duplicated code -> convert to a function
	T item;
	switch(t) {
		case FLOAT:
			item = std::atof(str.substr(start_pos).c_str());
			break;
		case UNSIGNED_INT:
			item = (unsigned int)std::atoi(str.substr(start_pos).c_str());
			break;
		case UNKNOWN:
			break;
	}

	tokens.push_back(item); // Grabs the last parsed string
	return tokens;
}

void Importer::ReadFile(std::string path) {
	std::ifstream file(path);
	  
	if(!file.is_open()) {
		std::cerr << "Could not open file" << std::endl;
	}

	std::string line;
	std::string delim = " ";

	std::vector<float> split_f;
	std::vector<unsigned int> split_ui;
	std::vector<Vertex> v_list;
	std::vector<unsigned int> i_list;

	/* Parse .obj file */
	while(std::getline(file, line)) {

		if(line[0] == 'v') {

			Vertex v;
			split_f = split<float>(line, delim);
			v.x = split_f[1];
			v.y = split_f[2];
			v.z = split_f[3];
			v_list.push_back(v);

		} else if(line[0] == 'f') {

			split_ui = split<unsigned int>(line, delim); 
			for(int i = 1; i < split_ui.size(); i++) {
			  i_list.push_back(split_ui[i]); 
			}
		}
	}
	
	Mesh mesh(v_list, i_list); 
	m_meshes.push_back(mesh);
	std::cout << "End of Importer::ReadFile function" << "\n";
}

void Importer::Render(Shader &shader) {
	for(auto& x : m_meshes) {
		x.Render(shader);
	}
}

