#ifndef RUBIK_H
#define RUBIK_H

#include "rubik_utils.h"

class RubikCube {
public:
	int num_cubes;
	rubik_utils::Cubes cubes;
	rubik_utils::Groups groups;
	RubikCube();

	void move_left_group(float a);
	void move_right_group(float a);

	void move_group(char group_id);
	
	void view_cubes();
};
 
RubikCube::RubikCube() {	

	std::vector<char> ids = rubik_utils::default_cube_ids;
	std::vector<glm::vec3> positions = rubik_utils::default_cube_positions;
	std::vector<std::vector<char> > colors = rubik_utils::default_cube_colors;
	
	for (int i = 0; i < ids.size(); i++) {
		//std::cout << i << " Debugger 3000" << std::endl;
		Cube* tmp_cube = new Cube(ids[i], colors[i]);
		tmp_cube->translation(positions[i]);
		this->cubes[ids[i]] = tmp_cube;
	}

	this->groups = rubik_utils::default_groups();
	this->num_cubes = ids.size();
}


void RubikCube::move_left_group(float a) {
	std::vector<char> cube_ids = groups['L'];

	for (int i = 0; i < cube_ids.size(); i++) {
		//std::cout << cube_ids[i] << std::endl;
		Cube *tmp = cubes[cube_ids[i]];
		tmp->rotation(a);
	}
}

void RubikCube::move_right_group(float a) {
	std::vector<char> cube_ids = groups['R'];

	for (int i = 0; i < cube_ids.size(); i++) {
		//std::cout << cube_ids[i] << std::endl;
		Cube* tmp = cubes[cube_ids[i]];
		tmp->rotation(a);
	}
}

void RubikCube::move_group(char group_id) {
	std::vector<char> cube_ids = groups[group_id];
	for (int i = 0; i < cube_ids.size(); i++) {		
		Cube* tmp = cubes[cube_ids[i]];
		tmp->rotation(1.0f);
	}
}

void RubikCube::view_cubes() {
	for (auto iter = cubes.begin(); iter != cubes.end(); ++iter) {
		iter->second->print();
	}
}

#endif