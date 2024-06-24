#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

	public:	
		const float _speed = 0.5f;
		float _yaw = -90.0f; // horizontal movement
		float _pitch = 0.0f; // vertical movement
		float _fov = 90.0f;
		float lastX = 300;
		float lastY = 400;

		glm::vec3 _pos;
		glm::vec3 _front;
		glm::vec3 _up;

		Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) :
		_pos(pos), _front(front), _up(up) {}

		glm::mat4 LookAtMatrix();
		void MoveCamera(GLFWwindow *window, float deltaTime);
		void LookAround(float xpos, float ypos);
		void AdjustFov(double yoffset);

};
