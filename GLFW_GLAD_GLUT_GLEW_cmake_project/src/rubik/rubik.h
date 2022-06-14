#ifndef RUBIK_H
#define RUBIK_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "value.h"
#include "cube.h"
#include "group.h"
#include "params.h"

typedef std::map<int, std::pair<char, char > > Colors;
typedef std::map<char, Cube* > Cubes;
typedef std::vector<char> VecChar;

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

	void print(std::vector< std::vector<char> > mapper, std::vector<char> ids, bool border, bool content);
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
	//print_rubik(true);
}

std::vector<char> RubikCube::update_group(std::vector<char> to_update, bool clockwise) {
	int rotation_value = clockwise ? 6 : 2;
	char center = to_update.back();
	to_update.pop_back();
	std::rotate(to_update.begin(), to_update.begin() + rotation_value, to_update.end());
	to_update.push_back(center);
	return to_update;
}

// Actualiza los grupos vecinos de un grupo especifico(group_id)
void RubikCube::update_groups(char group_id, bool clockwise) {
	std::vector<char> neighborhood = group::neighborhood(group_id);	
	std::vector<char> group = groups[group_id];

	// Creamos una copia de los cubos, donde realizaremos las busquedas, mientras el original es modificado
	Cubes tmp_cubes = cubes;
	
	// Representa a la cara superior respecto a la cara que hicimos la rotacion (Sentido horario)
	std::vector< std::vector<char> > current = {
		{ group[0], group[1], group[2] },
		{ group[2], group[3], group[4] },
		{ group[4], group[5], group[6] },
		{ group[6], group[7], group[0] }
	};

	// Representa a la cara derecha respecto a la cara que hicimos la rotacion (Sentido horario)
	std::vector< std::vector<char> > neighbour = {
		{ group[2], group[3], group[4] },
		{ group[4], group[5], group[6] },
		{ group[6], group[7], group[0] },
		{ group[0], group[1], group[2] }
	};

	for (int i = 0; i < 4; i++) {
		char neighbour_id = neighborhood[i + 1];
		
		group = groups[neighbour_id];
		for (int j = 0; j < 3; j++) {
			char current_cube = current[i][j];
			char neighbour_cube = neighbour[i][j];

			std::vector<char>::iterator itr = std::find(group.begin(), group.end(), neighbour_cube);
			int index = std::distance(group.begin(), itr);
			
			groups[neighbour_id][index] = current_cube;
		}
	}

	groups[group_id] = update_group(groups[group_id], clockwise);

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

//Render con OpenGL
void RubikCube::render_transformation(GLFWwindow* window, unsigned int VBO[], unsigned int VAO[], char group_id, bool clockwise) {
	//print_rubik(true);

	for (int i = 0; i < 9; i++) {
		// Aplicamos las transformaciones
		transformation(group_id, clockwise);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		int k = 0;
		for (auto iter = cubes.begin(); iter != cubes.end(); ++iter) {
			glBindBuffer(GL_ARRAY_BUFFER, VBO[k]);
			glBufferData(
				GL_ARRAY_BUFFER,
				sizeof(float) * iter->second->vertex.size(),
				static_cast<void*>(iter->second->vertex.data()),
				GL_STATIC_DRAW
			);
			k++;
		}
		draw_cubes(VAO);
		params::sleep();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// Actualizamos los grupos
	update_groups(group_id, clockwise);

	//groups[group_id] = update_group(groups[group_id], clockwise);
	//print_rubik(true);
	
}

void RubikCube::draw_cubes(unsigned int VAO[]) {
	for (int j = 0; j < params::CUBES; j++) {
		glBindVertexArray(VAO[j]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

// Dibujar cubo en consola
void RubikCube::print(std::vector< std::vector<char> > mapper, std::vector<char> group_id, bool border, bool content) {
	std::map<char, char*> console_color = color::console_colors;
	for (int i = 0; i < mapper.size(); i++) {
		std::vector<char> row = mapper[i];
		std::string border_left = border ? "            |" : "|";
		std::cout << border_left;
		for (int j = 0; j < row.size(); j++) {
			char cube = row[j];
			char group = group_id[j];
			char color = cubes[cube]->get_color_by_group(group);
			char* console = console_color[color];
			printf(console, content ? cubes[cube]->id : color);
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
	/*
	std::vector<char> left = groups['L'];
	std::vector<char> front = groups['F'];
	std::vector<char> right = groups['R'];
	std::vector<char> back = groups['B'];
	ids = { 'L', 'L', 'L', 'F', 'F', 'F', 'R', 'R', 'R', 'B', 'B', 'B' };
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
	*/
}

#endif