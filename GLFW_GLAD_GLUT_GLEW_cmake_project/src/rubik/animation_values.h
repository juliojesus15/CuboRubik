#ifndef ANIMATION_VALUES_H
#define ANIMATION_VALUES_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <vector>

namespace animation {
	typedef std::vector<glm::vec3>VecVertex;	

	VecVertex get_corner_position(float scala, bool orientation) {
		float flag = orientation ? 1.0f : -1.0;
		VecVertex  buffer = {
			glm::vec3(-1.0f * scala * flag,  1.0f * scala * flag,  1.0f * scala * flag), // corner F
			glm::vec3( 1.0f * scala * flag,  1.0f * scala * flag,  1.0f * scala * flag), // corner F	
			glm::vec3( 1.0f * scala * flag, -1.0f * scala * flag,  1.0f * scala * flag), // corner F	
			glm::vec3(-1.0f * scala * flag, -1.0f * scala * flag,  1.0f * scala * flag), // corner F		
			glm::vec3( 1.0f * scala * flag,  1.0f * scala * flag, -1.0f * scala * flag), // corner B
			glm::vec3(-1.0f * scala * flag,  1.0f * scala * flag, -1.0f * scala * flag), // corner B		
			glm::vec3(-1.0f * scala * flag, -1.0f * scala * flag, -1.0f * scala * flag), // corner B	
			glm::vec3( 1.0f * scala * flag, -1.0f * scala * flag, -1.0f * scala * flag), // corner B
		};
		return buffer;
    };

	VecVertex get_border_position(float scala, bool orientation) {
		float flag = orientation ? 1.0f : -1.0;
		VecVertex  buffer = {
			glm::vec3( 0.0f * scala * flag,  1.0f * scala * flag,  1.0f * scala * flag),  // Border F		
			glm::vec3( 1.0f * scala * flag,  0.0f * scala * flag,  1.0f * scala * flag),  // Border F	
			glm::vec3( 0.0f * scala * flag, -1.0f * scala * flag,  1.0f * scala * flag),  // Border F	
			glm::vec3(-1.0f * scala * flag,  0.0f * scala * flag,  1.0f * scala * flag),  // Border F		
			glm::vec3( 0.0f * scala * flag,  1.0f * scala * flag, -1.0f * scala * flag),  // Border B 		
			glm::vec3(-1.0f * scala * flag,  0.0f * scala * flag, -1.0f * scala * flag),  // Border B		
			glm::vec3( 0.0f * scala * flag, -1.0f * scala * flag, -1.0f * scala * flag),  // Border B		
			glm::vec3( 1.0f * scala * flag,  0.0f * scala * flag, -1.0f * scala * flag),  // Border B
			glm::vec3(-1.0f * scala * flag,  1.0f * scala * flag,  0.0f * scala * flag),  // Border L
			glm::vec3(-1.0f * scala * flag, -1.0f * scala * flag,  0.0f * scala * flag),  // Border L	
			glm::vec3( 1.0f * scala * flag,  1.0f * scala * flag,  0.0f * scala * flag),  // Border R
			glm::vec3( 1.0f * scala * flag, -1.0f * scala * flag,  0.0f * scala * flag)   // Border R	
		};
		return  buffer;
	};

	VecVertex get_center_position(float scala, bool orientation) {
		float flag = orientation ? 1.0f : -1.0;
		VecVertex  buffer = {
			glm::vec3( 0.0f * scala * flag,  0.0f * scala * flag,  1.0f * scala * flag), // F
			glm::vec3( 0.0f * scala * flag,  0.0f * scala * flag, -1.0f * scala * flag), // B
			glm::vec3( 1.0f * scala * flag,  0.0f * scala * flag,  0.0f * scala * flag), // R
			glm::vec3(-1.0f * scala * flag,  0.0f * scala * flag,  0.0f * scala * flag), // L
			glm::vec3( 0.0f * scala * flag,  1.0f * scala * flag,  0.0f * scala * flag), // U
			glm::vec3( 0.0f * scala * flag, -1.0f * scala * flag,  0.0f * scala * flag), // D
		};
		return buffer;
	};
}

#endif