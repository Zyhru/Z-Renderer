#include "Importer.h"
#include <map>


template <typename T> 
std::vector<T> Importer::split(std::string str, std::string delim) {
	size_t start_pos = 0;
	size_t end_pos   = 0;

	std::vector<T> tokens;
	std::string token;

	DataType t;
	if(std::is_same<T, float>::value) {
		t = FLOAT;
	} else if(std::is_same<T, unsigned int>::value) {
		t = UNSIGNED_INT;
	} else if(std::is_same<T, std::string>::value) {
		t = STRING;
	} else {
		t = UNKNOWN;
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
			case STRING:
				if constexpr (std::is_same<T, std::string>()) {
					item = token;
				}
				break;
			case UNKNOWN:
				// error handling I guess
				break;
		}
		tokens.push_back(item);
	}

	// TODO: Duplicated code -> convert to a function
	T item;
	std::string lastToken = str.substr(start_pos);
	switch(t) {
		case FLOAT:
			item = std::atof(str.substr(start_pos).c_str());
			break;
		case UNSIGNED_INT:
			item = (unsigned int)std::atoi(str.substr(start_pos).c_str());
			break;
		case STRING:
			if constexpr (std::is_same<T, std::string>()) {
				item = lastToken;
			}
			break;
		case UNKNOWN:
			break;
	}

	tokens.push_back(item); 
	return tokens;
}

void Importer::ReadFile(std::string path, PolygonMode mode) {
	std::ifstream file(path);
	if(!file.is_open()) {
		std::cerr << "Could not open file" << std::endl;
		return;
	}

	std::string line;
	std::string delim = " ";

	std::vector<std::vector<std::string>> meshInfo;
	std::vector<std::string> meshData;
	bool parsingMesh = false;
	int i = 0;

	/* Parse .obj file */
	while(std::getline(file, line)) {

		// parse openmtl to apply material and textures
		if(line[0] == 'o') {
			//std::cout << "Mesh: " << i+1 << std::endl;
			//std::cout << line << std::endl;
			parsingMesh = true;
			i++;
		}

		if(parsingMesh) {
			if(line[0] == 'o' && i >= 1) {
				meshInfo.push_back(meshData);
				meshData.clear();
			}
			meshData.push_back(line);
		}

	}

	meshInfo.push_back(meshData);
	meshInfo.erase(meshInfo.begin());

	// Parse mesh
	std::vector<glm::vec3> pos;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> tcoords;
	std::map<int, glm::vec3> map;

	for(int i = 0; i < meshInfo.size(); i++) {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		for(int j = 0; j < meshInfo[i].size(); j++) {
			if(meshInfo[i][j][0] == 'v') {
				char z = meshInfo[i][j][1];
				if (z == ' ') {
					std::vector<float> parsedPositions = split<float>(meshInfo[i][j], delim);
					glm::vec3 vector;
					vector.x = parsedPositions[1];
					vector.y = parsedPositions[2];
					vector.z = parsedPositions[3];
					pos.push_back(vector);

				} else if(z == 't') {
					std::vector<float> parsedTCoords = split<float>(meshInfo[i][j], delim);
					glm::vec2 texCoords;
					texCoords.x = parsedTCoords[1];
					texCoords.y = parsedTCoords[2];
					tcoords.push_back(texCoords);
				} else if(z == 'n') {
					std::vector<float> parsedNormals = split<float>(meshInfo[i][j], delim);
					glm::vec3 normal;
					normal.x = parsedNormals[1];
					normal.y = parsedNormals[2];
					normal.z = parsedNormals[3];
					normals.push_back(normal);
				}
			}

			if(meshInfo[i][j][0] == 'f') {
				
				std::vector<std::string> face = split<std::string>(meshInfo[i][j], " ");

				//std::cout << meshInfo[i][j] << std::endl;
				for(int k = 0; k < face.size(); k++) {
					std::vector<unsigned int> x = split<unsigned int>(face[k], "/");
					if(x.size() == 1) continue;

					//std::cout << "Face size: " << face.size() << std::endl;
					//std::cout << "Face: " << face[k] << std::endl;
					//std::cout << "Face Elements: " << x[0] << std::endl;

					// Generate VBO
					Vertex vertex;
					uint64_t v  = x[0];
					uint64_t vt = x[1]; 
					uint64_t vn = x[2];
					glm::vec3 vVertices =  pos[v - 1];
					glm::vec2 vTexCoords = tcoords[vt - 1];
					glm::vec3 vNormals = normals[vn - 1];

					vertex.vertex = vVertices;

					//vertex.textureCoords = vTexCoords;
					//vertex.vertexNormals = vNormals;
					vertices.push_back(vertex);
					map.insert({v, vVertices});

				}
			}
		}
		

		for(int i = 0; i < vertices.size(); i++) {
			indices.push_back(i);
		}

		#if 0
		std::cout << std::endl;
		int count = 0;
		for(auto& val : vertices) {
			std::cout << "Index: " << count  << " " << val.vertex.x << "," << val.vertex.y << "," << val.vertex.z << std::endl;
			++count;
		}
		#endif

		// Triangluate the quads
		switch(mode) {
			case NORMAL:
				std::cout << "No need for conversion" << std::endl;
				createMesh(vertices, indices);
				break;
			case QUADTOTRIANGLE:
				std::cout << "Converting quads to triangles" << std::endl;
				std::vector<unsigned int> list = triangulateQuads(indices);
				createMesh(vertices, list);
				break;
		}

		std::cout << std::endl;
	}

	#if 0
	for(auto iter = map.begin(); iter != map.end(); iter++) {
		int key = iter->first;
		glm::vec3 val = iter->second;
		std::cout << "v" << key << ": " << val.x << "," << val.y << "," << val.z << std::endl;
	}
	#endif

	std::cout << "End of Importer::ReadFile function" << "\n";
	file.close();
}

std::vector<unsigned int> Importer::triangulateQuads(std::vector<unsigned int>& indexBuffer) {
	std::vector<unsigned int> list;
	for(int i = 0; i < indexBuffer.size(); i+= 4) {

		#if 0
		std::cout << "Processing: " << 
		indexBuffer[i]   <<  "," <<
		indexBuffer[i+1] <<  "," <<
		indexBuffer[i+2] <<  "," <<
		indexBuffer[i+3] << std::endl;
		#endif

		// triangle one
		list.push_back(indexBuffer[i]); // 1 
		list.push_back(indexBuffer[i+1]); // 3
		list.push_back(indexBuffer[i+2]); // 2

		// triangle two
		list.push_back(indexBuffer[i]); // 1
		list.push_back(indexBuffer[i+2]); // 2
		list.push_back(indexBuffer[i+3]); // 0
		
	}


	#if 0
	std::cout << "TRIANGULATE BUFFER: " << std::endl;
	for(auto& item : list) {
		std::cout << item << std::endl;
	}
	#endif

	return list;
}

void Importer::createMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
	Mesh mesh(vertices, indices);
	m_meshes.push_back(mesh);
}

void Importer::Render(Shader &shader) {
	for(auto& x : m_meshes) {
		x.Render(shader);
	}
}
