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
	
	void render_transformation(GLFWwindow* window, unsigned int VBO[], unsigned int VAO[], char group_id, bool clockwise);

private:
	void transformation(char group_id, bool clockwise);
	void draw_cubes(unsigned int VAO[]);
	std::vector<char> update_group(std::vector<char> to_update, bool clockwise);
	void update_groups(char group_id, bool clockwise);
	
	void print(std::vector< std::vector<char> > mapper, std::vector<char> ids, bool flag, bool content);
	void print_rubik(bool content);
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
		cubes[key]->transformation(axis[group_id], position[group_id]);
	}
}

//Metodos para renderizar con OpenGL
void RubikCube::render_transformation(GLFWwindow* window, unsigned int VBO[], unsigned int VAO[], char group_id, bool clockwise) {
	std::vector<char> cube_ids = groups[group_id];
		
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

	print_rubik(true);
	//print_rubik(false);
}

// Render de los cubos en la vetana(windows) del openGL
void RubikCube::draw_cubes(unsigned int VAO[]) {
	for (int j = 0; j < params::CUBES; j++) {
		glBindVertexArray(VAO[j]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

// Dibujar cubo en consola
void RubikCube::print(std::vector< std::vector<char> > mapper, std::vector<char> group_id, bool flag, bool content) {
	std::map<char, char*> console_color = color::console_colors;
	for (int i = 0; i < mapper.size(); i++) {
		std::vector<char> row = mapper[i];
		std::string border_left = flag ? "            |" : "|";
		std::cout << border_left;
		for (int j = 0; j < row.size(); j++) {
			char cube = row[j];
			char group = group_id[j];
			char color = cubes[cube]->get_color(group);			
			char* console = console_color[color];
			printf(console, content ? cubes[cube]->id: color);
		}
		std::cout << std::endl;
	}
}

// content: { true: visualizar el id del cubo, false, visualizar solo el color }
void RubikCube::print_rubik(bool content) {
	std::vector<char> mapper = groups['U'];	
	std::vector<char> ids = { 'U', 'U', 'U' };
	std::vector< std::vector<char> > top = {
		{mapper[0], mapper[1], mapper[2]},
		{mapper[7], mapper[8], mapper[3]},
		{mapper[6], mapper[5], mapper[4]}
	};
	print(top, ids, true, content);
	
	std::vector<char> left = groups['L'];
	std::vector<char> front = groups['F'];
	std::vector<char> right = groups['R'];
	std::vector<char> back = groups['B'];	
	ids = { 'L', 'L', 'L', 'F', 'F', 'F', 'R', 'R', 'R', 'B', 'B', 'B'};
	std::vector< std::vector<char> > mid = {
		{left[0], left[1], left[2], front[0], front[1], front[2], right[0], right[1], right[2], back[0], back[1], back[2]},
		{left[7], left[8], left[3], front[7], front[8], front[3], right[7], right[8], right[3], back[7], back[8], back[3]},
		{left[6], left[5], left[4], front[6], front[5], front[4], right[6], right[5], right[4], back[6], back[5], back[4]}
	};
	print(mid, ids, false, content);
	
	mapper = groups['D'];
	ids = { 'D', 'D', 'D' };
	std::vector< std::vector<char> > down = {
		{mapper[0], mapper[1], mapper[2]},
		{mapper[7], mapper[8], mapper[3]},
		{mapper[6], mapper[5], mapper[4]}
	};
	print(down, ids, true, content);
	std::cout << "===================================================" << std::endl;
}

#endif