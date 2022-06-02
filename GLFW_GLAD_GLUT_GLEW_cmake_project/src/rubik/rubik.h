#ifndef RUBIK_H
#define RUBIK_H

#include "rubik_utils.h"

class RubikCube {
public:
	int num_cubes;
	rubik_utils::Cubes cubes;
	rubik_utils::Groups groups;
	RubikCube();
};

RubikCube::RubikCube() {	
	std::vector<char> ids = rubik_utils::default_cube_ids;
	std::vector<glm::vec3> positions = rubik_utils::default_cube_positions;
	std::vector<std::vector<char> > colors = rubik_utils::default_cube_colors;
	
	for (int i = 0; i < ids.size(); i++) {
		Cube* tmp_cube = new Cube(ids[i], colors[i]);
		tmp_cube->translation(positions[i]);
		this->cubes[ids[i]] = tmp_cube;
	}

	this->groups = rubik_utils::default_groups();
	this->num_cubes = positions.size();
}

#endif