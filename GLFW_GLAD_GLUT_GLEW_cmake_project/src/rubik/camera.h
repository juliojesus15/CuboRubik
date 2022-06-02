#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

using glm::vec3;

class Camera {
public:
	Camera();
	vec3 cameraPos;
	vec3 cameraFront;
	vec3 cameraUp;

	float cameraSpeed;

	// timing
	float deltaTime;
	float lastFrame;

private:

};

Camera::Camera() {
	this->cameraPos = vec3(0.0f, 0.0f, 3.0f);
	this->cameraFront = vec3(0.0f, 0.0f, -1.0f);
	this->cameraUp = vec3(0.0f, 1.0f, 0.0f);
}

#endif