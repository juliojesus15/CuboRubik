#ifndef RUBIK_H
#define RUBIK_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "value.h"
#include "cube.h"
#include "group.h"
#include "params.h"

typedef std::map<char, Cube* > Cubes;

class RubikCube {
public:
	Cubes cubes;
	group::VecGroup groups;

	RubikCube();		
	void print_cube();
	void render_transformation(GLFWwindow* window, unsigned int VBO[], unsigned int VAO[], char group_id, bool clockwise);

private:
	void transformation(char group_id, bool clockwise);
	void RubikCube::draw_cubes(unsigned int VAO[]);
	std::vector<char> update_group(std::vector<char> to_update, bool clockwise);
	void update_groups(char group_id, bool clockwise);

	void print_groups();

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

std::vector<char> RubikCube::update_group(std::vector<char> to_update, bool clockwise) {	
	int rotation_value = clockwise ? 6 : 2;
	char center = to_update.back();	
	to_update.pop_back();
	std::rotate(to_update.begin(), to_update.begin() + rotation_value, to_update.end());
	to_update.push_back(center);
	return to_update;
}

// update_groups: Actualiza los grupos vecinos de un grupo especifico(group_id)
void RubikCube::update_groups(char group_id, bool clockwise) {
	//group['R'] = { 'U', 'B', 'D', 'F', 'U'};
	std::vector<char> neighborhood = group::neighborhood(group_id);	
	//group['R'] = { 'T', 'L', 'C', 'F', 'I', 'Q', 'Z', 'W', 'N' };
	std::vector<char> current_group = groups[group_id];

	std::vector< std::vector<char> > tmp = {
		{current_group[0], current_group[1], current_group[2]}, //B
		{current_group[2], current_group[3], current_group[4]}, //D
		{current_group[4], current_group[5], current_group[6]}, //F
		{current_group[6], current_group[7], current_group[0]}, //U
	};	
}

// Clokcwise -> True: sentido horario || False: Sentido Antihorario 
// Group_id  -> Grupo que aplicaremos la transformacíon, el caracter indica una key del map definido en group.h 
void RubikCube::transformation(char group_id, bool clockwise) {
	group::MapGroup axis = clockwise ? group::rotation_axis_clockwise() : group::rotation_axis_inverted();
	group::MapGroup position = clockwise ? group::translation_pos_clockwise() : group::translation_pos_inverted();

	std::vector<char> cube_ids = groups[group_id];

	for (int i = 0; i < cube_ids.size(); i++) {		
		char key = cube_ids[i];
		cubes[key]->rotation(axis[group_id], position[group_id]);
	}
}

//Metodos para renderizar con OpenGL
void RubikCube::render_transformation(GLFWwindow* window, unsigned int VBO[], unsigned int VAO[], char group_id, bool clockwise) {
	std::vector<char> cube_ids = groups[group_id];
	std::cout << "============================================================0" << std::endl;
	std::cout << "ANTES DE LA TRANSFORMACION" << std::endl;
	print_groups();
	for (int j = 0; j < cube_ids.size(); j++) {
	//	std::cout << cube_ids[j] << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < 9; i++) {
		transformation(group_id, clockwise);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int k = 0;
		for (auto iter = cubes.begin(); iter != cubes.end(); ++iter) {
			glBindBuffer(GL_ARRAY_BUFFER, VBO[k]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iter->second->vertex.size(), static_cast<void*>(iter->second->vertex.data()), GL_STATIC_DRAW);
			k++;
		}

		draw_cubes(VAO);
		params::sleep();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	update_groups(group_id, clockwise);
	groups[group_id] = update_group(groups[group_id], clockwise);
	cube_ids = groups[group_id];

	std::cout << "Despues DE LA TRANSFORMACION" << std::endl;
	print_groups();
	for (int j = 0; j < cube_ids.size(); j++) {
		//std::cout << cube_ids[j] << " ";
	}
	std::cout << std::endl;
	std::cout << "============================================================0" << std::endl;
}

void RubikCube::draw_cubes(unsigned int VAO[]) {
	for (int j = 0; j < params::CUBES; j++) {
		glBindVertexArray(VAO[j]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void RubikCube::print_groups() {
	for (auto iter = groups.begin(); iter != groups.end(); ++iter) {
		//iter->second.size();
		std::cout << "Group Id: " << iter->first << std::endl;
		std::vector<char> tmp = iter->second;
		for (int i = 0; i < tmp.size(); i++) {
			std::cout << tmp[i] << " ";
		}
		std::cout << std::endl;
	}
}

void RubikCube::print_cube() {
	for (auto iter = groups.begin(); iter != groups.end(); ++iter) {
		//iter->second.size();
		std::cout << "Group Id: " << iter->first << std::endl;
		std::vector<char> tmp = iter->second;
		for (int i = 0; i < tmp.size(); i++) {
			std::cout << tmp[i] << " ";
		}
		std::cout << std::endl;
	}
}

#endif