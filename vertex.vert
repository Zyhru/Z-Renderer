#version 330 core
layout (location = 0) in vec3 pos;
//layout (location = 0) in vec2 texcoords;
//layout (location = 0) in vec3 normals;

//out vec2 TexCoord;
//out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() 
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	//TexCoord = vec2(texcoords);
	//Normal = vec3(normals);
}
