#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <iostream>

#include "params.h"

class Camera {
public:
	glm::mat4 projection; 
	glm::mat4 view;
	
	float fov;
	float yaw, pitch;
	float mouse_x, mouse_y;

	Camera();

	void update_perspective();
	void update_view();	

	void update_fov(float yoffset);
	void update_mouse_position(float x_pos, float y_pos);
	void update_target();
		
	void move_up(float speed);
	void move_down(float speed);
	void move_left(float speed);
	void move_right(float speed);

private:
	glm::vec3 camera_pos;
	glm::vec3 camera_target;
	glm::vec3 camera_up;

};

Camera::Camera() {	
	this->fov = 45.0f;
	this->yaw = -90.0f;
	this->pitch = 0.0f;
	this->mouse_x = (float)params::SCR_WIDTH / 2.0;
	this->mouse_y = (float)params::SCR_HEIGHT / 2.0;
	
	this->camera_up = glm::vec3(0.0f, 1.0f, 0.0f);	
	this->camera_pos = glm::vec3(0.0f, 0.0f, 10.0f);
	this->camera_target = glm::vec3(0.0f, 0.0f, -1.0f);
}

void Camera::update_perspective() {	
	this->projection = glm::perspective(this->fov, (float)params::SCR_WIDTH / (float)params::SCR_HEIGHT, 0.1f, 100.0f);
}

void Camera::update_view() {		
	this->view = glm::lookAt(camera_pos, camera_pos + camera_target, camera_up);
}

void Camera::update_fov(float yoffset) {
	fov -= yoffset;
	if (fov < 1.0f) fov = 1.0f;
	if (fov > 45.0f) fov = 45.0f;
}

void Camera::update_mouse_position(float x_pos, float y_pos) {
	float sensitivity = 0.1f; 
	float xoffset = (x_pos - mouse_x) * sensitivity;
	float yoffset = (mouse_y - y_pos) * sensitivity;
	
	mouse_x = x_pos;
	mouse_y = y_pos;
		
	yaw += xoffset;
	pitch += yoffset;
	
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;	
}

void Camera::update_target() {
	glm::vec3 new_target;
	new_target.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	new_target.y = sin(glm::radians(this->pitch));
	new_target.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	
	this->camera_target = glm::normalize(new_target);
}

void Camera::move_up(float speed) {	
	this->camera_pos += speed * camera_target;
}

void Camera::move_down(float speed) {	
	this->camera_pos -= speed * camera_target;
}

void Camera::move_left(float speed) {	
	this->camera_pos -= glm::normalize(glm::cross(camera_target, camera_up)) * speed;
}

void Camera::move_right(float speed) {	
	this->camera_pos += glm::normalize(glm::cross(camera_target, camera_up)) * speed;
}

#endif