#version 330 core

out vec4 FragColor;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
 	
	//FragColor = vec4(lightColor * objectColor, 1.0f);
	FragColor = vec4(0.58f, 0.74f, 0.29f, 1.0f);
}
