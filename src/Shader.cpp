#include "Shader.h"

void Shader::Load(std::string vertexFile, std::string fragmentFile) {
	std::string vertexShaderSource = ReadFile(vertexFile);
	std::string fragmentShaderSource = ReadFile(fragmentFile);

	//std::cout << fragmentShaderSource << std::endl;

	if(vertexShaderSource == "") std::cout << "Vertex Shader file is empty" << std::endl;
	if(fragmentShaderSource == "") std::cout << "Fragment Shader file is empty" << std::endl;

	const char* v_source = vertexShaderSource.c_str();
	const char* f_source = fragmentShaderSource.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &v_source, nullptr);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &f_source, nullptr);
	glCompileShader(fragmentShader);

	_shaderID = glCreateProgram();
	glAttachShader(_shaderID, vertexShader);
	glAttachShader(_shaderID, fragmentShader);
	glLinkProgram(_shaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Use() {
	glUseProgram(_shaderID);
}

std::string Shader::ReadFile(std::string path) {
	std::ifstream file(path);

	std::string str;
	std::string line;

	while(std::getline(file, line)) { 
		str += line + "\n";
	}

	return str;

}


void Shader::SetFloat(const std::string &name, float value) {
	int location = glGetUniformLocation(_shaderID, name.c_str());
	glUniform1f(location, value);
}


void Shader::SetInt(const std::string &name, int value) {
	int location = glGetUniformLocation(_shaderID, name.c_str());
	glUniform1f(location, value);
}


void Shader::SetBool(const std::string &name, bool value) {
	int location = glGetUniformLocation(_shaderID, name.c_str());
	glUniform1f(location, (int)value);
}


void Shader::SetMat4(const std::string &name, glm::mat4& value) {
	int location = glGetUniformLocation(_shaderID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}


void Shader::CheckForCompileErrors(unsigned int shader, std::string type) {



}





















