#ifndef RUBIK_H
#define RUBIK_H

#include "rubik_utils.h"
#include "group.h"

class RubikCube {
public:
	int num_cubes;
	rubik_utils::Cubes cubes;
	group::VecGroup groups;

	RubikCube();
	
	void move_group(char group_id);
	
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

	this->groups = group::default_groups();
	this->num_cubes = ids.size();
}


void RubikCube::move_group(char group_id) {
	group::MapGroup to_rotation = group::define_rotation_axis();
	group::MapGroup to_translation = group::define_translation_pos();

	std::vector<char> cube_ids = groups[group_id];

	for (int i = 0; i < cube_ids.size(); i++) {
		Cube* tmp = cubes[cube_ids[i]];
		tmp->rotation(to_rotation[group_id], to_translation[group_id]);	
	}
}


#endif