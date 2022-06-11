#ifndef RUBIK_H
#define RUBIK_H

#include "value.h"
#include "cube.h"
#include "group.h"

typedef std::map<char, Cube* > Cubes;

class RubikCube {
public:
	Cubes cubes;
	group::VecGroup groups;

	RubikCube();	
	void move_group(char group_id, bool clockwise);	
};
 
RubikCube::RubikCube() {	
	std::vector<char> ids = values::cube_ids;
	std::vector<glm::vec3> positions = values::cube_positions;
	std::vector<std::vector<char> > colors = values::cube_colors;
	
	for (int i = 0; i < ids.size(); i++) {
		Cube* tmp_cube = new Cube(ids[i], colors[i]);
		tmp_cube->translation(positions[i]);
		this->cubes[ids[i]] = tmp_cube;
	}
	this->groups = group::default_groups();	
}

// Clokcwise -> True: sentido horario || False: Sentido Antihorario 
// Group_id  -> Grupo que aplicaremos la transformacíon, el caracter indica una key del map definido en group.h 
void RubikCube::move_group(char group_id, bool clockwise) {
	group::MapGroup to_rotation = clockwise ? group::define_rotation_axis_clockwise() : group::define_rotation_axis();
	group::MapGroup to_translation = clockwise ? group::define_translation_pos_clockwise() : group::define_translation_pos();

	std::vector<char> cube_ids = groups[group_id];

	for (int i = 0; i < cube_ids.size(); i++) {
		Cube* tmp = cubes[cube_ids[i]];
		tmp->rotation(to_rotation[group_id], to_translation[group_id]);	
	}
}


#endif