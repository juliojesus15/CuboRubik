#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <iostream>

#include "global.h"

class Camera {
public:
	glm::mat4 projection; 
	glm::mat4 view;
	
	Camera();

	void define_perspective();
	void update_perspective(float zoom);
	
	void define_view();
	void update_view(bool flag);	

private:
	glm::vec3 camera_pos;
	glm::vec3 camera_target;
	glm::vec3 camera_up;

	float zoom;	
	double counter_axis_x;
	double counter_axis_y;
};

Camera::Camera() {
	this->counter_axis_x = 0.1f;
	this->counter_axis_y = 0.1f;
	
	this->zoom = glm::radians(45.0f);
		
	this->camera_pos = glm::vec3(0.0f, 0.0f, 15.0f);
	this->camera_target = glm::vec3(0.0f, 0.0f, 0.0f);
	this->camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::define_perspective() {	
	this->projection = glm::perspective(this->zoom, (float)tools::SCR_WIDTH / (float)tools::SCR_HEIGHT, 0.1f, 100.0f);
}

void Camera::update_perspective(float zoom) {	
	this->zoom = glm::radians(zoom);
	this->projection = glm::perspective(this->zoom, (float)tools::SCR_WIDTH / (float)tools::SCR_HEIGHT, 0.1f, 100.0f);	
}

void Camera::define_view() {		
	this->view = glm::lookAt(this->camera_pos, this->camera_target, this->camera_up);
}

void Camera::update_view(bool flag) {	
	float dir = flag ? (1.0f) : (-1.0f);
	
	float camX = static_cast<float>(sin(counter_axis_x * dir) * 15.0f);
	float camZ = static_cast<float>(cos(counter_axis_x * dir) * 15.0f);

	this->counter_axis_x += + 0.001f;
	
	this->camera_pos = glm::vec3(camX, 0.0f, camZ);
	
	this->view = glm::mat4(1.0f); 
	this->view = glm::lookAt(camera_pos, this->camera_target, this->camera_up);
}

#endif