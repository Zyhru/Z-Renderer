#include "Camera.h"

void Camera::MoveCamera(GLFWwindow *window, float deltaTime) {
  
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  float velocity = _speed * deltaTime;
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    _pos += _front * velocity;
  } else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    _pos -= _front * velocity;
  } else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    _pos -= glm::normalize(glm::cross(_front, _up)) * velocity;
  } else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    _pos += glm::normalize(glm::cross(_front, _up)) * velocity;
  }

} 


void Camera::AdjustFov(double yoffset) {
	_fov -= (float) yoffset;
	if(_fov < 1.0f) _fov = 1.0f;
	if(_fov > 90.0f) _fov = 90.0f;
}

void Camera::LookAround(float xpos, float ypos) {

  // Calculate the mouse offset since the last frame
  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;
  
  // sensitivity
  float sens = 0.1f;
  xoffset *= sens;
  yoffset *= sens;
  
   // Adjusting Yaw and Pitch values based on mouse input
  _yaw   += xoffset;
  _pitch += yoffset;

  if(_pitch > 89.0f)  _pitch = 89.0f;
  if(_pitch < -89.0f) _pitch = -89.0f;

  // Calculating/Updating direction vector
  glm::vec3 direction;
  direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
  direction.y = sin(glm::radians(_pitch));
  direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
  _front = glm::normalize(direction);

}



glm::mat4 Camera::LookAtMatrix() {
	  return glm::lookAt(_pos, _pos + _front, _up);
};



