#ifndef RUBIK_CUBE_UTILS_H
#define RUBIK_CUBE_UTILS_H


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include <map>

#include "cube.h"

namespace rubik_utils {
    typedef std::map<char, Cube* > Cubes;
    typedef std::map<char, std::vector<char> > Groups;

	std::vector<char> default_cube_ids = {         
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
        'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

	std::vector<std::vector<char> > default_cube_colors = {		
		{ 'O', 'B', 'W' },  { 'B', 'W' },   { 'B', 'R', 'W' },
        { 'B', 'O' },       { 'B' },        { 'B', 'R' },
        { 'B', 'Y', 'O' },  { 'B', 'Y' },   { 'B', 'Y', 'R' },

        { 'W', 'O'},        { 'W'},         { 'R', 'W' },
        { 'O'},                             { 'R'},
        { 'Y', 'O'},        { 'Y'},         { 'R', 'Y' },
        
        { 'O', 'G', 'W' },  { 'G', 'W' },   { 'G', 'R', 'W' },
        { 'G', 'O' },       { 'G' },        { 'G', 'R' },
        { 'O', 'G', 'Y' },  { 'G', 'Y' },   { 'G', 'Y', 'R' },
	};

	std::vector<glm::vec3> default_cube_positions = {		
        glm::vec3(-0.40f,  0.50f, -0.40f), glm::vec3( 0.65f,  0.50f, -0.40f), glm::vec3( 1.70f,  0.50f, -0.40f),
        glm::vec3(-0.40f, -0.55f, -0.40f), glm::vec3( 0.65f, -0.55f, -0.40f), glm::vec3( 1.70f, -0.55f, -0.40f),
        glm::vec3(-0.40f, -1.60f, -0.40f), glm::vec3( 0.65f, -1.60f, -0.40f), glm::vec3( 1.70f, -1.60f, -0.40f),        
        
        glm::vec3(-0.40f,  0.50f,  0.65f), glm::vec3( 0.65f,  0.50f,  0.65f), glm::vec3( 1.70f,  0.50f,  0.65f),
        glm::vec3(-0.40f, -0.55f,  0.65f),                                    glm::vec3( 1.70f, -0.55f,  0.65f),
        glm::vec3(-0.4f,  -1.60f,  0.65f), glm::vec3( 0.65f, -1.60f,  0.65f), glm::vec3( 1.70f, -1.60f,  0.65f),

        glm::vec3(-0.40f,  0.50f,  1.70f), glm::vec3( 0.65f,  0.50f,  1.70f), glm::vec3( 1.70f,  0.50f,  1.70f),
        glm::vec3(-0.40f, -0.55f,  1.70f), glm::vec3( 0.65f, -0.55f,  1.70f), glm::vec3( 1.70f, -0.55f,  1.70f),
        glm::vec3(-0.40f, -1.60f,  1.70f), glm::vec3( 0.65f, -1.60f,  1.70f), glm::vec3( 1.70f, -1.60f,  1.70f)
	};    

    Groups default_groups() {
        Groups group;
        group['B'] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
        group['F'] = {'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        group['U'] = {'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        group['D'] = {'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        group['L'] = {'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        group['R'] = {'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        return group;
    }
}

#endif