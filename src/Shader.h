#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

class Shader { 
	private: 
		void CheckForCompileErrors(unsigned int shader, std::string type);
		std::string ReadFile(std::string path);

	public:
		unsigned _shaderID = -1;
		void Use();
		void Load(std::string vertexFile, std::string fragmentFile);
		void SetFloat(const std::string &name, float value);
		void SetInt(const std::string &name, int value);
		void SetBool(const std::string &name, bool value);
		void SetMat4(const std::string &name, glm::mat4& value);
	
	
};
